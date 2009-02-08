#include "Michael1.h"
#include "Ports.h"


Michael1::Michael1()
{
	// We're Alive!
	printf("Hello!\n\n\n");
	
	// Driver's Station Inputs
	left_stick = new Joystick(LEFT_DRIVE_JOYSTICK);
	right_stick = new Joystick(RIGHT_DRIVE_JOYSTICK);
	shooter_stick = new Joystick(SHOOTER_JOYSTICK);
	
	// Robot Inputs
	autonswitch[0]= new DigitalInput(4,AUTON_SELECTOR_1); //1's bit
	autonswitch[1]= new DigitalInput(4,AUTON_SELECTOR_2); //2's bit
	autonswitch[2]= new DigitalInput(4,AUTON_SELECTOR_3); //4's bit
	autonswitch[3]= new DigitalInput(4,AUTON_SELECTOR_4);//8's bit
	
	// Robot Outputs
	ariels_light = new DigitalOutput(ARIELS_LIGHT);
	intake = new Victor(INTAKE_ROLLER);
	shooter = new Victor(SHOOTER_ROLLER);
	
	// Helper Objects
	dt = new DriveTrain();
	cam = new Michael1Camera(false);
	
	// System-Wide timer. Never to be reset.
	time = new Timer();
	time->Start();
	
	// WPILib crap
	GetWatchdog().SetExpiration(100);
	GetWatchdog().SetEnabled(false);
}

void Michael1::Autonomous(void)
{
	printf("\n\n\tStart Autonomous:\n\n");
	
	ariels_light->Set(1);
	RunScript( &(scripts[AutonSwitchValue()][0]) );
	
	printf("\n\n\tFinished Autonomous\n\n");
}

/* RunScript is blocking (pauses thread until script is complete)
 * Takes a pointer to a Command in a Command array (Script).
 * Iterates over said array until reaches "END" command.
 */
void Michael1::RunScript(Command* scpt){
	bool finished = false;
	
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

/* Return decimal value of binary
 * 4 pin digital switch.
 */
int Michael1::AutonSwitchValue(){
	int b1 = abs(1-autonswitch[1]->Get());
	int b2 = abs(1-autonswitch[2]->Get());
	int b4 = abs(1-autonswitch[3]->Get());
	//int b8 = abs(1-autonswitch[0]->Get());
	return (b1 + b2*2 + b4*4 /* + b8*8 */ );
}


void Michael1::OperatorControl(void)
{
	printf("\n\n\tStart Teleop:\n\n");
	ariels_light->Set(0);
	double oldTime = 0;
	
	while (IsOperatorControl())
	{	
		double newTime = time->Get();
		if(newTime - oldTime >= UPDATE_INTERVAL){
			//printf("left: %f, right: %f\n", dt->encoder_left->GetDistance(), dt->encoder_right->GetDistance());
			printf("\n\ny axis: %f\n\n", shooter_stick->GetY());
			//driver
			if (left_stick->GetTrigger() || right_stick->GetTrigger()){
				dt->SlipTankDrive(left_stick, right_stick);
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
			
			//shooter
			if (shooter_stick->GetTrigger() || shooter_stick->GetRawButton(3)){
				shooter->Set((0.5 - shooter_stick->GetY()) * -1);
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
