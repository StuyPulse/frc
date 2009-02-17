#include "WPILib.h"
#include "StuyEncoder.h"

class DriveTrain {  
	
public:
	DriveTrain();
	
	// Teleop Methods
	void TankDrive(Joystick *left, Joystick *right);
	void SmoothMotors(float left, float right);
	
	// Autonomous Methods
	void Turn(float,float);
	void GoDistance(float,float);
	
	// Low Level Methods
	void SetMotors(float left, float right);
	void UpdateSensors();
	
	// Owned Components
	DigitalOutput *coast;
	
	bool slipMode;
	bool invert_left;
	bool invert_right;
	Gyro *gyro;

private:
	
	SpeedController *motor_left;
	SpeedController *motor_right;
	Accelerometer *accel;
	StuyEncoder *encoder_left;
	StuyEncoder *encoder_right;
	StuyEncoder *encoder_center;

	
};
