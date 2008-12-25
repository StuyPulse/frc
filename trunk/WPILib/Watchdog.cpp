/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Watchdog.h"

#include "Utility.h"

/**
 * The Watchdog is born.
 */
Watchdog::Watchdog(void)
	:	m_fpgaWatchDog(NULL)
{
	m_fpgaWatchDog = new tWatchdog(&status);
	wpi_assertCleanStatus(status);
	SetExpiration(kDefaultWatchdogExpiration_ms);
	SetEnabled(true);
}

/**
 * Time to bury him in the back yard.
 */
Watchdog::~Watchdog(void)
{
	SetEnabled(false);
	delete m_fpgaWatchDog;
	m_fpgaWatchDog = NULL;
}

/**
 * Throw the dog a bone.
 * 
 * When everything is going well, you feed your dog when you get home.
 * Let's hope you don't drive your car off a bridge on the way home...
 * Your dog won't get fed and he will starve to death.
 * 
 * By the way, it's not cool to ask the neighbor (some random task) to
 * feed your dog for you.  He's your responsibility!
 * 
 * @returns Returns the previous state of the watchdog before feeding it.
 */
bool Watchdog::Feed(void)
{
	bool previous = GetEnabled();
	m_fpgaWatchDog->strobeFeed(&status);
	wpi_assertCleanStatus(status);
	return previous;
}

/**
 * Put the watchdog out of its misery.
 * 
 * Don't wait for your dying robot to starve when there is a problem.
 * Kill it quickly, cleanly, and humanely.
 */
void Watchdog::Kill(void)
{
	m_fpgaWatchDog->strobeKill(&status);
	wpi_assertCleanStatus(status);
}

/**
 * Read how long it has been since the watchdog was last fed.
 * 
 * @return The number of milliseconds since last meal.
 */
UINT32 Watchdog::GetTimer(void)
{
	UINT32 timer = m_fpgaWatchDog->readTimer(&status);
	wpi_assertCleanStatus(status);
	return timer / (kSystemClockTicksPerMicrosecond * 1000);
}

/**
 * Read what the current expiration is.
 * 
 * @return The number of milliseconds before starvation.
 */
UINT32 Watchdog::GetExpiration(void)
{
	UINT32 expiration = m_fpgaWatchDog->readExpiration(&status);
	wpi_assertCleanStatus(status);
	return expiration / (kSystemClockTicksPerMicrosecond * 1000);
}

/**
 * Configure how many milliseconds your watchdog can be neglected before he starves to death.
 * 
 * @param expiration_ms The number of milliseconds before starvation.
 */
void Watchdog::SetExpiration(UINT32 expiration_ms)
{
	m_fpgaWatchDog->writeExpiration(expiration_ms * (kSystemClockTicksPerMicrosecond * 1000), &status);
	wpi_assertCleanStatus(status);
}

/**
 * Find out if the watchdog is currently enabled or disabled (mortal or immortal).
 * 
 * @return Enabled or disabled.
 */
bool Watchdog::GetEnabled(void)
{
	bool enabled = !m_fpgaWatchDog->readImmortal(&status);
	wpi_assertCleanStatus(status);
	return enabled;
}

/**
 * Enable or disable the watchdog timer.
 * 
 * When enabled, you must keep feeding the watchdog timer to
 * keep the watchdog active, and hence the dangerous parts 
 * (motor outputs, etc.) can keep functioning.
 * When disabled, the watchdog is immortal and will remain active
 * even without being fed.  It will also ignore any kill commands
 * while disabled.
 * 
 * @param enabled Enable or disable the watchdog.
 */
void Watchdog::SetEnabled(bool enabled)
{
	m_fpgaWatchDog->writeImmortal(!enabled, &status);
	wpi_assertCleanStatus(status);
}

/**
 * Check in on the watchdog and make sure he's still kicking.
 * 
 * This indicates that your watchdog is allowing the system to operate.
 * It is still possible that the network communications is not allowing the
 * system to run, but you can check this to make sure it's not your fault.
 * Check IsSystemActive() for overall system status.
 * 
 * If the watchdog is disabled, then your watchdog is immortal.
 * 
 * @return Is the watchdog still alive?
 */
bool Watchdog::IsAlive(void)
{
	bool alive = m_fpgaWatchDog->readStatus_Alive(&status);
	wpi_assertCleanStatus(status);
	return alive;
}

/**
 * Check on the overall status of the system.
 * 
 * @return Is the system active (i.e. PWM motor outputs, etc. enabled)?
 */
bool Watchdog::IsSystemActive(void)
{
	bool alive = m_fpgaWatchDog->readStatus_SystemActive(&status);
	wpi_assertCleanStatus(status);
	return alive;
}

