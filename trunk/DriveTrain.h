#include "WPILib.h"

#define UPDATE_INTERVAL 0.1
#define NUM_ACCEL_SAMPLES 20

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
	DigitalOutput *coast;
	
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
	  double enc_accel_r[NUM_ACCEL_SAMPLES];	// calculated encoder acceleration
	  double enc_accel_l[NUM_ACCEL_SAMPLES];
	  double enc_accel_r_avg;
	  double enc_accel_l_avg;
	  double accel[NUM_ACCEL_SAMPLES];		// two time intervals of accelerometer readings
	  double accel_avg;
	  double diff;			// difference in cm/s^2 between encoders and accel
	  int sampleNumber;
	} SlippageInfo;
	
	SlippageInfo slip;
};
