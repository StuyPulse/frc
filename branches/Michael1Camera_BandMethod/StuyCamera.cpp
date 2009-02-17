#include "WPILib.h"
#include "Ports.h"
#include "StuyCamera.h"

#define FRAMES_SEC 10
#define COMPRESSION 0
#define RESOLUTION k320x240
#define ROTATION ROT_180

Image *img;
PixelValue *testPixel;

StuyCamera::StuyCamera(bool serv)
{
	testPixel = new PixelValue();
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
		printf("initilaized camera...\n");
	}
	
}

//loads new image from camera into Camera object
bool StuyCamera::GetNewImage()
{
	if ( !GetImage(img, &imgTimestamp) )  { 
	 printf("error getting image from camera\n");
	}
	Point* p = new Point();
	p->x = 10;
	p->y = 10;
	frcGetPixelValue(img, *p, testPixel);
	printf("Value is: %d\n", testPixel->hsl.L);
}

double StuyCamera::getTimestamp()
{
	return(imgTimestamp);
}
