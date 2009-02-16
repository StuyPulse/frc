#include "Michael1.h"
#include "Ports.h"


/*
  void Michael1::Turntoshoot(){
	while(cam->TrackTarget() && cam->oktoshoot()!= 3){
		if(cam->oktoshoot() < 3){
			dt->SetMotors(.05, .05);
		}else if(cam->oktoshoot() >3){
			dt->SetMotors(-.05, -.05);
			}
		}
}
*/

Michael1::Michael1()
{
	// We're Alive!
	printf("Hello!\n\n\n");
	
	// Driver's Station Inputs
	left_stick = new Joystick(LEFT_DRIVE_JOYSTICK);
	right_stick = new Joystick(RIGHT_DRIVE_JOYSTICK);
	shooter_stick = new Joystick(SHOOTER_JOYSTICK);
	
	// Robot Inputs
	autonswitch = new BinarySwitch(4, AUTON_SELECTOR_4, AUTON_SELECTOR_3, AUTON_SELECTOR_2, AUTON_SELECTOR_1);
	alliance_selector = new DigitalInput(4,ALLIANCE_SELECTOR);
	// Robot Outputs
	ariels_light = new DigitalOutput(ARIELS_LIGHT);
	intake = new Victor(INTAKE_ROLLER);
	shooter = new Victor(SHOOTER_ROLLER);
	servo_1 = new Servo(SERVO1);
	servo_2 = new Servo(SERVO2);
	 	
	// Helper Objects
	dt = new DriveTrain();
	cam = new Michael1Camera(false);
	
	ds = DriverStation::GetInstance();
	
	// System-Wide timer. Never to be reset.
	time = new Timer();
	time->Start();
	
	// WPILib crap
	GetWatchdog().SetExpiration(100);
}

void Michael1::Autonomous(void)
{
	time->Reset();
	GetWatchdog().SetEnabled(false);

	printf("\n\n\tStart Autonomous:\n\n");
	/*while(1){
		printf("autonswitch: %d%d%d%d -> %d\n", autonswitch->GetBit(0),autonswitch->GetBit(1),autonswitch->GetBit(2),autonswitch->GetBit(3), autonswitch->Get());
		Wait(1.0);
	}
	*/
	servo_1->Set(0);
	servo_2->Set(1);
	RunScript( &(scripts[autonswitch->Get()][0]) );
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
				dt->Turn(scpt->param1,14.5 - time->Get());
				break;
			case JSTK:
				dt->SetMotors(scpt->param1, scpt->param2);
				Wait(14.5 - time->Get());
				break;
			case WAIT:
				dt->SetMotors(0,0);
				Wait(scpt->param1);
				break;
			case FWD:
				dt->GoDistance(scpt->param1,14.5 - time->Get());
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
	double oldTime = 0;
	GetWatchdog().SetEnabled(false);
	ds->SetDigitalOut(3,false);
	dt->gyro->Reset();
	
	
	while (IsOperatorControl())
	{	
		double newTime = time->Get();
		if(newTime - oldTime >= 0.1){
			dt->UpdateSensors();
			oldTime = newTime;	
			printf("%f \n", dt->gyro->GetAngle());
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
		if (ds->GetDigitalIn(6) || fabs(shooter->Get()) > 0)
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
			servo_1->Set(1);
			servo_2->Set(0);
		}
	}
}



START_ROBOT_CLASS(Michael1);
