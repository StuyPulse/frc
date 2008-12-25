/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "PIDController.h"
#include "PID.h"
#include <math.h>

/**
 * Allocate a PID object with the given constants for P, I, D
 * @param the proportional coefficient
 * @param the integral coefficient
 * @param the derivative coefficient
 */
PIDController::PIDController(float p, float i, float d)
{
	m_controlLoop = new Notifier(PIDController::Calculate,this);
	
	m_P = p;
	m_I = i;
	m_D = d;
	m_maximumOutput = 1.0;
	m_minimumOutput = -1.0;
	
	m_maximumInput = 0;
	m_minimumInput = 0;
	
	m_continuous = false;
	
	m_enabled = false;
	
	m_setpoint = 0;
	
	m_prevError = 0;
	
	m_totalError = 0;
	
	m_tolerence = .05;

	m_result = 0;
	
	m_pidInput = 0;
	
	m_pidOutput = 0;
	
	m_controlLoop->StartPeriodic(1000);
}
	
/**
 * Free the PID object
 */
PIDController::~PIDController(void)
{
	delete m_controlLoop;
}
 /**
  * Read the input, calculate the output accordingly, and write to the output.
  * This should only be called by the Notifier created during initialization.
  * @param pointer to the PIDController object to run on
  */	
void PIDController::Calculate(void *controller)
{
	PIDController* control = (PIDController*)controller;
	if (control->m_pidInput == 0)
		return;
	if (control->m_pidOutput == 0)
		return;
	float input = control->m_pidInput->PIDGet();
	
	if (control->m_enabled)
	{
		control->m_error = control->m_setpoint - input;
		if (control->m_continuous)
		{
			if (fabs(control->m_error) > 
				control->m_maximumInput - control->m_minimumInput)
			{
				if (control->m_error > 0)
					control->m_error = control->m_error  -
					control->m_maximumInput + control->m_minimumInput;
				else
					control->m_error = control->m_error  +
					control->m_maximumInput - control->m_minimumInput;
			}
		}

		if (((control->m_totalError + control->m_error) * control->m_I <
				control->m_maximumOutput) &&
				((control->m_totalError + control->m_error) * control->m_I >
				control->m_minimumOutput))
			control->m_totalError += control->m_error;

				
		control->m_result = control->m_P * control->m_error + 
			control->m_I * control->m_totalError +
			control->m_D * (control->m_error - control->m_prevError);
		control->m_prevError = control->m_error;
		
		if (control->m_result > control->m_maximumOutput)
			control->m_result = control->m_maximumOutput;
		else if (control->m_result < control->m_minimumOutput)
			control->m_result = control->m_minimumOutput;
		
		control->m_pidOutput->PIDWrite(control->m_result);
	}
}

/**
 * Return the current PID result
 * This is always centered on zero and constrained the the max and min outs
 * @return the latest calculated output
 */
float PIDController::Get(void)
{
	return m_result;
}

/**
 *  Set the PID controller to consider the input to be continuous,
 *  Rather then using the max and min in as constraints, it considers them to
 *  be the same point and automatically calculates the shortest route to
 *  the setpoint.
 */
void PIDController::SetContinuous(void)
{
	m_continuous = true;
}
/**
 *  Set the PID controller to consider the input to be continuous,
 *  Rather then using the max and min in as constraints, it considers them to
 *  be the same point and automatically calculates the shortest route to
 *  the setpoint.
 * @param true turns on continuous, false turns off continuous
 */
void PIDController::SetContinuous(bool continuous)
{
	m_continuous = continuous;
}

/**
 * Sets the PIDSource object from which the PIDController gets its feedback.
 * @param the source of feedback for the PIDController
 */
void PIDController::SetInput(PIDSource *pidInput)
{
	m_pidInput = pidInput;
}

/**
 * Sets the PIDSource object from which the PIDController gets its feedback,
 * as well as the maximum and minimum values expected from the input.
 * @param the source of feedback for the PIDController
 * @param the minimum value expected from the input
 * @param the maximum value expected from the output
 */
void PIDController::SetInput(PIDSource *pidInput, float minimumInput,
		float maximumInput)
{
	m_pidInput = pidInput;
	m_minimumInput = minimumInput;
	m_maximumInput = maximumInput;	
	SetSetpoint(m_setpoint);
}

/**
 * Sets the PIDOutput object which the PIDController writes to.
 * @param the source of feedback for the PIDController
 */
void PIDController::SetOutput(PIDOutput *pidOutput)
{
	m_pidOutput = pidOutput;
}

/**
 * Sets the PIDOutput object which the PIDController writes to, as well as the 
 * minimum and maximum values to write.
 * @param the source of feedback for the PIDController
 * @param the minimum value to write to the output
 * @param the maximum value to write to the output
 */
void PIDController::SetOutput(PIDOutput *pidOutput, float minimumOutput,
		float maximumOutput)
{
	m_pidOutput = pidOutput;
	m_minimumOutput = minimumOutput;
	m_maximumOutput = maximumOutput;
}

/**
 * Set the setpoint for the PIDController
 * @param the desired setpoint
 */
void PIDController::SetSetpoint(float setpoint)
{
	if (m_maximumInput > m_minimumInput) {
		if (setpoint > m_maximumInput)
			m_setpoint = m_maximumInput;
		else if (setpoint < m_minimumInput)
			m_setpoint = m_minimumInput;
		else
			m_setpoint = setpoint;
	}
	else
		m_setpoint = setpoint;
}

/**
 * Returns the current setpoint of the PIDController
 * @return the current setpoint
 */
float PIDController::GetSetpoint(void)
{
	return m_setpoint;
}

/**
 * Retruns the current difference of the input from the setpoint
 * @return the current error
 */
float PIDController::GetError(void)
{
	return m_error;
}

/*
 * Set the percentage error which is considered tolerable for use with
 * OnTarget.
 * @param percentage error which is tolerable
 */
void PIDController::SetTolerence(float percent)
{
	m_tolerence = percent;
}

/*
 * Return true if the error is within the percentage of the total input range,
 * determined by SetTolerance. This asssumes that the maximum and minimum input
 * were set using SetInput.
 */
bool PIDController::OnTarget(void)
{
	return (fabs(m_error)<m_tolerence / 100 * 
			(m_maximumInput - m_minimumInput));
}

/**
 * Begin running the PIDController
 */
void PIDController::Enable(void)
{
	m_enabled = true;
}
/**
 * Stop running the PIDController, this sets the output to zero before stopping.
 */
void PIDController::Disable(void)
{
	m_enabled = false;
	m_pidOutput->PIDWrite(0);
}

/**
 * Reset the previous error,, the integral term, and disable the controller.
 */
void PIDController::Reset(void)
{
	Disable();
	
	m_prevError = 0;
	
	m_totalError = 0;
	
	m_result = 0;
}
