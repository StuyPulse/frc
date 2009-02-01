#include "StuyCamera.h"

class Michael1Camera : public StuyCamera
{
public:
	Michael1Camera(bool);
	bool FindTargets();
	ParticleAnalysisReport par;

private:
	TrackingThreshold td_green;
	TrackingThreshold td_pink;
};
