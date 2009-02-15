#include "DriveTrain.h"
#include "Ports.h"
#include <math.h>


DriveTrain::DriveTrain()
{
	motor_left = new Victor(LEFT_DRIVE_MOTOR);
	invert_left = false;
	
	motor_right = new Victor(RIGHT_DRIVE_MOTOR);
	invert_right = true;
	
	encoder_left = new StuyEncoder(LEFT_ENCODER_A, LEFT_ENCODER_B);
	encoder_right = new StuyEncoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B);
	encoder_center = new StuyEncoder(CENTER_ENCODER_A, CENTER_ENCODER_B);
	encoder_left->SetDistancePerPulse(-1 * ((6.0/12.0) * 3.1415926535) / ((44.0/12.0)*128.0));
	encoder_right->SetDistancePerPulse(((6.0/12.0) * 3.1415926535) / ((44.0/12.0)*128.0));
	encoder_center->SetDistancePerPulse(((4.0/12.0) * 3.1415926535) / 500.0);
	encoder_left->Start();
	encoder_right->Start();
	encoder_center->Start();
	
	accel = new Accelerometer(ACCELEROMETER); //(slot, pin)
	accel->SetZero(1.508);
	accel->SetSensitivity(0.3);
	
	gyro = new Gyro(GYRO); //(slot, pin)
	gyro->SetSensitivity(0.007);
	//clockwise = positive
	
	coast = new DigitalOutput(4, 6);
	coast->Set(1);
}




// Abstracted Methods

#define TURN_T .1 // time per loop
#define TURN_P .03  // Prop Gain <range xxx -> xxx>
#define TURN_I 0.03  //Integral Gain was .02
#define TURN_D 0.01 //Differential Gain
void DriveTrain::Turn(float angle){
	gyro->Reset();
	int breakout = 0;
	double p, i, d, err, lastErr;
	p = i = d = err = 0;
	lastErr = gyro->GetAngle()-angle;
	while(1) {
		err = gyro->GetAngle()-angle;
		p = err;
		i = i + err * TURN_T;
		d = (err-lastErr)/TURN_T;
		lastErr = err;
		if(fabs(err) > 20)
			i = 0; 
		double leftmotor= p*TURN_P + d*TURN_D + i*TURN_I;
		
		if(fabs(angle - gyro->GetAngle()) > 1.5){
			SetMotors(leftmotor, -leftmotor);
			breakout = 0;
		} else {
			breakout++;
			if (breakout >= 2){
				SetMotors(0, 0);
				break;
			}
		}
		
		Wait(TURN_T);
	}
}
#define FWD_T .1 // time per loop
#define FWD_P .05  // range 0.02 -> 0.1
#define FWD_D 0 // range 0.01 -> 0.05
#define FWD_I 0 
void DriveTrain::GoDistance(float distance){
	encoder_center->Reset();
	gyro->Reset();
	double p, i, d, err, lastErr;
	double multiplier = 0.5;
	p = i = d = err = 0;
	lastErr = gyro->GetAngle();
	while(encoder_center->GetDistance() < distance) {
		err = gyro->GetAngle();
		p = err;
		i = i + err * FWD_T;
		d = (err-lastErr)/FWD_T;
		lastErr = err;
		double diff= p*FWD_P + d*FWD_D + i*FWD_I;
		if (encoder_center->GetDistance() > distance - 7)
		{
			multiplier = (distance - encoder_center->GetDistance()) / 14;
			if (multiplier < .2)
			{
				multiplier = 0.2;
			}
		}
		SetMotors((multiplier + diff), (multiplier-diff));
		Wait(FWD_T);
	}
	coast->Set(0);
	SetMotors(0,0);
	Wait(1);
	coast->Set(1);
}


//	TankDrive (uses Y axis)
void DriveTrain::TankDrive(Joystick *left, Joystick *right)
{
	float l = -1 * left->GetY();
	float r = -1 * right->GetY();
	
	SetMotors(l, r);
}


#define GAIN 0.04
void DriveTrain::SmoothMotors(float left, float right){
		
	if(left > motor_left->Get()){
		motor_left->Set(motor_left->Get() + GAIN);
	    } else if (left < motor_left->Get()){
			motor_left->Set(motor_left->Get() - GAIN);
		}
	if(right > motor_right->Get()){
			motor_right->Set(motor_right->Get() + GAIN);
		} else if (right < motor_right->Get()){
			motor_right->Set(motor_right->Get() - GAIN);
		}

}

//	Lets you specify a float directly instead of being stuck with Y Axiss
void DriveTrain::SetMotors(float left, float right){
	if (invert_left){
		left *= -1;
	}
	if (invert_right){
		right *= -1;
	}
	
	motor_left->Set(left);
	motor_right->Set(right);
}

// Instead of using a timed task, call this ever 10th of a second
void DriveTrain::UpdateSensors(){
	encoder_center->Update();
	encoder_left->Update();
	encoder_right->Update();
}
