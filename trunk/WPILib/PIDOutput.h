/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef PID_OUTPUT_H
#define PID_OUTPUT_H

/**
 * PIDSource class is a generic output for the PID class.
 * PWMs use this class.
 * Users implement this interface to allow for a PIDController to 
 * write directly to outputs
 */
class PIDOutput
{
public:
	virtual void PIDWrite(float output) = 0;
};

#endif
