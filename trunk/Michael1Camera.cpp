#include "Michael1Camera.h"

Michael1Camera::Michael1Camera(bool serv) : Camera(serv){
	tdata = GetTrackingData(GREEN, FLUORESCENT);
}

bool Michael1Camera::FindTargets(){
	bool found = FindColor(IMAQ_HSL, &tdata.hue, &tdata.saturation, &tdata.luminance, &par);
	printf("Report: %f\n", par.center_mass_x_normalized);
	if (found) {
		return true;
	} else {
		return false;
	}
}

