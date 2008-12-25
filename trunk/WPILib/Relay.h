/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef RELAY_H_
#define RELAY_H_

#include "SensorBase.h"

class DigitalModule;

/**
 * Class for Spike style relay outputs.
 * Relays are intended to be connected to spikes or similar relays. The relay channels controls
 * a pair of pins that are either both off, one on, the other on, or both on. This translates into
 * two spike outputs at 0v, one at 12v and one at 0v, one at 0v and the other at 12v, or two 
 * spike outputs at 12V. This allows off, full forward, or full reverse control of motors without
 * variable speed.  It also allows the two channels (forward and reverse) to be used independently
 * for something that does not care about voltage polatiry (like a solenoid).
 */
class Relay : public SensorBase {
public:
	typedef enum {kOff, kOn, kForward, kReverse} Value;
	typedef enum {kBothDirections, kForwardOnly, kReverseOnly} Direction;

	Relay(UINT32 channel, Direction direction = kBothDirections);
	Relay(UINT32 slot, UINT32 channel, Direction direction = kBothDirections);
	~Relay(void);

	void Set(Value value);

private:
	void InitRelay(UINT32 slot);

	UINT32 m_channel;
	Direction m_direction;
	DigitalModule *m_module;
};

#endif
