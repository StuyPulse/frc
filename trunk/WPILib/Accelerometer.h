/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include "AnalogChannel.h"
#include "SensorBase.h"

/** 
 * Handle operation of the accelerometer.
 * The accelerometer reads acceleration directly through the sensor. Many sensors have
 * multiple axis and can be treated as multiple devices. Each is calibrated by finding
 * the center value over a period of time.
 */
class Accelerometer : public SensorBase {
public:
	Accelerometer(UINT32 channel);
	Accelerometer(UINT32 slot, UINT32 channel);
	Accelerometer(AnalogChannel *channel);
	~Accelerometer(void);

	float GetAcceleration(void);
	void SetSensitivity(float sensitivity);
	void SetZero(float zero);

private:
	void InitAccelerometer(void);

	AnalogChannel *m_analogChannel;
	float m_voltsPerG;
	float m_zeroGVoltage;
	bool m_allocatedChannel;
};

float GetAccelerometer(UINT32 slot, UINT32 channel);
float GetAccelerometer(UINT32 channel);
void SetAccelerometerSensitivity(UINT32 slot, UINT32 channel, float sensitivity);
void SetAccelerometerSensitivity(UINT32 channel, float sensitivity);
void SetAccelerometerZero(UINT32 slot, UINT32 channel, float zero);
void SetAccelerometerZero(UINT32 channel, float zero);

#endif
