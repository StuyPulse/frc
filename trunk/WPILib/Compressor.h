/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef COMPRESSOR_H_
#define COMPRESSOR_H_

#define COMPRESSOR_PRIORITY 90

#include "SensorBase.h"
#include "Relay.h"

class DigitalInput;

/**
 * Compressor object.
 * The Compressor object is designed to handle the operation of the compressor, pressure sensor and
 * relay for a FIRST robot pneumatics system. The Compressor object starts a task which runs in the
 * backround and periodically polls the pressure sensor and operates the relay that controls the
 * compressor.
 */ 
class Compressor: public SensorBase
{
public:
	Compressor(UINT32 pressureSwitchChannel, UINT32 compressorRelayChannel);
	Compressor(UINT32 pressureSwitchSlot, UINT32 pressureSwitchChannel,
				UINT32 compresssorRelaySlot, UINT32 compressorRelayChannel);
	~Compressor(void);

	void Start(void);
	void Stop(void);
	bool Enabled(void);
	UINT32 GetPressureSwitchValue(void);
	void SetRelayValue(Relay::Value relayValue);

private:
	void InitCompressor(UINT32 pressureSwitchSlot, UINT32 pressureSwitchChannel,
					UINT32 compresssorRelaySlot, UINT32 compressorRelayChannel);

	DigitalInput *m_pressureSwitch;
	Relay *m_relay;
	bool m_enabled;
	INT32 m_taskID;
};

#endif

