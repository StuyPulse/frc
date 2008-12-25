/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef QUAD_ENCODER_H_
#define QUAD_ENCODER_H_

#include "ChipObject.h"
#include "CounterBase.h"
#include "SensorBase.h"

class DigitalSource;

/**
 * Class to read quad encoders.
 * Quadrature encoders are devices that count shaft rotation and can sense direction. The output of
 * the QuadEncoder class is an integer that can count either up or down, and can go negative for
 * reverse direction counting. When creating QuadEncoders, a direction is supplied that changes the
 * sense of the output to make code more readable if the encoder is mounted such that forward movement
 * generates negative values. Quadrature encoders have two digital outputs, an A Channel and a B Channel
 * that are out of phase with each other to allow the FPGA to do direction sensing. 
 */
class Encoder: public SensorBase, public CounterBase
{
public:
	Encoder(UINT32 aChannel, UINT32 bChannel, bool reverseDirection=false);
	Encoder(UINT32 aSlot, UINT32 aChannel, UINT32 bSlot, UINT32 _bChannel, bool reverseDirection=false);
	Encoder(DigitalSource *aSource, DigitalSource *bSource, bool reverseDirection=false);
	Encoder::Encoder(DigitalSource &aSource, DigitalSource &bSource, bool reverseDirection);
	virtual ~Encoder(void);

	// CounterBase interface
	void Start(void);
	INT32 Get(void);
	void Reset(void);
	void Stop(void);
	UINT32 GetPeriod(void);
	void SetMaxPeriod(UINT32 maxPeriod);
	bool GetStopped(void);
	bool GetDirection(void);

private:
	void InitEncoder(bool _reverseDirection);

	DigitalSource *m_aSource;		// the A phase of the quad encoder
	DigitalSource *m_bSource;		// the B phase of the quad encoder
	bool m_allocatedASource;		// was the A source allocated locally?
	bool m_allocatedBSource;		// was the B source allocated locally?
	tEncoder* m_encoder;
	UINT8 m_index;
};

#endif

