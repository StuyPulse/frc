#include <vector>

class BaseDriveTrain
{
	
public:
	virtual ~BaseDriveTrain(); //possibly accept an array of speed controllers
	
	virtual void setMotor(int i, double speed);
	virtual void setMotor(int[] i, double speed);
	
protected:
	std::vector <*SpeedController> motors; //pointer to array of pointers to SpeedControllers

}
