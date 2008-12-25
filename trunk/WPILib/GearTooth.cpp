/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "GearTooth.h"

/**
 * Common code called by the constructors.
 */
void GearTooth::InitGTS(bool directionSensitive)
{
	if (directionSensitive)
	{
		SetPulseLengthMode(kGearToothThreshold);
	}
}

/**
 * Construct a GearTooth sensor given a channel.
 * 
 * The default module is assumed.
 * 
 * @param channel The GPIO channel on the digital module that the sensor is connected to.
 * @param directionSensitive Enable the pulse length decoding in hardware to specify count direction.
 */
GearTooth::GearTooth(UINT32 channel, bool directionSensitive)
	: Counter(channel)
{
	InitGTS(directionSensitive);
}

/**
 * Construct a GearTooth sensor given a channel and module.
 * 
 * @param slot The slot in the chassis that the digital module is plugged in to.
 * @param channel The GPIO channel on the digital module that the sensor is connected to.
 * @param directionSensitive Enable the pulse length decoding in hardware to specify count direction.
 */
GearTooth::GearTooth(UINT32 slot, UINT32 channel, bool directionSensitive)
	: Counter(slot, channel)
{
	InitGTS(directionSensitive);
}

/**
 * Construct a GearTooth sensor given a digital input.
 * This should be used when sharing digial inputs.
 * 
 * @param source An object that fully descibes the input that the sensor is connected to.
 * @param directionSensitive Enable the pulse length decoding in hardware to specify count direction.
 */
GearTooth::GearTooth(DigitalSource *source, bool directionSensitive)
	: Counter(source)
{
	InitGTS(directionSensitive);
}

GearTooth::GearTooth(DigitalSource &source, bool directionSensitive): Counter(source)
{
	InitGTS(directionSensitive);
}

/**
 * Free the resources associated with a gear tooth sensor.
 */
GearTooth::~GearTooth(void)
{
}

