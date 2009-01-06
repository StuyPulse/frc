class BaseDriveTrain
{
	
public:
	virtual ~BaseDriveTrain()
	
	virtual void setMotor(int i, double speed);
	virtual void setMotor(int[] i, double speed);
	
protected:
	SpeedController*[] motors;
	
private:
	BaseDriveTrain(); //make sure nobody instansiates a BaseDriveTrain
	
	
}
