#include "DigitalModule.h"
#include "DigitalOutput.h"
#include "CDigitalOutput.h"

static DigitalOutput* digitalOutputs[kDigitalModules][kDigitalChannels];
static bool initialized = false;

void SetDigitalOutput(UINT32 slot, UINT32 channel, UINT32 value)
{
	if (!initialized)
	{
		for (unsigned i = 0; i < kDigitalModules; i++)
			for (unsigned j = 0; j < kDigitalChannels; j++)
				digitalOutputs[i][j] = NULL;
		initialized = true;
	}
	if (SensorBase::CheckDigitalModule(slot) && SensorBase::CheckDigitalChannel(channel))
	{
		if (digitalOutputs[DigitalModule::SlotToIndex(slot)][channel] == NULL)
		{
			digitalOutputs[DigitalModule::SlotToIndex(slot)][channel] = new DigitalOutput(slot, channel);
		}
		digitalOutputs[slot][channel]->Set(value);
	}
}

void SetDigitalOutput(UINT32 channel, UINT32 value)
{
	SetDigitalOutput(SensorBase::GetDefaultDigitalModule(), channel, value);
}
