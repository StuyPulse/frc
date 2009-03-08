#include "Michael1.h"
#include "Ports.h"

Image *img;
bool cols[IMG_WIDTH];
PixelValue *pixel_value_scratch;
PixelValue* value;
Point* pixel;
TrackingThreshold *color;
TrackingThreshold pink, green;


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
	
	
	value = new PixelValue();
	pixel = new Point();
	color = new TrackingThreshold();
	
	sprintf (pink.name, "PINK");
	pink.hue.minValue = 220;   
	pink.hue.maxValue = 255;  
	pink.saturation.minValue = 75;   
	pink.saturation.maxValue = 255;      
	pink.luminance.minValue = 85;  
	pink.luminance.maxValue = 255;
	// GREEN
	sprintf (green.name, "GREEN");
	green.hue.minValue = 55;   
	green.hue.maxValue = 125;  
	green.saturation.minValue = 58;   
	green.saturation.maxValue = 255;    
	green.luminance.minValue = 92;  
	green.luminance.maxValue = 255;
	
	
}


bool Michael1::HSLinThreshold(PixelValue* val, TrackingThreshold* range){
	bool inH = (val->hsl.H >= range->hue.minValue) && (val->hsl.H <= range->hue.maxValue);
	bool inS = (val->hsl.S >= range->saturation.minValue) && (val->hsl.S <= range->saturation.maxValue);
	bool inL = (val->hsl.L >= range->luminance.minValue) && (val->hsl.L <= range->luminance.maxValue);
	//printf("H: %d S: %d L: %d\n", val->hsl.H, val->hsl.S, val->hsl.L);
	return (inH && inS && inL);
}

int Michael1::checkzone(int allianceName){
	if (allianceName == RED)
			color = &pink;
		else
			color = &green;

		//green, center zone3
		int col = 0;
		int row = zone3line1;
		int zonetotal = 0;

			for (col=(zone2end +1);col <= zone3end; col +=zone3increment){
				pixel->x = col;
				pixel->y = row;
				frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line1
				if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
			}
			row = zone3line2;
			for (col=(zone2end +1);col <= zone3end; col +=zone3increment){
				pixel->x = col;
				pixel->y = row;
				frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line2
				if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
			 }
			printf("Zone3 Total: %d\n", zonetotal);
			if (zonetotal >= zone3threshold)return 2;

			//right yellow, zone4
				row = zone4line1;
				zonetotal = 0;

					for (col=(zone3end +1);col <= zone4end; col +=zone4increment){
						pixel->x = col;
						pixel->y = row;
						frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line1
						if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
					}
					row = zone4line2;
					for (col=(zone3end +1);col <= zone4end; col +=zone4increment){
						pixel->x = col;
						pixel->y = row;
						frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line2
						if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
					}
					printf("Zone4 Total: %d\n", zonetotal);
					if (zonetotal >= zone4threshold)return 3;

	//left yellow, zone2
			row = zone2line1;
			zonetotal = 0;
			for (col=(zone1end +1);col <= zone2end; col +=zone2increment){
				pixel->x = col;
				pixel->y = row;
				frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line1
				if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
					}
				row = zone2line2;
			for (col=(zone1end +1);col <= zone2end; col +=zone2increment){
				pixel->x = col;
				pixel->y = row;
				frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line2
				if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
					}
			printf("Zone2 Total: %d\n", zonetotal);
			if (zonetotal >= zone2threshold)return 1;


	//right red, zone5
		row = zone5line1;
		zonetotal = 0;
		 for (col=(zone4end +1);col <= zone5end; col +=zone5increment){
			pixel->x = col;
			pixel->y = row;
			frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line1
			if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
									}
		row = zone5line2;
		for (col=(zone4end +1);col <= zone5end; col +=zone5increment){
			pixel->x = col;
			pixel->y = row;
			frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line2
			if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
									}
		printf("Zone5 Total: %d\n", zonetotal);
		if (zonetotal >= zone5threshold)return 4;

		//left red, zone1
			row = zone1line1;
			zonetotal = 0;
			 for (col = 0;col <= zone1end; col +=zone1increment){
				pixel->x = col;
				pixel->y = row;
				frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line1
				if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
										}
			row = zone1line2;
			for (col = 0;col <= zone1end; col +=zone1increment){
				pixel->x = col;
				pixel->y = row;
				frcGetPixelValue(img, *pixel, value);//get and test pixel values for zone3line2
				if (HSLinThreshold(value, color))zonetotal++;  // we need a pink/green switch
										}
			printf("Zone1 Total: %d\n", zonetotal);
			if (zonetotal >= zone1threshold)return 0;

	return -1;         //no target found

}

void Michael1::Autonomous(void)
{
	GetWatchdog().SetEnabled(false);
	while(IsAutonomous()){
		img = frcCreateImage(IMAQ_IMAGE_HSL);
		GetImage(img, NULL);
		    bool pin[5];
			pin[0] = pin[1] = pin[2] = pin[3] = pin[4] = false;
			
			int camZone = checkzone(1); // 1 is red, 2 is green
			if (camZone > -1){
				pin[camZone] = true;
			}
			printf("camzone = %d", camZone);
			ds->SetDigitalOut(1, pin[0]);
			ds->SetDigitalOut(2, pin[1]);
			ds->SetDigitalOut(3, pin[2]);
			ds->SetDigitalOut(4, pin[3]);
			ds->SetDigitalOut(5, pin[4]);
		frcDispose(img);
		Wait(0.1);
	}
	printf("end auton");
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
			/*
			cam->UpdateCols();
			printf("\n\n");
			for (int i = 0; i < 320; i++){
				if (cam->cols[i])
					printf("X");
				else
					printf("_");
			}
			*/
			oldTime = newTime;	
			//ShowActivity("Center_mass_x %f, Center_mass_y %f Height %f, Width %f", cam->par1.center_mass_x, cam->par1.center_mass_y, cam->par1.imageHeight, cam->par1.imageWidth);
		}
		
						
		
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
