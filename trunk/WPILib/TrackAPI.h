/********************************************************************************
*  Project   		: FIRST Motor Controller
*  File Name  		: TrackAPI.h          
*  Contributors   	: ELF
*  Creation Date 	: August 12, 2008
*  Revision History	: Source code & revision history maintained at sourceforge.WPI.edu    
*  File Description	: Globally defined values for the FIRST Vision API
* 
*  API: Because nivision.h uses C++ style comments, any file including this
*  must be a .cpp (not .c).
*/
/*----------------------------------------------------------------------------*/
/*        Copyright (c) FIRST 2008.  All Rights Reserved.                     */
/*  Open Source Software - may be modified and shared by FRC teams. The code  */
/*  must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib. */
/*----------------------------------------------------------------------------*/

#ifndef __TRACKAPI_H__
#define __TRACKAPI_H__

#include "VisionAPI.h"
#include "BaeUtilities.h"

/*  Structures */
typedef struct TrackingThreshold_struct {
	char name[64];
	Range hue;
	Range saturation;
	Range luminance;
} TrackingThreshold;
		
/*  Enumerated Types */

/** Predefined hues */
typedef enum FrcHue_enum { 
	// Basic colors
	RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, WHITE, PINK
}FrcHue;

/** Predefined saturation / luminance settings */
typedef enum FrcLight_enum { 
	PASSIVE_LIGHT, BRIGHT_LIGHT, ACTIVE_LIGHT, WHITE_LIGHT, FLUORESCENT
}FrcLight;

/* color tracking support functions */
TrackingThreshold GetTrackingData(FrcHue hue, FrcLight light);

void PrintReport(ParticleAnalysisReport* myReport);
void PrintReport(ColorReport* myReport);
void PrintReport(TrackingThreshold* myReport);

/*  Tracking functions */

/* find a color in current camera image */
int FindColor(FrcHue color, ParticleAnalysisReport* trackReport);
int FindColor(const Range* hueRange, ParticleAnalysisReport *trackReport);
int FindColor(const Range* hueRange, int minSaturation, ParticleAnalysisReport *trackReport);
int FindColor(ColorMode mode, const Range* plane1Range, const Range* plane2Range, 
		const Range* plane3Range, ParticleAnalysisReport *trackReport);
int FindColor(ColorMode mode, const Range* plane1Range, const Range* plane2Range, 
		const Range* plane3Range, ParticleAnalysisReport *trackReport, ColorReport *colorReport);


#endif

