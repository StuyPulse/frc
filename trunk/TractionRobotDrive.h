#include "WPILib.h"
#include "DriveTrain.h"

class TractionRobotDrive : public DriveTrain {
	
public:
	TractionRobotDrive(UINT32 left, UINT32 right, double _cof);
	
private:
	double cof;
	
};
