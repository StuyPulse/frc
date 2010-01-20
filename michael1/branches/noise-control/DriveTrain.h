#include "WPILib.h"

class DriveTrain {
	
public:
	DriveTrain();
	
	void TankDrive(Joystick *left, Joystick *right);
	void SmoothTankDrive(Joystick *left, Joystick *right);
	void SetMotors(float left, float right);
	void UpdateSlip();
	void SmoothMotors(float, float);
	void AssociateSensors(Encoder*, Encoder*, Gyro*, Accelerometer*);
	Encoder *encoder_left;
	Encoder *encoder_right;
	Gyro *gyro;
	Accelerometer *accel;
	SpeedController *motor_left;
	SpeedController *motor_right;
	
	bool invert_left;
	bool invert_right;

private:
	typedef struct {
	  /* if a quantity is in an array, the value of the array
	     at an index is the value of that quantity at the
	     time that has the same index
	  */
	  double displ_l[3]; //displacement of the left hand side
	  double displ_r[3]; //           "  "   " right   "    "
		double vel_l[3];
		double vel_r[3];
	  double accel_r;    //acceleration  "   "     "   "    "
	  double accel_l;    //           "  "   " left    "    "
	  double time[3];    //time
	  int timesRun;
	} slipage_info;
	Timer *timer;
	slipage_info slip;
	bool slipControlEnabled;
};
