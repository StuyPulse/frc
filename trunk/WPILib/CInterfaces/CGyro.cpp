#include "CGyro.h"

static Gyro* gyros[2] = {NULL, NULL};

static Gyro *AllocateGyro(UINT32 slot, UINT32 channel)
{
	if (!SensorBase::CheckAnalogModule(slot) || !SensorBase::CheckAnalogChannel(channel))
		return NULL;
	if (gyros[channel] == NULL)
	{
		gyros[channel] = new Gyro(slot, channel);
	}
	return gyros[channel];
}

void InitGyro(UINT32 slot, UINT32 channel)
{
	AllocateGyro(slot, channel);
}

void InitGyro(UINT32 channel)
{
	InitGyro(SensorBase::GetDefaultAnalogModule(), channel);
}

float GetGyroAngle(UINT32 slot, UINT32 channel)
{
	Gyro *gyro = AllocateGyro(slot, channel);
	if (gyro) return gyro->GetAngle();
	return 0.0;
}

float GetGyroAngle(UINT32 channel)
{
	return GetGyroAngle(SensorBase::GetDefaultAnalogModule(), channel);
}

void ResetGyro(UINT32 slot, UINT32 channel)
{
	Gyro *gyro = AllocateGyro(slot, channel);
	if (gyro) gyro->Reset();
}

void ResetGyro(UINT32 channel)
{
	ResetGyro(SensorBase::GetDefaultAnalogModule(), channel);
}

void SetGyroSensitivity(UINT32 slot, UINT32 channel, float voltsPerDegreePerSecond)
{
	Gyro *gyro = AllocateGyro(slot, channel);
	if (gyro) gyro->SetSensitivity(voltsPerDegreePerSecond);
}

void SetGyroSensitivity(UINT32 channel, float voltsPerDegreePerSecond)
{
	SetGyroSensitivity(SensorBase::GetDefaultAnalogModule(), channel, voltsPerDegreePerSecond);
}


