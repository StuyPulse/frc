#include "DriverStation.h"
#include "CDriverStation.h"

static DriverStation *ds = NULL;

float GetStickAxis(UINT32 stick, UINT32 axis)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetStickAxis(stick, axis);
}

short GetStickButtons(UINT32 stick)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetStickButtons(stick);
}

float GetAnalogIn(UINT32 channel)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetAnalogIn(channel);
}

bool GetDigitalIn(UINT32 channel)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetDigitalIn(channel);
}

void SetDigitalOut(UINT32 channel, bool value)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	ds->SetDigitalOut(channel, value);
}

bool GetDigitalOut(UINT32 channel)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetDigitalOut(channel);
}

bool IsDisabled(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->IsDisabled();
}

bool IsAutonomous(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->IsAutonomous();
}

bool IsOperatorControl(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->IsOperatorControl();
}

UINT32 GetPacketNumber(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetPacketNumber();
}

UINT32 GetAlliance(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetAlliance();
}

UINT32 GetLocation(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetLocation();
}

float GetBatteryVoltage(void)
{
	if (ds == NULL) ds = DriverStation::GetInstance();
	return ds->GetBatteryVoltage();
}
