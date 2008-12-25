/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef CPPCOUNTER_BASE_H_
#define CPPCOUNTER_BASE_H_

/**
 * Class for counting the number of ticks on a digital input channel.
 * Encoders, Gear tooth sensors, and counters should all subclass this so it can be used to
 * build more advanced classes for control and driving.
 */
class CounterBase
{
public:
	virtual void Start(void) = 0;
	virtual INT32 Get(void) = 0;
	virtual void Reset(void) = 0;
	virtual void Stop(void) = 0;
	virtual UINT32 GetPeriod(void) = 0;
	virtual void SetMaxPeriod(UINT32 maxPeriod) = 0;
	virtual bool GetStopped(void) = 0;
	virtual bool GetDirection(void) = 0;
};

#endif
