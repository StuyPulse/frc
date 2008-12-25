/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "AnalogTriggerOutput.h"
#include "AnalogTrigger.h"
#include "Utility.h"
#include "WPIStatus.h"

/**
 * Create an object that represents one of the four outputs from an analog trigger.
 * 
 * Because this class derives from DigitalSource, it can be passed into routing functions
 * for Counter, Encoder, etc.
 * 
 * @param trigger A pointer to the trigger for which this is an output.
 * @param outputType An enum that specifies the output on the trigger to represent.
 */
AnalogTriggerOutput::AnalogTriggerOutput(AnalogTrigger *trigger, AnalogTriggerOutput::Type outputType)
	: m_trigger (trigger)
	, m_outputType (outputType)
{
}

AnalogTriggerOutput::~AnalogTriggerOutput()
{
}

/**
 * Get the state of the analog trigger output.
 * @return The state of the analog trigger output.
 */
bool AnalogTriggerOutput::Get(void)
{
	tRioStatusCode status=0;
	switch(m_outputType)
	{
	case kInWindow:
		return m_trigger->m_trigger->readOutput_InHysteresis(m_trigger->m_index, &status);
	case kState:
		return m_trigger->m_trigger->readOutput_OverLimit(m_trigger->m_index, &status);
	case kRisingPulse:
	case kFallingPulse:
		wpi_fatal(AnalogTriggerPulseOutputError);
	}
	// Should never get here.
	wpi_assert(false);
	return false;
}

/**
 * @return The value to be written to the channel field of a routing mux.
 */
UINT32 AnalogTriggerOutput::GetChannelForRouting(void)
{
	return (m_trigger->m_index << 2) + m_outputType;
}

/**
 * @return The value to be written to the module field of a routing mux.
 */
UINT32 AnalogTriggerOutput::GetModuleForRouting(void)
{
	return m_trigger->m_index >> 2;
}

/**
 * @return The value to be written to the module field of a routing mux.
 */
bool AnalogTriggerOutput::GetAnalogTriggerForRouting(void)
{
	return true;
}



/**
 * Request interrupts asynchronously on this digital input.
 */
void AnalogTriggerOutput::RequestInterrupts(tInterruptHandler handler)
{
	wpi_assert(false);
}

/**
 * Request interrupts synchronously on this digital input.
 */
void AnalogTriggerOutput::RequestInterrupts(void)
{
	wpi_assert(false);
}

