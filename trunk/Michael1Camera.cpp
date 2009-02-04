#include "Michael1Camera.h"

Michael1Camera::Michael1Camera(bool serv) : StuyCamera(serv){
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
		return true;
	} else {
		return false;
	}
}

