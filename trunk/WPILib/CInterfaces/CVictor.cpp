#include "CVictor.h"
#include "CPWM.h"

static SensorBase *CreateVictor(UINT32 slot, UINT32 channel)
{
	return new Victor(slot, channel);
}

void SetVictorSpeed(UINT32 module, UINT32 channel, float speed)
{
	Victor *victor = (Victor *) AllocatePWM(module, channel, CreateVictor);
	if (victor)	victor->Set(speed);
}

void SetVictorRaw(UINT32 channel, UINT8 value)
{
	Victor *victor = (Victor *) AllocatePWM(channel, CreateVictor);
	if (victor) victor->SetRaw(value);
}

void SetVictorSpeed(UINT32 channel, float speed)
{
	Victor *victor = (Victor *) AllocatePWM(channel, CreateVictor);
	if (victor) victor->Set(speed);
}

UINT8 GetVictorRaw(UINT32 channel)
{
	Victor *victor = (Victor *) AllocatePWM(channel, CreateVictor);
	if (victor)
		return victor->GetRaw();
	else
		return 0;
}

void SetVictorRaw(UINT32 module, UINT32 channel, UINT8 value)
{
	Victor *victor = (Victor *) AllocatePWM(module, channel, CreateVictor);
	if (victor) victor->SetRaw(value);
}

UINT8 GetVictorRaw(UINT32 module, UINT32 channel)
{
	Victor *victor = (Victor *) AllocatePWM(module, channel, CreateVictor);
	if (victor)
		return victor->GetRaw();
	else
		return 0;
}

