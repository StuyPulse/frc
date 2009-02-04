/********************************************************************************
*  Project   		: FIRST Motor Controller
*  File Name  		: Target.cpp        
*  Contributors   	: ELF, DWD, EMF
*  Creation Date 	: January 12, 2008
*  Revision History	: Source code & revision history maintained at sourceforge.WPI.edu   
*  File Description	: Tracking Routines for FIRST Vision API
*/ 
/*----------------------------------------------------------------------------*/
/*        Copyright (c) FIRST 2008.  All Rights Reserved.                     */
/*  Open Source Software - may be modified and shared by FRC teams. The code  */
/*  must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib. */
/*----------------------------------------------------------------------------*/

#include "string.h"
#include "vxWorks.h" 

#include "AxisCamera.h" 
#include "FrcError.h"
#include "Target.h" 
#include "Utility.h" 

int Target_debugFlag = 0;
#define DPRINTF if(Target_debugFlag)dprintf

struct HitNode {
	int nodeIndex;
	double nodeArea;
	HitNode* next;
	HitNode(int newIndex = -1, double newArea = 0) {
		nodeIndex = newIndex;
		nodeArea = newArea;
		next = NULL;
	}
	void printNode() {
		DPRINTF(LOG_DEBUG, "~!~ index=%i ~!~ nodeArea=%g ", nodeIndex, nodeArea);
	}
};
struct HitList {
	HitNode *head;
	HitList() {
		head = NULL;
	}
	~HitList() {
		if(head == NULL)
			return;
		if(head->next == NULL) {
			delete head;
			return;
		}
		HitNode *toDelete = head;
		HitNode *temp = head->next;
		while(temp != NULL) {
			delete toDelete;
			toDelete = temp;
			temp = temp->next;
		}
		delete toDelete;
		return;
	}
	int AddNode(int index, double area) {
		if (head == NULL) {
			head = new HitNode(index, area);
		} else {
			//create the new node now
			HitNode *insert = new HitNode(index,area);
			//check to see if this should go before head
			if(area > head->nodeArea) {
				insert->next = head;
				head = insert;
				return 1;
			}
			//a temporary pointer to keep position
			HitNode *current = head;
			//loop until we find where we need to insert new node
			while(current->nodeArea > area) {
				//reached end of list
				if(current->next == NULL) {
					current->next = insert;
					return 1;
				}
				//found position to insert the new node
				else if(current->next->nodeArea < area) {
					insert->next = current->next;
					current->next = insert;
					return 1;
				}
				//did not find position, advance the pointer
				else {
					current = current->next;
				}
			}
		}
		return 0;
	}
	void debugDump() {
		if (head == NULL) {
			DPRINTF(LOG_DEBUG, "~~no entries in HitList");
		} else {
			DPRINTF(LOG_DEBUG, "~~HitList:");
			HitNode *toPrint = head;
			//HitNode *temp = head;
			while(toPrint != NULL) {
				toPrint->printNode();
				toPrint = toPrint->next;
			}
			DPRINTF(LOG_DEBUG, "~~end of HitList");
		}
	}
};


/**
 * NOTE: This is included temporarily until the updated WPILib 
 * is released with the proper headers and immplmentation for 
 * this method. It will be in TrackAPI.cpp.
 * 
* @brief Find the largest particle that meets a criteria 
* @param binaryImage Image to inspect
* @param rect area to search
* @return 0 = error
*/
bool TempInArea(Image* binaryImage, int particleIndex, Rect rect)
{ 
	char funcName[]="InArea";
	double position;
	
	imaqMeasureParticle(binaryImage, particleIndex, 0, 
			IMAQ_MT_BOUNDING_RECT_LEFT, &position);
	if ( position < (rect.left             ) ) return false; // outside left of rectangle?
	
	imaqMeasureParticle(binaryImage, particleIndex, 0, 
			IMAQ_MT_BOUNDING_RECT_TOP, &position);
	if ( position < (rect.top              ) ) return false; // outside top of rectangle ?

	imaqMeasureParticle(binaryImage, particleIndex, 0, 
			IMAQ_MT_BOUNDING_RECT_RIGHT, &position);
	if (position > (rect.left + rect.width) ) return false;	// outside right of rectangle ?
	
	imaqMeasureParticle(binaryImage, particleIndex, 0, 
			IMAQ_MT_BOUNDING_RECT_BOTTOM, &position);
	if (position > (rect.top + rect.height) ) return false; // outside bottom of rectangle ?	

	DPRINTF(LOG_INFO, "particle %i is in (%i %i) height %i width %i\n", 
			particleIndex, rect.left, rect.top, rect.height, rect.width);
	return true; 
}


/**
* @brief Find the largest particles that meet a criteria 
* @param binaryImage Image to inspect
* @param hitReport structure containing arry of hits - first hit is largest 
* @param rect area to search
* @param numParticles Number of particles in array
* @return 0 = error
*/
int GetLargestParticles(Image* binaryImage, ImageHits *hitReport, Rect rect,
		int numberHitsRequested)
{	
	//char funcName[]="GetLargestParticles";
	HitList *hitsInArea = new HitList();  // list to contain all particles within area sorted by size
	int i;
	
	/* determine number of particles in thresholded image */	
	int numParticles = -1;
	int success = frcCountParticles(binaryImage, &numParticles);
	if ( !success )	{ return success; }	
	//DPRINTF(LOG_DEBUG, "particles requested = %i ; particles found in image = %i", numberHitsRequested, numParticles);	
	
	/* if no particles found we can quit here */
	if (numParticles <= 0)  {  return 1; 	}  // successful, but zero particles found

	/* get areas of each particle and insert into list */
	double particleArea;
	int count = 0;
	for (i = 0; i < numParticles; ++i) {		
		success = imaqMeasureParticle(binaryImage, i, 0, IMAQ_MT_AREA, &particleArea);
		if ( !success )	{ return success; }	
		//DPRINTF (LOG_INFO, "size of particle %i = %g", i, particleArea);
		// see if is in the right area and large enough to be considered a possible target
		
		//TODO: Call InArea & delete TempInArea when new WPILib is released
		//if (InArea(binaryImage, i, rect)) {
		//if ( InArea(binaryImage, i, rect) && (particleArea >= FRC_MINIMUM_PIXELS_FOR_TARGET) ) {
		if ( TempInArea(binaryImage, i, rect) && (particleArea >= FRC_MINIMUM_PIXELS_FOR_TARGET) ) {
			hitsInArea->AddNode(i,particleArea);
			count++;
		}
	}
	// see what's in the list 
	hitsInArea->debugDump();
	
	// fill in return structure - number of hits
	if (numParticles < numberHitsRequested) {
		hitReport->numberOfHits = numParticles;		
	} else {
		hitReport->numberOfHits = numberHitsRequested;		
	}
	
	// fill in return structure - indices & areas of largest hits
	HitNode *hitPtr = hitsInArea->head;	
	for (i = 0; i < hitReport->numberOfHits; ++i) {	
		if (hitPtr == NULL) {
			break;
		}
		hitReport->indices[i] = hitPtr->nodeIndex;
		hitReport->areas[i] = hitPtr->nodeArea;
		//DPRINTF (LOG_INFO, "put index %i in hitReport %i", hitPtr->nodeIndex, hitReport->indices[i]);
		hitPtr = hitPtr->next;
	}	
	// dispose of HitList 
	delete hitsInArea;		
	return 1;  // success
}

/**
* @brief Search for color particles. Supports IMAQ_IMAGE_HSL and IMAQ_IMAGE_RGB. 
* @param mode Color mode, either IMAQ_HSL or IMAQ_RGB
* @param plane1Range The range for the first plane (hue or red)
* @param plane2Range The range for the second plane (saturation or green)
* @param plane3Range The range for the third plane (luminance or blue)
* @param hitReport Contains array of numberHits largest targets
* @param rect Rectangle to confine search to
* @param numberHitsRequested maximum number to return
* @return 0 = error
*/
int FindColorHits(ColorMode mode, const Range* plane1Range, const Range* plane2Range, 
		const Range* plane3Range, ImageHits* hitReport, Rect rect, 
		int numberHitsRequested)
{
	char funcName[]="FindColorHits";
	int errorCode = 0;
	int success = 0;
	/* fixed limit to number of hits processed
	 * larger # takes more processing time but can eliminate failure due to 
	 * interference for instance, a red or green area in the stands or 
	 * closer targets of the wrong alliance
	*/
	if (numberHitsRequested > FRC_MAX_HITS)  numberHitsRequested = FRC_MAX_HITS;
			
	/* create an image object */
	Image* cameraImage = frcCreateImage(IMAQ_IMAGE_HSL);
	if (!cameraImage)  { return success; }

	/* get image from camera - if the camera has not finished initializing,
	 * this will fail */
	success = GetImage(cameraImage,NULL);
	if (!success){
		DPRINTF(LOG_INFO, "No camera Image available Error = %i %s", 
				errorCode, GetVisionErrorText(errorCode));
		frcDispose(cameraImage); 
		imaqSetError(errorCode, funcName);	//reset error code for the caller	
		return success;		
	}	

	/* Color threshold the image */
	success = frcColorThreshold(cameraImage, cameraImage, mode, plane1Range, plane2Range, plane3Range);
	if ( !success )	{ 
		errorCode = GetLastVisionError(); 
		DPRINTF (LOG_DEBUG, "Error = %i  %s ", errorCode, GetVisionErrorText(errorCode));
		frcDispose(funcName,cameraImage,NULL); 
		return success; 
	}	
	/* get largest particles that meet criteria */
	/* GetLargestParticles fills out only the indices in the hitReport */
	success = GetLargestParticles(cameraImage, hitReport, rect, numberHitsRequested);
	if ( !success )	{
		errorCode = GetLastVisionError(); 
		DPRINTF (LOG_DEBUG, "Error after GetLargestParticles=%i  %s ", errorCode, GetVisionErrorText(errorCode));
		frcDispose(funcName,cameraImage,NULL); 
		imaqSetError(ERR_COLOR_NOT_FOUND, funcName);
		return success; 
	}
	if (hitReport->numberOfHits==0) {
		imaqSetError(ERR_COLOR_NOT_FOUND, funcName);
		frcDispose(funcName,cameraImage,NULL); 
		return 0; 
	}
	//DPRINTF(LOG_INFO, "number hits found = %i\n", hitReport->numberOfHits);	
	
	/* Particles were found --
	 * Fill in report information for the largest particles 
	 */	
	double imageTime = GetTime();
	for (int i=0; i<hitReport->numberOfHits; ++i) {
		hitReport->pars[i].imageTimestamp = imageTime;	
		success = frcParticleAnalysis(cameraImage, hitReport->indices[i], &hitReport->pars[i]);
	}
	/* clean up */
	frcDispose(funcName,cameraImage,NULL); 
	
	return success;	
}

/**
* @brief Check if two pixels are vertically or horizontally aligned 
* @param center1 Center pixel of first partical (x for vertical alignment, y for horizontal)
* @param center2 Center pixel of second partical (x for vertical alignment, y for horizontal)
* @param dimension1 of first partical (width for vertical alignment, height for horizontal)
* @param dimension2 of second partical (width for vertical alignment, height for horizontal)
* @return true if aligned vertically or horizontally
*/
bool Aligned(int center1, int center2, int dimension1, int dimension2)
{
	char funcName[]="Aligned";
	float averageWidth = (dimension1 + dimension2) / 2.0;
	//scale down width
	averageWidth *= FRC_ALIGNMENT_SCALE;
	int centerDiff = abs(center1 - center2);
	if (centerDiff < averageWidth) {
		//DPRINTF(LOG_DEBUG,"Aligned Centers: %i %i Widths: %i  %i", center1, center2, dimension1, dimension2);
		return true;	
	}
	//dimensions (widths or heights) should be nearly the same. If they are 
	//different, most likely there is glare or incorrect color specification
	DPRINTF(LOG_DEBUG,"Not Aligned Centers: %i %i Widths: %i  %i", center1, center2, dimension1, dimension2);
	return false;
}

/**
* @brief Check if two values are approximately adjacent
* @param value1 Center pixel of first partical (x for vertical alignment, y for horizontal)
* @param value2 Center pixel of second partical (x for vertical alignment, y for horizontal)
* @return true if particles are within a 5 pixel buffer
*/
bool Adjacent(int value1, int value2)
{
	char funcName[]="Adjacent";
	if ( abs(value1 - value2) <= FRC_MAX_IMAGE_SEPARATION ) return true;
	DPRINTF(LOG_DEBUG,"Not Adjacent  %i  %i", value1, value2);
	return false;
}


/**
* @brief Check if two values are approximately the same size, 
* Make the check loose to allow for differences in light & color recognition
* @param area1 First area
* @param area2 Second area
* @return true if particles size differences are small enough
*/
bool SizesRelative(double area1, double area2)
{
	char funcName[]="SizesRelative";
	if ( (area2 < (area1 * FRC_SIZE_FACTOR)) && (area1 < (area2 * FRC_SIZE_FACTOR)) ) {
		return true;
	}
	DPRINTF(LOG_DEBUG,"Targets too different in size %g  %g", area1, area2);
	return false;
}

							  
/**
 * 
 * 
 * 
* @brief Search for two colors in relation to each other in an Image.
* Supports IMAQ_IMAGE_HSL color mode. 
* @param td1 Tracking data for the first color, including hue, sat, lum
* @param td2 Tracking data for the second color, including hue, sat, lum
* @param position Position of second color in relation to the first:
* 			ABOVE, BELOW, RIGHT or LEFT
* @param trackReport Particle analysis report for the first color (td1) 
* @param numberHits Max number of particles to request of each color
* @return 0 = error
*/

int FindTwoColors(TrackingThreshold td1, TrackingThreshold td2, 
		SecondColorPosition position, ParticleAnalysisReport *trackReport)
{ 	return FindTwoColors(td1, td2, position, trackReport, 3); }

int FindTwoColors(TrackingThreshold td1, TrackingThreshold td2, 
		SecondColorPosition position, ParticleAnalysisReport *trackReport,
		int numberHits)
{
	char funcName[]="FindTwoColors";
	int success;
	
	// create list of color hits
	ImageHits color1Hits;	// define return object
	memset(&color1Hits, 0, sizeof(ImageHits));

	// search for the largest particles of the first color
	// get several particles in case the first one turns out not to be a target
	success = FindColorHits(IMAQ_HSL, 
			&td1.hue, &td1.saturation, &td1.luminance, 
			&color1Hits, IMAQ_NO_RECT, numberHits);	
	if (!success) return success;
	//PrintReport(&color1Hits);
	//DPRINTF(LOG_DEBUG, ">>>>>>>>>>>>>>> found first color: %s particles: %i", td1.name, color1Hits.numberOfHits);

	ImageHits color2Hits;	// define return object
	memset(&color2Hits, 0, sizeof(ImageHits));
	success = FindColorHits(IMAQ_HSL, 
			&td2.hue, &td2.saturation, &td2.luminance, 
			&color2Hits, IMAQ_NO_RECT, numberHits);
	if (!success) return success;
	//PrintReport(&color2Hits);
	//DPRINTF(LOG_DEBUG, ">>>>>>>>>>>>>>> found second color: %s particles: %i\n", td2.name, color2Hits.numberOfHits);

	ParticleAnalysisReport *firstTrackReport;
	ParticleAnalysisReport *secondTrackReport;
		
	// check all 1st color begining with the largest
	double sizeInImage;
	for (int i=0; i<color1Hits.numberOfHits; ++i)  {
		firstTrackReport = &color1Hits.pars[i];
		sizeInImage = firstTrackReport->particleToImagePercent;
		if ( sizeInImage < FRC_COLOR_TO_IMAGE_PERCENT) {
			DPRINTF(LOG_DEBUG,"First target too small: %g", sizeInImage);
			break;
		}
		// check all 2nd color begining with the largest
		DPRINTF(LOG_DEBUG,"\nBEGIN CHECK");
		for (int j=0; j<color2Hits.numberOfHits; ++j)  {
			secondTrackReport = &color2Hits.pars[j];
			sizeInImage = secondTrackReport->particleToImagePercent;
			if (secondTrackReport->particleToImagePercent < FRC_COLOR_TO_IMAGE_PERCENT) {
				DPRINTF(LOG_DEBUG,"Second target too small: %g", sizeInImage);
				break;
			}
			// found both colors. check position.
			switch (position) {
			  case ABOVE: //is second color above first color?
				if (secondTrackReport->center_mass_y < firstTrackReport->center_mass_y) 
					{	
						// add in the SizesRelative call if needed -
						// so far it does not seem necessary
						if ( Aligned(firstTrackReport->center_mass_x,
								secondTrackReport->center_mass_x,
								firstTrackReport->boundingRect.width,	
								secondTrackReport->boundingRect.width) && 
							Adjacent( firstTrackReport->boundingRect.top,
								(secondTrackReport->boundingRect.top + 
								secondTrackReport->boundingRect.height) ) &&
							SizesRelative(firstTrackReport->particleArea, 
								secondTrackReport->particleArea	)  )  
						{	
							//return the relevant track report
							DPRINTF(LOG_DEBUG,"++++++  FOUND +++++");
							memcpy(trackReport, firstTrackReport, sizeof(ParticleAnalysisReport));
							return true;
						}
					}	
				break;
			  case BELOW: //is second color below first color?
				if (secondTrackReport->center_mass_y > firstTrackReport->center_mass_y) 
				{	
					if ( Aligned(firstTrackReport->center_mass_x,
							secondTrackReport->center_mass_x,
							firstTrackReport->boundingRect.width,	
							secondTrackReport->boundingRect.width) &&
						Adjacent( (firstTrackReport->boundingRect.top + 
							firstTrackReport->boundingRect.height),							
							secondTrackReport->boundingRect.top) )  
					{	
						memcpy(trackReport, firstTrackReport, sizeof(ParticleAnalysisReport));
						return true;
					}
				}	
				break;
			  case RIGHT: //is second color to the right of first color?
				if (secondTrackReport->center_mass_x > firstTrackReport->center_mass_x) 
				{	
					if ( Aligned(firstTrackReport->center_mass_y,
							secondTrackReport->center_mass_y,
							firstTrackReport->boundingRect.width,	
							secondTrackReport->boundingRect.width)&&
						Adjacent( (firstTrackReport->boundingRect.left + 
							secondTrackReport->boundingRect.width),
							secondTrackReport->boundingRect.left ) )  
					{	
						memcpy(trackReport, firstTrackReport, sizeof(ParticleAnalysisReport));
						return true;
					}
				}	
				break;
			  case LEFT:  //is second color to the left of first color?
				if (secondTrackReport->center_mass_x < firstTrackReport->center_mass_x) 
				{	
					if ( Aligned(firstTrackReport->center_mass_y,
							secondTrackReport->center_mass_y,
							firstTrackReport->boundingRect.width,	
							secondTrackReport->boundingRect.width) &&
						Adjacent( firstTrackReport->boundingRect.left,
							(secondTrackReport->boundingRect.left + 
							secondTrackReport->boundingRect.width) ) )
					{	
						memcpy(trackReport, firstTrackReport, sizeof(ParticleAnalysisReport));
						return true;
					}
				}	
				break;
			  default:
				DPRINTF(LOG_ERROR, "invalid position parameter");
		  }
		}
	}
	DPRINTF(LOG_DEBUG, "%s size %g and %s size %g NOT IN CORRECT POSITION", td1.name, firstTrackReport->particleArea,
			td2.name, secondTrackReport->particleArea);

	return false;
}

/**
 *   Data functions for tracking
 */

/**
 * Print image hit report
 * @param myReport Report to print
 */
void PrintReport(ImageHits *myReport)
{
	char funcName[]="PrintReport";
	//dprintf(LOG_INFO, "ImageHit Report"); 
	//dprintf(LOG_INFO, "\n    %s%i  \n -------",
	//		"numberOfHits = ", myReport->numberOfHits); 
	dprintf(LOG_INFO, "ImageHit Report: %i hit\(s)      ", myReport->numberOfHits); 
	if (myReport->numberOfHits > 0) {
		for (int i=0; i<myReport->numberOfHits; ++i) {
			dprintf(LOG_INFO, "\n    hit %i  %s%i  %s%g  %s%i    %s%i",
				i, "index = ", myReport->indices[i], 
				"area = ", myReport->areas[i], 
				"center of mass x = ", myReport->pars[i].center_mass_x, 
				"center of mass y = ", myReport->pars[i].center_mass_y ); 
		}
	} else {
		dprintf(LOG_INFO, "\nno luck!");
	}
	dprintf(LOG_INFO, "\n-------\n");
}


