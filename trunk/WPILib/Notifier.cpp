/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Notifier.h"
#include "Synchronized.h"
#include "Utility.h"
#include "WPIStatus.h"
//#include "semLib.h"

static Notifier *timerQueueHead = NULL;
static SEM_ID m_semaphore = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
static tAlarm *talarm = NULL;
static tInterruptManager *manager = NULL;

/**
 * Create a Notifier for timer event notification.
 * @param handler The handler is called at the notification time which is set
 * using StartSingle or StartPeriodic.
 */
Notifier::Notifier(TimerEventHandler handler, void *param)
{
	tRioStatusCode status = 0;
	wpi_assert(handler != NULL);
	m_handler = handler;
	m_param = param;
	m_periodic = false;
	m_expirationTime = 0;
	m_period = 0;
	m_nextEvent = NULL;
	m_queued = false;
	CRITICAL_REGION(m_semaphore)
	{
		// do the first time intialization of static variables
		if (talarm == NULL)
		{
			manager = new tInterruptManager(1 << kTimerInterruptNumber, false, &status);
			manager->registerHandler(ProcessQueue, NULL, &status);
			manager->enable(&status);
			talarm = new tAlarm(&status);
		}
	}
	END_REGION;
	wpi_assertCleanStatus(status);
}

/**
 * Free the resources for a timer event.
 * All resources will be freed and the timer event will be removed from the
 * queue if necessary.
 */
Notifier::~Notifier(void)
{
	tRioStatusCode status = 0;
	talarm->writeEnable(false, &status);
	delete talarm;
	manager->disable(&status);
	delete manager;
	wpi_assertCleanStatus(status);
}

/**
 * Update the alarm hardware to reflect the current first element in the queue.
 * Compute the time the next alarm should occur based on the current time and the
 * period for the first element in the timer queue.
 * WARNING: this method does not do synchronization! It must be called from somewhere
 * that is taking care of synchronizing access to the queue.
 */
void Notifier::UpdateAlarm(void)
{
	tRioStatusCode status = 0;
	if (timerQueueHead == NULL)
	{
		// turn off alarm if the queue is empty
		talarm->writeEnable(false, &status);
	}
	else
	{
		// write the first item in the queue into the trigger time
		timerQueueHead->m_expirationTime = GetFPGATime() + timerQueueHead->m_period;
		talarm->writeTriggerTime(timerQueueHead->m_expirationTime, &status);
		talarm->writeEnable(true, &status);
	}
	wpi_assertCleanStatus(status);
}

/**
 * ProcessQueue is called whenever there is a timer interrupt.
 * We need to wake up and process the current top item in the timer queue as long
 * as its scheduled time is after the current time. Then the item is removed or 
 * rescheduled (repetitive events) in the queue.
 */
void Notifier::ProcessQueue(tNIRIO_u32 mask, void *params)
{
	Notifier *current;
	while (1)				// keep processing past events until no more
	{
		CRITICAL_REGION(m_semaphore)
		{
			UINT32 currentTime = GetFPGATime();
			current = timerQueueHead;
			if (current == NULL || current->m_expirationTime > currentTime)
			{
				break;		// no more timer events to process
			}
			// need to process this entry
			timerQueueHead = current->m_nextEvent;
			if (current->m_periodic)
			{
				// if periodic, requeue the event
				// compute when to put into queue
				current->InsertInQueue(false);
			}
		}
		END_REGION;

		current->m_handler(current->m_param);	// call the event handler
	}
	// reschedule the first item in the queue
	CRITICAL_REGION(m_semaphore)
	{
		UpdateAlarm();
	}
	END_REGION;
}

/**
 * Insert this Notifier into the timer queue in right place.
 * WARNING: this method does not do synchronization! It must be called from somewhere
 * that is taking care of synchronizing access to the queue.
 * @param updateAlarm If true, the UpdateAlarm method is called which will enable the
 * alarm if necessary. Only updated when called from the interrupt routine. This ensures
 * that the public methods only update the queue after finishing inserting.
 */
void Notifier::InsertInQueue(bool updateAlarm)
{
	tRioStatusCode status = 0;
	m_expirationTime = GetFPGATime() + m_period;
	if (timerQueueHead == NULL || timerQueueHead->m_expirationTime >= this->m_expirationTime)
	{
		// the queue is empty or greater than the new entry
		// the new entry becomes the first element
		this->m_nextEvent = timerQueueHead;
		timerQueueHead = this;
		if (updateAlarm)
			UpdateAlarm();						// since the first element changed, update alarm
		wpi_assertCleanStatus(status);
	}
	else
	{
		for (Notifier *n = timerQueueHead; n != NULL; n = n->m_nextEvent)
		{
			if (n->m_nextEvent == NULL || n->m_expirationTime > this->m_expirationTime)
			{
				// if the new element goes after the *n element
				this->m_nextEvent = n->m_nextEvent;
				n->m_nextEvent = this;
				break;
			}
		}
	}
	m_queued = true;
}

/**
 * Delete this Notifier from the timer queue.
 * WARNING: this method does not do synchronization! It must be called from somewhere
 * that is taking care of synchronizing access to the queue.
 * Remove this Notifier from the timer queue and adjust the next interrupt time to reflect
 * the current top of the queue.
 */
void Notifier::DeleteFromQueue(void)
{
	if (m_queued)
	{
		semTake(m_semaphore, WAIT_FOREVER);
		m_queued = false;
		wpi_assert(timerQueueHead != NULL);
		if (timerQueueHead == this)
		{
			// remove the first item in the list - update the alarm
			timerQueueHead = this->m_nextEvent;
			UpdateAlarm();
		}
		else
		{
			for (Notifier *n = timerQueueHead; n != NULL; n = n->m_nextEvent)
			{
				if (n->m_nextEvent == this)
				{
					// this element is the next element from *n from the queue
					n->m_nextEvent = this->m_nextEvent;	// point around this one
				}
			}
		}
	}
}

/**
 * Register for single event notification.
 * A timer event is queued for a single event after the time has run out. The
 * event handler will be called at that time.
 */
void Notifier::StartSingle(UINT32 periodInUs)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_periodic = false;
		m_period = periodInUs;
		DeleteFromQueue();
		InsertInQueue(true);
	}
	END_REGION;
}

/**
 * Register for periodic event notification.
 * A timer event is queued for periodic event notification. Each time the intterupt
 * occurs, the event will be immedeatly requeued for the same time interval.
 */
void Notifier::StartPeriodic(UINT32 periodInUs)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_periodic = true;
		m_period = periodInUs;
		DeleteFromQueue();
		InsertInQueue(true);
	}
	END_REGION;
}

/**
 * Stop timer events from occuring.
 * Stop any repeating timer events from occuring. This will also remove any single
 * notification events from the queue.
 */
void Notifier::Stop(void)
{
	CRITICAL_REGION(m_semaphore)
	{
		DeleteFromQueue();
	}
	END_REGION;
}
