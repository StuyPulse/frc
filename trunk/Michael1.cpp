#include "Michael1.h"


Script scpt[] = {
//	{time, left, right},
	{0.0, 1, 1},
	{1, -1, -1},
	{2, 0, 0}
};


Michael1::Michael1()
{
	// We're Alive!
	printf("Hello!\n\n\n");
	
	// Human Controllers
	left_stick = new Joystick(1);
	right_stick = new Joystick(2);
	shooter_stick = new Joystick(3);

	// Human Indicators
	ariels_light = new DigitalOutput(1);

	// Ball Handling System
	intake = new Victor(4, 3);
	shooter = new Victor(4, 4);
	
	// Robot Components
	dt = new DriveTrain(1, 2, 4); //configure drive train in drivetrain.cpp
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
	double t_start = time->Get();
	int index = -1;
	int size = sizeof(scpt)/sizeof(scpt[0]);
	
	while (IsAutonomous())
	{
		if (size-1 == index){
			break;
		}
		if (time->Get() - t_start > scpt[index+1].time){
			index++;
			dt->SetMotors(scpt[index].left, scpt[index].right);
		}
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
		double newTime = time->Get();
		if(newTime - oldTime >= UPDATE_INTERVAL){
			dt->UpdateSlip();
			
			//driver
			if (left_stick->GetTrigger() || right_stick->GetTrigger()){
				dt->SmoothTankDrive(left_stick, right_stick);
			} else {
				dt->TankDrive(left_stick, right_stick);
			}
			
			//shooter
			if (shooter_stick->GetTrigger() || shooter_stick->GetRawButton(3)){
				shooter->Set(0.5 - shooter_stick->GetY());
			} else {
				shooter->Set(0);
			}
			
			//intake
			if (shooter_stick->GetRawButton(6) || shooter_stick->GetRawButton(11))
				intake->Set(shooter_stick->GetThrottle());
			if (shooter_stick->GetRawButton(7) || shooter_stick->GetRawButton(10))
				intake->Set(0);
			
			
			oldTime = newTime;
		}
		
	}
}



START_ROBOT_CLASS(Michael1);
