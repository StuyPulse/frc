/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

class PIDOutput;
class PIDSource;
class Notifier;

/**
 * Class implements a PID Control Loop.
 * 
 * Creates a separate thread which reads the given PIDSource and takes
 * care of the integral calculations, as well as writing the given
 * PIDOutput
 */
class PIDController
{
private:
	float m_P;			// factor for "proportional" control
	float m_I;			// factor for "integral" control
	float m_D;			// factor for "derivative" control
	float m_maximumOutput;	// |maximum output|
	float m_minimumOutput;	// |minimum output|
	
	float m_maximumInput;		// maximum input - limit setpoint to this
	float m_minimumInput;		// minimum input - limit setpoint to this
	
	bool m_continuous;	// do the endpoints wrap around? eg. Absolute encoder
	
	bool m_enabled; 			//is the pid controller enabled
	
	float m_prevError;	// the prior sensor input (used to compute velocity)
	
	double m_totalError; //the sum of the errors for use in the integral calc
	
	float m_tolerence;	//the percetage error that is considered on target
	
	float m_setpoint;
	
	float m_error;
	
	float m_result;
	
	PIDSource *m_pidInput;
	PIDOutput *m_pidOutput;

	static void Calculate(void *controller);

	Notifier *m_controlLoop;
	
public:
	PIDController(float p, float i, float d);
	~PIDController(void);
	float Get(void);
	void SetContinuous(void);
	void SetContinuous(bool continuous);
	void SetInput(PIDSource *pidInput);
	void SetInput(PIDSource *pidInput, float minimumInput, float maximumInput);
	void SetOutput(PIDOutput *pidOutput);
	void SetOutput(PIDOutput *pidOutput, float mimimumOutput,
			float maximumOutput);
	
	void SetSetpoint(float setpoint);
	float GetSetpoint(void);

	float GetError(void);
	
	void SetTolerence(float percent);
	bool OnTarget(void);
	
	void Enable(void);
	void Disable(void);
	
	void Reset(void);
};

#endif
