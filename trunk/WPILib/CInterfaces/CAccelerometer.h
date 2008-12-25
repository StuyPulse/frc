#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

float GetAcceleration(UINT32 channel);
float GetAcceleration(UINT32 slot, UINT32 channel);
void SetAccelerometerSensitivity(UINT32 channel, float sensitivity);
void SetAccelerometerSensitivity(UINT32 slot, UINT32 channel, float sensitivity);
void SetAccelerometerZero(UINT32 channel, float zero);
void SetAccelerometerZero(UINT32 slot, UINT32 channel, float zero);

#endif

