#include "StuyCamera.h"
#include "Target.h"

class Michael1Camera : public StuyCamera
{
public:
	Michael1Camera(bool);
	bool TrackTarget();

private:
	TrackingThreshold td1, td2;
	ParticleAnalysisReport par1, par2;

};
