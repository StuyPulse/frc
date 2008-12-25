/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "RobotBase.h"

#include "DriverStation.h"
#include "Utility.h"
#include <taskLib.h>

RobotBase* RobotBase::m_instance = NULL;

void RobotBase::setInstance(RobotBase* robot)
{
	wpi_assert(m_instance == NULL);
	m_instance = robot;
}

RobotBase &RobotBase::getInstance(void)
{
	return *m_instance;
}

/**
 * Constructor for a generic robot program.
 * User code should be placed in the constuctor that runs before the Autonomous or Operator
 * Control period starts. The constructor will run to completion before Autonomous is entered.
 * 
 * This must be used to ensure that the communications code starts. In the future it would be
 * nice to put this code into it's own task that loads on boot so ensure that it runs.
 */
RobotBase::RobotBase(void)
	: m_taskID (0)
	, m_ds (NULL)
{
	m_ds = DriverStation::GetInstance();
}

/**
 * Free the resources for a RobotBase class.
 * This includes deleting all classes that might have been allocated as Singletons to they
 * would never be deleted except here.
 */
RobotBase::~RobotBase(void)
{
	SensorBase::DeleteSingletons();
	m_instance = NULL;
}

/**
 * Check on the overall status of the system.
 * 
 * @return Is the system active (i.e. PWM motor outputs, etc. enabled)?
 */
bool RobotBase::IsSystemActive(void)
{
	return m_watchdog.IsSystemActive();
}

/**
 * Return the instance of the Watchdog timer.
 * Get the watchdog timer so the user program can either disable it or feed it when
 * necessary.
 */
Watchdog &RobotBase::GetWatchdog()
{
	return m_watchdog;
}

/**
 * Determine if the Robot is currently disabled.
 * @return True if the Robot is currently disabled by the field controls.
 */
bool RobotBase::IsDisabled(void)
{
	return m_ds->IsDisabled();
}

/**
 * Determine if the robot is currently in Autnomous mode.
 * @return True if the robot is currently operating Autonomously as determined by the field controls.
 */
bool RobotBase::IsAutonomous(void)
{
	return m_ds->IsAutonomous();
}

/**
 * Determine if the robot is currently in Operator Control mode.
 * @return True if the robot is currently operating in Tele-Op mode as determined by the field controls.
 */
bool RobotBase::IsOperatorControl(void)
{
	return m_ds->IsOperatorControl();
}

/**
 * Indicates if new data is available from the driver station.
 * @todo The current implementation is silly.  We already know this explicitly without trying to figure it out.
 * @return Has new data arrived over the network since the last time this function was called?
 */
bool RobotBase::IsNewDataAvailable(void)
{
	static UINT32 previousPacketNumber = 0;

	if (m_ds->GetPacketNumber() == previousPacketNumber)
	{
		return false;
	}

	previousPacketNumber = m_ds->GetPacketNumber();
	return true;
}

/**
 * Static interface that will start the competition in the new task.
 */
void RobotBase::robotTask(FUNCPTR factory)
{
	RobotBase::setInstance((RobotBase*)factory());
	RobotBase::getInstance().StartCompetition();
}

/**
 * 
 * Start the robot code.
 * This function starts the robot code running by spawning a task. Currently tasks seemed to be
 * started by LVRT without setting the VX_FP_TASK flag so floating point context is not saved on
 * interrupts. Therefor the program experiences hard to debug and unpredictable results. So the
 * LVRT code starts this function, and it, in turn, starts the actual user program.
 */
void RobotBase::startRobotTask(FUNCPTR factory)
{
	printf("WPILib was compiled from SVN revision %s\n", SVN_REV);

	// check for prior copy of running task
	INT32 oldId = taskNameToId("FRCRobotTask");
	if(oldId != ERROR)
	{
		taskDelete(oldId);
	}

	// spawn robot task
	// this is done to ensure that the C++ robot task is spawned with the floating point
	// context save parameter. Need to talk to the real-time group about this.
	RobotBase::getInstance().m_taskID = taskSpawn("FRCRobotTask",
					100,							// priority
					VX_FP_TASK,					// floating point C++ context save
					64000,						// stack size
					(FUNCPTR)RobotBase::robotTask,	// function to be called
					(INT32)factory,0,0,0,0,0,0,0,0,0);	// parameters (unused)
	printf("Spawned FRCRobotTask (0x%0x)\n", RobotBase::getInstance().m_taskID);
}
