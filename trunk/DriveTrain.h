#include "WPILib.h"
#include "StuyEncoder.h"

#define UPDATE_INTERVAL 0.1
#define NUM_ACCEL_SAMPLES 20

class DriveTrain {  
	
public:
	DriveTrain(int, int, int);
	
	void TankDrive(Joystick *left, Joystick *right);
	void SmoothTankDrive(Joystick *left, Joystick *right);
	void SetMotors(float left, float right);
	void UpdateSlip();
	void Turn(float);
	void GoDistance(float);
	void GetAverages();
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
	  double displ[2];	// displacement (cm) since encoder init
	  double vel[2];		// velocity between displacements[0] and [1]
	  double accel[NUM_ACCEL_SAMPLES];	// calculated encoder acceleration
	} EncoderHist;
	
	typedef struct {
	  double accel[NUM_ACCEL_SAMPLES];
	} AccelHist;
	
	EncoderHist rightEncHist;
	EncoderHist leftEncHist;
	AccelHist accelHist;
};
