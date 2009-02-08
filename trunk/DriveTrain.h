#include "WPILib.h"
#include "StuyEncoder.h"

class DriveTrain {  
	
public:
	DriveTrain();
	
	// Teleop Methods
	void TankDrive(Joystick *left, Joystick *right);
	void SmoothTankDrive(Joystick *left, Joystick *right);
	void SlipTankDrive(Joystick *left, Joystick *left);
	
	void SetMotors(float left, float right);
	void SmoothMotors(float left, float right);
	void CorrectSlip(float left, float right);
	
	// Autonomous Methods
	void Turn(float);
	void GoDistance(float);
	
	DigitalOutput *coast;
	
	StuyEncoder *encoder_left;
	StuyEncoder *encoder_right;
	StuyEncoder *encoder_center;
	Gyro *gyro;
	
	bool invert_left;
	bool invert_right;

private:
	
	void UpdateSlip();
	void GetAverages();
	
	SpeedController *motor_left;
	SpeedController *motor_right;
	Accelerometer *accel;
	
};
