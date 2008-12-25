/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "IterativeRobot.h"
#include <iostream.h>

/**
 * Constructor for RobotIterativeBase
 * 
 * The constructor initializes the instance variables for the robot to indicate
 * the status of initialization for disabled, autonomous, and teleop code.
 */
IterativeRobot::IterativeRobot()
{
	printf("RobotIterativeBase Constructor Start\n");
	// set status for initialization of disabled, autonomous, and teleop code.
	m_disabledInitialized = false;
	m_autonomousInitialized = false;
	m_teleopInitialized = false;

	// keep track of the number of continuous loops performed per period
	m_disabledLoops = 0;
	m_autonomousLoops = 0;
	m_teleopLoops = 0;
	
	m_period = kDefaultPeriod;

	// Start the timer for the main loop
	m_mainLoopTimer.Start();

	printf("RobotIterativeBase Constructor Finish\n");
}

/**
 * Free the resources for a RobotIterativeBase class.
 */
IterativeRobot::~IterativeRobot(void)
{
}

/**
 * Set the period for the periodic functions.
 * 
 * The period is set in microseconds for the length of time between calls to the
 * periodic functions.  Default period is 5,000 microseconds (200Hz iteration loop).
 */
void IterativeRobot::SetPeriod(UINT32 periodInMicroSec)
{
	m_period = periodInMicroSec;
}

/**
 * Get the number of loops per second for the IterativeRobot
 * 
 * Get the number of loops per second for the IterativeRobot.  The default period of
 * 5,000 microseconds results in 200 loops per second.  (200Hz iteration loop).
 */
UINT32 IterativeRobot::GetLoopsPerSec(void)
{
	return ((UINT32) 1000000 / m_period);
}

/**
 * Provide an alternate "main loop" via StartCompetition().
 * 
 * This specific StartCompetition() implements "main loop" behavior like that of the FRC
 * control system in 2008 and earlier, with a primary (slow) loop that is
 * called periodically, and a "fast loop" (a.k.a. "spin loop") that is 
 * called as fast as possible with no delay between calls. 
 */
void IterativeRobot::StartCompetition(void)
{
	printf("RobotIterativeBase StartCompetition() Commenced\n");
	
	// first and one-time initialization
	RobotInit();
	
	// loop forever, calling the appropriate mode-dependent function
	while (TRUE)
	{
		// Call the appropriate function depending upon the current robot mode
		if (IsDisabled())
		{
			// call DisabledInit() if we are now just entering disabled mode from
			// either a different mode or from power-on
			if(!m_disabledInitialized)
			{
				DisabledInit();
				m_disabledInitialized = true;
				// reset the initialization flags for the other modes
				m_autonomousInitialized = false;
				m_teleopInitialized = false;
				printf("Disabled_Init() completed\n");
			}
			if (NextPeriodReady())
			{
				DisabledPeriodic();
			}
			DisabledContinuous();
		}
		else if (IsAutonomous())
		{
			// call AutonomousInit() if we are now just entering autonomous mode from
			// either a different mode or from power-on
			if(!m_autonomousInitialized)
			{
				// KBS NOTE:  old code reset all PWMs and relays to "safe values"
				// whenever entering autonomous mode, before calling
				// "Autonomous_Init()"
				AutonomousInit();
				m_autonomousInitialized = true;
				// reset the initialization flags for the other modes
				m_disabledInitialized = false;
				m_teleopInitialized = false;
				printf("Autonomous_Init() completed\n");
			}
			if (NextPeriodReady())
			{
				AutonomousPeriodic();
			}
			AutonomousContinuous();
		}
		else
		{
			// call TeleopInit() if we are now just entering teleop mode from
			// either a different mode or from power-on
			if(!m_teleopInitialized)
			{
				TeleopInit();
				m_teleopInitialized = true;
				// reset the initialization flags for the other modes
				m_disabledInitialized = false;
				m_autonomousInitialized = false;
				printf("Teleop_Init() completed\n");
			}
			if (NextPeriodReady())
			{
				TeleopPeriodic();
			}
			TeleopContinuous();
		}
	}	
	printf("RobotIterativeBase StartCompetition() Ended\n");
}

/**
 * Determine if the appropriate next periodic function should be called.
 * 
 * This function makes adjust for lateness in the cycle by keeping track of how late
 * it was and crediting the next period with that amount.
 */
//TODO: decide what this should do if it slips more than one cycle.

bool IterativeRobot::NextPeriodReady(void)
{
	static UINT32 adjustment = 0;	
	UINT32 elapsed_time = m_mainLoopTimer.Get();
	
	if ((elapsed_time + adjustment) >= m_period)
	{
		// immediately reset the timer and calculate the next adjustment
		m_mainLoopTimer.Reset();
		adjustment = (elapsed_time + adjustment) - m_period;
		// check for slippage of more than one cycle
		// TODO:  Should really notify the user somehow when this happens
		if (adjustment > m_period) {
			adjustment = 0;
			cout << "P" << endl;
		}
		return true;
	}
	return false;
}

/**
 * Robot-wide initialization code should go here.
 * 
 * Users should override this method for default Robot-wide initialization which will
 * be called when the robot is first powered on.  It will be called exactly 1 time.
 */
void IterativeRobot::RobotInit(void)
{
	printf("Default RobotIterativeBase::RobotInit() method running\n");
}

/**
 * Initialization code for disabled mode should go here.
 * 
 * Users should override this method for initialization code which will be called each time
 * the robot enters disabled mode.
 */
void IterativeRobot::DisabledInit(void)
{
	printf("Default RobotIterativeBase::DisabledInit() method running\n");
}

/**
 * Initialization code for autonomous mode should go here.
 * 
 * Users should override this method for initialization code which will be called each time
 * the robot enters autonomous mode.
 */
void IterativeRobot::AutonomousInit(void)
{
	printf("Default RobotIterativeBase::AutonomousInit() method running\n");
}

/**
 * Initialization code for teleop mode should go here.
 * 
 * Users should override this method for initialization code which will be called each time
 * the robot enters teleop mode.
 */
void IterativeRobot::TeleopInit(void)
{
	printf("Default RobotIterativeBase::TeleopInit() method running\n");
}

/**
 * Periodic code for disabled mode should go here.
 * 
 * Users should override this method for code which will be called periodically at a regular
 * rate while the robot is in disabled mode.
 */
void IterativeRobot::DisabledPeriodic(void)
{
	printf("D - %d\n", m_disabledLoops);
	m_disabledLoops = 0;
}

/**
 * Periodic code for autonomous mode should go here.
 *
 * Users should override this method for code which will be called periodically at a regular
 * rate while the robot is in autonomous mode.
 */
void IterativeRobot::AutonomousPeriodic(void)
{
	printf("A - %d\n", m_autonomousLoops);
	m_autonomousLoops = 0;
}

/**
 * Periodic code for teleop mode should go here.
 *
 * Users should override this method for code which will be called periodically at a regular
 * rate while the robot is in teleop mode.
 */
void IterativeRobot::TeleopPeriodic(void)
{
	printf("T - %d", m_teleopLoops);
	m_teleopLoops = 0;
}

	

/**
 * Continuous code for disabled mode should go here.
 *
 * Users should override this method for code which will be called repeatedly as frequently
 * as possible while the robot is in disabled mode.
 */
void IterativeRobot::DisabledContinuous(void)
{
  m_disabledLoops++;
}

/**
 * Continuous code for autonomous mode should go here.
 *
 * Users should override this method for code which will be called repeatedly as frequently
 * as possible while the robot is in autonomous mode.
 */
void IterativeRobot::AutonomousContinuous(void)
{
  m_autonomousLoops++;
}

/**
 * Continuous code for teleop mode should go here.
 *
 * Users should override this method for code which will be called repeatedly as frequently
 * as possible while the robot is in teleop mode.
 */
void IterativeRobot::TeleopContinuous(void)
{
  m_teleopLoops++;
}

