#ifndef C_ANALOG_CHANNEL_H
#define C_ANALOG_CHANNEL_H

#include "WPILib.h"
#include "CWrappers.h"

AnalogChannel *AllocateAnalogChannel(UINT32 module, UINT32 channel, SensorCreator createObject);

#endif

