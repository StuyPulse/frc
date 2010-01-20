class DriveTrainTC : DriveTrain
{
	
public:
	virtual ~DriveTrainTC();
	
	void setCof(double cof);
	virtual void setMotor(int i, double speed);
	
private:
	double cof;
	
}
