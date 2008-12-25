/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef NOTIFIER_H
#define NOTIFIER_H

#include "ChipObject.h"

typedef void (*TimerEventHandler)(void *param);

class Notifier
{
public:
	Notifier(TimerEventHandler handler, void *param);
	virtual ~Notifier(void);
	void StartSingle(UINT32 periodInUs);
	void StartPeriodic(UINT32 periodInUs);
	void Stop(void);
private:
	static const UINT32 kTimerInterruptNumber = 28;
	static void ProcessQueue(tNIRIO_u32 mask, void *params); // process the timer queue on a timer event
	static void UpdateAlarm(void);			// update the FPGA alarm since the queue has changed
	void InsertInQueue(bool updateAlarm);	// insert this Notifier in the timer queue
	void DeleteFromQueue(void);				// delete this Notifier from the timer queue
	TimerEventHandler m_handler;			// address of the handler
	void *m_param;							// a parameter to pass to the handler
	UINT32 m_period;						// the relative time (either periodic or single)
	UINT32 m_expirationTime;				// absolute expiration time for the current event
	Notifier *m_nextEvent;					// next Nofifier event
	bool m_periodic;						// true if this is a periodic event
	static Notifier *m_head;				// head of list of current Notifiers
	bool m_queued;							// indicates if this entry is queued
};

#endif
