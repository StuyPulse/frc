/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef TIMER_H_
#define TIMER_H_

#include "semLib.h"

typedef void (*TimerInterruptHandler)(void *param);

void Wait(UINT32 milliseconds);
UINT32 GetGameTime(void);
UINT32 GetUsClock(void);
UINT32 GetMsClock(void);


/**
 * Timer objects measure accumulated time in milliseconds.
 * The timer object functions like a stopwatch. It can be started, stopped, and cleared. When the
 * timer is running its value counts up in milliseconds. When stopped, the timer holds the current
 * value. The implemenation simply records the time when started and subtracts the current time
 * whenever the value is requested.
 */
class Timer
{
public:
	Timer(void);
	virtual ~Timer();
	UINT32 Get(void);
	void Reset(void);
	void Start(void);
	void Stop(void);

private:
	UINT32 m_startTime;
	UINT32 m_accumulatedTime;
	bool m_running;
	SEM_ID m_semaphore;
};

#endif
