#include "Michael1.h"

Michael1::Michael1()
{
	// We're Alive!
	printf("Hello!\n\n\n");
	
	// Human Controllers
	right_stick = new Joystick(1);
	left_stick = new Joystick(2);

	// Human Indicators
	ariels_light = new DigitalOutput(1);

	// Robot Components
	dt = new DriveTrain(); //configure drive train in drivetrain.cpp
	cam = new Michael1Camera(false);
	
	time = new Timer();
	time->Start();
	
	// WPILib crap
	GetWatchdog().SetExpiration(100);
}


void Michael1::Autonomous(void)
{
	printf("\n\n\tStart Autonomous:\n\n");
	GetWatchdog().SetEnabled(false);
	ariels_light->Set(1);
		
	while (IsAutonomous())
	{
		Wait(0.1);
		dt->SmoothTankDrive(left_stick, right_stick);
	}

}


void Michael1::OperatorControl(void)
{
	printf("\n\n\tStart Teleop:\n\n");
	GetWatchdog().SetEnabled(false);
	ariels_light->Set(0);
	double oldTime = 0;
	
	while (IsOperatorControl())
	{
		dt->TankDrive(left_stick, right_stick);
		
		double newTime = time->Get();
		if(newTime - oldTime >= UPDATE_INTERVAL){
			dt->UpdateSlip();
			oldTime = newTime;
		}
		
	}
}



START_ROBOT_CLASS(Michael1);
