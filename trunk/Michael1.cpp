#include "Michael1.h"
#include "Ports.h"


Michael1::Michael1()
{
	// We're Alive!
	printf("Hello!\n\n\n");
	
	// Human Controllers
	left_stick = new Joystick(LEFT_DRIVE_JOYSTICK);
	right_stick = new Joystick(RIGHT_DRIVE_JOYSTICK);
	shooter_stick = new Joystick(SHOOTER_JOYSTICK);
	autonswitch[0]= new DigitalInput(4,AUTON_SELECTOR_1); //1's bit
	autonswitch[1]= new DigitalInput(4,AUTON_SELECTOR_2); //2's bit
	autonswitch[2]= new DigitalInput(4,AUTON_SELECTOR_3); //4's bit
	autonswitch[3]= new DigitalInput(4,AUTON_SELECTOR_4);//8's bit
	
	
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
	int autonSwitchValue = (abs(1-autonswitch[1]->Get()))+(abs(1-autonswitch[2]->Get())*2)+(abs(1-autonswitch[3]->Get())*4);
	autonSwitchValue--;
	printf("switch = %d\n", autonSwitchValue);
	bool finished = false;
	
	while(1){
		ariels_light->Set(cam->TrackTarget());
	}

	Command* scpt = &(scripts[autonSwitchValue][0]);
	
	while (IsAutonomous())
	{
		switch(scpt->cmd){
		case TURN:
			dt->Turn(scpt->param1);
			break;
		case JSTK:
			dt->SetMotors(scpt->param1, scpt->param2);
			Wait(scpt->param3);
			break;
		case WAIT:
			dt->SetMotors(0,0);
			Wait(scpt->param1);
			break;
		case FWD:
			dt->GoDistance(scpt->param1);
			break;
		default:
			dt->SetMotors(0,0);
			finished = true;
		}
		if (finished){
			break;
		}
		scpt++;
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
