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
	int AllianceSwitchValue();
	//Inputs
	RobotDrive *arcade;
	Michael1Camera *cam;
	Joystick *left_stick;
	Joystick *right_stick;
	Joystick *shooter_stick;
	DigitalInput *autonswitch[4];
	DigitalInput *alliance_selector;
	//Outputs
	DriveTrain *dt; // contains motor_left, motor_right
	DigitalOutput *ariels_light;
	DriverStation *ds;
	Servo *servo_1;
	Servo *servo_2;
	SpeedController *intake;
	SpeedController *shooter;
	
private:
	int AutonSwitchValue();
	
	void RunScript(Command*);
	
	//Timer
	Timer *time;
	
};
