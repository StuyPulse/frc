#include "Michael1Camera.h"

extern PixelValue *pixel_value_scratch;
extern Image *img;

Michael1Camera::Michael1Camera(bool serv) : StuyCamera(serv){
	/* image data for tracking - override default parameters if needed */
			/* recommend making PINK the first color because GREEN is more 
			 * subsceptible to hue variations due to lighting type so may
			 * result in false positives */
			// PINK
			sprintf (pink.name, "PINK");
			pink.hue.minValue = 220;   
			pink.hue.maxValue = 255;  
			pink.saturation.minValue = 75;   
			pink.saturation.maxValue = 255;      
			pink.luminance.minValue = 85;  
			pink.luminance.maxValue = 255;
			// GREEN
			sprintf (green.name, "GREEN");
			green.hue.minValue = 55;   
			green.hue.maxValue = 125;  
			green.saturation.minValue = 58;   
			green.saturation.maxValue = 255;    
			green.luminance.minValue = 92;  
			green.luminance.maxValue = 255;
			
}

bool Michael1Camera::HSLinThreshold(PixelValue* val, TrackingThreshold* range){
	bool inH = (val->hsl.H >= range->hue.minValue) && (val->hsl.H <= range->hue.maxValue);
	bool inS = (val->hsl.S >= range->saturation.minValue) && (val->hsl.S <= range->saturation.maxValue);
	bool inL = (val->hsl.L >= range->luminance.minValue) && (val->hsl.L <= range->luminance.maxValue);
	return (inH && inS && inL);
}

#define COL_PERCENT 0.5
void Michael1Camera::UpdateCols(){
	pixel = new Point();
	value = new PixelValue();
	for(int col = 0; col < IMG_WIDTH; col++){
		int matches = 0;
		int upper = QUL - ( abs(QUL - QUR) * col/IMG_WIDTH );
		int lower = QLL - ( abs(QLL - QLR) * col/IMG_WIDTH );
		for (int row = lower; row < upper; row++){
			pixel->x = col;
			pixel->y = row;
			frcGetPixelValue(img, *pixel, value);
			if (HSLinThreshold(value, &pink))
				matches++;
		}
		cols[col] = matches / abs(upper-lower) > COL_PERCENT;
	}
	delete(pixel);
	delete(value);
}

#define REQUIRED_CONFIDENCE 0.5
int Michael1Camera::ReturnZone(){
	if (SegmentConfidence(0,150) > REQUIRED_CONFIDENCE)
		return 0;
	if (SegmentConfidence(151,200) > REQUIRED_CONFIDENCE)
		return 1;
	if (SegmentConfidence(201,300) > REQUIRED_CONFIDENCE)
		return 2;
	if (SegmentConfidence(301,310) > REQUIRED_CONFIDENCE)
		return 3;
	if (SegmentConfidence(311,319) > REQUIRED_CONFIDENCE)
		return 4;
	return -1;
}

float Michael1Camera::SegmentConfidence(int l, int r){
	int hits = 0;
	for (int i = l; i <= r; i++){
		if (cols[i])
			hits++;
	}
	return hits/(r - l);
}
/*

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
	if(FindTwoColors(td1, td2, ABOVE, &par1))
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
	return 0; 
}
*/
