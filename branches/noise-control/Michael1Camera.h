#include "Camera.h"

class Michael1Camera : public Camera
{
public:
	Michael1Camera(bool);
	bool FindTargets();
	ParticleAnalysisReport par;

private:
	TrackingThreshold td_green;
	TrackingThreshold td_pink;
};
