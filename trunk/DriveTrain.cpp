#include "DriveTrain.h"

DriveTrain::DriveTrain(UINT32 left, UINT32 right, bool invertLeft, bool invertRight)
{
	motors = new RobotDrive::RobotDrive(left, right, 1.0);
	invert_left = invertLeft;
	invert_right = invertRight;
	timer = new Timer();
	timer->Start();
}

void DriveTrain::AssociateSensors(Encoder *_left, Encoder *_right, Gyro *_gyro, Accelerometer *_accel){
	encoder_left = _left;
	encoder_right = _right;
	gyro = _gyro;
	accel = _accel;
}

//	TankDrive (uses Y axis)
void DriveTrain::SetMotors(Joystick *left, Joystick *right) {
	float l = left->GetY();
	float r = right->GetY();
	SetMotors(l, r);
}

//	Lets you specify a float directly instead of being stuck with Y Axiss
void DriveTrain::SetMotors(float left, float right) {
	if (invert_left){
		left *= -1;
	}
	if (invert_right){
		right *= -1;
	}
	motors->SetLeftRightMotorSpeeds(right, left);
}

bool DriveTrain::SetSpeed(float speed, float dir){
	bool atspeed = false;
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
			else {
				slip.time[2]= timer->Get();
				slip.displ_l[2] = encoder_left->GetDistance();
				slip.displ_r[2] = encoder_right->GetDistance();
				//v_f = v_i + a_f * (f - i) & s_f = s_i + v_f * (f - i)
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
			printf("%f", slip.accel_r + slip.accel_l
				- 2 * accel->GetAcceleration()
				* 980.0);
			}
	return atspeed;
}

