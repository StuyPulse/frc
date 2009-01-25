#include "DriveTrain.h"


DriveTrain::DriveTrain()
{
	motor_left = new Victor(4, 1);
	invert_left = true;
	
	motor_right = new Victor(4, 2);
	invert_right = false;
	
	encoder_left = new Encoder(4,2,4,3); //(slot, pin, slot, pin)
	encoder_right = new Encoder(4,4,4,5); //(slot, pin, slot, pin)
	encoder_left->SetDistancePerTick(6 * 3.1415926535 * 2.54 / 1000);
	encoder_right->SetDistancePerTick(6 * 3.1415926535 * 2.54 / 1000);
	encoder_left->Start();
	encoder_right->Start();
	
	accel = new Accelerometer(1, 1); //(slot, pin)
	accel->SetZero(1.508);
	accel->SetSensitivity(0.3);
	
	gyro = new Gyro(1, 2); //(slot, pin)
	
	coast = new DigitalOutput(4, 6);
	coast->Set(1);
	
	slip.sampleNumber = 0;
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
	// calculate average velocity between this sample and last
	slip.vel_l[1] = (slip.displ_l[1] - slip.displ_l[0]) / (UPDATE_INTERVAL);
	slip.vel_r[1] = (slip.displ_r[1] - slip.displ_r[0]) / (UPDATE_INTERVAL);
	// calculate change in velocity (acceleration)
	slip.accel[NUM_ACCEL_SAMPLES-1] = accel->GetAcceleration() * 980.0;
	slip.enc_accel_l[NUM_ACCEL_SAMPLES-1] = (slip.vel_l[1] - slip.vel_l[0]) / (UPDATE_INTERVAL);
	slip.enc_accel_r[NUM_ACCEL_SAMPLES-1] = (slip.vel_r[1] - slip.vel_r[0]) / (UPDATE_INTERVAL);
		
	slip.enc_accel_r_avg = 0;
	slip.enc_accel_l_avg = 0;
	slip.accel_avg = 0;
	for (int i = 0; i<NUM_ACCEL_SAMPLES; i++){
		slip.enc_accel_r_avg += slip.enc_accel_r[i];
		slip.enc_accel_l_avg += slip.enc_accel_l[i];
		slip.accel_avg += slip.accel[i];
	}
	slip.enc_accel_r_avg /= NUM_ACCEL_SAMPLES;
	slip.enc_accel_l_avg /= NUM_ACCEL_SAMPLES;
	slip.accel_avg /= NUM_ACCEL_SAMPLES;
	
	printf("%f,%f\n",slip.accel_avg, slip.enc_accel_l_avg);
	
	//slip.diff = slip.accel[0] - (slip.enc_accel_l + slip.enc_accel_r)/2;
	
	

	//printf("Velocity based on encoders:\n\tleft_velocity: %f\n\tright_velocity: %f\n\n", slip.vel_l[1], slip.vel_r[1]);
	//printf("accelerometer - encoder: %f\n\n", slip.diff);
	
	
	// push this sample back
	for(int i = 1; i < NUM_ACCEL_SAMPLES; i++){
		slip.enc_accel_l[i-1] = slip.enc_accel_l[i];
		slip.enc_accel_r[i-1] = slip.enc_accel_r[i];
		slip.accel[i-1] = slip.accel[i];
	}
	slip.displ_l[0] = slip.displ_l[1];
	slip.displ_r[0] = slip.displ_r[1];
	slip.vel_l[0] = slip.vel_l[1];
	slip.vel_r[0] = slip.vel_r[1];
	slip.sampleNumber++;
	
}
