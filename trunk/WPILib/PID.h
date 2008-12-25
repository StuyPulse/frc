/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef PID_H_
#define PID_H_

#include "WPILib.h"

/**
 * Class implements a PID Control Loop.
 * 
 * On each "iteration" with new PID control values, call the CalcPWM() method
 * 
 * Implementation is currently incomplete -- does not yet have an implementation
 * for "integral" control.  (i.e. current this is just a PD control loop)
 */
class PID
{
private:
	float P_;			// factor for "proportional" control
	float I_;			// factor for "integral" control
	float D_;			// factor for "derivative" control
	float max_pwm_;		// maximum PWM value to provide as output from PID loop
	
	INT32 prev_actual_;	// the prior actual sensor reading (used to compute velocity)
		
public:
	PID(float p, float i, float d, float max_pwm, INT32 actual);
	~PID(void);
	float CalcPWM(INT32 desired, INT32 actual);
};

#endif
