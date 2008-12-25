#ifndef _C_DRIVER_STATION_H
#define _C_DRIVER_STATION_H

float GetStickAxis(UINT32 stick, UINT32 axis);
short GetStickButtons(UINT32 stick);

float GetAnalogIn(UINT32 channel);
bool GetDigitalIn(UINT32 channel);
void SetDigitalOut(UINT32 channel, bool value);
bool GetDigitalOut(UINT32 channel);

bool IsDisabled(void);
bool IsAutonomous(void);
bool IsOperatorControl(void);

UINT32 GetPacketNumber(void);
UINT32 GetAlliance(void);
UINT32 GetLocation(void);

float GetBatteryVoltage(void);

#endif
