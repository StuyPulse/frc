#include <iostream.h>
#include <time.h>
#include "math.h"
#include "WPILib.h"
#include "DriveTrain.h"
#include "Michael1Camera.h"

#define TURN 1
#define JSTK 2
#define WAIT 3
#define GOFW 4

typedef struct {
	int cmd;
	float param1;
	float param2;
	float param3;
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
