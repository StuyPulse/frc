/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __DRIVER_STATION_H__
#define __DRIVER_STATION_H__

#include "SensorBase.h"

struct FRCControlData;
class AnalogChannel;

/**
 * Provide access to the network communication data to / from the Driver Station.
 */
class DriverStation : public SensorBase
{
public:
	enum Alliance {kRed, kBlue, kInvalid};

	virtual ~DriverStation(void);
	static DriverStation *GetInstance(void);

	static const UINT32 kBatterySlot = 1;
	static const UINT32 kBatteryChannel = 8;
	static const UINT32 kJoystickPorts = 4;
	static const UINT32 kJoystickAxes = 6;

	float GetStickAxis(UINT32 stick, UINT32 axis);
	short GetStickButtons(UINT32 stick);

	float GetAnalogIn(UINT32 channel);
	bool GetDigitalIn(UINT32 channel);
	void SetDigitalOut(UINT32 channel, bool value);
	bool GetDigitalOut(UINT32 channel);

	bool IsDisabled(void);
	bool IsAutonomous(void);
	bool IsOperatorControl(void);

	UINT32 GetPacketNumber(void);
	Alliance GetAlliance(void);
	UINT32 GetLocation(void);

	float GetBatteryVoltage(void);

protected:
	DriverStation(void);

	void GetData(void);
	void SetData(void);

private:
	static void InitTask(DriverStation *ds);
	static DriverStation *m_instance;
	static const INT32 kUpdatePeriod_ms = 50;

	void Task(void);

	struct FRCControlData *m_controlData;
	char *m_userControl;
	char *m_userStatus;
	UINT8 m_digitalOut;
	AnalogChannel *m_batteryChannel;
	INT32 m_taskID;
};

#endif

