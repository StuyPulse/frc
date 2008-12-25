
/********************************************************************************
*  Project   		: FIRST Motor Controller
*  File Name  		: AxisCamera.cpp        
*  Contributors 	: TD, ELF, JDG, SVK
*  Creation Date 	: July 29, 2008
*  Revision History	: Source code & revision history maintained at sourceforge.WPI.edu    
*  File Description	: Axis camera access for the FIRST Vision API
*      The camera task runs as an independent thread 
*/    
/*----------------------------------------------------------------------------*/
/*        Copyright (c) FIRST 2008.  All Rights Reserved.                     */
/*  Open Source Software - may be modified and shared by FRC teams. The code  */
/*  must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib. */
/*----------------------------------------------------------------------------*/                   


#include "sockLib.h" 
#include "vxWorks.h" 

#include "errno.h"
#include "fioLib.h"
#include "hostLib.h" 
#include "inetLib.h" 
#include "signal.h"
#include "sigLib.h"		// for signal
#include <string>
#include "time.h"
#include "usrLib.h"

#include "AxisCamera.h" 
#include "BaeUtilities.h"
#include "FrcError.h"
#include "VisionAPI.h" 

// To locally enable debug printing: set AxisCamera_debugFlag to a 1, to disable set to 0
int AxisCamera_debugFlag = 0;
#define DPRINTF if(AxisCamera_debugFlag)dprintf

/** packet size */
#define DEFAULT_PACKET_SIZE 512
/** port for communicating with camera */
#define CAMERA_PORT 80
/** port for sending video to laptop */
#define VIDEO_TO_PC_PORT 1180
/** how old an image is before it's discarded */
#define CAMERA_IMAGE_STALE_TIME_SEC 2.0  
/** time to wait for a new image in blocking call */
#define MAX_BLOCKING_TIME_SEC 0.5

/* define size of image buffer */

/** @brief Camera data to be accessed globally */
struct {
	int readerPID; // Set to taskID for signaling
	int index; /* -1,0,1 */
	int	acquire; /* 0:STOP CAMERA; 1:START CAMERA */
	int cameraReady;  /* 0: CAMERA NOT INITIALIZED; 1: CAMERA INITIALIZED */
	int	decode; /* 0:disable decoding; 1:enable decoding to HSL Image */
	struct {
		//
		// To find the latest image timestamp, access:
		// globalCamera.data[globalCamera.index].timestamp
		//
		double timestamp;
		char*	cameraImage;
		int cameraImageSize;
		Image* decodedImage;
		int decodedImageSize;
	}data[2];
	int cameraMetrics[CAM_NUM_METRICS];
}globalCamera;

/* run flag */
static short cont = 0;

/**
 * @brief Get the most recent camera image.
 * Supports IMAQ_IMAGE_RGB and IMAQ_IMAGE_HSL.
 * @param image Image to return to; image must have been first created using frcCreateImage. 
 * When you are done, use frcDispose.
 * @param timestamp Timestamp to return to; will record the time at which the image was stored.
 * @param lastImageTimestamp Input - timestamp of last image; prevents serving of stale images
 * @return 0 is failure, 1 is success
 * @sa frcCreateImage(), frcDispose()
 */
int GetImageBlocking(Image* image, double *timestamp, double lastImageTimestamp)
{
	char funcName[]="GetImageBlocking";
	int success;
	double startTime = GetTime();
	
	while (1)
	{
		success = GetImage(image, timestamp);
		if (!success) return (success);
		
		if (*timestamp > lastImageTimestamp)
			return (1); // GOOD IMAGE RETURNED

		if (GetTime() > (startTime + MAX_BLOCKING_TIME_SEC))
		{
			imaqSetError(ERR_CAMERA_BLOCKING_TIMEOUT, funcName);
			globalCamera.cameraMetrics[CAM_BLOCKING_TIMEOUT]++;
			return (0); // NO IMAGE AVAILABLE WITHIN specified time
		}
		globalCamera.cameraMetrics[CAM_BLOCKING_COUNT]++;
		taskDelay (1);
	}
}

/**
 * @brief Verifies that the camera is initialized
 * @return 0 for failure, 1 for success
 */
int CameraInitialized()
{
	int success = 0;
	/* check to see if camera is initialized */
	if (!globalCamera.cameraReady)  {
		imaqSetError(ERR_CAMERA_NOT_INITIALIZED, funcName);
		DPRINTF (LOG_DEBUG, "Camera request before camera is initialized");
		globalCamera.cameraMetrics[CAM_GETIMAGE_BEFORE_INIT]++;
		globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
		return success;
	}
	
	if (globalCamera.index == -1){
		imaqSetError(ERR_CAMERA_NO_BUFFER_AVAILABLE, funcName);
		DPRINTF (LOG_DEBUG, "No camera image available");
		globalCamera.cameraMetrics[CAM_GETIMAGE_BEFORE_AVAILABLE]++;
		globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
		return success;
	}
	return 1;
}

/**
 * @brief Gets the most recent camera image, as long as it is not stale.
 * Supported image types: IMAQ_IMAGE_RGB, IMAQ_IMAGE_HSL
 * @param image Image to return, must have first been created with frcCreateImage or imaqCreate. 
 * When you finish with the image, call frcDispose() to dispose of it.
 * @param timestamp Returned timestamp of when the image was taken from the camera
 * @return failure = 0, success = 1
 */
int GetImage(Image* image, double *timestamp)
{
	char funcName[]="GetImage";
	int success = 0;
	int readIndex;
	int	readCount = 10;
	double currentTime = time(NULL);
	double currentImageTimestamp;

	/* check to see if camera is initialized */
	
	if (!CameraInitialized()) {return success;}
	
	/* try readCount times to get an image */
	while (readCount) {
		readIndex = globalCamera.index;
		if (!imaqDuplicate(image, globalCamera.data[readIndex].decodedImage)) {
			int errorCode = GetLastVisionError(); 
			DPRINTF (LOG_DEBUG,"Error duplicating image= %i  %s ", errorCode, GetVisionErrorText(errorCode));			
		}
		// save the timestamp to check before returning
		currentImageTimestamp = globalCamera.data[readIndex].timestamp;
		
		// make sure this buffer is not being written to now
		if (readIndex == globalCamera.index) break;
		readCount--;
	}
	
	/* were we successful ? */
	if (readCount){
		success = 1;
		if (timestamp != NULL)
			  *timestamp = currentImageTimestamp; // Return image timestamp	  
	} else{
		globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
	}
	
	/* Ensure the buffered image is not too old - set this "stale time" above */
	if (currentTime > globalCamera.data[globalCamera.index].timestamp + CAMERA_IMAGE_STALE_TIME_SEC){
		DPRINTF (LOG_CRITICAL, "STALE camera image (THIS COULD BE A BAD IMAGE)");
		imaqSetError(ERR_CAMERA_STALE_IMAGE, funcName);
		globalCamera.cameraMetrics[CAM_STALE_IMAGE]++;
		globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
		success = 0;
	}
	globalCamera.cameraMetrics[CAM_GETIMAGE_SUCCESS]++;
	return success;
}
#if 0
/**
 * @brief Gets the most recent camera image, as long as it is not stale.
 * Supported image types: IMAQ_IMAGE_RGB, IMAQ_IMAGE_HSL
 * @param image Image to return, must have first been created with frcCreateImage or imaqCreate. 
 * When you finish with the image, call frcDispose() to dispose of it.
 * @param timestamp Returned timestamp of when the image was taken from the camera
 * @return failure = 0, success = 1
 */
int GetRawImageAndDecodeIt(Image* image, double *timestamp)
{
	char funcName[]="GetRawImageAndDecodeIt";
	//int bytesToRead; 
	int errorCode;
	int success = 0;
	int readIndex;
	int	readCount = 10;
	int cameraImageSize;
	char *cameraImageString;
	double currentTime = time(NULL);
	double currentImageTimestamp;

	/* check to see if camera is initialized */
	
	if (!CameraInitialized()) {return success;}
	
	/* try readCount times to get an image */
	while (readCount) {
		readIndex = globalCamera.index;
		cameraImageSize = globalCamera.data[readIndex].cameraImageSize;
		cameraImageString = (char *) malloc(cameraImageSize);
		if (NULL == cameraImageString) {
			DPRINTF (LOG_DEBUG, "Unable to allocate cameraImage");
			globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
			return success;
		}
		memcpy (cameraImageString, globalCamera.data[readIndex].cameraImage, cameraImageSize);
		currentImageTimestamp = globalCamera.data[readIndex].timestamp;
		// make sure this buffer is not being written to now
		if (readIndex == globalCamera.index) break;
		free (cameraImageString);
		readCount--;
	}
	/* write string to image struct */
	if (readCount){
	  success = Priv_ReadJPEGString_C(image, (const unsigned char*)cameraImageString, cameraImageSize);
	  free(cameraImageString);
	  if ( !success )	{ 
		  errorCode = GetLastError(); 
		  globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
	  }
	  if (timestamp != NULL)
		  *timestamp = currentImageTimestamp; // Return image timestamp
	  
	  //DPRINTF (LOG_DEBUG, "Read JPEGString success = %i  readLength = %i", success, cameraImageSize );
	}else{
	  globalCamera.cameraMetrics[CAM_READ_JPEG_FAILURE]++;
	  globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
	  DPRINTF (LOG_DEBUG, "Read JPEGString FAILED");
	}
	
	/* Ensure the buffered image is not too old - set this "stale time" above */
	if (currentTime > globalCamera.data[globalCamera.index].timestamp + CAMERA_IMAGE_STALE_TIME_SEC){
		DPRINTF (LOG_CRITICAL, "STALE camera image (THIS COULD BE A BAD IMAGE)");
		imaqSetError(ERR_CAMERA_STALE_IMAGE, funcName);
		globalCamera.cameraMetrics[CAM_STALE_IMAGE]++;
		globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
		success = 0;
	}
	globalCamera.cameraMetrics[CAM_GETIMAGE_SUCCESS]++;
	return success;
}
#endif

/**
 * @brief Internal method to get a raw image from the buffer
 * @param imageData returned image data
 * @param numBytes returned number of bytes in buffer
 * @param currentImageTimestamp returned buffer time of image data
 * @return 0 if failure; 1 if success
 */
static int GetImageData(char** imageData, int* numBytes, double* currentImageTimestamp)
{
	char funcName[]="GetImageData";
	int success = 0;
	int readIndex;
	int	readCount = 10;
	int cameraImageSize;
	char *cameraImageString;

	/* check to see if camera is initialized */
			
	if (!CameraInitialized()) {return success;}
			
	/* try readCount times to get an image */
	while (readCount) {
		readIndex = globalCamera.index;
		cameraImageSize = globalCamera.data[readIndex].cameraImageSize;
		//cameraImageString = (Image *) malloc(cameraImageSize);
		cameraImageString = new char[cameraImageSize];
		if (NULL == cameraImageString) {
					DPRINTF (LOG_DEBUG, "Unable to allocate cameraImage");
					globalCamera.cameraMetrics[CAM_GETIMAGE_FAILURE]++;
					return success;
		}
		memcpy (cameraImageString, globalCamera.data[readIndex].cameraImage, cameraImageSize);
		*currentImageTimestamp = globalCamera.data[readIndex].timestamp;
		// make sure this buffer is not being written to now
		if (readIndex == globalCamera.index) break;
		free (cameraImageString);
		readCount--;
	}
	if (readCount){
		*imageData = cameraImageString;
		*numBytes = cameraImageSize;
		return 1;
	}		
	return (OK);
}

/**
 * @brief Blocking call to get images for PC.
 * This should be called from a separate task to maintain camera read performance. 
 * It is intended to be used for sending raw (undecoded) image data to the PC.
 * @param imageData image data to return
 * @param numBytes number of bytes in buffer
 * @param timestamp timestamp of buffer returned
 * @param lastImageTimestamp buffer time of last image data sent to PC
 */
int GetImageDataBlocking(char** imageData, int* numBytes, double* timestamp, double lastImageTimestamp)
{

	//char funcName[]="GetImageDataBlocking";
	int success;
	double startTime = GetTime();
	
    *imageData = NULL;
	while (1)
	{
		success = GetImageData(imageData, numBytes, timestamp);
		if (!success) return (success);
		
		if (*timestamp > lastImageTimestamp)
			return (1); // GOOD IMAGE DATA RETURNED

        delete *imageData;
        *imageData = NULL;

		if (GetTime() > (startTime + MAX_BLOCKING_TIME_SEC))
		{
			imaqSetError(ERR_CAMERA_BLOCKING_TIMEOUT, funcName);
			return (0); // NO IMAGE AVAILABLE WITHIN specified time
		}
		globalCamera.cameraMetrics[CAM_BLOCKING_COUNT]++;
		taskDelay (1);
	}
}

/**
 * @brief Accessor for camera instrumentation data
 * @param the counter queried
 * @return the counter value
 */
int GetCameraMetric(FrcvCameraMetric metric)
{	return globalCamera.cameraMetrics[metric];  }

/**
 * @brief Close socket & report error
 * @param errstring String to print
 * @param socket Socket to close
 * @return error
 */
int cameraCloseSocket(char *errstring, int socket)
{
	char funcName[]="cameraCloseSocket";
	DPRINTF (LOG_CRITICAL, "CAMERA ERROR: %s", errstring );
	close (socket);
	return (ERROR);
}

#define MEASURE_SOCKET_TIME 1   

/**
 * @brief Manage access to the camera. Sets up sockets and reads images
 * @return error
 */
int cameraJPEGServer(int frames, int compression, ImageSize resolution, ImageRotation rotation)
{
	char funcName[]="cameraJPEGServer";
	char *serverName = "192.168.0.90";		/* camera @ */ 
	cont = 1;
	int errorCode = 0;
	int printCounter = 0;
	int	writeIndex;
	int authorizeCount = 0;
	int authorizeConfirmed = 0;
	static const int authenticationStringsCount = 3;
    static const char* authenticationStrings[] = {
    		"cm9vdDphZG1pbg==", /* root, admin*/
    		"RlJDOkZSQw==",     /* FRC, FRC */
    		"cm9vdDpwYXNz=="    /* root, pass*/
    };

	DPRINTF (LOG_DEBUG, "cameraJPEGServer" ); 
	
	struct sockaddr_in cameraAddr;
	int sockAddrSize;  
	int camSock = 0;    

	char resStr[10];
	switch (resolution) {
		case k640x480: { sprintf(resStr,"640x480"); break; }
		case k320x240: { sprintf(resStr,"320x240"); break; }
		case k160x120: { sprintf(resStr,"160x120"); break; }
		default: {DPRINTF (LOG_DEBUG, "code error - resolution input" ); break; }
	}
	
	/* Generate camera initialization string */
	/* changed resolution to 160x120 from 320x240 */
	/* supported resolutions are: 640x480, 640x360, 320x240, 160x120 */	
	char * getStr1 = 
	"GET /axis-cgi/mjpg/video.cgi?showlength=1&camera=1&";	
		
	char insertStr[100];
	sprintf (insertStr, "des_fps=%i&compression=%i&resolution=%s&rotation=%i", 
			frames, compression, resStr, (int)rotation);	
	
	char * getStr2 = " HTTP/1.1\n\
User-Agent: HTTPStreamClient\n\
Host: 192.150.1.100\n\
Connection: Keep-Alive\n\
Cache-Control: no-cache\n\
Authorization: Basic %s;\n\n";		

	char getStr[strlen(getStr1) + strlen(insertStr) + strlen(getStr2)];      
    sprintf (getStr, "%s:%s%s",	getStr1, insertStr, getStr2);

	DPRINTF(LOG_DEBUG, "revised camera string: \n%s", getStr);
	/* Allocation */
	char tempBuffer[1024];
    
	RETRY:
	while (globalCamera.acquire == 0) SleepSec(0.5);

	if (!authorizeConfirmed){
	  if (authorizeCount < authenticationStringsCount){
	    sprintf (tempBuffer, getStr, authenticationStrings[authorizeCount]);
	  } else {
		imaqSetError(ERR_CAMERA_AUTHORIZATION_FAILED, funcName);
		perror ("Camera authorization failed ... Incorrect password on camera!!");
		return (ERROR);
	  }
	}

	while (1)
	{
	  globalCamera.cameraMetrics[CAM_SOCKET_INIT_ATTEMPTS]++;	  

	  /* create camera socket */
	  DPRINTF (LOG_DEBUG, "creating camSock" ); 
	  if ((camSock = socket (AF_INET, SOCK_STREAM, 0)) == ERROR) {	
		imaqSetError(ERR_CAMERA_SOCKET_CREATE_FAILED, funcName);
		perror ("Failed to create socket");
		cont = 0;
		return (ERROR);
	  }

	  sockAddrSize = sizeof (struct sockaddr_in);
	  bzero ((char *) &cameraAddr, sockAddrSize);
	  cameraAddr.sin_family = AF_INET;
	  cameraAddr.sin_len = (u_char) sockAddrSize;
	  cameraAddr.sin_port = htons (CAMERA_PORT);

	  DPRINTF (LOG_DEBUG, "getting IP" );
	  if (( (int)(cameraAddr.sin_addr.s_addr = inet_addr (serverName) ) == ERROR) &&
		( (int)(cameraAddr.sin_addr.s_addr = hostGetByName (serverName) ) == ERROR)) 
	  {	
		cameraCloseSocket("Failed to get IP, check hostname or IP", camSock);
		continue;
	  }
	  
	  DPRINTF (LOG_INFO, "Attempting to connect to camSock" ); 
	  if (connect (camSock, (struct sockaddr *) &cameraAddr, sockAddrSize) == ERROR) 	{
		imaqSetError(ERR_CAMERA_CONNECT_FAILED, funcName);
		cameraCloseSocket("Failed to connect to camera - check network", camSock);
		continue;
	  }	  

#if MEASURE_SOCKET_SETUP
	  socketEndTime = GetTime(); 
	  setupTime = socketEndTime - socketStartTime; 
	  printf("\n***socket setup time = %g\n", setupTime );
#endif	  
	  
	  globalCamera.cameraMetrics[CAM_SOCKET_OPEN]++;
	  break;
	} // end while (trying to connect to camera)

	DPRINTF (LOG_DEBUG, "writing GET request to camSock" ); 
	if (write (camSock, tempBuffer , strlen(tempBuffer) ) == ERROR) {
		return cameraCloseSocket("Failed to send GET request", camSock);
	}

	//DPRINTF (LOG_DEBUG, "reading header" ); 
	/* Find content-length, then read that many bytes */
	int counter = 2;
	char* contentString = "Content-Length: ";
	char* authorizeString = "200 OK";
	
#define MEASURE_TIME 0
#if MEASURE_TIME
	//timing parameters - only measure one at the time
	double loopStartTime = 0.0; // measuring speed of execution loop
	double loopEndTime = 0.0;
	double cameraStartTime = 0.0;
	double cameraEndTime = 0.0;
	double previousStartTime = 0.0;
	int performanceLoopCounter = 0;
	int maxCount = 30;
#endif
	
	while (cont) {
#if MEASURE_TIME
		previousStartTime = loopStartTime;  // first time is bogus
		loopStartTime = GetTime(); 
#endif	
		// If camera has been turned OFF, jump to RETRY
		//if (globalCamera.acquire == 0) goto RETRY;
		
		/* Determine writer index */
		if (globalCamera.index == 0)
			writeIndex = 1;
		else
			writeIndex = 0;
		
		/* read header */
		//TODO: check for error in header, increment ERR_CAMERA_HEADER_ERROR
		char initialReadBuffer[DEFAULT_PACKET_SIZE] = "";
		char intermediateBuffer[1];
		char *trailingPtr = initialReadBuffer;
		int trailingCounter = 0;
		

#if MEASURE_TIME
		cameraStartTime = GetTime(); 
#endif	

		while (counter) {
			if (read (camSock, intermediateBuffer, 1) <= 0) {
				cameraCloseSocket("Failed to read image header", camSock);
				globalCamera.cameraMetrics[ERR_CAMERA_HEADER_ERROR]++;
				goto RETRY;
			}

			strncat(initialReadBuffer, intermediateBuffer, 1);
			if (NULL != strstr(trailingPtr, "\r\n\r\n")) {

				  if (!authorizeConfirmed){

					  if (strstr(initialReadBuffer, authorizeString))
					  {
						  authorizeConfirmed = 1;
						  /* set camera to initialized */
						  globalCamera.cameraReady = 1; 
					  }
					  else
					  {
						  cameraCloseSocket("Not authorized to connect to camera", camSock);
						  authorizeCount++;
				  goto RETRY;
					  }
				}
				--counter;
			}
			if (++trailingCounter >= 4) {
				trailingPtr++;
			}
		}
	
		counter = 1;
		char *contentLength = strstr(initialReadBuffer, contentString);
		if (contentLength == NULL) {
			globalCamera.cameraMetrics[ERR_CAMERA_HEADER_ERROR]++;
			cameraCloseSocket("No content-length token found in packet", camSock);
			goto RETRY;
		}
		/* get length of image content */
		contentLength = contentLength + strlen(contentString);
		globalCamera.data[writeIndex].cameraImageSize = atol (contentLength);
		
		if(globalCamera.data[writeIndex].cameraImage)
			free(globalCamera.data[writeIndex].cameraImage);
		//globalCamera.data[writeIndex].cameraImage = (Image *) malloc(globalCamera.data[writeIndex].cameraImageSize);
		globalCamera.data[writeIndex].cameraImage = (char*)malloc(globalCamera.data[writeIndex].cameraImageSize);
		if (NULL == globalCamera.data[writeIndex].cameraImage) {
			return cameraCloseSocket("Failed to allocate space for imageString", camSock);
		}
		globalCamera.cameraMetrics[CAM_BUFFERS_WRITTEN]++;
		
		//
		// This is a blocking camera read function, and will block if the camera
		// has been disconnected from the cRIO.  If however the camera is
		// POWERED OFF while connected to the cRIO, this function NEVER RETURNS
		//
		int bytesRead = fioRead (camSock, (char *)globalCamera.data[writeIndex].cameraImage,
				globalCamera.data[writeIndex].cameraImageSize);

#if MEASURE_TIME
		cameraEndTime = GetTime(); 
#endif	
		
		//DPRINTF (LOG_DEBUG, "Completed fioRead function - bytes read:%d", bytesRead);
		if (bytesRead <= 0) {
			cameraCloseSocket("Failed to read image data", camSock);
			goto RETRY;
		} else if (bytesRead != globalCamera.data[writeIndex].cameraImageSize){
			perror ("ERROR: Failed to read entire image: readLength does not match bytes read");
			globalCamera.cameraMetrics[CAM_BAD_IMAGE_SIZE]++;
		}
		// if decoding the JPEG to an HSL Image, do it here
		if (globalCamera.decode) {
			if(globalCamera.data[writeIndex].decodedImage)
				frcDispose(globalCamera.data[writeIndex].decodedImage);
			globalCamera.data[writeIndex].decodedImage = frcCreateImage(IMAQ_IMAGE_HSL);
			if (! Priv_ReadJPEGString_C(globalCamera.data[writeIndex].decodedImage, 
					(const unsigned char *)globalCamera.data[writeIndex].cameraImage, 
					globalCamera.data[writeIndex].cameraImageSize) ) {
				DPRINTF (LOG_DEBUG, "failure creating Image");			
			}
		}
		
		// TODO: React to partial image
		globalCamera.data[writeIndex].timestamp = GetTime();
		globalCamera.index = writeIndex;
		
		/* signal a listening task */
		if (globalCamera.readerPID) {
			if (taskKill (globalCamera.readerPID,SIGUSR1) == OK)
				DPRINTF (LOG_DEBUG, "SIGNALING PID= %i", globalCamera.readerPID);
			else
				globalCamera.cameraMetrics[CAM_PID_SIGNAL_ERR]++;
				DPRINTF (LOG_DEBUG, "ERROR SIGNALING PID= %i", globalCamera.readerPID);
		}

		globalCamera.cameraMetrics[CAM_NUM_IMAGE]++;	
		printCounter ++;
		if (printCounter == 1000) { 
			DPRINTF (LOG_DEBUG, "imageCounter = %i", globalCamera.cameraMetrics[CAM_NUM_IMAGE]); 
			printCounter=0; 
		}
		
		taskDelay(1);  
		
#if MEASURE_TIME
		loopEndTime = GetTime(); 
		performanceLoopCounter++;
		if (performanceLoopCounter <= maxCount) {
			DPRINTF (LOG_DEBUG, "%i DONE!!!: loop = ,%g,  camera = ,%g,  difference = ,%g, loopRate= ,%g,",
					performanceLoopCounter, loopEndTime-loopStartTime, cameraEndTime-cameraStartTime, 
					(loopEndTime-loopStartTime) - (cameraEndTime-cameraStartTime),
					loopStartTime-previousStartTime);						
		}
#endif	
	}  /* end while (cont) */

	/* clean up */
	close (camSock);
	cont = 0;
	DPRINTF (LOG_INFO, "\nJPEG SERVER ENDING  errorCode = %i\n", errorCode );
	
	return (OK);
}

/**
 * @brief Start signaling a task when new images are available
 * @param taskID number for task to get the signal
 */
void StartImageSignal(int taskId) // Start issuing a SIGUSR1 signal to the specified taskId
{	globalCamera.readerPID = taskId; }

/**
 * @brief Start serving images
 */
void StartImageAcquisition(void)
{	
	char funcName[]="StartImageAcquisition";
	globalCamera.cameraMetrics[CAM_STARTS]++;  
	globalCamera.acquire = 1; 
	DPRINTF(LOG_DEBUG, "starting acquisition");
}


/**
 * @brief Stop serving images
 */
void StopImageAcquisition(void)
{	globalCamera.cameraMetrics[CAM_STOPS]++;  globalCamera.acquire = 0; }


/**
 * @brief This is the routine that is run when the task is spawned
 */
static int initCamera(int frames, int compression, ImageSize resolution, ImageRotation rotation, int decode) {
	char funcName[]="initCamera";
	//let user code determine debug level
	//SetDebugFlag ( DEBUG_SCREEN_AND_FILE  ) ;
	
	DPRINTF(LOG_DEBUG, "\n+++++ camera task starting: rotation = %i", (int)rotation);
	int errorCode;

	/* Initialize globalCamera area */
	bzero ((char *)&globalCamera, sizeof(globalCamera));
	globalCamera.index = -1;
	globalCamera.decode = decode;
	
	/* allow writing to vxWorks target */
	Priv_SetWriteFileAllowed(1); 
	
	/* TEST - start acquisition immediately */
	StartImageAcquisition();
	
	/* Call this if you want the camera to auto start on bootup 
	 * otherwise, frcStartJPEGServer must be called from your program
	 */
	DPRINTF (LOG_DEBUG, "calling cameraJPEGServer" ); 
	// cameraJPEGServer runs until camera is stopped
	errorCode = cameraJPEGServer(frames, compression, resolution, rotation);	
	DPRINTF (LOG_INFO, "errorCode from cameraJPEGServer = %i\n", errorCode ); 
	
	/* Now, before obtaining images, frcStartImageAcquisition must be called 
	 */
	return (OK);
}

/**
 * @brief Start the camera task
 * @param frames Frames per second 
 * @param compression Camera image compression 
 * @param resolution Camera image size 
 * @param rotation Camera image rotation 
 * @param decode 0: do not decode to Image, 1: decode (default) 
 * @return TaskID of camera task, or -1 if error.
 */
int StartCameraTask()
{
	return StartCameraTask(10, 0, k160x120, ROT_0);
}
int StartCameraTask(int frames, int compression, ImageSize resolution, ImageRotation rotation)
{
	return StartCameraTask(frames, compression, resolution, rotation, 1);
}
int StartCameraTask(int frames, int compression, ImageSize resolution, ImageRotation rotation, int decode)
{
	char funcName[]="startCameraTask";
	DPRINTF(LOG_DEBUG, "starting camera");
	
	int cameraTaskID = 0;
	
	//range check
	if (frames < 1) frames = 1;
	else if (frames > 30) frames = 30;
	if (compression < 0) compression = 0;		
	else if (compression > 100) compression = 100;
	if ( (decode < 0) || (decode > 1) ) decode = 1;	
	
	// stop any prior copy of running task
    StopCameraTask(); 
	
	// spawn camera task
	cameraTaskID = taskSpawn("FRC_Camera",
					100,							// priority
					VX_FP_TASK,						// floating point C++ context save
					64000,							// stack size
					(FUNCPTR) initCamera,			// function to be called
                    frames,							// frames per second
                    compression,					// image compression
                    resolution,						// image size
					rotation,						// adjustment for camera mount angle
					decode,							// decode
                    0,0,0,0,0);				// parameters (unused)
	
	DPRINTF(LOG_DEBUG, "spawned task id %i", cameraTaskID);
	
	if (cameraTaskID == -1)	{
		DPRINTF(LOG_DEBUG, "camera task failed to start");
		imaqSetError(ERR_CAMERA_TASK_SPAWN_FAILED, funcName);
	}
	return cameraTaskID;
}

/**
 * @brief Stops the camera task
 * @return TaskID of camera task killed, or -1 if none was running.
 */
int StopCameraTask()
{
    std::string taskName("FRC_Camera");    
	// check for prior copy of running task
	int oldTaskID = taskNameToId(const_cast<char*>(taskName.c_str()));
	if(oldTaskID != ERROR) { taskDelete(oldTaskID);  }
	return oldTaskID;
}

#if 0
/* if you want to run this task by itself to debug  
 * enable this code and make RunProgram the entry point 
 * and change to compile as a .out instead of .a
 */
extern "C"
{
void RunProgram(void);
int frcvision_StartupLibraryInit(void);
}
/** * @brief Start point of the program */
void RunProgram(void)
{	StartCameraTask();}

/** * @brief This is the main program that is run by the debugger or the robot on boot. */
int frcvision_StartupLibraryInit(void)
	{		RunProgram();		return 0;	}

#endif



