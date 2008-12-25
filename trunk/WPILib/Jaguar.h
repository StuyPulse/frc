/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef JAGUAR_H
#define JAGUAR_H

#include "PWM.h"
#include "SpeedController.h"

/**
 * Luminary Micro Jaguar Speed Control
 */
class Jaguar : public PWM, public SpeedController
{
public:
	Jaguar(UINT32 channel);
	Jaguar(UINT32 slot, UINT32 channel);
	virtual ~Jaguar();
	float Get(void);
	void Set(float value);

private:
	void InitJaguar(void);
};
#endif

