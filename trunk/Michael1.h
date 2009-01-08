#include "WPILib.h"

class Michael1 : public SimpleRobot
{
public:
	Michael1();
	
	void Autonomous(void);
	void OperatorControl(void);
	
	RobotDrive *dt;
	Joystick *left_stick;
	Joystick *right_stick;

};
