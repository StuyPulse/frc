#include "PWM.h"
#include "../PWM.h"
#include "CWrappers.h"
#include "../DigitalModule.h"

static bool PWMsInitialized = false;
static PWM *PWMs[kDigitalModules][kPwmChannels];

PWM *AllocatePWM(UINT32 module, UINT32 channel, SensorCreator createObject)
{
	if (!PWMsInitialized)
	{
		for (unsigned i = 0; i < kDigitalModules; i++)
			for (unsigned j = 0; j < kPwmChannels; j++)
				PWMs[i][j] = NULL;
		PWMsInitialized = true;
	}
	if (!SensorBase::CheckPWMModule(module) || !SensorBase::CheckPWMChannel(channel)) 
		return NULL;
	PWM *pwm = PWMs[DigitalModule::SlotToIndex(module)][channel - 1];
	if (pwm == NULL)
	{
		pwm = (PWM *) createObject(module, channel);
		PWMs[DigitalModule::SlotToIndex(module)][channel - 1] = pwm;
	}
	return pwm;
}


PWM *AllocatePWM(UINT32 channel, SensorCreator createObject)
{
	return AllocatePWM(SensorBase::GetDefaultDigitalModule(), channel, createObject);
}

