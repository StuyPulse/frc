/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef SENSORBASE_H_
#define SENSORBASE_H_

#include "chipobject/NiRio.h"
#include "ErrorBase.h"
#include <stdio.h>


/**
 * Base class for all sensors.
 * Stores most recent status information as well as containing utility functions for checking
 * channels and error processing.
 */
class SensorBase: public ErrorBase {
public:
	static const UINT32 kSystemClockTicksPerMicrosecond = 40;

	SensorBase(void);
	virtual ~SensorBase();
	static void SetDefaultAnalogModule(UINT32 slot);
	static void SetDefaultDigitalModule(UINT32 slot);
	static void SetDefaultSolenoidModule(UINT32 slot);
	static void DeleteSingletons(void);
	static UINT32 GetDefaultAnalogModule(void) { return m_defaultAnalogModule; }
	static UINT32 GetDefaultDigitalModule(void) { return m_defaultDigitalModule; }
	static UINT32 GetDefaultSolenoidModule(void) { return m_defaultSolenoidModule; }
	static bool CheckDigitalModule(UINT32 slot);
	static bool CheckRelayModule(UINT32 slot);
	static bool CheckPWMModule(UINT32 slot);
	static bool CheckSolenoidModule(UINT32 slot);
	static bool CheckAnalogModule(UINT32 slot);
	static bool CheckDigitalChannel(UINT32 channel);
	static bool CheckRelayChannel(UINT32 channel);
	static bool CheckPWMChannel(UINT32 channel);
	static bool CheckAnalogChannel(UINT32 channel);
	static bool CheckSolenoidChannel(UINT32 channel);
protected:
	void AddToSingletonList(void);

private:
	static UINT32 m_defaultAnalogModule;		/*JAL*/
	static UINT32 m_defaultDigitalModule;
	static UINT32 m_defaultSolenoidModule;
	static SensorBase *m_singletonList;
	SensorBase *m_nextSingleton;
};

const UINT32 kDigitalChannels = 14;				/*JAL*/
const UINT32 kAnalogChannels = 8;
const UINT32 kAnalogModules = 2;
const UINT32 kDigitalModules = 2;
const UINT32 kSolenoidChannels = 8;
const UINT32 kPwmChannels = 10;
const UINT32 kRelayChannels = 8;
const UINT32 kChassisSlots = 8;

#endif
