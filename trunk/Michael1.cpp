#include <iostream.h>
#include "math.h"
#include "WPILib.h"
#include "Michael1Camera.h"
#include "Michael1.h"


Michael1::Michael1()
{
// We're Alive!
	printf("Hello!\n\n\n");
// Outputs
	dt = new RobotDrive(1,2);
	ds = DriverStation::GetInstance();
	ariels_light = new DigitalOutput(1);
// Inputs
	left_stick = new Joystick(1);
	right_stick = new Joystick(2);
//	Camera
	cam = new Michael1Camera(true); //boolean parameter is PC server
// other calls
	GetWatchdog().SetExpiration(100);
}


void Michael1::Autonomous(void)
{
	GetWatchdog().SetEnabled(true);
	ariels_light->Set(1);
	
	while (IsAutonomous())
	{
		GetWatchdog().Feed();
		if(cam->GetNewImage()){
			//we have an image, process it!
			//will get called every 100ms (10fps)
		}
	}
	
}


void Michael1::OperatorControl(void)
{
	GetWatchdog().SetEnabled(true);
	ariels_light->Set(0);
	
	while (IsOperatorControl())
	{
		GetWatchdog().Feed();
		dt->SetLeftRightMotorSpeeds(
				-right_stick->GetY(),
				-left_stick->GetY()
		); // drive with arcade style (use right stick)
	}
}



START_ROBOT_CLASS(Michael1);
