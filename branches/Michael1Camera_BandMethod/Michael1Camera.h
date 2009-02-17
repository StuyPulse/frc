#include "StuyCamera.h"
#include "Target.h"

#define IMG_WIDTH 20
#define IMG_HEIGHT 240

#define QUL 240
#define QLL 151
#define QUR 181
#define QLR 90

class Michael1Camera : public StuyCamera
{
public:
	Michael1Camera(bool);
	
	// New Vision Code
	void UpdateCols();
	int ReturnZone();
	bool cols[IMG_WIDTH];
	
private:
	bool HSLinThreshold(PixelValue*, TrackingThreshold*);
	float SegmentConfidence(int l, int r);
	TrackingThreshold pink, green;
	
	PixelValue* value;
	Point* pixel;

	// Old Vision Code
	/*
	int oktoshoot();
	bool TrackTarget();
	ParticleAnalysisReport par1, par2;
private:
	*/

};
