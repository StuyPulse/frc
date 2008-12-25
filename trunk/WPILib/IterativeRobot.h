/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef ROBOT_ITERATIVE_H_
#define ROBOT_ITERATIVE_H_

#include "Timer.h"
#include "RobotBase.h"

/**
 * IterativeRobot implements a specific type of Robot Program framework, extending the RobotBase class.
 * 
 * The IterativeRobot class is intended to be subclassed by a user creating a robot program.
 * 
 * This class is intended to implement the "old style" default code, by providing
 * the following functions which are called by the main loop, StartCompetition(), at the appropriate times:
 * 
 * RobotInit() -- provide for initialization at robot power-on
 * 
 * Init() functions -- each of the following functions is called once when the
 *                     appropriate mode is entered:
 *  - DisabledInit()   -- called only when first disabled
 *  - AutonomousInit() -- called each and every time autonomous is entered from another mode
 *  - TeleopInit()     -- called each and every time teleop is entered from another mode
 * 
 * Periodic() functions -- each of these functions is called iteratively at the
 *                         appropriate periodic rate (aka the "slow loop").  The default period of
 *                         the iterative robot is 5,000 microseconds, giving a periodic frequency
 *                         of 200Hz (200 times per second).
 *   - DisabledPeriodic()
 *   - AutonomousPeriodic()
 *   - TeleopPeriodic()
 * 
 * Continuous() functions -- each of these functions is called repeatedly as
 *                           fast as possible:
 *   - DisabledContinuous()
 *   - AutonomousContinuous()
 *   - TeleopContinuous()
 * 
 */

class IterativeRobot : public RobotBase {
public:
	static const UINT32 kDefaultPeriod = 5000;	/** default (in microsec) for periodic functions **/
	virtual void StartCompetition(void);
	
	virtual void RobotInit(void);
	virtual void DisabledInit(void);
	virtual void AutonomousInit(void);
	virtual void TeleopInit(void);

	virtual void DisabledPeriodic(void);
	virtual void AutonomousPeriodic(void);
	virtual void TeleopPeriodic(void);

	virtual void DisabledContinuous(void);
	virtual void AutonomousContinuous(void);
	virtual void TeleopContinuous(void);

	void SetPeriod(UINT32 periodInMicroSec);
	UINT32 GetLoopsPerSec(void);
	
protected:
	virtual ~IterativeRobot(void);
	IterativeRobot(void);

private:
	bool NextPeriodReady(void);

	bool m_disabledInitialized;
	bool m_autonomousInitialized;
	bool m_teleopInitialized;
	UINT32 m_disabledLoops;
	UINT32 m_autonomousLoops;
	UINT32 m_teleopLoops;
	UINT32 m_period;
	
	Timer m_mainLoopTimer;
};

#endif

