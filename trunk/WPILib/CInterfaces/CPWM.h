#ifndef C_PWM_H
#define C_PWM_H

#include "WPILib.h"
#include "CWrappers.h"

PWM *AllocatePWM(UINT32 slot, UINT32 channel, SensorCreator creator);
PWM *AllocatePWM(UINT32 channel, SensorCreator creator);

#endif
