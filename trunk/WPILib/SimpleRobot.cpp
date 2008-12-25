/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "SimpleRobot.h"

#include "Timer.h"

SimpleRobot::SimpleRobot(void)
{
	m_robotMainOverridden = true;
}

/**
 * Autonomous should go here.
 * Users should add autonomous code to this method that should run while the field is
 * in the autonomous period.
 */
void SimpleRobot::Autonomous(void)
{
	printf("Information: Provided Autonomous() method running\n");
}

/**
 * Operator control (tele-operated) code should go here.
 * Users should add Operator Control code to this method that should run while the field is
 * in the Operator Control (tele-operated) period.
 */
void SimpleRobot::OperatorControl(void)
{
	printf("Information: Provided OperatorControl() method running\n");
}

/**
 * Robot main program for free-form programs.
 * 
 * This should be overridden by user subclasses if the intent is to not use the Autonomous() and
 * OperatorControl() methods. In that case, the program is responsible for sensing when to run
 * the autonomous and operator control functions in their program.
 * 
 * This method will be called immediately after the constructor is called. If it has not been
 * overridden by a user subclass (i.e. the default version runs), then the Autonomous() and
 * OperatorControl() methods will be called.
 */
void SimpleRobot::RobotMain(void)
{
	printf("Information: No user-supplied RobotMain()\n");
	m_robotMainOverridden = false;
}

/**
 * Start a competition.
 * This code needs to track the order of the field starting to ensure that everything happens
 * in the right order. Repeatedly run the correct method, either Autonomous or OperatorControl
 * when the robot is enabled. After running the correct method, wait for some state to change,
 * either the other mode starts or the robot is disabled. Then go back and wait for the robot
 * to be enabled again.
 */
void SimpleRobot::StartCompetition(void)
{
	RobotMain();
	if ( !m_robotMainOverridden)
	{
		while (1)
		{
			while (IsDisabled()) Wait(10);		// wait for robot to be enabled

			if (IsAutonomous())
			{
				Autonomous();					// run the autonomous method
				while (IsAutonomous() && !IsDisabled()) Wait(10);
			}
			else
			{
				OperatorControl();				// run the operator control method
				while (IsOperatorControl() && !IsDisabled()) Wait(10);
			}
		}
	}
}

