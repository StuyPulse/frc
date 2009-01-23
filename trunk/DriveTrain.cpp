#include "DriveTrain.h"
#include <time.h>

//Accelerometer accel = Accelerometer(1);
DriveTrain::DriveTrain()
{
	motor_left = new Victor(4, 1);
	invert_left = true;
	
	motor_right = new Victor(4, 2);
	invert_right = false;
	
	encoder_left = new Encoder(4,2,4,3); //(slot, pin, slot, pin)
	encoder_left->SetDistancePerTick(6 * 3.1415926535 * 2.54 / 200);
	encoder_right = encoder_left;
	encoder_left->Start();
	//encoder_right->Start();
	
	accel = new Accelerometer(1, 1); //(slot, pin)
	accel->SetZero(-0.994694);
	
	gyro = new Gyro(1, 2); //(slot, pin)
	
	timer = new Timer();
	
	slipControlEnabled = false;
}

void DriveTrain::slipControl(bool enabled){
	if (enabled == slipControlEnabled){
		return;
	}
	if(enabled){
		slipControlEnabled = true;
		timer->Start();
	} else {
		slipControlEnabled = false;
		timer->Stop();
		timer->Reset();
	}
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
	//if (slipControlEnabled)
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

void DriveTrain::UpdateSlip(){
	//bool atspeed = false;
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
			/*slip.accel_l =
				((slip.displ_l[2] - slip.displ_l[1])
				* (slip.time[1] - slip.time[0])
				- (slip.displ_l[1] - slip.displ_l[0])
				* (slip.time[2] - slip.time[1]))
				/ ((slip.time[2] - slip.time[1])
				* (slip.time[2] - slip.time[1])
				* (slip.time[1] - slip.time[0]))*/
			  //let's restate that
				//ok suppose we have times i < m < f and s = diplacement, v = velocity, a = acceleration
				slip.accel_l/*a_f*/ = ((((slip.displ_l[2]/*s_f*/ - slip.displ_l[1]/*s_m*/) / (slip.time[2]/*f*/ - slip.time[1]/*m*/))/*v_f*/
							- ((slip.displ_l[1]/*s_m*/ - slip.displ_l[0]/*s_i*/) / (slip.time[1]/*m*/ - slip.time[0]/*i*/))/*v_m*/)
						       / (slip.time[1]/*f*/ - slip.time[0]/*m*/));

			/*slip.accel_r = 
				((slip.displ_r[2] - slip.displ_r[1])
				* (slip.time[1] - slip.time[0])
				- (slip.displ_r[1] - slip.displ_r[0])
				* (slip.time[2] - slip.time[1]))
				/ ((slip.time[2] - slip.time[1])
				* (slip.time[2] - slip.time[1])
				* (slip.time[1] - slip.time[0]));*/
			//let's restate that
				//ok suppose we have times i < m < f and s = diplacement, v = velocity, a = acceleration
                                slip.accel_r/*a_f*/ = ((((slip.displ_r[2]/*s_f*/ - slip.displ_r[1]/*s_m*/) / (slip.time[2]/*f*/ - slip.time[1]/*m*/))/*v_f*/
							- ((slip.displ_r[1]/*s_m*/ - slip.displ_r[0]/*s_i*/) / (slip.time[1]/*m*/ - slip.time[0]/*i*/))/*v_m*/)
                                                       / (slip.time[1]/*f*/ - slip.time[0]/*m*/));
			
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
				
			/*printf("Accel diff: %f\n", (slip.accel_r + slip.accel_l)/2
				- accel->GetAcceleration()
				* 980.0);*/
			//printf("Velocity: %f\n", (((slip.displ_l[2]/*s_f*/ - slip.displ_l[1]/*s_m*/) / (slip.time[2]/*f*/ - slip.time[1]/*m*/))));
				/*printf("time0=%f, time1=%f, time2=%f\ndispl0=%f, displ1=%f, displ2=%f\n dispr0=%f, dispr1=%f, dispr2=%f\nAccel: %f\n\n"
						,slip.time[0],slip.time[1],slip.time[2]
						,slip.displ_l[0],slip.displ_l[1],slip.displ_l[2]
						,slip.displ_r[0],slip.displ_r[1],slip.displ_r[2]
						,accel.GetAcceleration());*/
			printf("Slip:\ndispl_l[0]\t%f\ndispl_l[1]\t%f\ndispl_l[2]\t%f\n\n"
					, slip.displ_l[0], slip.displ_l[1], slip.displ_l[2]);
			
			/*let's push our values down by one section of time*/
			slip.displ_r[0] = slip.displ_r[1];
			slip.displ_r[1] = slip.displ_r[2];
			slip.displ_l[0] = slip.displ_l[1];
			slip.displ_l[1] = slip.displ_l[2];
			/*likewise, let's push down our times so that they correspond with the values*/
			slip.time[0] = slip.time[1];
			slip.time[1] = slip.time[2];
			}
	//return atspeed;
}

