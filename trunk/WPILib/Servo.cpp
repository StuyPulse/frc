/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Servo.h"

/**
 * Common initialization code called by all constructors.
 * 
 * InitServo() assigns defaults for the period multiplier for the servo PWM control signal, as
 * well as the minimum and maximum PWM values supported by the servo.
 */
void Servo::InitServo()
{
	SetBounds(245, 0, 0, 0, 11);
	SetPeriodMultiplier(kPeriodMultiplier_4X);
}

/**
 * Constructor that assumes the default digital module.
 * 
 * @param channel The PWM channel on the digital module to which the servo is attached.
 */
Servo::Servo(UINT32 channel) : PWM(channel)
{
	InitServo();
}

/**
 * Constructor that specifies the digital module.
 * 
 * @param slot The slot in the chassis that the digital module is plugged into.
 * @param channel The PWM channel on the digital module to which the servo is attached.
 */
Servo::Servo(UINT32 slot, UINT32 channel) : PWM(slot, channel)
{
	InitServo();
}

Servo::~Servo(void)
{
}

/**
 * Set the servo position.
 * 
 * Servo values range from 0.0 to 1.0 corresponding to the range of full left to full right.
 * 
 * @param value Position from 0.0 to 1.0.
 */
void Servo::Set(float value)
{
	SetPosition(value);
}

/**
 * Get the servo position.
 * 
 * Servo values range from 0.0 to 1.0 corresponding to the range of full left to full right.
 * 
 * @return Position from 0.0 to 1.0.
 */
float Servo::Get(void)
{
	return GetPosition();
}

/**
 * Set the servo angle.
 * 
 * Assume that the servo angle is linear with respect to the PWM value (big assumption, need to test).
 * 
 * Servo angles that are out of the supported range of the servo simply "saturate" in that direction
 * In other words, if the servo has a range of (X degrees to Y degrees) than angles of less than X
 * result in an angle of X being set and angles of more than Y degrees result in an angle of Y being set.
 * 
 * @param degrees The angle in degrees to set the servo.
 */
void Servo::SetAngle(float degrees)
{
	if (degrees < kMinServoAngle)
	{
		degrees = kMinServoAngle;
	}
	else if (degrees > kMaxServoAngle)
	{
		degrees = kMaxServoAngle;
	}

	SetPosition(((float) (degrees - kMinServoAngle)) / GetServoAngleRange());
}

/**
 * Get the servo angle.
 * 
 * Assume that the servo angle is linear with respect to the PWM value (big assumption, need to test).
s
 * @return The angle in degrees to which the servo is set.
 */
float Servo::GetAngle(void)
{
	return (float)GetPosition() * GetServoAngleRange() + kMinServoAngle;
}
