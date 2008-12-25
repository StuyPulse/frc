#include "../WPILib.h"
#include "CJaguar.h"
#include "CWrappers.h"
#include "CPWM.h"

static SensorBase *CreateJaguar(UINT32 slot, UINT32 channel)
{
	return new Jaguar(slot, channel);
}

void SetJaguarSpeed(UINT32 module, UINT32 channel, float speed)
{
	Jaguar *jaguar = (Jaguar *) AllocatePWM(module, channel, CreateJaguar);
	if (jaguar)	jaguar->Set(speed);
}

void SetJaguarSpeed(UINT32 channel, float speed)
{
	Jaguar *jaguar = (Jaguar *) AllocatePWM(SensorBase::GetDefaultDigitalModule(), channel, CreateJaguar);
	if (jaguar) jaguar->Set(speed);
}

void SetJaguarRaw(UINT32 channel, UINT8 value)
{
	Jaguar *jaguar = (Jaguar *) AllocatePWM(SensorBase::GetDefaultDigitalModule(), channel, CreateJaguar);
	if (jaguar) jaguar->SetRaw(value);
}

UINT8 GetJaguarRaw(UINT32 channel)
{
	Jaguar *jaguar = (Jaguar *) AllocatePWM(SensorBase::GetDefaultDigitalModule(), channel, CreateJaguar);
	if (jaguar)
		return jaguar->GetRaw();
	else
		return 0;
}

void SetJaguarRaw(UINT32 module, UINT32 channel, UINT8 value)
{
	Jaguar *jaguar = (Jaguar *) AllocatePWM(module, channel, CreateJaguar);
	if (jaguar) jaguar->SetRaw(value);
}

UINT8 GetJaguarRaw(UINT32 module, UINT32 channel)
{
	Jaguar *jaguar = (Jaguar *) AllocatePWM(module, channel, CreateJaguar);
	if (jaguar)
		return jaguar->GetRaw();
	else
		return 0;
}

