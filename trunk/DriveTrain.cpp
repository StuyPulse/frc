#include "DriveTrain.h"
#include "Ports.h"
#include <math.h>


DriveTrain::DriveTrain()
{
	motor_left = new Victor(LEFT_DRIVE_MOTOR);
	invert_left = true;
	
	motor_right = new Victor(RIGHT_DRIVE_MOTOR);
	invert_right = false;
	
	encoder_left = new Encoder(LEFT_ENCODER_A, LEFT_ENCODER_B); //(slot, pin, slot, pin)
	encoder_right = new Encoder(RIGHT_ENCODER_A, RIGHT_ENCODER_B); //(slot, pin, slot, pin)
	encoder_center = new Encoder(CENTER_ENCODER_A, CENTER_ENCODER_B); //(slot, pin, slot, pin)
	encoder_left->SetDistancePerPulse(6 * 3.1415926535 * 2.54 / 250);
	encoder_right->SetDistancePerPulse(6 * 3.1415926535 * 2.54 / 250);
	encoder_center->SetDistancePerPulse(6 * 3.1415926535 * 2.54 / 250);
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
#define TURN_P 1
#define TURN_I 1
#define TURN_D 1
void DriveTrain::Turn(float angle){
	gyro->Reset();
	double lastAngle = 0;
	while(1) {
		double p = TURN_P * ((angle - gyro->GetAngle())/angle);
		double d = TURN_D * (gyro->GetAngle()-lastAngle);
			lastAngle = gyro->GetAngle();
		
		double pid = TURN_FULL * (p - d);
		if((angle - gyro->GetAngle()) < -2){
			SetMotors(-1*pid, pid);
		} else if ((angle - gyro->GetAngle()) > 2){
			SetMotors(pid, -1*pid);
		} else {
			SetMotors(0, 0);
			break;
		}
		Wait(0.1);
	}
}

void DriveTrain::GoDistance(float distance){
	encoder_right->Reset();
	encoder_left->Reset();
	while (-0.5*(encoder_left->GetDistance() + encoder_right->GetDistance()) < distance){
		SetMotors(0.2,0.2);
	}
	coast->Set(0);
	SetMotors(0,0);
	Wait(1);
	coast->Set(1);
}



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
	float slip_left = (leftEncHist.vel[1]) - (centerEncHist.vel[1]);
	float slip_right = (rightEncHist.vel[1]) - (centerEncHist.vel[1]);
	float setleft = left - (slip_left * SLIP_GAIN);
	float setright = right - (slip_right * SLIP_GAIN); 
	SetMotors(setleft, setright);
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



// this must be executed every SLIP_UPDATE_INTERVAL
void DriveTrain::UpdateSlip(){
	// push old sample back
	for(int i = 1; i < NUM_ACCEL_SAMPLES; i++){
		leftEncHist.accel[i-1] = leftEncHist.accel[i];
		rightEncHist.accel[i-1] = rightEncHist.accel[i];
		centerEncHist.accel[i-1] = centerEncHist.accel[i];
		accelHist.accel[i-1] = accelHist.accel[i];
	}
	leftEncHist.displ[0] = leftEncHist.displ[1];
	rightEncHist.displ[0] = rightEncHist.displ[1];
	centerEncHist.displ[0] = centerEncHist.displ[1];
	leftEncHist.vel[0] = leftEncHist.vel[1];
	rightEncHist.vel[0] = rightEncHist.vel[1];
	centerEncHist.vel[0] = centerEncHist.vel[1];
	
	// read current encoder displacement
	leftEncHist.displ[1] = encoder_left->GetDistance();
	rightEncHist.displ[1] = encoder_right->GetDistance();
	centerEncHist.displ[1] = encoder_center-> GetDistance();
	
	// differentiate to get velocity
	leftEncHist.vel[1] = (leftEncHist.displ[1] - leftEncHist.displ[0]) / (UPDATE_INTERVAL);
	rightEncHist.vel[1] = (rightEncHist.displ[1] - rightEncHist.displ[0]) / (UPDATE_INTERVAL);
	centerEncHist.vel[1] = (centerEncHist.displ[1] - centerEncHist.displ[0]) / (UPDATE_INTERVAL);
	
	// differentiate to get acceleration
	leftEncHist.accel[NUM_ACCEL_SAMPLES-1] = (leftEncHist.vel[1] - leftEncHist.vel[0]) / (UPDATE_INTERVAL);
	rightEncHist.accel[NUM_ACCEL_SAMPLES-1] = (rightEncHist.vel[1] - rightEncHist.vel[0]) / (UPDATE_INTERVAL);
	accelHist.accel[NUM_ACCEL_SAMPLES-1] = accel->GetAcceleration() * 980.0;
	// I didn't bother to do center encoder accel...
	
	GetAverages();
	
}

void DriveTrain::GetAverages(){
	double averageRightEncAccel = 0;
	double averageLeftEncAccel = 0;
	double averageAccelerometer = 0;
	for (int i = 0; i<NUM_ACCEL_SAMPLES; i++){
		averageRightEncAccel += leftEncHist.accel[i];
		averageLeftEncAccel += rightEncHist.accel[i];
		averageAccelerometer += accelHist.accel[i];
	}
	averageRightEncAccel /= NUM_ACCEL_SAMPLES;
	averageLeftEncAccel /= NUM_ACCEL_SAMPLES;
	averageAccelerometer /= NUM_ACCEL_SAMPLES;
	
	printf("%f,%f\n",averageAccelerometer, averageLeftEncAccel);
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
