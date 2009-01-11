#include "WPILib.h"
#include "DriveTrain.h"
#include "TractionRobotDrive.h"

class Michael1 : public SimpleRobot
{
public:
	Michael1();
	void Autonomous(void);
	void OperatorControl(void);
	
	DriveTrain *dt;
	Joystick *left_stick;
	Joystick *right_stick;
	
};
