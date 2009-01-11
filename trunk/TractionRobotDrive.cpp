#include "TractionRobotDrive.h"

TractionRobotDrive::TractionRobotDrive(UINT32 left, UINT32 right, double _cof) : DriveTrain(left, right)
{
	cof = _cof;
}
