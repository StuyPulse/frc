#include "CAnalogChannel.h"

static bool analogChannelsInitialized = false;
static AnalogChannel *analogs[kAnalogModules][kAnalogChannels];

AnalogChannel *AllocateAnalogChannel(UINT32 module, UINT32 channel, SensorCreator createObject)
{
	if (!analogChannelsInitialized)
	{
		for (unsigned i = 0; i < kAnalogModules; i++)
			for (unsigned j = 0; j < kAnalogChannels; j++)
				analogs[i][j] = NULL;
		analogChannelsInitialized = true;
	}
	if (!SensorBase::CheckAnalogModule(module) || !SensorBase::CheckAnalogChannel(channel)) 
		return NULL;
	AnalogChannel *analog = analogs[AnalogModule::SlotToIndex(module)][channel - 1];
	if (analog == NULL)
	{
		analog = (AnalogChannel *) createObject(module, channel);
		analogs[AnalogModule::SlotToIndex(module)][channel - 1] = analog;
	}
	return analog;
}



