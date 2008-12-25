/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "ChipObject.h"
#include "SensorBase.h"

/**
 * Watchdog timer class.
 * The watchdog timer is designed to keep the robots safe. The idea is that the robot program must
 * constantly "feed" the watchdog otherwise it will shut down all the motor outputs. That way if a
 * program breaks, rather than having the robot continue to operate at the last known speed, the
 * motors will be shut down.
 * 
 * This is serious business.  Don't just disable the watchdog.  You can't afford it!
 * 
 * http://thedailywtf.com/Articles/_0x2f__0x2f_TODO_0x3a__Uncomment_Later.aspx
 */
class Watchdog : public SensorBase
{
public:
	static const UINT32 kDefaultWatchdogExpiration_ms = 500;

	Watchdog(void);
	~Watchdog(void);
	bool Feed(void);
	void Kill(void);
	UINT32 GetTimer(void);
	UINT32 GetExpiration(void);
	void SetExpiration(UINT32 expiration_ms);
	bool GetEnabled(void);
	void SetEnabled(bool enabled);
	bool IsAlive(void);
	bool IsSystemActive(void);

private:
	tWatchdog *m_fpgaWatchDog;
};

#endif
