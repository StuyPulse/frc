#include <iostream.h>
#include <time.h>
#include "math.h"
#include "WPILib.h"
#include "DriveTrain.h"
#include "Michael1Camera.h"
#include "Scripts.h"

class Michael1 : public SimpleRobot
{
public:
	Michael1();
	void Autonomous(void);
	void OperatorControl(void);
	
	//Inputs
	Michael1Camera *cam;
	Joystick *left_stick;
	Joystick *right_stick;
	Joystick *shooter_stick;
	DigitalInput *autonswitch[4];
	
	//Outputs
	DriveTrain *dt; // contains motor_left, motor_right
	DigitalOutput *ariels_light;
	
	SpeedController *intake;
	SpeedController *shooter;
	
	//Timer
	Timer *time;
};
