#ifndef C_JAGUAR_H
#define C_JAGUAR_H

#include "WPILib.h"

void SetJaguarSpeed(UINT32 module, UINT32 channel, float speed);
void SetJaguarSpeed(UINT32 channel, float speed);
void SetJaguarRaw(UINT32 channel, UINT8 value);
UINT8 GetJaguarRaw(UINT32 channel);
void SetJaguarRaw(UINT32 module, UINT32 channel, UINT8 value);
UINT8 GetJaguarRaw(UINT32 module, UINT32 channel);

#endif

