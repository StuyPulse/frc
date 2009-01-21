#include "DriveTrain.h"

DriveTrain::DriveTrain()
{
	motor_left = new Victor(1);
	invert_left = false;
	motor_right = new Jaguar(2);
	invert_right = true;
	
	timer = new Timer();
	timer->Start();
	encoder_left = new Encoder(4,2,4,3);
	encoder_right = encoder_left;
	gyro = new Gyro(2);
	accel = new Accelerometer(1);
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
	motor_left->Set(left);
	motor_right->Set(right);
}

//	TankDrive (uses Y axis)
void DriveTrain::TankDrive(Joystick *left, Joystick *right)
{
	float l = left->GetY();
	float r = right->GetY();
	SetMotors(l, r);
}

bool DriveTrain::GoshasCode(){
	bool atspeed = false;
	                /* We have to set some initial values */
			if(slip.time[0] == 0){
				slip.time[0] = timer->Get();
				slip.displ_l[0] = encoder_left->GetDistance();
				slip.displ_r[0] = encoder_right->GetDistance();
			}
			else if(slip.time[1] == 0){
				slip.time[1]= timer->Get();
				slip.displ_l[1] = encoder_left->GetDistance();
				slip.displ_r[1] = encoder_right->GetDistance();
			}
			/* after here, we're doing it for real */
			else {
				slip.time[2]= timer->Get();
				slip.displ_l[2] = encoder_left->GetDistance();
				slip.displ_r[2] = encoder_right->GetDistance();
			/*
			  the following code is derived from:
			   v_f = v_i + a_f * (f - i) & s_f = s_i + v_f * (f - i)
			*/
			slip.accel_l = 
				((slip.displ_l[2] - slip.displ_l[1])
				* (slip.time[1] - slip.time[0])
				- (slip.displ_l[1] - slip.displ_l[0])
				* (slip.time[2] - slip.time[1]))
				/ ((slip.time[2] - slip.time[1])
				* (slip.time[2] - slip.time[1])
				* (slip.time[1] - slip.time[0]));
			slip.accel_r = 
				((slip.displ_r[2] - slip.displ_r[1])
				* (slip.time[1] - slip.time[0])
				- (slip.displ_r[1] - slip.displ_r[0])
				* (slip.time[2] - slip.time[1]))
				/ ((slip.time[2] - slip.time[1])
				* (slip.time[2] - slip.time[1])
				* (slip.time[1] - slip.time[0]));
			
			slip.displ_r[0] = slip.displ_r[1];
			slip.displ_r[1] = slip.displ_r[2];
			slip.displ_l[0] = slip.displ_l[1];
			slip.displ_l[1] = slip.displ_l[2];
			
			slip.time[0] = slip.time[1];
			slip.time[1] = slip.time[2];
			
			/*
			if((slip.accel_r + slip.accel_l
				- 2 * accel->GetAcceleration()
				* (double)980 >= OK_DIFFERENCE) ||
				(slip.accel_r + slip.accel_l
							- 2 * accel->GetAcceleration()
							* (double)980 <= -OK_DIFFERENCE)){
					printf("OH TEH NOES WE ARE SLIPPING\n");
			}
			else {
				printf("\t\t\tNO SLIPPING\n");
			}*/
			printf("%f\n", slip.accel_r + slip.accel_l
				- 2 * accel->GetAcceleration()
				* 980.0);
			}
	return atspeed;
	
}

