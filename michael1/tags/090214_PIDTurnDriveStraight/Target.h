/********************************************************************************
*  Project   		: FIRST Motor Controller
*  File Name  		: Target.h          
*  Contributors   	: ELF
*  Creation Date 	: January 12, 2008
*  Revision History	: Source code & revision history maintained at sourceforge.WPI.edu    
*  File Description	: Globally defined values for the FIRST Vision API
*/
/*----------------------------------------------------------------------------*/
/*        Copyright (c) FIRST 2008.  All Rights Reserved.                     */
/*  Open Source Software - may be modified and shared by FRC teams. The code  */
/*  must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib. */
/*----------------------------------------------------------------------------*/

#ifndef __TARGET_H__
#define __TARGET_H__

#include "TrackAPI.h"

/*  Constants */
/* 
 * If you want to change these settings, test with 
 * GREEN in several different light settings. Remember
 * there may be more glare on the field which could
 * cause failure to recognize the whole target.
 */
/** In order to report a color particle it must have this
 * number of pixels or more. Because the color parameters
 * are set fairly wide to ensure recognition in different
 * light settings, it is common to pick up random pixels
 * of similar colors in the enviornment. This parameter
 * reduces the number of very small particles processed.
 */
#define FRC_MINIMUM_PIXELS_FOR_TARGET 5

/** Scaling factor for determining alignment of target colors 
 * to ensure one target is exactly above the other, use a
 * smaller number. However, light shining directly on the
 * target causes significant variation, so this parameter
 * is best left fairly high. */
#define FRC_ALIGNMENT_SCALE 3.0

/** Tolerance for two-color target color separation (# pixels) 
 * this is loose enough for any image size but could be tightened 
 * (reduced) to reduce false alarms
 */
#define FRC_MAX_IMAGE_SEPARATION 20

/** Tolerance for two-color target particle size (factor) 
 * keep this relatively large so that differences in color or light
 * do not affect target recognition */
#define FRC_SIZE_FACTOR 3

/** Maximum number of color particles to find */
#define FRC_MAX_HITS 10

/** Image quality requirement: particle must be this % of pixels
 * For instance, a 320x240 image has 76800 pixels. With this 
 * tolerance at .001, the image must be 77 pixels.
 * Uses a percentage instead of a fixed # of pixels so different
 * image sizes will work the same way */
#define FRC_COLOR_TO_IMAGE_PERCENT 0.001

/*  Structures */
/** This structure holds information about the particles found 
 * of a particular color */
typedef struct ImageHits_struct {
	int numberOfHits;
	int indices[FRC_MAX_HITS];
	double areas[FRC_MAX_HITS];
	ParticleAnalysisReport pars[FRC_MAX_HITS];
} ImageHits;		
		
/*  Enumerated Types */
/** Position of the second color related to the first color */
enum SecondColorPosition {ABOVE, BELOW, RIGHT, LEFT};
	
/* color tracking support functions */
int FindTwoColors(TrackingThreshold td1, TrackingThreshold td2, 
		SecondColorPosition position, ParticleAnalysisReport *trackReport);
int FindTwoColors(TrackingThreshold td1, TrackingThreshold td2, 
		SecondColorPosition position, ParticleAnalysisReport *trackReport,int numberHits);
void PrintReport(ImageHits* myReport);

#endif

