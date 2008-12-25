#ifndef C_GYRO_H
#define C_GYRO_H

#include "WPILib.h"

float GetGyroAngle(UINT32 channel);
float GetGyroAngle(UINT32 slot, UINT32 channel);
void ResetGyro(UINT32 channel);
void ResetGyro(UINT32 slot, UINT32 channel);
void SetGyroSensitivity(UINT32 slot, UINT32 channel, float voltsPerDegreePerSecond);
void SetGyroSensitivity(UINT32 channel, float voltsPerDegreePerSecond);

#endif

