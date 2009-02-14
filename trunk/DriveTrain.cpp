#include "DriveTrain.h"
#include "Ports.h"
#include <math.h>


DriveTrain::DriveTrain()
{
	motor_left = new Victor(LEFT_DRIVE_MOTOR);
	invert_left = true;
	
	
	motor_right = new Victor(RIGHT_DRIVE_MOTOR);
	invert_right = false;
	
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
#define TURN_P .022  // Prop Gain <range xxx -> xxx>
#define TURN_I 0.022 //Integral Gain
#define TURN_D 0.01 // Differential Gain
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
#define FWD_P .04  // range 0.02 -> 0.1
#define FWD_D 0 // range 0.01 -> 0.05
void DriveTrain::GoDistance(float distance){
	encoder_center->Reset();
	gyro->Reset();
	double lastAngle = 0;
	double left, right;
	while (encoder_center->GetDistance() < distance){
		double p = FWD_P * gyro->GetAngle();
		double d = FWD_D * ((gyro->GetAngle()-lastAngle)/FWD_T);
		lastAngle = gyro->GetAngle();
		left = (0.5 + p - d);
		right = (0.5 - p + d);
		SetMotors((1*(left/2)), (1*(right/2)));
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


#define SLIP_GAIN 0.02 //something
void DriveTrain::CorrectSlip(float left, float right){
	/*float slip_left = encoder_left->GetVelocity() - encoder_center->GetVelocity();
	float slip_right = encoder_right->GetVelocity() - encoder_center->GetVelocity();
	//float setleft = left - (slip_left * SLIP_GAIN);
	//float setright = right - (slip_right * SLIP_GAIN); 

	motor_left->Set(left);
	motor_right->Set(right);*/
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
	
	if (slipMode){
		CorrectSlip(left, right);
	} else {
		motor_left->Set(left);
		motor_right->Set(right);
	}
}
