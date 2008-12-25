/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "PID.h"

	/**
	 * Allocate a PID object with the given constants for P, I, D, and max_power
	 */
	PID::PID(float p, float i, float d, float max_pwm, INT32 actual)
	{
		P_ = p;
		I_ = i;
		D_ = d;
		prev_actual_ = actual;
				
		// if max_pwm is reasonable, use it, otherwise set max_pwm to 1.0
		if ((max_pwm > 0.0) && (max_pwm < 1.0)) {
			max_pwm_ = max_pwm;
		} else {
			max_pwm_ = 1.0;
		}

	}
	
	/**
	 * Free the PID object
	 */
	PID::~PID(void)
	{
	}
	
	/**
	 * Calculate a PWM value for the motor given the current sensor info.  
	 * 
	 */
	float PID::CalcPWM(INT32 desired, INT32 actual)
	{
		INT32 velocity;
		INT32 error;
		
		float p = 0;
		float i = 0;
		float d = 0;
		float pwm;
				
		error = desired - actual;
		velocity = actual - prev_actual_;
		
		// compute the new "proportional" term
		p = error * P_;
		
		// compute the new "integral" term
		// NOTE:  Not yet implemented!
		i = 0;
		
		// compute the new "derivative" term
		d = velocity * -D_;
		
		pwm = p + i + d;
		
		/*
		cout << "a:" << actual <<
			" d:" << desired <<
			" e:" << error <<
			" v:" << velocity <<
			" p:" << p <<
			" d:" << d << 
			" pwm:" << pwm << endl;
			*/
		
		// constrain power settings
		if (pwm > max_pwm_) {
			pwm = max_pwm_;
		} else if (pwm < -max_pwm_) {
			pwm = -max_pwm_;
		}
			
		// retain the current actual value for the next iteration
		prev_actual_ = actual;
		
		return pwm;			
	}



