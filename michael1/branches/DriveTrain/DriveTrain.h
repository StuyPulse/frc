#include <vector>

/*

	DriveTrain Class
		I wanted an expandable drive train class to be part of the robot code.
		The WPILib "RobotDrive" class is essentially useless. It does not allow
		for any expansions, and is just plain messy. We don't need it. This class
		can give us the motor grouping that RobotDrive would.

*/

class DriveTrain
{
	
public:
	virtual ~DriveTrain(); //possibly accept an array of speed controllers
	
	virtual void setMotor(int i, double speed);
	virtual void setMotor(int[] i, double speed);
	
protected:
	std::vector <*SpeedController> motors; //pointer to array of pointers to SpeedControllers

}
