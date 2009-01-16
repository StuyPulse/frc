class Michael1 : public SimpleRobot
{
public:
	Michael1();
	
	void Autonomous(void);
	void OperatorControl(void);
	
	DriverStation *ds;
	RobotDrive *dt;
	DigitalOutput *ariels_light;
	Joystick *left_stick;
	Joystick *right_stick;
	Camera *cam;
};
