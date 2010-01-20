#include "WPILib.h"

class StuyEncoder : public Encoder
{
public:
	StuyEncoder(UINT32, UINT32);
	void Update(); //should be moved to private, and put in a task spawned by constructor
	//double GetDistance(); // inherited from Encoder class
	double GetVelocity();
	double GetAcceleration();
	double interval;
	bool invert;

	
private:
	typedef struct {
	  double displ[2];	// displacement (cm) since encoder init
	  double vel[2];	// velocity between displacements[0] and [1]
	  double accel;	// calculated encoder acceleration
	} metrics;

	metrics hist;
	
	double _invert(double);
};
