#include "Michael1.h"

// Controller

Michael1::Michael1()
{
	// Views
	dt = new DriveTrain(1, 2);
	
	// Models
	left_stick = new Joystick(1);
	right_stick = new Joystick(2);
	
	// other calls
	GetWatchdog().SetExpiration(100);
}


void Michael1::Autonomous(void)
{	
	GetWatchdog().SetEnabled(false);
	dt->motors->Drive(0.5, 0.0); 	// drive forwards half speed
	Wait(2.0); 				//    for 2 seconds
	dt->motors->Drive(0.0, 0.0); 	// stop robot
}


void Michael1::OperatorControl(void)
{
	GetWatchdog().SetEnabled(true);
	while (IsOperatorControl())
	{
		GetWatchdog().Feed();
		dt->motors->TankDrive(left_stick, right_stick); // drive with arcade style (use right stick)
	}
}

START_ROBOT_CLASS(Michael1);
