class Michael1DriveTrain : TractionControlledDriveTrain {
	
public:
	Michael1DriveTrain(*SpeedController left, *SpeedController right);
	void tankDrive(float left, float right);
	void arcadeDrive(float speed, float direction);


	
}