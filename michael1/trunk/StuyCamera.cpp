#include "WPILib.h"
#include "Ports.h"
#include "StuyCamera.h"

#define FRAMES_SEC 10
#define COMPRESSION 0
#define RESOLUTION k320x240
#define ROTATION ROT_180

StuyCamera::StuyCamera(bool serv)
{
	horizontalServo = new Servo(CAM_HORIZONTAL);
	verticalServo = new Servo(CAM_VERTICAL);
	horizontalServo->Set(0.5);
	verticalServo->Set(0.5);
	imgTimestamp = 0.0;
	oldTimestamp = 0.0;
	if( StartCameraTask(FRAMES_SEC, COMPRESSION, RESOLUTION, ROTATION) == -1){
		printf("failed to init camera\n");
	} else {
		if (serv){
			Wait(2.0);
			pcvs = new PCVideoServer(); 
			pcvs->Start();
		}
	}
}

//loads new image from camera into Camera object
bool StuyCamera::GetNewImage()
{
	if ( !GetImage(img, &imgTimestamp) )  { 
	 printf("error getting image from camera\n");
	}
	if (imgTimestamp <= oldTimestamp){
		return false;
	} else {
		oldTimestamp = imgTimestamp;
		Point p;
		p.x = 50;
		p.y = 50;
		PixelValue *pv = new PixelValue();
		frcGetPixelValue(img, p, pv);
		double d = pv->hsl.H;
		printf("The value is %f", d);
		return true;
	}
}

double StuyCamera::getTimestamp()
{
	return(imgTimestamp);
}
