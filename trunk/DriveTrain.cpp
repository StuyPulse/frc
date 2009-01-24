#include "DriveTrain.h"
#include <time.h>

 
//#define PHASE_1	//test displacement encoders
//#define PHASE_2	//test velocity based on encoders
//#define PHASE_3	//test acceleration (t_2 - t_1) based on encoders
//#define PHASE_4	//test acceleration (t_2/2-t_0/2) based on encoders
//#define PHASE_5	//compare acceleration from encoders and acceleration

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
	
	timer = new Timer();
	timer->Start();
	
	slip.timesRun = 0;
	
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

void DriveTrain::UpdateSlip(){
	if(slip.timesRun == 0) {
		slip.time[0] = timer->Get();
		slip.timesRun++;
		slip.displ_l[0] = encoder_left->GetDistance();
		slip.displ_r[0] = encoder_right->GetDistance();
	}
	else if(slip.timesRun == 1) {
		slip.time[1] = timer->Get();
		slip.timesRun++;
		slip.displ_l[1] = encoder_left->GetDistance();
		slip.displ_r[1] = encoder_right->GetDistance();
		slip.vel_l[1] = (slip.displ_l[1] - slip.displ_l[0]) / (slip.time[1] - slip.time[0]);
		slip.vel_r[1] = (slip.displ_r[1] - slip.displ_r[0]) / (slip.time[1] - slip.time[0]);
	}
	else {
		slip.time[2] = timer->Get();
		slip.displ_l[2] = encoder_left->GetDistance();
		slip.displ_r[2] = encoder_right->GetDistance();
		slip.vel_l[2] = (slip.displ_l[2] - slip.displ_l[1]) / (slip.time[2] - slip.time[1]);
		slip.vel_r[2] = (slip.displ_r[2] - slip.displ_r[1]) / (slip.time[2] - slip.time[1]);
		#ifdef PHASE_3
			slip.accel_l = (slip.vel_l[2] - slip.vel_l[1]) / (slip.time[2] - slip.time[1]);
			slip.accel_r = (slip.vel_r[2] - slip.vel_r[1]) / (slip.time[2] - slip.time[1]);
		#endif
		#ifdef PHASE_4
			slip.accel_l = (slip.vel_l[2] - slip.vel_l[1]) / (slip.time[2]/2 - slip.time[0]/2);
			slip.accel_r = (slip.vel_r[2] - slip.vel_r[1]) / (slip.time[2]/2 - slip.time[0]/2);
		#endif

		#ifdef PHASE_1
			printf("Displacement based on encoders:\n\tleft_encoder: %f\n\tright_encoder: %f\n\n", slip.displ_l[2], slip.displ_r[2]);
		#endif
		#ifdef PHASE_2
			printf("Velocity based on encoders:\n\tleft_velocity: %f\n\tright_velocity: %f\n\n", slip.vel_l[2], slip.vel_r[2]);
		#endif
		#ifdef PHASE_3
			printf("Acceleration based on encoders(t_2-t_1):\n\tleft_acceleration: %f\n\tright_acceleration: %f\n\n", slip.accel_l, slip.accel_r);
		#endif
		#ifdef PHASE_4
			printf("Acceleration based on encoders(t_2/2-t_1/2):\n\tleft_acceleration: %f\n\tright_acceleration\n\n", slip.accel_l, slip.accel_r);
		#endif
		#ifdef PHASE_5
			printf("accelerometer - encoder:\n\n", accel->GetAcceleration * 980.0 - (slip.accel_l/2 + slip.accel_r/2));
		#endif
		//HERE WE PUSH DOWN THE VALUES
			slip.vel_l[1] = slip.vel_l[2];
			slip.vel_r[1] = slip.vel_r[2];
			slip.time[0] = slip.time[1];
			slip.time[1] = slip.time[2];
			slip.displ_l[0] = slip.displ_l[1];
			slip.displ_l[1] = slip.displ_l[2];
			slip.displ_r[0] = slip.displ_r[1];
			slip.displ_r[1] = slip.displ_r[2];
	}
}
