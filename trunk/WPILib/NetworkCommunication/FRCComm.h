/*************************************************************
 * 					NOTICE
 * 
 * 	These are the only externally exposed functions to the
 *   NetworkCommunication library
 * 
 * This is an implementation of FRC Spec for Comm Protocol
 * Revision 4.5, June 30, 2008
 *
 * Copyright (c) National Instruments 2008.  All Rights Reserved.
 *
 *************************************************************/

#ifndef __FRC_COMM_H__
#define __FRC_COMM_H__

#include <vxWorks.h>

#define USER_CONTROL_DATA_SIZE 936
#define USER_STATUS_DATA_SIZE 984

struct FRCControlData{
	UINT16 packetIndex;
	union {
		UINT8 control;
		struct {
			UINT8 reset : 1;
			UINT8 notEStop : 1;
			UINT8 enabled : 1;
			UINT8 autonomous : 1;
			UINT8 :1;
			UINT8 resync : 1;
			UINT8 cRIOChkSum :1;
			UINT8 fpgaChkSum :1;
		};
	};
	UINT8 dsDigitalIn;
	UINT16 teamID;

	char dsID_Alliance;
	char dsID_Position;

	union {
		INT8 stick0Axes[6];
		struct {
			INT8 stick0Axis1;
			INT8 stick0Axis2;
			INT8 stick0Axis3;
			INT8 stick0Axis4;
			INT8 stick0Axis5;
			INT8 stick0Axis6;
		};
	};
	UINT16 stick0Buttons;		// Left-most 4 bits are unused

	union {
		INT8 stick1Axes[6];
		struct {
			INT8 stick1Axis1;
			INT8 stick1Axis2;
			INT8 stick1Axis3;
			INT8 stick1Axis4;
			INT8 stick1Axis5;
			INT8 stick1Axis6;
		};
	};
	UINT16 stick1Buttons;		// Left-most 4 bits are unused

	union {
		INT8 stick2Axes[6];
		struct {
			INT8 stick2Axis1;
			INT8 stick2Axis2;
			INT8 stick2Axis3;
			INT8 stick2Axis4;
			INT8 stick2Axis5;
			INT8 stick2Axis6;
		};
	};
	UINT16 stick2Buttons;		// Left-most 4 bits are unused

	union {
		INT8 stick3Axes[6];
		struct {
			INT8 stick3Axis1;
			INT8 stick3Axis2;
			INT8 stick3Axis3;
			INT8 stick3Axis4;
			INT8 stick3Axis5;
			INT8 stick3Axis6;
		};
	};
	UINT16 stick3Buttons;		// Left-most 4 bits are unused

	//Analog inputs are 10 bit right-justified
	UINT16 analog1;
	UINT16 analog2;
	UINT16 analog3;
	UINT16 analog4;

	UINT64 cRIOChecksum;
	UINT32 FPGAChecksum0;
	UINT32 FPGAChecksum1;
	UINT32 FPGAChecksum2;
	UINT32 FPGAChecksum3;

	char versionData[8];
};

/**
 * Structure for DS to robot control packets
 */
typedef struct {
	FRCControlData commonData;
	char userDefined[USER_CONTROL_DATA_SIZE];
	INT32 crcPad;
	INT32 crcChecksum;
} ControlData;

extern "C" {
	int getControlData(FRCControlData *data, char *userData, int wait_ms);
	int setStatusData(float battery, UINT8 dsDigitalOut, char *userData, int userDataLength, int wait_ms);

	void setNewDataSem(SEM_ID);
	void setResyncSem(SEM_ID);
	void signalResyncActionDone(void);
	
	// this UINT32 is really a LVRefNum
	void setNewDataOccurRef(UINT32 refnum);
	void setResyncOccurRef(UINT32 refnum);
};

#endif
