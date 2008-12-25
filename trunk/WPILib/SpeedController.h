/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef SPEED_CONTROLLER_H
#define SPEED_CONTROLLER_H

/**
 * Pure virtual base class for speed controlling devices.
 */
class SpeedController
{
public:
	virtual ~SpeedController() {}
	/**
	 * Common interface for setting the speed of a speed controller.
	 * 
	 * @param speed The speed to set.  Value should be between -1.0 and 1.0.
	 */
	virtual void Set(float speed) = 0;
	/**
	 * Common interface for getting the current set speed of a speed controller.
	 * 
	 * @return The current set speed.  Value is between -1.0 and 1.0.
	 */
	virtual float Get(void) = 0;
};

#endif

