#include "Michael1Camera.h"

Michael1Camera::Michael1Camera(bool serv, int Alliance) : StuyCamera(serv){
	/* image data for tracking - override default parameters if needed */
			/* recommend making PINK the first color because GREEN is more 
			 * subsceptible to hue variations due to lighting type so may
			 * result in false positives */
			// PINK
			sprintf (td1.name, "PINK");
			td1.hue.minValue = 220;   
			td1.hue.maxValue = 255;  
			td1.saturation.minValue = 75;   
			td1.saturation.maxValue = 255;      
			td1.luminance.minValue = 85;  
			td1.luminance.maxValue = 255;
			// GREEN
			sprintf (td2.name, "GREEN");
			td2.hue.minValue = 55;   
			td2.hue.maxValue = 125;  
			td2.saturation.minValue = 58;   
			td2.saturation.maxValue = 255;    
			td2.luminance.minValue = 92;  
			td2.luminance.maxValue = 255;
}

bool Michael1Camera::TrackTarget(){
	if ( FindTwoColors(td1, td2, ABOVE, &par1) ){
		ShowActivity("X: %f, Y: %f", par1.center_mass_x_normalized, par1.center_mass_y_normalized);
		//horizontalServo->Set(horizontalServo->Get() + (par1.center_mass_x_normalized/2)*0.2);
		//verticalServo->Set(verticalServo->Get() - (par1.center_mass_y_normalized/2)*0.2);
		return true;
	} else {
		return false;
	}
}

int Michael1Camera::oktoshoot(){
	if(FindTwoColors(td1, td2, ABOVE, &par1)){
		if ((par1.center_mass_x_normalized<=0.2)&&(par1.center_mass_x_normalized>=-.2)){ 
			return 3;
		}else if((par1.center_mass_x_normalized<=.5)&&(par1.center_mass_x_normalized>.2)){
			return 2;
		}else if(par1.center_mass_x_normalized>.5){
			return 1;
		}else if((par1.center_mass_x_normalized<-.2)&&(par1.center_mass_x_normalized>=-.5)){
			return 4;
		}else if(par1.center_mass_x_normalized<-.5){
			return 5;
		}
	}else{
		return 0;
	}
}
float Michael1Camera::distancetoshoot(){
	TrackTarget();
	return par1.particleToImagePercent;
	}


