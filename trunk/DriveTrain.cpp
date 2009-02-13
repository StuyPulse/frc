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

#define TURN_FULL 1
#define TURN_P .5  // range 0.02 -> 0.1
#define TURN_D 0 // range 0.01 -> 0.05
void DriveTrain::Turn(float angle){
	gyro->Reset();
	double lastAngle = 0;
	int i = 0;
	while(i <= 10) {
		double p = TURN_P * ((angle - gyro->GetAngle())/angle);
		double d = TURN_D * (gyro->GetAngle()-lastAngle);
		lastAngle = gyro->GetAngle();
		
		double pid = TURN_FULL * (p - d);
		if((angle - gyro->GetAngle()) < -10){
			SetMotors(-1*pid, pid);
			i = 0;
		} else if ((angle - gyro->GetAngle()) > 10){
			SetMotors(-1*pid, pid);
			i = 0;
		} else if ((angle - gyro->GetAngle()) < 10 && (angle - gyro->GetAngle()) > -10){
			i++;
			if (i >= 10){
			SetMotors(0, 0);
			}
		}
		Wait(0.1);
	}
}
#define T 0.1 //time per loop
#define PG 0.06
//proportional
#define DG 0 //differential
void DriveTrain::GoDistance(float distance){
	encoder_center->Reset();
	gyro->Reset();
	double lastAngle = 0;
	double left, right;
	while (encoder_center->GetDistance() < distance){
		double p = PG * gyro->GetAngle();
		double d = DG * ((gyro->GetAngle()-lastAngle)/T);
		lastAngle = gyro->GetAngle();
		left = (0.5 + p - d);
		right = (0.5 - p + d);
		SetMotors(left, right);
		Wait(T);
	}
	coast->Set(0);
	SetMotors(0,0);
	Wait(1);
	coast->Set(1);
}
/* pidleft = K * gyro + .2
 * pidright = K * gyro + .2
 * K is proportion and use DEFINE*/



// SetMotor() Methods

//	TankDrive (uses Y axis)
void DriveTrain::TankDrive(Joystick *left, Joystick *right)
{
	float l = -1 * left->GetY();
	float r = -1 * right->GetY();
	SetMotors(l, r);
}

void DriveTrain::SmoothTankDrive(Joystick *left, Joystick *right)
{
	float l = -1 * left->GetY();
	float r = -1 * right->GetY();
	SmoothMotors(l, r);
}

void DriveTrain::SlipTankDrive(Joystick *left, Joystick *right)
{
	float l = -1 * left->GetY();
	float r = -1 * right->GetY();
	CorrectSlip(l, r);
}


#define SLIP_GAIN 0.02 //something
void DriveTrain::CorrectSlip(float left, float right){
	/*float slip_left = encoder_left->GetVelocity() - encoder_center->GetVelocity();
	float slip_right = encoder_right->GetVelocity() - encoder_center->GetVelocity();
	float setleft = left - (slip_left * SLIP_GAIN);
	float setright = right - (slip_right * SLIP_GAIN); 
	SetMotors(setleft, setright);
	*/
}

#define GAIN 0.04
void DriveTrain::SmoothMotors(float left, float right){
	if (invert_left){
		left *= -1;
	}
	if (invert_right){
		right *= -1;
	}
		
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
