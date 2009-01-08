#include "WPILib.h"

class Michael1 : SimpleRobot {
	
public:
	RobotDrive dt;
	
	void Autonomous(void);
	void OperatorControl(void);
	
	Joystick left_stick;
	Joystick right_stick

}