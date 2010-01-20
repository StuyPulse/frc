#include "StuyCamera.h"
#include "Target.h"

#define RED 1
#define GREEN 2

#define zone1end 85      //right boundary of column in pixels -- for left red light
#define zone1line1 130   // upper line to be tested  N.B. origin is upper left
#define zone1line2 230   // lower line to be tested
#define zone1threshold 10 //number of hits required for target detection
#define zone1increment 1	//target width is 62


#define zone2end 150     // left yellow light
#define zone2line1 135   // upper line to be tested
#define zone2line2 235   // lower line to be tested
#define zone2threshold 10 //number of hits required for target detection
#define zone2increment 1  //target width is 62

#define zone3end 265     // center green light
#define zone3line1 140   // upper line to be tested
#define zone3line2 230   // lower line to be tested
#define zone3threshold 10 //number of hits required for target detection
#define zone3increment 1	//target width is 58

#define zone4end 310     // right yellow light
#define zone4line1 165   // upper line to be tested
#define zone4line2 175   // lower line to be tested
#define zone4threshold 10 //number of hits required for target detection
#define zone4increment 1	//target width is 44

#define zone5end 320     // right yellow light
#define zone5line1 159   // upper line to be tested  N.B. origin is upper left
#define zone5line2 161   // lower line to be tested
#define zone5threshold 10 //number of hits required for target detection
#define zone5increment 1	//target width is 28


#define IMG_WIDTH 320
#define IMG_HEIGHT 240

// 20px per col, 320 cols.. Thats 6400 pixels.
#define QUL 210 //241
#define QLL 190 //151
#define QUR 190 //181
#define QLR 90 //90

class Michael1Camera : public StuyCamera
{
public:
	Michael1Camera(bool);
	
	// New Vision Code
	//void UpdateCols();
	//int ReturnZone();	
private:
	bool HSLinThreshold(PixelValue*, TrackingThreshold*);
	//float SegmentConfidence(int l, int r);
	// Old Vision Code
	/*
	int oktoshoot();
	bool TrackTarget();
	ParticleAnalysisReport par1, par2;
private:
	*/

};
