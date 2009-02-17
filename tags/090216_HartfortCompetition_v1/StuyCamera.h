#include "vxWorks.h" 
#include "AxisCamera.h" 
#include "BaeUtilities.h"
#include "FrcError.h" 
#include "PCVideoServer.h" 
#include "TrackAPI.h"
#include "Target.h"

class StuyCamera
{
public:
	StuyCamera(bool); // parameter denotes to start a PC Server
	bool GetNewImage(); // returns true on new image, false on no new image
	double getTimestamp(); // returns imgTimestamp

protected:
	Image *img;
	Servo *horizontalServo;
	Servo *verticalServo;
	double imgTimestamp;
	double oldTimestamp;
	PCVideoServer *pcvs;

};

typedef struct {
	bool alliance; // true = ours, false = opposing
} Targets;
