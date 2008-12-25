/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "DriverStation.h"
#include "AnalogChannel.h"
#include "Timer.h"
#include "Utility.h"
#include "WPIStatus.h"
#include "NetworkCommunication/FRCComm.h"
#include <strLib.h>

DriverStation* DriverStation::m_instance = NULL;

/**
 * DriverStation contructor.
 * 
 * This is only called once the first time GetInstance() is called
 */
DriverStation::DriverStation(void)
	: m_controlData (NULL)
	, m_userControl (NULL)
	, m_userStatus (NULL)
	, m_digitalOut (0)
	, m_batteryChannel (NULL)
	, m_taskID (0)
{
	m_controlData = new FRCControlData;
	m_userControl = new char[USER_CONTROL_DATA_SIZE];
	m_userStatus = new char[USER_STATUS_DATA_SIZE];
	bzero(m_userStatus, USER_STATUS_DATA_SIZE);

	// initialize packet number and control words to zero;
	m_controlData->packetIndex = 0;
	m_controlData->control = 0;

	// set all joystick axis values to neutral; buttons to OFF
	m_controlData->stick0Axis1 = m_controlData->stick0Axis2 = m_controlData->stick0Axis3 = 0;
	m_controlData->stick1Axis1 = m_controlData->stick1Axis2 = m_controlData->stick1Axis3 = 0;
	m_controlData->stick2Axis1 = m_controlData->stick2Axis2 = m_controlData->stick2Axis3 = 0;
	m_controlData->stick3Axis1 = m_controlData->stick3Axis2 = m_controlData->stick3Axis3 = 0;
	m_controlData->stick0Axis4 = m_controlData->stick0Axis5 = m_controlData->stick0Axis6 = 0;
	m_controlData->stick1Axis4 = m_controlData->stick1Axis5 = m_controlData->stick1Axis6 = 0;
	m_controlData->stick2Axis4 = m_controlData->stick2Axis5 = m_controlData->stick2Axis6 = 0;
	m_controlData->stick3Axis4 = m_controlData->stick3Axis5 = m_controlData->stick3Axis6 = 0;
	m_controlData->stick0Buttons = 0;
	m_controlData->stick1Buttons = 0;
	m_controlData->stick2Buttons = 0;
	m_controlData->stick3Buttons = 0;

	// initialize the analog and digital data.
	m_controlData->analog1 = 0;
	m_controlData->analog2 = 0;
	m_controlData->analog3 = 0;
	m_controlData->analog4 = 0;
	m_controlData->dsDigitalIn = 0;

	m_batteryChannel = new AnalogChannel(kBatterySlot, kBatteryChannel);

	AddToSingletonList();

	m_taskID = taskSpawn("FRCDriverStation",
						100,
						VX_FP_TASK,							// options
						20000,								// stack size
						(FUNCPTR) DriverStation::InitTask,	// function to start
						(INT32) this,							// parameter 1 - pointer to this class
						0, 0, 0, 0, 0, 0, 0, 0, 0);	// additional unused parameters
	if (m_taskID == ERROR)
	{
		wpi_fatal(DriverStationTaskError);
	}
}

DriverStation::~DriverStation(void)
{
	taskDelete(m_taskID);
	delete m_batteryChannel;
	delete m_controlData;
	delete[] m_userControl;
	delete[] m_userStatus;
	m_instance = NULL;
}

void DriverStation::InitTask(DriverStation *ds)
{
	ds->Task();
}

void DriverStation::Task(void)
{
	while (true)
	{
		SetData();
		Wait(kUpdatePeriod_ms);
	}
}

/**
 * Return a pointer to the singleton DriverStation.
 */
DriverStation* DriverStation::GetInstance(void)
{
	if (m_instance == NULL)
	{
		m_instance = new DriverStation();
	}
	return m_instance;
}

/**
 * Copy data from the DS task for the user.
 * If no new data exists, it will just be returned, otherwise
 * the data will be copied from the DS polling loop.
 */
void DriverStation::GetData(void)
{
	getControlData(m_controlData, m_userControl, WAIT_FOREVER);
}

/**
 * Copy status data from the DS task for the user.
 * This is used primarily to set digital outputs on the DS.
 */
void DriverStation::SetData(void)
{
	setStatusData(GetBatteryVoltage(), m_digitalOut, m_userStatus,
			USER_STATUS_DATA_SIZE, WAIT_FOREVER);
}

/**
 * Read the battery voltage from the specified AnalogChannel.
 * 
 * This accessor assumes that the battery voltage is being measured
 * through the voltage divider on an analog breakout.
 * 
 * @return The battery voltage.
 */
float DriverStation::GetBatteryVoltage(void)
{
	wpi_assert(m_batteryChannel != NULL);

	// The Analog bumper has a voltage divider on the battery source.
	// Vbatt *--/\/\/\--* Vsample *--/\/\/\--* Gnd
	//         680 Ohms            1000 Ohms
	return m_batteryChannel->GetAverageVoltage() * (1680.0 / 1000.0);
}

/**
 * Get the value of the axis on a joystick.
 * This depends on the mapping of the joystick connected to the specified port.
 * 
 * @param stick The joystick to read.
 * @param axis The analog axis value to read from the joystick.
 * @return The value of the axis on the joystick.
 */
float DriverStation::GetStickAxis(UINT32 stick, UINT32 axis)
{
	if (axis < 1 || axis > kJoystickAxes)
	{
		wpi_fatal(BadJoystickAxis);
		return 0.0;
	}

	INT8 value;
	GetData();
	switch (stick)
	{
		case 1:
			value = m_controlData->stick0Axes[axis-1];
			break;
		case 2:
			value = m_controlData->stick1Axes[axis-1];
			break;
		case 3:
			value = m_controlData->stick2Axes[axis-1];
			break;
		case 4:
			value = m_controlData->stick3Axes[axis-1];
			break;
		default:
			wpi_fatal(BadJoystickIndex);
			return 0.0;
	}
	float result = ((float) value) / 128.0;
	wpi_assert(result < 1.0 && result >= -1.0);
	return result;
}

/**
 * The state of the buttons on the joystick.
 * 12 buttons (4 msb are unused) from the joystick.
 * 
 * @param stick The joystick to read.
 * @return The state of the buttons on the joystick.
 */
short DriverStation::GetStickButtons(UINT32 stick)
{
	wpi_assert ((stick >= 1) && (stick <= 4));
	GetData();
	switch (stick)
	{
	case 1:
		return m_controlData->stick0Buttons;
	case 2:
		return m_controlData->stick1Buttons;
	case 3:
		return m_controlData->stick2Buttons;
	case 4:
		return m_controlData->stick3Buttons;
	}
	return 0;
}

/**
 * Get an analog voltage from the Driver Station.
 * The analog values are returned as UINT32 values for the Driver Station analog inputs.
 * These inputs are typically used for advanced operator interfaces consisting of potentiometers
 * or resistor networks representing values on a rotary switch.
 * 
 * @param channel The analog input channel on the driver station to read from. Valid range is 1 - 4.
 * @return The analog voltage on the input.
 */
float DriverStation::GetAnalogIn(UINT32 channel)
{
	wpi_assert ((channel >= 1) && (channel <= 4));
	GetData();
	switch (channel)
	{
	case 1:
		return m_controlData->analog1;
	case 2:
		return m_controlData->analog2;
	case 3:
		return m_controlData->analog3;
	case 4:
		return m_controlData->analog4;
	}
	return 0;
}

/**
 * Get values from the digital inputs on the Driver Station.
 * Return digital values from the Drivers Station. These values are typically used for buttons
 * and switches on advanced operator interfaces.
 * @param channel The digital input to get. Valid range is 1 - 8.
 */
bool DriverStation::GetDigitalIn(UINT32 channel)
{
	wpi_assert ((channel >= 1) && (channel <= 8));
	GetData();
	return ((m_controlData->dsDigitalIn >> (channel-1)) & 0x1) ? true : false;
}

/**
 * Set a value for the digital outputs on the Driver Station.
 * 
 * Control digital outputs on the Drivers Station. These values are typically used for
 * giving feedback on a custom operator station such as LEDs.
 * 
 * @param channel The digital output to set. Valid range is 1 - 8.
 * @param value The state to set the digital output.
 */
void DriverStation::SetDigitalOut(UINT32 channel, bool value) 
{
	wpi_assert ((channel >= 1) && (channel <= 8));
	m_digitalOut &= ~(0x1 << (channel-1));
	m_digitalOut |= ((UINT8)value << (channel-1));
}

/**
 * Get a value that was set for the digital outputs on the Driver Station.
 * @param channel The digital ouput to monitor. Valid range is 1 through 8.
 * @return A digital value being output on the Drivers Station.
 */
bool DriverStation::GetDigitalOut(UINT32 channel) 
{
	wpi_assert ((channel >= 1) && (channel <= 8));
	return ((m_digitalOut >> (channel-1)) & 0x1) ? true : false;;
}

bool DriverStation::IsDisabled(void)
{
	GetData();
	return !m_controlData->enabled;
}

bool DriverStation::IsAutonomous(void)
{
	GetData();
	return m_controlData->autonomous;
}

bool DriverStation::IsOperatorControl(void)
{
	GetData();
	return !m_controlData->autonomous;
}

/**
 * Return the DS packet number.
 * The packet number is the index of this set of data returned by the driver station.
 * Each time new data is received, the packet number (included with the sent data) is returned.
 */
UINT32 DriverStation::GetPacketNumber(void)
{
	GetData();
	return m_controlData->packetIndex;
}


DriverStation::Alliance DriverStation::GetAlliance(void)
{
	if (m_controlData->dsID_Alliance == 'R') return kRed;
	if (m_controlData->dsID_Alliance == 'B') return kBlue;
	wpi_assert(false);
	return kInvalid;
}

UINT32 DriverStation::GetLocation(void)
{
	wpi_assert ((m_controlData->dsID_Position >= '1') && (m_controlData->dsID_Position <= '3'));
	return m_controlData->dsID_Position - '0';
}

