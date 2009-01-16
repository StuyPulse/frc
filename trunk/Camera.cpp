#include "WPILib.h"
#include "Camera.h"

#define FRAMES_SEC 10
#define COMPRESSION 0
#define RESOLUTION k320x240
#define ROTATION ROT_180

Camera::Camera(bool serv)
{
	imgTimestamp = 0.0;
	oldTimestamp = 0.0;
	if( StartCameraTask(FRAMES_SEC, COMPRESSION, RESOLUTION, ROTATION) == -1){
		printf("failed to init camera\n");
	} else {
		if (serv){
			pcvs = new PCVideoServer(); 
			pcvs->Start();
		}
	}
}

//loads new image from camera into Camera object
bool Camera::GetNewImage()
{
	if ( !GetImage(img, &imgTimestamp) )  { 
	 printf("error getting image from camera\n");
	}
	if (imgTimestamp <= oldTimestamp){
		return false;
	} else {
		oldTimestamp = imgTimestamp;
		return true;
	}
}

double Camera::getTimestamp()
{
	return(imgTimestamp);
}
