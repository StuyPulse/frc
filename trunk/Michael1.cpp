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
	alliance_selector = new DigitalInput(4,ALLIANCE_SELECTOR);
	// Robot Outputs
	ariels_light = new DigitalOutput(ARIELS_LIGHT);
	intake = new Victor(INTAKE_ROLLER);
	shooter = new Victor(SHOOTER_ROLLER);
	servo_1 = new Servo(SERVO1);
	servo_2 = new Servo(SERVO2);
	 	
	// Helper Objects
	arcade = new RobotDrive(1, 2);
	dt = new DriveTrain();
	cam = new Michael1Camera(false, AllianceSwitchValue());
	
	ds = DriverStation::GetInstance();
	
	// System-Wide timer. Never to be reset.
	time = new Timer();
	time->Start();
	
	// WPILib crap
	GetWatchdog().SetExpiration(100);
}

void Michael1::Autonomous(void)
{
	GetWatchdog().SetEnabled(false);

	printf("\n\n\tStart Autonomous:\n\n");
	RunScript( &(scripts[AutonSwitchValue() - 1][0]) );
	Wait(1);
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
	int b1, b2, b4, b8, answer;
	b1 = abs(1-autonswitch[0]->Get());
	b2 = abs(1-autonswitch[1]->Get());
	b4 = abs(1-autonswitch[2]->Get());
	b8 = abs(1-autonswitch[3]->Get());
	//printf("b1: %d, b2: %d, b4: %d, b8: %d\n", b1, b2, b4, b8);
	answer = (b1 + b2*2 + b4*4 + b8*8);
	printf("%d", answer);
	return answer;
}

int Michael1::AllianceSwitchValue(){
	return alliance_selector->Get();
}

void Michael1::OperatorControl(void)
{
	printf("\n\n\tStart Teleop:\n\n");
	double oldTime = 0;
	GetWatchdog().SetEnabled(false);
	ds->SetDigitalOut(3,false);
	
	while (IsOperatorControl())
	{	
		double newTime = time->Get();
		if(newTime - oldTime >= 0.1){
			dt->encoder_center->Update();
			dt->encoder_left->Update();
			dt->encoder_right->Update();
			oldTime = newTime;
			//printf ("%d \n", AutonSwitchValue());
		
		}
		
						
		//dan's goggles
		cam->TrackTarget();
		bool pin[5];
		pin[0] = pin[1] = pin[2] = pin[3] = pin[4] = false;
		if(cam->TrackTarget())
			pin[cam->oktoshoot()-1] = true;
		ds->SetDigitalOut(1, pin[0]);
		ds->SetDigitalOut(2, pin[1]);
		ds->SetDigitalOut(3, pin[2]);
		ds->SetDigitalOut(4, pin[3]);
		ds->SetDigitalOut(5, pin[4]);
		ShowActivity("** Particle image percent %f **",cam->distancetoshoot());
		//joystick motor control
		if (ds->GetDigitalIn(1)){
			if (left_stick->GetTrigger() || right_stick->GetTrigger()){
				//dt->slipMode = true;
				dt->TankDrive(left_stick, right_stick);
			} else {
				//dt->slipMode = false;
				dt->SetMotors(-(left_stick->GetY() / 2), -(right_stick->GetY() / 2));
			}
		} else {
			dt->TankDrive(left_stick, right_stick);
		}
		

		//brakes
		if (left_stick->GetRawButton(2) || right_stick->GetRawButton(2)){
			dt->coast->Set(0);
		} else {
			dt->coast->Set(1);
		}
					
		//shooter
		if (shooter_stick->GetTrigger() || shooter_stick->GetRawButton(3)){
			shooter->Set(-0.75);
		} else {
			shooter->Set(shooter_stick->GetY() * 0.5);
		}
		
		/* OI switch box
		 * Left 1u, 2d
		 * mid  5u, 3d
		 * rig	6u, 4d*/
		
		//intake
		if (ds->GetDigitalIn(6))
			intake->Set(1);
		else if (ds->GetDigitalIn(4))
			intake->Set(-1);
		else
			intake->Set(0);		
		
		
		//Servos
		if(ds->GetDigitalIn(5)){
			servo_1->Set(0);
			servo_2->Set(1);
		}
		else if (ds->GetDigitalIn(3)){
			servo_1->Set(1);
			servo_2->Set(0);
		}
		else
		{
			servo_1->Set(.5);
			servo_2->Set(.5);
		}
	}
}



START_ROBOT_CLASS(Michael1);
