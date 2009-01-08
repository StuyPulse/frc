#include "Stuylib.h" //includes WPILib

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
Michael1::Michael1(void): stick(1)
{
	GetWatchdog().SetExpiration(100);
	
	dt = new Michael1DriveTrain(1,2);
	
	left_joystick = new Joystick(1);
	right_joystick = new Joystick(2);
}

void Michael1::Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		dt.setMotor(0, 1);
		dt.setMotor(0, -1);
		Wait(2.0);
		dt.setMotor(0, 1);
		dt.setMotor(0, -1);
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

