/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Ultrasonic.h"

#include "Counter.h"
#include "DigitalInput.h"
#include "DigitalOutput.h"
#include "Timer.h"
#include "Utility.h"
#include "WPIStatus.h"

static INT32 g_taskID = 0; // task doing the sensing
static Ultrasonic *g_firstSensor = NULL; // head of the ultrasonic sensor list
static bool g_automaticEnabled = false; // automatic round robin mode
static SEM_ID g_semaphore = 0; // synchronize access to the list of sensors

/**
 * Background task that goes through the list of ultrasonic sensors and pings each one in turn. The counter
 * is configured to read the timing of the returned echo pulse.
 */
void Ultrasonic::ultrasonicChecker(void)
{
	Ultrasonic *u= NULL;
	Timer timer;
	timer.Start();
	while (g_automaticEnabled)
	{
		if (u == NULL)
			u = g_firstSensor;
		if (u->IsEnabled())
		{
			// do a single ping and get results
			INT32 finishedCounterValue = u->m_counter->Get() + 2;
			u->m_pingChannel->Pulse(kPingTime);
			timer.Reset();
			while (timer.Get() < kMaxUltrasonicTime)
			{
				if (u->m_counter->Get() == finishedCounterValue)
					break;
				Wait(1);
			}
			Wait(20);
		}
		u = u->m_nextSensor;
	}
}

/**
 * Initialize the Ultrasonic Sensor.
 * This is the common code that initializes the ultrasonic sensor given that there
 * are two digital I/O channels allocated. If the system was running in automatic mode (round robin)
 * when the new sensor is added, it is stopped, the sensor is added, then automatic mode is
 * restored.
 */
void Ultrasonic::Initialize(void)
{
	if (g_semaphore == 0) // static g_semaphore created 1st time only
		g_semaphore = semBCreate(SEM_Q_PRIORITY, SEM_FULL);

	bool originalMode = g_automaticEnabled;
	SetAutomaticMode(false); // kill task when adding a new sensor
	semTake(g_semaphore, WAIT_FOREVER); // link this instance on the list
	{
		m_nextSensor = g_firstSensor;
		g_firstSensor = this;
	}
	semGive(g_semaphore);

	m_counter = new Counter(m_echoChannel); // set up counter for this sensor
	m_counter->SetSemiPeriodMode(true);
	m_counter->Reset();
	m_counter->Start();
	m_enabled = true; // make it available for round robin scheduling
	SetAutomaticMode(originalMode);
}

/**
 * Create an instance of the Ultrasonic Sensor using the default module.
 * This is designed to supchannel the Daventech SRF04 and Vex ultrasonic sensors. This
 * constructor assumes that both digital I/O channels are in the default digital module.
 * @param pingChannel The digital output channel that sends the pulse to initiate the sensor sending
 * the ping.
 * @param echoChannel The digital input channel that receives the echo. The length of time that the
 * echo is high represents the round trip time of the ping, and the distance.
 */
Ultrasonic::Ultrasonic(UINT32 pingChannel, UINT32 echoChannel)
{
	m_pingChannel = new DigitalOutput(pingChannel);
	m_echoChannel = new DigitalInput(echoChannel);
	m_allocatedChannels = true;
	Initialize();
}

/**
 * Create an instance of an Ultrasonic Sensor from a DigitalInput for the echo channel and a DigitalOutput
 * for the ping channel.
 * @param pingChannel The digital output object that starts the sensor doing a ping. Requires a 10uS pulse to start.
 * @param echoChannel The digital input object that times the return pulse to determine the range.
 */
Ultrasonic::Ultrasonic(DigitalOutput *pingChannel, DigitalInput *echoChannel)
{
	if (pingChannel == NULL || echoChannel == NULL)
	{
		wpi_fatal(NullParameter);
		return;
	}
	m_allocatedChannels = false;
	m_pingChannel = pingChannel;
	m_echoChannel = echoChannel;
	Initialize();
}

/**
 * Create an instance of an Ultrasonic Sensor from a DigitalInput for the echo channel and a DigitalOutput
 * for the ping channel.
 * @param pingChannel The digital output object that starts the sensor doing a ping. Requires a 10uS pulse to start.
 * @param echoChannel The digital input object that times the return pulse to determine the range.
 */
Ultrasonic::Ultrasonic(DigitalOutput &pingChannel, DigitalInput &echoChannel)
{
	m_allocatedChannels = false;
	m_pingChannel = &pingChannel;
	m_echoChannel = &echoChannel;
	Initialize();
}

/**
 * Create an instance of the Ultrasonic sensor using specified modules.
 * This is designed to supchannel the Daventech SRF04 and Vex ultrasonic sensors. This
 * constructors takes the channel and module slot for each of the required digital I/O channels.
 * @param pingSlot The digital module that the pingChannel is in.
 * @param pingChannel The digital output channel that sends the pulse to initiate the sensor
 * sending the ping.
 * @param echoSlot The digital module that the echoChannel is in.
 * @param echoChannel The digital input channel that receives the echo. The length of time
 * that the echo is high represents the round trip time of the ping, and the distance.
 */
Ultrasonic::Ultrasonic(UINT32 pingSlot, UINT32 pingChannel,
		UINT32 echoSlot, UINT32 echoChannel)
{
	m_pingChannel = new DigitalOutput(pingSlot, pingChannel);
	m_echoChannel = new DigitalInput(echoSlot, echoChannel);
	m_allocatedChannels = true;
	Initialize();
}

/**
 * Destructor for the ultrasonic sensor.
 * Delete the instance of the ultrasonic sensor by freeing the allocated digital channels.
 * If the system was in automatic mode (round robin), then it is stopped, then started again
 * after this sensor is removed (provided this wasn't the last sensor).
 */
Ultrasonic::~Ultrasonic(void)
{
	bool wasAutomaticMode = g_automaticEnabled;
	SetAutomaticMode(false);
	if (m_allocatedChannels)
	{
		delete m_pingChannel;
		delete m_echoChannel;
	}
	wpi_assert(g_firstSensor != NULL);

	semTake(g_semaphore, WAIT_FOREVER);
	{
		if (this == g_firstSensor)
		{
			g_firstSensor = m_nextSensor;
			if (g_firstSensor == NULL)
			{
				SetAutomaticMode(false);
			}
		}
		else
		{
			wpi_assert(g_firstSensor->m_nextSensor != NULL);
			for (Ultrasonic *s = g_firstSensor; s != NULL; s = s->m_nextSensor)
			{
				if (this == s->m_nextSensor)
				{
					s->m_nextSensor = s->m_nextSensor->m_nextSensor;
					break;
				}
			}
		}
	}
	semGive(g_semaphore);
	if (g_firstSensor != NULL && wasAutomaticMode)
		SetAutomaticMode(true);
}

/**
 * Turn Automatic mode on/off.
 * When in Automatic mode, all sensors will fire in round robin, waiting a set
 * time between each sensor.
 * @param enabling Set to true if round robin scheduling should start for all the ultrasonic sensors. This
 * scheduling method assures that the sensors are non-interfering because no two sensors fire at the same time.
 * If another scheduling algorithm is preffered, it can be implemented by pinging the sensors manually and waiting
 * for the results to come back.
 */
void Ultrasonic::SetAutomaticMode(bool enabling)
{
	if (enabling == g_automaticEnabled)
		return; // ignore the case of no change

	g_automaticEnabled = enabling;
	if (enabling)
	{
		// enabling automatic mode.
		// Clear all the counters so no data is valid
		for (Ultrasonic *u = g_firstSensor; u != NULL; u = u->m_nextSensor)
		{
			u->m_counter->Reset();
		}
		// Start round robin task
		if (g_taskID == 0) // start the round robin task
		{
			g_taskID = taskSpawn("UltrasonicChecker", kPriority,
					VX_FP_TASK, // options
					20000, // stack size
					(FUNCPTR) ultrasonicChecker, // function to start
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0); // additional unused parameters
			wpi_assert(g_taskID != ERROR);
		}
	}
	else
	{
		// disabling automatic mode. Wait for task to stop running.
		while (taskIdVerify(g_taskID) == OK)
			// wait for the round robin task to exit
			taskDelay(1);

		// clear all the counters (data now invalid) since automatic mode is stopped
		for (Ultrasonic *u = g_firstSensor; u != NULL; u = u->m_nextSensor)
		{
			u->m_counter->Reset();
		}
		g_taskID = 0;
	}
}

/**
 * Single ping to ultrasonic sensor.
 * Send out a single ping to the ultrasonic sensor. This only works if automatic (round robin)
 * mode is disabled. A single ping is sent out, and the counter should count the semi-period
 * when it comes in. The counter is reset to make the current value invalid.
 */
void Ultrasonic::Ping(void)
{
	// TODO: Either assert or disable, not both.
	wpi_assert(!g_automaticEnabled);
	SetAutomaticMode(false); // turn off automatic round robin if pinging single sensor
	m_counter->Reset(); // reset the counter to zero (invalid data now)
	m_pingChannel->Pulse(kPingTime); // do the ping to start getting a single range
}

/**
 * Check if there is a valid range measurement.
 * The ranges are accumulated in a counter that will increment on each edge of the echo (return)
 * signal. If the count is not at least 2, then the range has not yet been measured, and is invalid.
 */
bool Ultrasonic::IsRangeValid(void)
{
	return m_counter->Get() > 1;
}

/**
 * Get the range in inches from the ultrasonic sensor.
 * @return UINT32 Range in inches of the target returned from the ultrasonic sensor. If there is
 * no valid value yet, i.e. at least one measurement hasn't completed, then return 0.
 */
UINT32 Ultrasonic::GetRangeInches(void)
{
	if (IsRangeValid())
		return m_counter->GetPeriod() * kSpeedOfSoundInchesPerSec / (2 * 1000000);
	else
		return 0;
}

/**
 * Get the range in millimeters from the ultrasonic sensor.
 * @return UINT32 Range in millimeters of the target returned by the ultrasonic sensor.
 * If there is no valid value yet, i.e. at least one measurement hasn't complted, then return 0.
 */
UINT32 Ultrasonic::GetRangeMM(void)
{
	return GetRangeInches() * 254 / 10;
}

