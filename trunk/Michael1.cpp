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
	
	// WPILib crap
	GetWatchdog().SetExpiration(100);
}


void Michael1::Autonomous(void)
{
	printf("\n\n\tStart Autonomous:\n\n");
	GetWatchdog().SetEnabled(false);
	ariels_light->Set(0);
	dt->slipControl(true);
	
	while (IsAutonomous())
	{
		Wait(0.1);
		//printf("Encoder: %f, ", dt->encoder_left->GetDistance());
		//printf("Gyro: %f, ", dt->gyro->GetAngle());
		//printf("Accel: %f", dt->accel->GetAcceleration());
		//printf("\n\n");
		dt->TankDrive(left_stick, right_stick);
		dt->UpdateSlip(); //calling slipControl(true) should spawn a task which does this.
		/*Wait(.1);
		if(cam->FindTargets()){
			ariels_light->Set(1);
		} else {
			ariels_light->Set(0);
		}
		*/
	}

}


void Michael1::OperatorControl(void)
{
	printf("\n\n\tStart Teleop:\n\n");
	GetWatchdog().SetEnabled(false);
	ariels_light->Set(1);
	dt->slipControl(false);
	
	while (IsOperatorControl())
	{
		dt->TankDrive(left_stick, right_stick);
	}
}



START_ROBOT_CLASS(Michael1);
