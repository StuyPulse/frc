#include <iostream.h>
#include "math.h"
#include "WPILib.h"
#include "DriveTrain.h"
#include "Michael1Camera.h"
#include "Michael1.h"


Michael1::Michael1()
{
// We're Alive!
	printf("Hello!\n\n\n");
// Outputs
	dt = new DriveTrain(1,2, true, true); //analog out 1 and 2, invert, invert
	ds = DriverStation::GetInstance();
	ariels_light = new DigitalOutput(1);
// Inputs
	left_stick = new Joystick(1);
	right_stick = new Joystick(2);
//	Camera
	cam = new Michael1Camera(false); //boolean parameter is PC server
// other calls
	GetWatchdog().SetExpiration(100);
}


void Michael1::Autonomous(void)
{
	printf("\n\n\tStart Autonomous:\n\n");
	GetWatchdog().SetEnabled(true);
	
	while (IsAutonomous())
	{
		GetWatchdog().Feed();
		if(cam->FindTargets()){
			ariels_light->Set(1);
		} else {
			ariels_light->Set(0);
		}
	}
	
}


void Michael1::OperatorControl(void)
{
	printf("\n\n\tStart Teleop:\n\n");
	GetWatchdog().SetEnabled(true);
	ariels_light->Set(1);
	
	while (IsOperatorControl())
	{
		GetWatchdog().Feed();
		dt->SetMotors(left_stick, right_stick);
	}
}



START_ROBOT_CLASS(Michael1);
