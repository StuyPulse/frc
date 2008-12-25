/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "DigitalModule.h"
#include "I2C.h"
#include "PWM.h"
#include "Resource.h"
#include "Utility.h"
#include "WPIStatus.h"

static Resource *DIOChannels = NULL;

/**
 * Get an instance of an Digital Module.
 * Singleton digital module creation where a module is allocated on the first use
 * and the same module is returned on subsequent uses.
 */
DigitalModule* DigitalModule::GetInstance(UINT32 slot)
{
	CheckDigitalModule(slot);
	if (m_modules[slot] == NULL)
	{
		m_modules[slot] = new DigitalModule(slot);
	}
	return (DigitalModule*)m_modules[slot]; 
}

UINT32 DigitalModule::SlotToIndex(UINT32 slot)
{
	const UINT32 mapping[] = {0,0,0,0,0,1,0,0};
	return mapping[slot - 1];
}

/**
 * Create a new instance of an digital module.
 * Create an instance of the digital module object. Initialize all the parameters
 * to reasonable values on start.
 * Setting a global value on an digital module can be done only once unless subsequent
 * values are set the previously set value.
 * Digital modules are a singleton, so the constructor is never called outside of this class.
 */
DigitalModule::DigitalModule(UINT32 slot)
	: Module(slot)
	, m_fpgaDIO (NULL)
{
	Resource::CreateResourceObject(&DIOChannels, tDIO::kNumSystems * kDigitalChannels);
	m_fpgaDIO = new tDIO(SlotToIndex(m_slot), &status);

	// Make sure that the 9403 IONode has had a chance to initialize before continuing.
	while(m_fpgaDIO->readLoopTiming(&status) == 0) taskDelay(1);
	if (m_fpgaDIO->readLoopTiming(&status) != kExpectedLoopTiming)
	{
		wpi_fatal(LoopTimingError);
		printf("DIO LoopTiming: %d, expecting: %d\n", m_fpgaDIO->readLoopTiming(&status), kExpectedLoopTiming);
	}
	m_fpgaDIO->writePWMConfig_Period(PWM::kDefaultPwmPeriod, &status);
	m_fpgaDIO->writePWMConfig_MinHigh(PWM::kDefaultMinPwmHigh, &status);

	// Ensure that PWM output values are set to OFF
	for (UINT32 pwm_index = 1; pwm_index <= kPwmChannels; pwm_index++)
	{
		SetPWM(pwm_index, PWM::kPwmDisabled);
		SetPWMPeriodScale(pwm_index, 3); // Set all to 4x by default.
	}

	// Turn off all relay outputs.
	m_fpgaDIO->writeSlowValue_RelayFwd(0, &status);
	m_fpgaDIO->writeSlowValue_RelayRev(0, &status);
	AddToSingletonList();
}

DigitalModule::~DigitalModule()
{
	delete m_fpgaDIO;
	m_modules[m_slot] = NULL;
}

/**
 * Set a PWM channel to the desired value. The values range from 0 to 255 and the period is controlled
 * by the PWM Period and MinHigh registers.
 * 
 * @param channel The PWM channel to set.
 * @param value The PWM value to set.
 */
void DigitalModule::SetPWM(UINT32 channel, UINT8 value)
{
	CheckPWMChannel(channel);
	m_fpgaDIO->writePWMValue(channel - 1, value, &status);
}

/**
 * Get a value from a PWM channel. The values range from 0 to 255.
 * 
 * @param channel The PWM channel to read from.
 * @return The raw PWM value.
 */
UINT8 DigitalModule::GetPWM(UINT32 channel)
{
	CheckPWMChannel(channel);
	return m_fpgaDIO->readPWMValue(channel - 1, &status);
}

/**
 * Set how how often the PWM signal is squelched, thus scaling the period.
 * 
 * @param channel The PWM channel to configure.
 * @param squelchMask The 2-bit mask of outputs to squelch.
 */
void DigitalModule::SetPWMPeriodScale(UINT32 channel, UINT32 squelchMask)
{
	CheckPWMChannel(channel);
	m_fpgaDIO->writePWMPeriodScale(channel - 1, squelchMask, &status);
}

/**
 * Set the state of a relay.
 * Set the state of a relay output to be forward. Relays have two outputs and each is
 * independently set to 0v or 12v.
 */
void DigitalModule::SetRelayForward(UINT32 channel, bool on)
{
	status = 0;
	CheckRelayChannel(channel);
	// TODO: Protect me with a semaphore.
	UINT32 forwardRelays = m_fpgaDIO->readSlowValue_RelayFwd(&status);
	if (on)
		forwardRelays |= 1 << (channel - 1);
	else
		forwardRelays &= ~(1 << (channel - 1));
	m_fpgaDIO->writeSlowValue_RelayFwd(forwardRelays, &status);
	wpi_assertCleanStatus(status);
}

/**
 * Set the state of a relay.
 * Set the state of a relay output to be reverse. Relays have two outputs and each is
 * independently set to 0v or 12v.
 */
void DigitalModule::SetRelayReverse(UINT32 channel, bool on)
{
	status = 0;
	CheckRelayChannel(channel);
	// TODO: Protect me with a semaphore.
	UINT32 reverseRelays = m_fpgaDIO->readSlowValue_RelayRev(&status);
	if (on)
		reverseRelays |= 1 << (channel - 1);
	else
		reverseRelays &= ~(1 << (channel - 1));
	m_fpgaDIO->writeSlowValue_RelayRev(reverseRelays, &status);
	wpi_assertCleanStatus(status);
}

/**
 * Allocate Digital I/O channels.
 * Allocate channels so that they are not accidently reused. Also the direction is set at the
 * time of the allocation.
 */
bool DigitalModule::AllocateDIO(UINT32 channel, bool input)
{
	status = 0;
	DIOChannels->Allocate(kDigitalChannels * SlotToIndex(m_slot) + channel - 1);
	UINT32 outputEnable = m_fpgaDIO->readOutputEnable(&status);
	UINT32 bitToSet = 1 << (RemapDigitalChannel(channel - 1));
	UINT32 outputEnableValue;
	if (input)
	{
		outputEnableValue = outputEnable & (~ bitToSet ); // clear the bit for read
	}
	else
	{
		outputEnableValue = outputEnable | bitToSet; // set the bit for write
	}
	m_fpgaDIO->writeOutputEnable(outputEnableValue, &status);
	wpi_assertCleanStatus(status);
	return true;
}

/**
 * Free the resource associated with a digital I/O channel.
 */
void DigitalModule::FreeDIO(UINT32 channel)
{
	DIOChannels->Free(kDigitalChannels * SlotToIndex(m_slot) + channel - 1);
}

/**
 * Write a digital I/O bit to the FPGA.
 * Set a single value on a digital I/O channel.
 */
void DigitalModule::SetDIO(UINT32 channel, short value)
{
	status = 0;
	if (value != 0 && value != 1)
	{
		wpi_fatal(NonBinaryDigitalValue);
		if (value != 0)
			value = 1;
	}
	UINT16 currentDIO = m_fpgaDIO->readDO(&status);
	if(value == 0)
	{
		currentDIO = currentDIO & ~(1 << RemapDigitalChannel(channel - 1));
	}
	else if (value == 1)
	{
		currentDIO = currentDIO | (1 << RemapDigitalChannel(channel - 1));
	} 
	m_fpgaDIO->writeDO(currentDIO, &status);
	wpi_assertCleanStatus(status);
}

/**
 * Read a digital I/O bit from the FPGA.
 * Get a single value from a digital I/O channel.
 */
UINT32 DigitalModule::GetDIO(UINT32 channel)
{
	status = 0;
	UINT32 currentDIO = m_fpgaDIO->readDI(&status);
	
	//Shift 00000001 over channel-1 places.
	//AND it against the currentDIO
	//if it == 0, then return 0
	//else return 1
	wpi_assertCleanStatus(status);
	UINT32 value = (currentDIO >> RemapDigitalChannel(channel - 1)) & 1;
	return value;
}

/**
 * Generate a single pulse.
 * Write a pulse to the specified digital output channel. There can only be a single pulse going at any time.
 */
void DigitalModule::Pulse(UINT32 channel, UINT8 pulseLength)
{
	UINT32 mask = 1 << RemapDigitalChannel(channel - 1);
	m_fpgaDIO->writePulseLength(pulseLength, &status);
	m_fpgaDIO->writePulse(mask, &status);
	wpi_assertCleanStatus(status);
}

/**
 * Check a DIO line to see if it is currently generating a pulse.
 */
bool DigitalModule::IsPulsing(UINT32 channel)
{
	UINT32 mask = 1 << RemapDigitalChannel(channel - 1);
	UINT16 pulseRegister = m_fpgaDIO->readPulse(&status);
	wpi_assertCleanStatus(status);
	return pulseRegister & mask != 0;
}

/**
 * Check if any DIO line is currently generating a pulse.
 */
bool DigitalModule::IsPulsing(void)
{
	UINT16 pulseRegister = m_fpgaDIO->readPulse(&status);
	wpi_assertCleanStatus(status);
	return pulseRegister != 0;
}

/**
 * Return a pointer to an I2C object for this digital module
 * The caller is responsible for deleting the pointer.
 */
I2C* DigitalModule::GetI2C(UINT32 address)
{
	return new I2C(this, address);
}


