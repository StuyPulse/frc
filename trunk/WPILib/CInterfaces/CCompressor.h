#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#include "WPILib.h"

void CreateCompressor(UINT32 pressureSwitch, UINT32 relayChannel);
void CreateCompressor(UINT32 pressureSwitchSlot, UINT32 pressureSwitchChannel,
						UINT32 relaySlot, UINT32 relayChannel);
void StartCompressor(void);
void StopCompressor(void);
bool CompressorEnabled(void);

#endif

