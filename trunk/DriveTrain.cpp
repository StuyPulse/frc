#include "DriveTrain.h"

DriveTrain::DriveTrain(UINT32 left, UINT32 right, bool invertLeft, bool invertRight)
{
	motors = new RobotDrive::RobotDrive(left, right, 1.0);
	invert_left = invertLeft;
	invert_right = invertRight;
}

void DriveTrain::SetMotors(Joystick *left, Joystick *right) {
	float l = left->GetY();
	float r = right->GetY();
	if (invert_left){
		l *= -1;
	}
	if (invert_right){
		r *= -1;
	}
	motors->SetLeftRightMotorSpeeds(r, l);
}

void DriveTrain::SetMotors(float left, float right) {
	if (invert_left){
		left *= -1;
	}
	if (invert_right){
		right *= -1;
	}
	motors->SetLeftRightMotorSpeeds(right, left);
}
