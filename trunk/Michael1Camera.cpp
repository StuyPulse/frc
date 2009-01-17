#include "Michael1Camera.h"

Michael1Camera::Michael1Camera(bool serv) : Camera(serv){
	tdata = GetTrackingData(RED, FLUORESCENT);
}

bool Michael1Camera::FindTargets(){
	FindColor(IMAQ_HSL, &tdata.hue, &tdata.saturation, &tdata.luminance, &par);
	printf("Report: %f\n\n", par.particleToImagePercent);
	if (par.particleToImagePercent > 10.0) {
		return true;
	} else {
		return false;
	}
}

