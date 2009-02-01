#include "Michael1Camera.h"

Michael1Camera::Michael1Camera(bool serv) : StuyCamera(serv){
	sprintf (td_pink.name, "PINK");
	td_pink.hue.minValue = 220;   
	td_pink.hue.maxValue = 255;  
	td_pink.saturation.minValue = 75;   
	td_pink.saturation.maxValue = 255;      
	td_pink.luminance.minValue = 85;  
	td_pink.luminance.maxValue = 255;
	// GREEN
	sprintf (td_green.name, "GREEN");
	td_green.hue.minValue = 55;   
	td_green.hue.maxValue = 125;  
	td_green.saturation.minValue = 58;   
	td_green.saturation.maxValue = 255;    
	td_green.luminance.minValue = 92;  
	td_green.luminance.maxValue = 255;
}

bool Michael1Camera::FindTargets(){
	FindColor(IMAQ_HSL, &td_pink.hue, &td_pink.saturation, &td_pink.luminance, &par);
	printf("PinkPercent: %f\n\n", par.particleToImagePercent);
	float pink_percent = par.particleToImagePercent;
	//FindColor(IMAQ_HSL, &td_green.hue, &td_green.saturation, &td_green.luminance, &par);
	//printf("GreenPercent: %f\n\n", par.particleToImagePercent);
	//float green_percent = par.particleToImagePercent;
	if (pink_percent > 5.0 /*&& green_percent > 5.0*/) {
		return true;
	} else {
		return false;
	}
}

