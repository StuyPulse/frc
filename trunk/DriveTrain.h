#include "WPILib.h"

class DriveTrain {
	
public:
	DriveTrain(UINT32 left, UINT32 right, bool invertLeft, bool invertRight);
	RobotDrive *motors;
	void SetMotors(Joystick *left, Joystick *right);
	void SetMotors(float left, float right);
	
	bool invert_left;
	bool invert_right;
	
};
