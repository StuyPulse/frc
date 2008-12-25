/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Timer.h"

#include "Synchronized.h"
#include "Utility.h"
#include "syslib.h"

/**
 * Pause the program for a specified time.
 * 
 * Pause the execution of the program for a specified period of time given in milliseconds.
 * Motors will continue to run at their last assigned values, and sensors will continue to
 * update. Only the task containing the wait will pause until the wait time is expired.
 * 
 * @param milliseconds Length of time to pause
 */
void Wait(UINT32 milliseconds)
{
	taskDelay(sysClkRateGet() / 1000 * milliseconds);
}


/*
 * Get the length of time that has passed since the robot was enabled.
 * 
 * @returns The length of time since the robot was enabled in milliseconds.
 */
UINT32 GetEnabledTime(void)
{
	wpi_assert(false);
	return 0;
}

/*
 * Return the system clock time in microseconds.
 * 
 * Return the time from the FPGA hardware clock in microseconds since the FPGA
 * started.
 * @returns robot running time in microseconds.
 */
UINT32 GetUsClock(void)
{
	return GetFPGATime();
}

/**
 * Return the system clock time in milliseconds.
 * 
 * Return the time from the FPGA hardware clock in milliseconds since the FPGA
 * started.
 * @returns robot running time in milliseconds.
 */
UINT32 GetMsClock(void)
{
	return GetUsClock() / 1000;
}

/**
 * Create a new timer object.
 * 
 * Create a new timer object and reset the time to zero. The timer is initially not running and
 * must be started.
 */
Timer::Timer(void)
	: m_startTime (0)
	, m_accumulatedTime (0)
	, m_running (false)
	, m_semaphore (0)
{
	//Creates a semaphore to control access to critical regions.
	//Initially 'open'
	m_semaphore = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
	Reset();
}

Timer::~Timer()
{
	semFlush(m_semaphore);
}

/**
 * Get the current time from the timer. If the clock is running it is derived from
 * the current system clock the start time stored in the timer class. If the clock
 * is not running, then return the time when it was last stopped.
 * //unsigned Current time value for this timer in milliseconds
 * 
 * @return unsigned Current time value for this timer in microseconds (uSeconds)
 */
UINT32 Timer::Get(void)
{
	INT32 result;
	UINT32 currentTime = GetUsClock();

	CRITICAL_REGION(m_semaphore)
	{
		if(m_running)
		{
			result = (currentTime - m_startTime) + m_accumulatedTime;
		}
		else
		{
			result = m_accumulatedTime;
		}
	}
	END_REGION;

	return result;
}

/**
 * Reset the timer by setting the time to 0.
 * 
 * Make the timer startTime the current time so new requests will be relative now
 */
void Timer::Reset(void)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_accumulatedTime = 0;
		m_startTime = GetUsClock();
	}
	END_REGION;
}

/**
 * Start the timer running.
 * Just set the running flag to true indicating that all time requests should be
 * relative to the system clock.
 */
void Timer::Start(void)
{
	CRITICAL_REGION(m_semaphore)
	{
		m_startTime = GetUsClock();
		m_running = true;
	}
	END_REGION;
}

/**
 * Stop the timer.
 * This computes the time as of now and clears the running flag, causing all
 * subsequent time requests to be read from the accumulated time rather than
 * looking at the system clock.
 */
void Timer::Stop(void)
{
	UINT32 temp = Get();
	
	CRITICAL_REGION(m_semaphore)
	{
		m_accumulatedTime += temp;	
		m_running = false;
	}
	END_REGION;
}
