#include "WPILib.h"

#define SLIP_UPDATE_INTERVAL 0.1


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
	
	bool invert_left;
	bool invert_right;

private:
	SpeedController *motor_left;
	SpeedController *motor_right;
	
	typedef struct {
	  double displ_l[2];	// displacement (cm) since encoder init
	  double displ_r[2];
	  double vel_l[2];		// velocity between displacements[0] and [1]
	  double vel_r[2];
	  double enc_accel_r;	// calculated encoder acceleration
	  double enc_accel_l;
	  double accel[2];		// two time intervals of accelerometer readings
	  double diff;			// difference in cm/s^2 between encoders and accel
	} SlippageInfo;
	
	SlippageInfo slip;
};
