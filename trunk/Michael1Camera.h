#include "StuyCamera.h"
#include "Target.h"

class Michael1Camera : public StuyCamera
{
public:
	Michael1Camera(bool, int);
	float distancetoshoot();
	int oktoshoot();
	bool TrackTarget();
	ParticleAnalysisReport par1, par2;
private:
	TrackingThreshold td1, td2;
	

};
