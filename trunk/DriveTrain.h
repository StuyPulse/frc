#include "WPILib.h"

class DriveTrain {
	
public:
	DriveTrain(UINT32 left, UINT32 right, bool invertLeft, bool invertRight);
	RobotDrive *motors;
	
	void SetMotors(Joystick *left, Joystick *right);
	void SetMotors(float left, float right);
	bool SetSpeed(float speed, float dir);
	void AssociateSensors(Encoder*, Encoder*, Gyro*, Accelerometer*);
	
	Encoder *encoder_right;
	Encoder *encoder_left;
	Gyro *gyro;
	Accelerometer *accel;
	
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
	  double accel_r;    //acceleration  "   "     "   "    "
	  double accel_l;    //           "  "   " left    "    "
	  double time[3];    //time
	} slipage_info;
	Timer *timer;
	slipage_info slip;
};
