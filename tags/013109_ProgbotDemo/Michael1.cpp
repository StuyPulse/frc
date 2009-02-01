#include "Michael1.h"
#include "Ports.h"


Script scpt[] = {
//	{CMD, p1, p2, p3},
	{TURN, 40, 0, 0},
	{WAIT, .5, 0, 0},
	{GOFW, 600, 0, 0}
};


Michael1::Michael1()
{
	// We're Alive!
	printf("Hello!\n\n\n");
	
	// Human Controllers
	left_stick = new Joystick(LEFT_DRIVE_JOYSTICK);
	right_stick = new Joystick(RIGHT_DRIVE_JOYSTICK);
	shooter_stick = new Joystick(SHOOTER_JOYSTICK);

	// Human Indicators
	ariels_light = new DigitalOutput(ARIELS_LIGHT);

	// Ball Handling System
	intake = new Victor(INTAKE_ROLLER);
	shooter = new Victor(SHOOTER_ROLLER);
	
	// Robot Components
	dt = new DriveTrain();
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
	int index = 0;
	int size = sizeof(scpt)/sizeof(scpt[0]);
	
	while (IsAutonomous())
	{
		if (size == index){
			dt->SetMotors(0,0);
			break;
		}
		switch(scpt[index].cmd){
		case TURN:
			dt->Turn(scpt[index].param1);
			break;
		case JSTK:
			dt->SetMotors(scpt[index].param1, scpt[index].param2);
			Wait(scpt[index].param3);
			break;
		case WAIT:
			dt->SetMotors(0,0);
			Wait(scpt[index].param1);
			break;
		case GOFW:
			dt->GoDistance(scpt[index].param1);
			break;
		}
		index++;
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
			printf("left: %f, right: %f\n", dt->encoder_left->GetDistance(), dt->encoder_right->GetDistance());
			
			//driver
			if (left_stick->GetTrigger() || right_stick->GetTrigger()){
				dt->SmoothTankDrive(left_stick, right_stick);
			} else {
				dt->TankDrive(left_stick, right_stick);
			}
			
			if (left_stick->GetRawButton(2) || right_stick->GetRawButton(2)){
				dt->coast->Set(0);
			} else {
				dt->coast->Set(1);
			}
			
			if (shooter_stick->GetRawButton(9)){
				dt->gyro->Reset();
			}
			printf("%f", dt->gyro->GetAngle());
			
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
