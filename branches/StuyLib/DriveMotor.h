#include "StuyEncoder.h"
#include "WPILib.h"
#define VICTOR 1
#define JAGUAR 2

class DriveMotor {
public:
	DriveMotor(SpeedController* motor, StuyEncoder* enc);
	void Set(float);
	void SetVelocity(float);
	void SetAcceleration(float);
	bool invert;
	SpeedController* motor;
	StuyEncoder* enc;
	
};
