/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "SimpleCRobot.h"

#include "Timer.h"
#include "Utility.h"

static SimpleCRobot *simpleCRobot = NULL;

SimpleCRobot::SimpleCRobot(void)
{
	simpleCRobot = this;
	Initialize();
}

/**
 * Start a competition.
 * This code needs to track the order of the field starting to ensure that everything happens
 * in the right order. Repeatedly run the correct method, either Autonomous or OperatorControl
 * when the robot is enabled. After running the correct method, wait for some state to change,
 * either the other mode starts or the robot is disabled. Then go back and wait for the robot
 * to be enabled again.
 */
void SimpleCRobot::StartCompetition(void)
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

bool IsAutonomous(void)
{
	wpi_assert(simpleCRobot != NULL);
	return simpleCRobot->IsAutonomous();
}

bool IsOperatorControl(void)
{
	wpi_assert(simpleCRobot != NULL);
	return simpleCRobot->IsOperatorControl();
}

bool IsDisabled(void)
{
	wpi_assert(simpleCRobot != NULL);
	return simpleCRobot->IsDisabled();
}

void SetWatchdogEnabled(bool enable)
{
	simpleCRobot->GetWatchdog().SetEnabled(enable);
}

void SetWatchdogExpiration(UINT32 time)
{
	simpleCRobot->GetWatchdog().SetExpiration(time);
}

void WatchdogFeed(void)
{
	simpleCRobot->GetWatchdog().Feed();
}

