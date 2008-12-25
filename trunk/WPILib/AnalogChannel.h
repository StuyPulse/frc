/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef ANALOG_CHANNEL_H_
#define ANALOG_CHANNEL_H_

#include "SensorBase.h"

class AnalogModule;

/**
 * Analog channel class.
 * 
 * Each analog channel is read from hardware as a 12-bit number representing -10V to 10V.
 * 
 * Connected to each analog channel is an averaging and oversampling engine.  This engine accumulates
 * the specified ( by SetAverageBits() and SetOversampleBits() ) number of samples before returning a new
 * value.  This is not a sliding window average.  The only difference between the oversampled samples and
 * the averaged samples is that the oversampled samples are simply accumulated effectively increasing the
 * resolution, while the averaged samples are divided by the number of samples to retain the resolution,
 * but get more stable values.
 */
class AnalogChannel : public SensorBase
{
public:
	static const UINT32 kAccumulatorSlot = 1;
	static const UINT32 kAccumulatorNumChannels = 2;
	static const UINT32 kAccumulatorChannels[kAccumulatorNumChannels];

	AnalogChannel(UINT32 slot, UINT32 channel);
	AnalogChannel(UINT32 channel);
	virtual ~AnalogChannel();

	AnalogModule *GetModule(void);

	INT16 GetValue(void);
	INT32 GetAverageValue(void);

	float GetVoltage(void);
	float GetAverageVoltage(void);

	UINT32 GetSlot(void);
	UINT32 GetChannel(void);

	void SetAverageBits(UINT32 bits);
	UINT32 GetAverageBits(void);
	void SetOversampleBits(UINT32 bits);
	UINT32 GetOversampleBits(void);

	UINT32 GetLSBWeight(void);
	INT32 GetOffset(void);

	bool IsAccumulatorChannel(void);
	void InitAccumulator(void);
	void SetAccumulatorInitialValue(INT64 value);
	void ResetAccumulator(void);
	void SetAccumulatorCenter(INT32 center);
	void SetAccumulatorDeadband(INT32 deadband);
	INT64 GetAccumulatorValue(void);
	UINT32 GetAccumulatorCount(void);
	void GetAccumulatorOutput(INT64 *value, UINT32 *count);

private:
	void InitChannel(UINT32 slot, UINT32 channel);
	UINT32 m_channel;
	AnalogModule *m_module;
	tAccumulator *m_accumulator;
	INT64 m_accumulatorOffset;
};

#endif
