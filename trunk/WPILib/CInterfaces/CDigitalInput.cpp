#include "DigitalModule.h"
#include "DigitalInput.h"
#include "CDigitalInput.h"

static DigitalInput* digitalInputs[kDigitalModules][kDigitalChannels];
static bool initialized = false;

UINT32 GetDigitalInput(UINT32 slot, UINT32 channel)
{
	if (!initialized)
	{
		for (unsigned i = 0; i < kDigitalModules; i++)
			for (unsigned j = 0; j < kDigitalChannels; j++)
				digitalInputs[i][j] = NULL;
		initialized = true;
	}
	if (SensorBase::CheckDigitalModule(slot) && SensorBase::CheckDigitalChannel(channel))
	{
		if (digitalInputs[DigitalModule::SlotToIndex(slot)][channel] == NULL)
		{
			digitalInputs[DigitalModule::SlotToIndex(slot)][channel] = new DigitalInput(slot, channel);
		}
		return digitalInputs[slot][channel]->Get();
	}
	return 0;
}

UINT32 GetDigitalInput(UINT32 channel)
{
	return GetDigitalInput(SensorBase::GetDefaultDigitalModule(), channel);
}
