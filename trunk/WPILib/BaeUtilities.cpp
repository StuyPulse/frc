/********************************************************************************
*  Project   		: FIRST Motor Controller
*  File Name  		: BaeUtilities.cpp        
*  Contributors   	: JDG, ELF
*  Creation Date 	: July 20, 2008
*  Revision History	: Source code & revision history maintained at sourceforge.WPI.edu    
*  File Description	: Open source utility extensions for FIRST Vision API.
*/                            
/*----------------------------------------------------------------------------*/
/*        Copyright (c) FIRST 2008.  All Rights Reserved.                     */
/*  Open Source Software - may be modified and shared by FRC teams. The code  */
/*  must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib. */
/*----------------------------------------------------------------------------*/

#include "math.h"
#include "stdioLib.h" 
#include "string.h"
#include "sysLib.h" // for sysClkRateGet
#include "time.h"
#include "usrLib.h" // for taskDelay
 
#include "BaeUtilities.h"

/**
 *   Utility functions for frcvision
 */

/**
 * debug output flag options:
 * DEBUG_OFF, DEBUG_MOSTLY_OFF, DEBUG_SCREEN_ONLY, DEBUG_FILE_ONLY, DEBUG_SCREEN_AND_FILE
 */
static DebugOutputType	dprintfFlag = DEBUG_OFF;  


/**
 * Set the debug flag to print to screen, file on cRIO, both or neither
 * @param tempString The format string.
 */
void SetDebugFlag ( DebugOutputType flag  )  
{ dprintfFlag = flag; }


/**
 * Debug print to a file and/or a terminal window.
 * Call like you would call printf.
 * Set functionName in the function if you want the correct function name to print out.
 * The file line number will also be printed.
 * @param tempString The format string.
 */
void dprintf ( char * tempString, ...  )  /* Variable argument list */
{
  va_list	args;			  /* Input argument list */
  int		line_number;      /* Line number passed in argument */
  int		type;
  char		*functionName;    /* Format passed in argument */
  char		*fmt;             /* Format passed in argument */
  char		text[512];   	  /* Text string */
  char		outtext[512];     /* Text string */
  FILE		*outfile_fd;      /* Output file pointer */
  char		filepath[128];    /* Text string */
  int		fatalFlag=0;
  char		*filename;
  int		index;
  int		tempStringLen;

  if (dprintfFlag == DEBUG_OFF) { return; }
  
  va_start (args, tempString);
  
  tempStringLen = strlen(tempString);
  filename = tempString;
  for (index=0;index<tempStringLen;index++){
	  if (tempString[index] == ' ') {
		  printf( "ERROR in dprintf: malformed calling sequence (%s)\n",tempString);return;
	  	}
	  if (tempString[index] == '\\' || tempString[index] == '/')
		  filename = tempString + index + 1;
  }
  
  /* Extract function name */
  functionName = va_arg (args, char *);
 
 /* Extract line number from argument list */
  line_number = va_arg (args, int);

 /* Extract information type from argument list */
  type = va_arg (args, int);

 /* Extract format from argument list */
  fmt = va_arg (args, char *);

  vsprintf (text, fmt, args);

  va_end (args);

  /* Format output statement */
  switch (type)
   {
   case DEBUG_TYPE:
     sprintf (outtext, "[%s:%s@%04d] DEBUG %s\n",
              filename, functionName, line_number, text);
     break;
   case INFO_TYPE:
     sprintf (outtext, "[%s:%s@%04d] INFO %s\n",
              filename, functionName, line_number, text);
     break;
   case ERROR_TYPE:
     sprintf (outtext, "[%s:%s@%04d] ERROR %s\n",
              filename, functionName, line_number, text);
     break;
   case CRITICAL_TYPE:
     sprintf (outtext, "[%s:%s@%04d] CRITICAL %s\n",
              filename, functionName, line_number, text);
     break;
   case FATAL_TYPE:
     fatalFlag = 1;
     sprintf (outtext, "[%s:%s@%04d] FATAL %s\n",
              filename, functionName, line_number, text);
     break;
   default:
     printf( "ERROR in dprintf: malformed calling sequence\n");
     return;
     break;
   }

  sprintf (filepath, "%s.debug", filename);

  /* Write output statement */
  switch (dprintfFlag)
  {
  default:
  case DEBUG_OFF: 
  	break;
  case DEBUG_MOSTLY_OFF: 
  	if (fatalFlag)	{
	  if ((outfile_fd = fopen (filepath, "a+")) != NULL)	  {
	    fwrite (outtext, sizeof (char), strlen (outtext), outfile_fd);
	    fclose (outfile_fd);
	  }
	}
  	break;
  case DEBUG_SCREEN_ONLY: 
  	printf ("%s", outtext);
  	break;
  case DEBUG_FILE_ONLY: 
	if ((outfile_fd = fopen (filepath, "a+")) != NULL)	{
	  fwrite (outtext, sizeof (char), strlen (outtext), outfile_fd);
	  fclose (outfile_fd);
	}
  	break;
  case DEBUG_SCREEN_AND_FILE: // BOTH
  	printf ("%s", outtext);
	if ((outfile_fd = fopen (filepath, "a+")) != NULL)	{
	  fwrite (outtext, sizeof (char), strlen (outtext), outfile_fd);
	  fclose (outfile_fd);
	}
  	break;
  }
}


/**
 * @brief Normalizes a value in a range, used for drive input
 * @param position The position in the range, starting at 0
 * @param range The size of the range that position is in
 * @return The normalized position from -1 to +1
 */
double RangeToNormalized(double position, int range){
	return(((position*2.0)/(double)range)-1.0);
}

/**
 * @brief Convert a normalized value to the corresponding value in a range.
 * This is used to convert normalized values to the servo command range.
 * @param normalizedValue The normalized value (in the -1 to +1 range)
 * @param minRange The minimum of the range (0 is default)
 * @param maxRange The maximum of the range (1 is default)
 * @return The value in the range corresponding to the input normalized value
 */
float NormalizeToRange(float normalizedValue, float minRange, float maxRange) {
	float range = maxRange-minRange;
	float temp = (float)((normalizedValue / 2.0)+ 0.5)*range;
	return (temp + minRange);
}	
float NormalizeToRange(float normalizedValue) {
	return (float)((normalizedValue / 2.0) + 0.5);
}	


/**
 * @brief Gives system time with nanosecond resolution
 * @return The time
*/
double GetTime ( void  )  
{
	struct timespec tp;
	
	clock_gettime(CLOCK_REALTIME,&tp);
	double realTime = (double)tp.tv_sec + (double)((double)tp.tv_nsec*1e-9);
	
	return (realTime);
}

/**
 * @brief Find the elapsed time since a specified time.
 * @param startTime The starting time
 * @return How long it has been since the starting time
 */
double ElapsedTime ( double startTime  )  
{
	double realTime = GetTime();	
	return (realTime-startTime);
}

/**
 * @brief Sleep for the specified time
 * Use instead of "Wait" when when resolution greater than ms needed or when values in seconds are preferred.
 * @param sleepTime the amount of time to sleep (in seconds)
 * @return void
 */
void SleepSec ( double sleepTime )  
{
int ticksPerSec = sysClkRateGet();
int ticksToSleep;

  if (sleepTime <= 0)return;
  
  ticksToSleep = (int)((double)ticksPerSec * sleepTime);
  taskDelay(ticksToSleep);
  
}

/**
 * @brief Displays an activity indicator to console. 
 * Call this function like you would call printf.
 * @param fmt The format string
*/
void ShowActivity (char *fmt, ...)
{
  static char   activity_indication_string[] = "|/-\\";
  static int    ai = 3;
  va_list       args;
  char          text[1024];

  va_start (args, fmt);

  vsprintf (text, fmt, args);

  ai = ai == 3 ? 0 : ai + 1;

  printf ("%c %s \r", activity_indication_string[ai], text);
  fflush (stdout);

  va_end (args);
}


#define PI 3.14159265358979
/**
 * @brief Calculate sine wave increments (-1.0 to 1.0). 
 * The first time this is called, it sets up the time increment. Subsequent calls
 * will give values along the sine wave depending on current time. If the wave is
 * stopped and restarted, it must be reinitialized with a new "first call".
 * 
 * @param period length of time to complete a complete wave
 * @param sinStart Where to start the sine wave (0.0 = 2 pi, pi/2 = 1.0, etc.)
 */
double SinPosition (double *period, double sinStart)
{
  double rtnVal;
  static int increment=-1;
  static int synchronized=0;
  static double sinePeriod=0.0;
  static double timestamp;
  static double factor;
  double sinArg;

  if (period != NULL) {
    increment = -1;
    synchronized = 0;
    sinePeriod = *period;
    if (sinePeriod <= 0.0) sinePeriod = 1.0;
  }

  if (increment == -1) {
    if (synchronized == 0) {
      synchronized = 1;
      timestamp = GetTime();
      return (0.0);
    } else {
      factor = (PI * 2.0 * ((GetTime()) - timestamp)) / sinePeriod;
      increment = 0;
    }
  }
  sinArg = (double)(increment++) * factor;
  sinArg += sinStart;
  rtnVal = sin (sinArg);  
  return (rtnVal);

}


