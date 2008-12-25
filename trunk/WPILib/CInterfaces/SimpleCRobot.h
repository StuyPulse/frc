/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef SIMPLE_C_ROBOT_H
#define SIMPLE_C_ROBOT_H

#include "RobotBase.h"

void Autonomous(void);
void OperatorControl(void);
void Initialize(void);

bool IsAutonomous(void);
bool IsOperatorControl(void);
bool IsDisabled(void);

void SetWatchdogEnabled(bool enable);
void SetWatchdogExpiration(UINT32 time);
void WatchdogFeed(void);

class SimpleCRobot: public RobotBase
{
public:
	SimpleCRobot(void);
	virtual ~SimpleCRobot() {}
	void StartCompetition(void);
};

#endif
