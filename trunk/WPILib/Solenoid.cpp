/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Solenoid.h"

#include "Resource.h"
#include "Utility.h"

static SEM_ID semaphore = semMCreate(SEM_DELETE_SAFE | SEM_INVERSION_SAFE); // synchronize access to multi-value registers
static Resource *allocated = NULL;

tSolenoid *Solenoid::m_fpgaSolenoidModule = NULL;
UINT32 Solenoid::m_refCount = 0;

/**
 * Common function to implement constructor behavior.
 */
void Solenoid::InitSolenoid()
{
	Resource::CreateResourceObject(&allocated, tSolenoid::kNumSystems * kSolenoidChannels);
	CheckSolenoidModule(m_chassisSlot);
	CheckSolenoidChannel(m_channel);

	m_refCount++;
	if (m_refCount == 1)
	{
		m_fpgaSolenoidModule = new tSolenoid(&status);
	}

	allocated->Allocate(SlotToIndex(m_chassisSlot) * kSolenoidChannels + m_channel - 1);
	wpi_assertCleanStatus(status);
}

/**
 * Constructor.
 * 
 * @param channel The channel on the module to control.
 */
Solenoid::Solenoid(UINT32 channel)
	: m_chassisSlot (GetDefaultSolenoidModule())
	, m_channel (channel)
{
	InitSolenoid();
}

/**
 * Constructor.
 * 
 * @param slot The slot that the 9472 module is plugged into.
 * @param channel The channel on the module to control.
 */
Solenoid::Solenoid(UINT32 slot, UINT32 channel)
	: m_chassisSlot (slot)
	, m_channel (channel)
{
	InitSolenoid();
}

/**
 * Destructor.
 */
Solenoid::~Solenoid()
{
	allocated->Free(SlotToIndex(m_chassisSlot) * kSolenoidChannels + m_channel - 1);
	if (m_refCount == 1)
	{
		delete m_fpgaSolenoidModule;
		m_fpgaSolenoidModule = NULL;
	}
	m_refCount--;
}

/**
 * Convert slot number to index.
 * 
 * @param slot The slot in the chassis where the module is plugged in.
 * @return An index to represent the module internally.
 */
UINT32 Solenoid::SlotToIndex(UINT32 slot)
{
	return 0;
}

/**
 * Set the value of a solenoid.
 * 
 * @param on Turn the solenoid output off or on.
 */
void Solenoid::Set(bool on)
{
	semTake(semaphore, WAIT_FOREVER);
	{
		UINT8 value = m_fpgaSolenoidModule->readDO7_0(&status);
		if (on)
		{
			value |= 1 << (m_channel - 1);
		}
		else
		{
			value &= ~(1 << (m_channel - 1));
		}
		m_fpgaSolenoidModule->writeDO7_0(value, &status);
	}
	semGive(semaphore);

	wpi_assertCleanStatus(status);
}

/**
 * Read the current value of the solenoid.
 * 
 * @return The current value of the solenoid.
 */
bool Solenoid::Get(void)
{
	UINT32 value = m_fpgaSolenoidModule->readDO7_0(&status) & ( 1 << (m_channel - 1));
	wpi_assertCleanStatus(status);
	return (value != 0);
}
