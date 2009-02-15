#include "WPILib.h"
#include "DriveMotor.h"

#define NORMAL_DRIVE 0
#define VELOCITY_DRIVE 1
#define ACCELERATION_DRIVE 2
#define LIMIT_ACCELERATION_DRIVE 3

class DriveTrain {  
	
public:
	DriveTrain();
	
	// Teleop Methods
	void TankDrive(Joystick *left, Joystick *right);
	void SmoothMotors(float left, float right);
	
	// Autonomous Methods
	void Turn(float);
	void GoDistance(float);
	
	// Low Level Methods
	void SetMotors(float left, float right);
	void UpdateSensors();
	
	// Owned Components
	DigitalOutput *coast;
	int mode;

private:
	DriveMotor *left_motor;
	DriveMotor *right_motor;
	Accelerometer *accel;
	StuyEncoder *encoder_center;
	Gyro *gyro;
	
};
