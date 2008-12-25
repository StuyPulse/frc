/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef VICTOR_H
#define VICTOR_H

#include "PWM.h"
#include "SpeedController.h"

/**
 * IFI Victor Speed Controller
 */
class Victor : public PWM, public SpeedController
{
public:
	Victor(UINT32 channel);
	Victor(UINT32 slot, UINT32 channel);
	virtual ~Victor();
	void Set(float value);
	float Get(void);

private:
	void InitVictor(void);
};

#endif

