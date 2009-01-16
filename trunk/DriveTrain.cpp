#include "DriveTrain.h"

DriveTrain::DriveTrain(UINT32 left, UINT32 right, bool invertLeft, bool invertRight)
{
	motors = new RobotDrive::RobotDrive(left, right, 1.0);
	invert_left = invertLeft;
	invert_right = invertRight;
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
