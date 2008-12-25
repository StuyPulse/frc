/********************************************************************************
*  Project   		: FIRST Motor Controller
*  File Name  		: BaeUtilities.h          
*  Contributors   	: JDG, ELF
*  Creation Date 	: August 12, 2008
*  Revision History	: Source code & revision history maintained at sourceforge.WPI.edu      
*  File Description	: Globally defined values for utilities
*/
/*----------------------------------------------------------------------------*/
/*        Copyright (c) FIRST 2008.  All Rights Reserved.                     */
/*     Open Source Software - may be modified and shared by FRC teams.        */
/*   Must be accompanied by the BSD license file in $(WIND_BASE)/WPILib.      */
/*----------------------------------------------------------------------------*/

#ifndef __BAEUTILITIES_H__
#define __BAEUTILITIES_H__

/*  Constants */

#define LOG_DEBUG    __FILE__,funcName,__LINE__,DEBUG_TYPE
#define LOG_INFO     __FILE__,funcName,__LINE__,INFO_TYPE
#define LOG_ERROR    __FILE__,funcName,__LINE__,ERROR_TYPE
#define LOG_CRITICAL __FILE__,funcName,__LINE__,CRITICAL_TYPE
#define LOG_FATAL    __FILE__,funcName,__LINE__,FATAL_TYPE
#define LOG_DEBUG    __FILE__,funcName,__LINE__,DEBUG_TYPE

/* Error Codes */
#define ERR_VISION_GENERAL_ERROR			166000	// 
#define ERR_COLOR_NOT_FOUND					166100	// frcvtrack.cpp
#define ERR_PARTICLE_TOO_SMALL				166101	// frcvtrack.cpp

#define ERR_CAMERA_FAILURE					166200	// frcAxis.cpp
#define ERR_CAMERA_SOCKET_CREATE_FAILED		166201	// frcAxis.cpp
#define ERR_CAMERA_CONNECT_FAILED			166202	// frcAxis.cpp
#define ERR_CAMERA_STALE_IMAGE				166203	// frcAxis.cpp
#define ERR_CAMERA_NOT_INITIALIZED			166204	// frcAxis.cpp
#define ERR_CAMERA_NO_BUFFER_AVAILABLE		166205	// frcAxis.cpp
#define ERR_CAMERA_HEADER_ERROR				166206	// frcAxis.cpp
#define ERR_CAMERA_BLOCKING_TIMEOUT			166207	// frcAxis.cpp
#define ERR_CAMERA_AUTHORIZATION_FAILED		166208	// frcAxis.cpp
#define ERR_CAMERA_TASK_SPAWN_FAILED		166209	// frcAxis.cpp
#define ERR_CAMERA_TASK_INPUT_OUT_OF_RANGE	166210	// frcAxis.cpp

/*   Enumerated Types */

/** debug levels */
enum dprint_type {DEBUG_TYPE, INFO_TYPE, ERROR_TYPE, CRITICAL_TYPE, FATAL_TYPE};

/** debug output setting */
typedef enum DebugOutputType_enum { 
	DEBUG_OFF, DEBUG_MOSTLY_OFF, DEBUG_SCREEN_ONLY, DEBUG_FILE_ONLY, DEBUG_SCREEN_AND_FILE
}DebugOutputType;

/*  Enumerated Types */

/* Utility functions */

/* debug */
void SetDebugFlag ( DebugOutputType flag  ); 
void dprintf ( char * tempString, ...  );  /* Variable argument list */

/* set FRC ranges for drive */
double RangeToNormalized(double pixel, int range);
/* change normalized value to any range - used for servo */
float NormalizeToRange(float normalizedValue, float minRange, float maxRange);
float NormalizeToRange(float normalizedValue);

/* system utilities */
double GetTime ( void  );
double ElapsedTime ( double startTime  ); 
void SleepSec ( double sleepTime );
void ShowActivity (char *fmt, ...);
double SinPosition (double *period, double sinStart);

#endif

