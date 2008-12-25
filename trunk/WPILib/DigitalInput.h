/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef DIGITAL_INPUT_H_
#define DIGITAL_INPUT_H_

class DigitalModule;

#include "DigitalSource.h"

/**
 * Class to read a digital input.
 * This class will read digital inputs and return the current value on the channel. Other devices
 * such as encoders, gear tooth sensors, etc. that are implemented elsewhere will automatically
 * allocate digital inputs and outputs as required. This class is only for devices like switches
 * etc. that aren't implemented anywhere else.
 */
class DigitalInput : public DigitalSource {
public:
	DigitalInput(UINT32 channel);
	DigitalInput(UINT32 slot, UINT32 channel);
	~DigitalInput(void);
	UINT32 Get(void);
	UINT32 GetChannel(void);

	// Digital Source Interface
	virtual UINT32 GetChannelForRouting(void);
	virtual UINT32 GetModuleForRouting(void);
	virtual bool GetAnalogTriggerForRouting(void);
	
	// Interruptable Interface
	virtual void RequestInterrupts(tInterruptHandler handler); ///< Asynchronus handler version.
	virtual void RequestInterrupts(void);		///< Synchronus Wait version.
	void SetUpSourceEdge(bool risingEdge, bool fallingEdge);

private:
	void InitDigitalInput(UINT32 slot, UINT32 channel);
	UINT32 m_channel;
	DigitalModule *m_module;
	bool m_lastValue;
};

UINT32 GetDigitalInput(UINT32 slot, UINT32 channel);
UINT32 GetDigitalInput(UINT32 channel);

#endif

