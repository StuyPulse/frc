/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef ROBOT_H_
#define ROBOT_H_

#include "Watchdog.h"

class DriverStation;

#define START_ROBOT_CLASS(_ClassName_) \
	RobotBase *FRC_userClassFactory(void) \
	{ \
		return new _ClassName_(); \
	} \
	extern "C" { \
		INT32 FRC_UserProgram_StartupLibraryInit(void) \
		{ \
			RobotBase::startRobotTask((FUNCPTR)FRC_userClassFactory); \
			return 0; \
		} \
	}

/**
 * Implement a Robot Program framework.
 * The RobotBase class is intended to be subclassed by a user creating a robot program.
 * Overridden Autonomous() and OperatorControl() methods are called at the appropriate time
 * as the match proceeds. In the current implementation, the Autonomous code will run to
 * completion before the OperatorControl code could start. In the future the Autonomous code
 * might be spawned as a task, then killed at the end of the Autonomous period.
 */
class RobotBase {
public:
	static RobotBase &getInstance(void);
	static void setInstance(RobotBase* robot);

	bool IsDisabled(void);
	bool IsAutonomous(void);
	bool IsOperatorControl(void);
	bool IsSystemActive(void);
	bool IsNewDataAvailable(void);
	Watchdog &GetWatchdog(void);
	static void startRobotTask(FUNCPTR factory);
	static void robotTask(FUNCPTR factory);

	INT32 m_taskID;

protected:
	virtual ~RobotBase(void);
	virtual void StartCompetition(void) = 0;
	RobotBase(void);

private:
	Watchdog m_watchdog;
	DriverStation *m_ds;

	static RobotBase *m_instance;
};

#endif

