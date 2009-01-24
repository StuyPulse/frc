#include "DriveTrain.h"


DriveTrain::DriveTrain()
{
	motor_left = new Victor(4, 1);
	invert_left = true;
	
	motor_right = new Victor(4, 2);
	invert_right = false;
	
	encoder_left = new Encoder(4,2,4,3); //(slot, pin, slot, pin)
	encoder_right = encoder_left;
	//encoder_right = new Encoder(4,2,4,3); //(slot, pin, slot, pin)
	encoder_left->SetDistancePerTick(6 * 3.1415926535 * 2.54 / 1000);
	//encoder_right->SetDistancePerTick(6 * 3.1415926535 * 2.54 / 1000);
	encoder_left->Start();
	//encoder_right->Start();
	
	accel = new Accelerometer(1, 1); //(slot, pin)
	accel->SetZero(-0.994694);
	
	gyro = new Gyro(1, 2); //(slot, pin)
}

//	Lets you specify a float directly instead of being stuck with Y Axiss
void DriveTrain::SetMotors(float left, float right)
{
	if (invert_left){
		left *= -1;
	}
	if (invert_right){
		right *= -1;
	}
	// remember, left and right give us acceleration intent
	motor_left->Set(left);
	motor_right->Set(right);
}

#define GAIN 0.03
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

//	TankDrive (uses Y axis)
void DriveTrain::TankDrive(Joystick *left, Joystick *right)
{
	float l = left->GetY();
	float r = right->GetY();
	SetMotors(l, r);
}

void DriveTrain::SmoothTankDrive(Joystick *left, Joystick *right)
{
	float l = left->GetY();
	float r = right->GetY();
	SmoothMotors(l, r);
}

// this must be executed every SLIP_UPDATE_INTERVAL
void DriveTrain::UpdateSlip(){
	// read current encoder distance
	slip.displ_l[1] = encoder_left->GetDistance();
	slip.displ_r[1] = encoder_right->GetDistance();
	// read instantanious accelerometer
	slip.accel[1] = accel->GetAcceleration() * 980.0;
	// calculate average velocity between this sample and last
	slip.vel_l[1] = (slip.displ_l[1] - slip.displ_l[0]) / SLIP_UPDATE_INTERVAL;
	slip.vel_r[1] = (slip.displ_r[1] - slip.displ_r[0]) / SLIP_UPDATE_INTERVAL;
	// calculate change in velocity (acceleration)
	slip.enc_accel_l = (slip.vel_l[1] - slip.vel_l[0]) / SLIP_UPDATE_INTERVAL;
	slip.enc_accel_r = (slip.vel_r[1] - slip.vel_r[0]) / SLIP_UPDATE_INTERVAL;

	slip.diff = slip.accel[0] - (slip.enc_accel_l + slip.enc_accel_r)/2;
	
	

	//printf("Velocity based on encoders:\n\tleft_velocity: %f\n\tright_velocity: %f\n\n", slip.vel_l[1], slip.vel_r[1]);
	printf("Acceleration based on encoders:\n\tleft_acceleration: %f\n\tright_acceleration: %f\n\n", slip.enc_accel_l, slip.enc_accel_r);
	//printf("accelerometer - encoder: %f\n\n", slip.diff);
	
	
	// push this sample back
	slip.accel[0] = slip.accel[1];
	slip.displ_l[0] = slip.displ_l[1];
	slip.displ_r[0] = slip.displ_r[1];
	slip.vel_l[0] = slip.vel_l[1];
	slip.vel_r[0] = slip.vel_r[1];
	
}
