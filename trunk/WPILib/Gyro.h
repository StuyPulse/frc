/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef GYRO_H_
#define GYRO_H_

#include "SensorBase.h"

class AnalogChannel;
class AnalogModule;

/**
 * Use a rate gyro to return the robots heading relative to a starting position.
 * The Gyro class tracks the robots heading based on the starting position. As the robot
 * rotates the new heading is computed by integrating the rate of rotation returned
 * by the sensor. When the class is instantiated, it does a short calibration routine
 * where it samples the gyro while at rest to determine the default offset. This is
 * subtracted from each sample to determine the heading.
 */
class Gyro : public SensorBase
{
public:
	static const UINT32 kOversampleBits = 7;
	static const UINT32 kAverageBits = 3;
	static const float kSamplesPerSecond = 50.0;
	static const UINT32 kCalibrationSampleTime = 5000;
	static const float kDefaultVoltsPerDegreePerSecond = 0.0125;

	Gyro(UINT32 slot, UINT32 channel);
	Gyro(UINT32 channel);
	Gyro(AnalogChannel *channel);
	Gyro(AnalogChannel &channel);
	~Gyro(void);
	float GetAngle(void);
	void SetSensitivity(float voltsPerDegreePerSecond);
	void Reset(void);

private:
	void InitGyro();

	AnalogChannel *m_analog;
	float m_voltsPerDegreePerSecond;
	float m_offset;
	bool m_channelAllocated;
};
#endif
