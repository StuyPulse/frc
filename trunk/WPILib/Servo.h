/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef SERVO_H
#define SERVO_H

#include "PWM.h"
#include "SpeedController.h"

/**
 * Standard hobby style servo.
 * 
 * The range parameters default to the appropriate values for the Hitec HS-322HD servo provided
 * in the FIRST Kit of Parts in 2008.
 */
class Servo : public PWM, public SpeedController
{
public:
	Servo(UINT32 channel);
	Servo(UINT32 slot, UINT32 channel);
	virtual ~Servo(void);
	void Set(float value);
	float Get(void);
	void SetAngle(float angle);
	float GetAngle(void);
	float GetMaxAngle(void) { return kMaxServoAngle; };
	float GetMinAngle(void) { return kMinServoAngle; };

private:
	void InitServo(void);
	float GetServoAngleRange(void) {return kMaxServoAngle - kMinServoAngle;}

	static const float kMaxServoAngle = 170.0;
	static const float kMinServoAngle = 0.0;
};

#endif

