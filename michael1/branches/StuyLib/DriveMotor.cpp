#include "DriveMotor.h"

DriveMotor::DriveMotor(SpeedController* Motor, StuyEncoder* Encoder){
	motor = Motor;
	enc = Encoder;
	enc->Start();
	invert = false;
}

void DriveMotor::Set(float raw){
	motor->Set(raw);
}

#define VEL_P 0.1
void DriveMotor::SetVelocity(float velocity){
	double err = velocity - enc->GetVelocity();
	Set(err*VEL_P);
}

#define ACCEL_P 0.1
void DriveMotor::SetAcceleration(float acceleration){
	double err = acceleration - enc->GetAcceleration();
	SetVelocity(err*ACCEL_P);
}
