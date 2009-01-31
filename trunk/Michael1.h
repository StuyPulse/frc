#include <iostream.h>
#include <time.h>
#include "math.h"
#include "WPILib.h"
#include "DriveTrain.h"
#include "Michael1Camera.h"


typedef struct {
	float time;
	float left;
	float right;
} Script;




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
	
	//Outputs
	DriveTrain *dt; // contains motor_left, motor_right
	DigitalOutput *ariels_light;
	
	SpeedController *intake;
	SpeedController *shooter;
	
	//Timer
	Timer *time;
};
