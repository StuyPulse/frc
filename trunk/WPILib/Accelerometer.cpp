/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Accelerometer.h"
#include "AnalogModule.h"
#include "Utility.h"
#include "WPIStatus.h"

/**
 * Common function for initializing the accelerometer.
 */
void Accelerometer::InitAccelerometer(void)
{
	m_voltsPerG = 1.0;
	m_zeroGVoltage = 2.5;
}

/**
 * Create a new instance of an accelerometer.
 * 
 * The accelerometer is assumed to be in the first analog module in the given analog channel. The
 * constructor allocates desired analog channel.
 */
Accelerometer::Accelerometer(UINT32 channel)
{
	m_analogChannel = new AnalogChannel(channel);
	m_allocatedChannel = true;
	InitAccelerometer();
}

/**
 * Create new instance of accelerometer.
 * 
 * Make a new instance of the accelerometer given a module and channel. The constructor allocates
 * the desired analog channel from the specified module
 */
Accelerometer::Accelerometer(UINT32 slot, UINT32 channel)
{
	m_analogChannel = new AnalogChannel(slot, channel);
	m_allocatedChannel = true;
	InitAccelerometer();
}

/**
 * Create a new instance of Accelerometer from an existing AnalogChannel.
 * Make a new instance of accelerometer given an AnalogChannel. This is particularly
 * useful if the port is going to be read as an analog channel as well as through
 * the Accelerometer class.
 */
Accelerometer::Accelerometer(AnalogChannel *channel)
{
	if (channel == NULL)
	{
		wpi_fatal(NullParameter);
	}
	else
	{
		m_analogChannel = channel;
		InitAccelerometer();
	}
	m_allocatedChannel = false;
}
	
/**
 * Delete the analog components used for the accelerometer.
 */
Accelerometer::~Accelerometer(void)
{
	if (m_allocatedChannel)
	{
		delete m_analogChannel;
	}
}

/**
 * Return the acceleration in Gs.
 * 
 * The acceleration is returned units of Gs.
 * 
 * @return The current acceleration of the sensor in Gs.
 */
float Accelerometer::GetAcceleration(void)
{
	return (m_analogChannel->GetAverageVoltage() - m_zeroGVoltage) / m_voltsPerG;
}

/**
 * Set the accelerometer sensitivity.
 * 
 * This sets the sensitivity of the accelerometer used for calculating the acceleration.
 * The sensitivity varys by accelerometer model. There are constants defined for various models.
 * 
 * @param sensitivity The sensitivity of accelerometer in Volts per G.
 */
void Accelerometer::SetSensitivity(float sensitivity)
{
	m_voltsPerG = sensitivity;
}

/**
 * Set the voltage that corresponds to 0 G.
 * 
 * The zero G voltage varys by accelerometer model. There are constants defined for various models.
 * 
 * @param zero The zero G voltage.
 */
void Accelerometer::SetZero(float zero)
{
	m_zeroGVoltage = zero;
}

/*
 * C Wrappers
 */

static Accelerometer *accelerometers[kAnalogModules][kAnalogChannels];
static bool accelerometersInitialized = false;

static Accelerometer *AllocateAccelerometer(UINT32 slot, UINT32 channel)
{
	if (!accelerometersInitialized)
	{
		for (unsigned s = 0; s < kAnalogModules; s++)
			for (unsigned c = 0; c < kAnalogChannels; c++)
				accelerometers[s][c] = NULL;
		accelerometersInitialized = true;
	}
	if (!SensorBase::CheckAnalogModule(slot) || !SensorBase::CheckAnalogChannel(channel))
		return NULL;
	Accelerometer *accel = accelerometers[AnalogModule::SlotToIndex(slot)][channel - 1];
	if (accel == NULL)
	{
		accel = new Accelerometer(slot, channel);
		accelerometers[AnalogModule::SlotToIndex(slot)][channel - 1] = accel;
	}
	return accel;
}

float GetAccelerometer(UINT32 slot, UINT32 channel)
{
	Accelerometer *accel = AllocateAccelerometer(slot, channel);
	if (accel)
		return accel->GetAcceleration();
	else
		return 0.0;
}

float GetAccelerometer(UINT32 channel)
{
	return GetAccelerometer(SensorBase::GetDefaultAnalogModule(), channel);
}

void SetAccelerometerSensitivity(UINT32 slot, UINT32 channel, float sensitivity)
{
	Accelerometer *accel = AllocateAccelerometer(slot, channel);
	if (accel)
		accel->SetSensitivity(sensitivity);
}

void SetAccelerometerSensitivity(UINT32 channel, float sensitivity)
{
	SetAccelerometerSensitivity(SensorBase::GetDefaultAnalogModule(), channel, sensitivity);
}

void SetAccelerometerZero(UINT32 slot, UINT32 channel, float zero)
{
	Accelerometer *accel = AllocateAccelerometer(slot, channel);
	if (accel) accel->SetZero(zero);
}

void SetAccelerometerZero(UINT32 channel, float zero)
{
	SetAccelerometerZero(SensorBase::GetDefaultAnalogModule(), channel);
}
