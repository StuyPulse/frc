#ifndef C_VICTOR_H
#define C_VICTOR_H

#include "../WPILib.h"
#include "CWrappers.h"

void SetVictorSpeed(UINT32 module, UINT32 channel, float speed);
void SetVictorSpeed(UINT32 channel, float speed);
void SetVictorRaw(UINT32 channel, UINT8 value);
UINT8 GetVictorRaw(UINT32 channel);
void SetVictorRaw(UINT32 module, UINT32 channel, UINT8 value);
UINT8 GetVictorRaw(UINT32 module, UINT32 channel);

#endif
