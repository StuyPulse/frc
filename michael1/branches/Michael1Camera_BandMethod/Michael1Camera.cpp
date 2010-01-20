#include "Michael1Camera.h"


Michael1Camera::Michael1Camera(bool serv) : StuyCamera(serv)
{
	
	// PINK
	
}



/*

#define COL_PERCENT 0.5
void Michael1Camera::UpdateCols(){
	pixel = new Point();
	for(int col = 0; col < IMG_WIDTH; col++){
		int matches = 0;
		int upper = QUL - ( abs(QUL - QUR) * col/IMG_WIDTH );
		int lower = QLL - ( abs(QLL - QLR) * col/IMG_WIDTH );
		for (int row = lower; row < upper; row++){
			pixel->x = col;
			pixel->y = row;
			frcGetPixelValue(img, *pixel, pixel_value_scratch);
			if (HSLinThreshold(pixel_value_scratch, &pink))
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
*/
