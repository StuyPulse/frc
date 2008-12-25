/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "I2C.h"
#include "DigitalModule.h"
#include "Utility.h"
#include "WPIStatus.h"

static SEM_ID semaphore = semMCreate(SEM_DELETE_SAFE | SEM_INVERSION_SAFE); // synchronize access to multi-value registers

/**
 * Constructor.
 * 
 * @param module The Digital Module to which the device is conneted.
 * @param deviceAddress The address of the device on the I2C bus.
 */
I2C::I2C(DigitalModule *module, UINT8 deviceAddress)
	: m_module (module)
	, m_deviceAddress (deviceAddress)
{
}

/**
 * Destructor.
 */
I2C::~I2C(void)
{
	
}

/**
 * Execute a write transaction with the device.
 * 
 * Write a byte to a register on a device and wait until the
 *   transaction is complete.
 * 
 * @param registerAddress The address of the register on the device to be written.
 * @param data The byte to write to the register on the device.
 */
void I2C::Write(UINT8 registerAddress, UINT8 data)
{
	semTake(semaphore, WAIT_FOREVER);
	{
		m_module->m_fpgaDIO->writeI2CConfig_Address(m_deviceAddress, &status);
		m_module->m_fpgaDIO->writeI2CConfig_Register(registerAddress, &status);
		m_module->m_fpgaDIO->writeI2CConfig_DataToSend(data, &status);
		m_module->m_fpgaDIO->writeI2CConfig_Read(false, &status);
		UINT8 transaction = m_module->m_fpgaDIO->readI2CStatus_Transaction(&status);
		m_module->m_fpgaDIO->strobeI2CStart(&status);
		while(transaction == m_module->m_fpgaDIO->readI2CStatus_Transaction(&status)) taskDelay(1);
		while(!m_module->m_fpgaDIO->readI2CStatus_Done(&status)) taskDelay(1);
	}
	semGive(semaphore);
}

/**
 * Execute a read transaction with the device.
 * 
 * Read 1, 2, 3, or 4 bytes from a device.
 * Most I2C devices will auto-increment the register pointer internally
 *   allowing you to read up to 4 consecutive registers on a device in a
 *   single transaction.
 * 
 * @param registerAddress The register to read first in the transaction.
 * @param count The number of bytes to read in the transaction.
 * @param buffer A pointer to the array of bytes to store the data read from the device.
 */
void I2C::Read(UINT8 registerAddress, UINT8 count, UINT8 *buffer)
{
	UINT32 data=0;
	if (count < 1 || count > 4)
	{
		wpi_fatal(I2CByteCountError);
		return;
	}
	if (buffer == NULL)
	{
		wpi_fatal(NullParameter);
		return;
	}

	semTake(semaphore, WAIT_FOREVER);
	{
		m_module->m_fpgaDIO->writeI2CConfig_Address(m_deviceAddress, &status);
		m_module->m_fpgaDIO->writeI2CConfig_Register(registerAddress, &status);
		m_module->m_fpgaDIO->writeI2CConfig_BytesToRead(count, &status);
		m_module->m_fpgaDIO->writeI2CConfig_Read(true, &status);
		UINT8 transaction = m_module->m_fpgaDIO->readI2CStatus_Transaction(&status);
		m_module->m_fpgaDIO->strobeI2CStart(&status);
		while(transaction == m_module->m_fpgaDIO->readI2CStatus_Transaction(&status)) taskDelay(1);
		while(!m_module->m_fpgaDIO->readI2CStatus_Done(&status)) taskDelay(1);
		data = m_module->m_fpgaDIO->readI2CDataReceived(&status);
	}
	semGive(semaphore);

	for(INT32 i=0; i<count; i++)
	{
		buffer[i] = (data >> (8*i)) & 0xFF;
	}
}

/**
 * Send a broadcast write to all devices on the I2C bus.
 * 
 * This is not currently implemented!
 * 
 * @param registerAddress The register to write on all devices on the bus.
 * @param data The value to write to the devices.
 */
void I2C::Broadcast(UINT8 registerAddress, UINT8 data)
{
}

/**
 * Verify that a device's registers contain expected values.
 * 
 * Most devices will have a set of registers that contain a known value that
 *   can be used to identify them.  This allows an I2C device driver to easily
 *   verify that the device contains the expected value.
 * 
 * @pre The device must support and be configured to use register auto-increment.
 * 
 * @param registerAddress The base register to start reading from the device.
 * @param count The size of the field to be verified.
 * @param expected A buffer containing the values expected from the device.
 */
bool I2C::VerifySensor(UINT8 registerAddress, UINT8 count, const UINT8 *expected)
{
	UINT8 deviceData[4];
	for (UINT8 i=0, curRegisterAddress = registerAddress; i < count; i+=4, curRegisterAddress+=4)
	{
		UINT8 toRead = count - i < 4 ? count - i : 4;
		Read(curRegisterAddress, toRead, deviceData);
		
		for (UINT8 j=0; j<toRead; j++)
		{
			if(deviceData[j] != expected[i + j]) return false;
		}
	}
	return true;
}

