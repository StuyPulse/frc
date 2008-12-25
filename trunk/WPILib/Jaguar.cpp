/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/


#include "Jaguar.h"
#include "DigitalModule.h"

/**
 * Common initialization code called by all constructors.
 */
void Jaguar::InitJaguar(void)
{
	/*
	 * Input profile defined by Luminary Micro.
	 * 
	 * Full reverse ranges from 0.671325ms to 0.6972211ms
	 * Proportional reverse ranges from 0.6972211ms to 1.4482078ms
	 * Neutral ranges from 1.4482078ms to 1.5517922ms
	 * Proportional forward ranges from 1.5517922ms to 2.3027789ms
	 * Full forward ranges from 2.3027789ms to 2.328675ms
	 */
	SetBounds(251, 135, 128, 120, 4);
	SetPeriodMultiplier(kPeriodMultiplier_1X);
	SetRaw(m_centerPwm);
}

/**
 * Constructor that assumes the default digital module.
 * 
 * @param channel The PWM channel on the digital module that the Jaguar is attached to.
 */
Jaguar::Jaguar(UINT32 channel) : PWM(channel)
{
	InitJaguar();
}

/**
 * Constructor that specifies the digital module.
 * 
 * @param slot The slot in the chassis that the digital module is plugged into.
 * @param channel The PWM channel on the digital module that the Jaguar is attached to.
 */
Jaguar::Jaguar(UINT32 slot, UINT32 channel) : PWM(slot, channel)
{
	InitJaguar();
}

Jaguar::~Jaguar(void)
{
}

/**
 * Set the PWM value.  
 * 
 * The PWM value is set using a range of -1.0 to 1.0, appropriately
 * scaling the value for the FPGA.
 * 
 * @param speed The speed value between -1.0 and 1.0 to set.
 */
void Jaguar::Set(float speed)
{
	SetSpeed(speed);
}

/**
 * Get the recently set value of the PWM.
 * 
 * @return The most recently set value for the PWM between -1.0 and 1.0.
 */
float Jaguar::Get(void)
{
	return GetSpeed();
}

