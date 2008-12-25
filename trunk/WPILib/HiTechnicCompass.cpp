/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "HiTechnicCompass.h"
#include "DigitalModule.h"
#include "I2C.h"
#include "Utility.h"
#include "WPIStatus.h"

/**
 * Constructor.
 * 
 * @param slot The slot of the digital module that the sensor is plugged into.
 */
HiTechnicCompass::HiTechnicCompass(UINT32 slot)
	: m_i2c (NULL)
{
	DigitalModule *module = DigitalModule::GetInstance(slot);
	m_i2c = module->GetI2C(kAddress);

	// Verify Sensor
	const UINT8 kExpectedManufacturer[] = "HiTechnc";
	const UINT8 kExpectedSensorType[] = "Compass ";
	if ( ! m_i2c->VerifySensor(kManufacturerBaseRegister, kManufacturerSize, kExpectedManufacturer) )
	{
		wpi_fatal(CompassManufacturerError);
		return;
	}
	if ( ! m_i2c->VerifySensor(kSensorTypeBaseRegister, kSensorTypeSize, kExpectedSensorType) )
	{
		wpi_fatal(CompassTypeError);
	}
}

/**
 * Destructor.
 */
HiTechnicCompass::~HiTechnicCompass(void)
{
	delete m_i2c;
	m_i2c = NULL;
}

/**
 * Get the compass angle in degrees.
 * 
 * The resolution of this reading is 1 degree.
 * 
 * @return Angle of the compass in degrees.
 */
float HiTechnicCompass::GetAngle(void)
{
	UINT16 heading;
	m_i2c->Read(kHeadingRegister, sizeof(heading), (UINT8 *)&heading);

	// Sensor is little endian... swap bytes
	heading = (heading >> 8) | (heading << 8);

	return (float)heading;
}

