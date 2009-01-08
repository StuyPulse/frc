

Michael1::Michael1(void): dt(1, 2) //implements dt constructor
{
	left_stick = new Joystick(1);
	right_stick = new Joystick(2);
	GetWatchdog().SetExpiration(100);
}


Michael1::Autonomous(void)
{
	GetWatchdog().SetEnabled(false);
	dt.Drive(0.5, 0.0); 	// drive forwards half speed
	Wait(2.0); 				//    for 2 seconds
	dt.Drive(0.0, 0.0); 	// stop robot
}


Michael1::OperatorControl(void)
{
	GetWatchdog().SetEnabled(true);
	while (IsOperatorControl())
	{
		GetWatchdog().Feed();
		dt.TankDrive(left_stick, right_stick); // drive with arcade style (use right stick)
	}
}
	
	
START_ROBOT_CLASS(Michael1);