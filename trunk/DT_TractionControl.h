class TractionControlledDriveTrain : BaseDriveTrain
{
	
public:
	void setWheelWeight(double weight);
	void setWheelCof(double cof);
	
	virtual void setMotor(int i, double speed);
	
private:
	double wheel_weight;
	double wheel_cof;
	
	TractionControlledDriveTrain();
	
}
