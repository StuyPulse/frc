#include "Accelerometer.h"
#include "CWrappers.h"

static Accelerometer* accelerometers[kAnalogModules][kAnalogChannels];
static bool initialized = false;

static Accelerometer *AllocateAccelerometer(UINT32 slot, UINT32 channel)
{
	if (!initialized)
	{
		initialized = true;
		for (unsigned i = 1; i <= kAnalogModules; i++)
			for (unsigned j = 1; j <= kAnalogChannels; j++)
				accelerometers[i][j] = NULL;
	}
	if (!SensorBase::CheckAnalogModule(slot) || !SensorBase::CheckAnalogChannel(channel))
		return NULL;
	if (accelerometers[slot][channel] == NULL)
	{
		accelerometers[slot][channel] = new Accelerometer(slot, channel);
	}
	return accelerometers[slot][channel];
}

float GetAcceleration(UINT32 channel)
{
	Accelerometer *accel = AllocateAccelerometer(SensorBase::GetDefaultAnalogModule(), channel);
	return accel->GetAcceleration();
}

float GetAcceleration(UINT32 slot, UINT32 channel)
{
	Accelerometer *accel = AllocateAccelerometer(slot, channel);
	return accel->GetAcceleration();
}

void SetAccelerometerSensitivity(UINT32 channel, float sensitivity)
{
	Accelerometer *accel = AllocateAccelerometer(SensorBase::GetDefaultAnalogModule(), channel);
	accel->SetSensitivity(sensitivity);
}

void SetAccelerometerSensitivity(UINT32 slot, UINT32 channel, float sensitivity)
{
	Accelerometer *accel = AllocateAccelerometer(slot, channel);
	accel->SetSensitivity(sensitivity);	
}

void SetAccelerometerZero(UINT32 channel, float zero)
{
	Accelerometer *accel = AllocateAccelerometer(SensorBase::GetDefaultAnalogModule(), channel);
	accel->SetZero(zero);
}

void SetAccelerometerZero(UINT32 slot, UINT32 channel, float zero)
{
	Accelerometer *accel = AllocateAccelerometer(slot, channel);
	accel->SetZero(zero);
}
