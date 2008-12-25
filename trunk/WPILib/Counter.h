/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef CPPCOUNTER_H_
#define CPPCOUNTER_H_

#include "AnalogTriggerOutput.h"
#include "CounterBase.h"
#include "SensorBase.h"

/**
 * Class for counting the number of ticks on a digital input channel.
 * This is a general purpose class for counting repetitive events. It can return the number
 * of counts, the period of the most recent cycle, and detect when the signal being counted
 * has stopped by supplying a maximum cycle time.
 */
class Counter : public SensorBase, public CounterBase
{
public:
	typedef enum {kTwoPulse=0, kSemiperiod=1, kPulseLength=2, kExternalDirection=3} Mode;

	Counter(void);
	Counter(UINT32 channel);
	Counter(UINT32 slot, UINT32 channel);
	Counter(DigitalSource *source);
	Counter(DigitalSource &source);
	Counter(AnalogTrigger *trigger);
	Counter(AnalogTrigger &trigger);
	virtual ~Counter(void);

	void SetUpSource(UINT32 channel);
	void SetUpSource(UINT32 slot, UINT32 channel);
	void SetUpSource(AnalogTrigger *analogTrigger, AnalogTriggerOutput::Type triggerType);
	void SetUpSource(AnalogTrigger &analogTrigger, AnalogTriggerOutput::Type triggerType);
	void SetUpSource(DigitalSource *source);
	void SetUpSource(DigitalSource &source);
	void SetUpSourceEdge(bool risingEdge, bool fallingEdge);
	void ClearUpSource(void);

	void SetDownSource(UINT32 channel);
	void SetDownSource(UINT32 slot, UINT32 channel);
	void SetDownSource(AnalogTrigger *analogTrigger, AnalogTriggerOutput::Type triggerType);
	void SetDownSource(AnalogTrigger &analogTrigger, AnalogTriggerOutput::Type triggerType);
	void SetDownSource(DigitalSource *source);
	void SetDownSource(DigitalSource &source);
	void SetDownSourceEdge(bool risingEdge, bool fallingEdge);
	void ClearDownSource(void);

	void SetUpDownCounterMode(void);
	void SetExternalDirectionMode(void);
	void SetSemiPeriodMode(bool highRisingPeriod);
	void SetPulseLengthMode(UINT32 threshold);

	// CounterBase interface
	void Start(void);
	INT32 Get(void);
	void Reset(void);
	void Stop(void);
	UINT32 GetPeriod(void);
	void SetMaxPeriod(UINT32 maxPeriod);
	void SetUpdateWhenEmpty(bool enabled);
	bool GetStopped(void);
	bool GetDirection(void);
private:
	void InitCounter(void);

	DigitalSource *m_upSource;		///< What makes the counter count up.
	DigitalSource *m_downSource;	///< What makes the counter count down.
	bool m_allocatedUpSource;		///< Was the upSource allocated locally?
	bool m_allocatedDownSource;	///< Was the downSource allocated locally?
	tCounter *m_counter;				///< The FPGA counter object.
	UINT32 m_index;					///< The index of this counter.
};

#endif
