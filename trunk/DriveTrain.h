#include "WPILib.h"

class DriveTrain {
	
public:
	DriveTrain(UINT32 left, UINT32 right, bool invertLeft, bool invertRight);
	RobotDrive *motors;
	
	void SetMotors(Joystick *left, Joystick *right);
	void SetMotors(float left, float right);
	bool SetSpeed(float speed, float dir);
	void AssociateSensors(Encoder*, Encoder*, Gyro*, Accelerometer*);
	
	typedef struct {
		double displ_l[3];
		double displ_r[3];
		double accel_l;
		double accel_r;
		double time[3];
	} slipage_info;
	
	Timer *timer;
	slipage_info slip;
	Encoder *encoder_right;
	Encoder *encoder_left;
	Gyro *gyro;
	Accelerometer *accel;
	
	bool invert_left;
	bool invert_right;
	
};
