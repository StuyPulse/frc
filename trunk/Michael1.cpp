#include "Michael1.h"

// Controller

Michael1::Michael1()
{
	// View
	dt = new RobotDrive(1,2);
	ds = DriverStation::GetInstance();
	ariels_light = new DigitalOutput(1);
	// Model
	left_stick = new Joystick(1);
	right_stick = new Joystick(2);
	
	// other calls
	GetWatchdog().SetExpiration(100);
}


void Michael1::Autonomous(void)
{
	GetWatchdog().SetEnabled(false);
	while (IsAutonomous()) {
	//if (StartCameraTask(10, 0, k160x120, ROT_0) == -1) {
		ariels_light->Set(1);
		Wait(2);
		ariels_light->Set(0);
		Wait(2);
	}
	//} else {
	//	ariels_light->Set(0);
	//}
}


void Michael1::OperatorControl(void)
{
	GetWatchdog().SetEnabled(true);
	while (IsOperatorControl())
	{
		GetWatchdog().Feed();
		dt->SetLeftRightMotorSpeeds(
				-1*right_stick->GetY(),
				-1*left_stick->GetY()
		); // drive with arcade style (use right stick)
	}
}

START_ROBOT_CLASS(Michael1);
