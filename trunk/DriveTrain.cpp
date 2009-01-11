#include "DriveTrain.h"

DriveTrain::DriveTrain(UINT32 left, UINT32 right)
{
	motors = new RobotDrive::RobotDrive(left, right, 1.0);
}
