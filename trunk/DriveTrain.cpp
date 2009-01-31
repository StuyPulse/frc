#include "DriveTrain.h"


DriveTrain::DriveTrain(int left, int right, int slot)
{
	motor_left = new Victor(slot, left);
	invert_left = false;
	
	motor_right = new Victor(slot, right);
	invert_right = true;
	
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

#define GAIN 0.05
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
	// push old sample back
	for(int i = 1; i < NUM_ACCEL_SAMPLES; i++){
		leftEncHist.accel[i-1] = leftEncHist.accel[i];
		rightEncHist.accel[i-1] = rightEncHist.accel[i];
		accelHist.accel[i-1] = accelHist.accel[i];
	}
	leftEncHist.displ[0] = leftEncHist.displ[1];
	rightEncHist.displ[0] = rightEncHist.displ[1];
	leftEncHist.vel[0] = leftEncHist.vel[1];
	rightEncHist.vel[0] = rightEncHist.vel[1];
	
	// read current encoder displacement
	leftEncHist.displ[1] = encoder_left->GetDistance();
	rightEncHist.displ[1] = encoder_right->GetDistance();
	// differentiate to get velocity
	leftEncHist.vel[1] = (leftEncHist.displ[1] - leftEncHist.displ[0]) / (UPDATE_INTERVAL);
	rightEncHist.vel[1] = (rightEncHist.displ[1] - rightEncHist.displ[0]) / (UPDATE_INTERVAL);
	// differentiate to get acceleration
	leftEncHist.accel[NUM_ACCEL_SAMPLES-1] = (leftEncHist.vel[1] - leftEncHist.vel[0]) / (UPDATE_INTERVAL);
	rightEncHist.accel[NUM_ACCEL_SAMPLES-1] = (rightEncHist.vel[1] - rightEncHist.vel[0]) / (UPDATE_INTERVAL);
	
	accelHist.accel[NUM_ACCEL_SAMPLES-1] = accel->GetAcceleration() * 980.0;
	
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
