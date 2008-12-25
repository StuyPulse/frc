/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef WPI_STATUS_H
#define WPI_STATUS_H

#ifdef WPI_STATUS_DEFINE_STRINGS
#define S(label, offset, message) const INT32 wpi_v_##label = offset; const char *wpi_s_##label = message ;
#else
#define S(label, offset, message) const INT32 wpi_v_##label = offset; extern const char *wpi_s_##label;
#endif

/*
 * Fatal errors
 */
S(IndexOutOfRange, -1, "Allocating channel or module that is out of range");
S(NotAllocated, -2, "Attempting to free unallocated resource");
S(ResourceAlreadyAllocated, -3, "Attempting to resuse an allocated resource");
S(NoAvailablePorts, -4, "No available ports to allocate");
S(NullParameter, -5, "An address parameter to a method is NULL");
S(GyroNotAccumulatorChannel, -6, "Gyro can only be used with Analog Channel 1 on either module");
S(CompassManufacturerError, -7, "Compass manufacturer doesn't match HiTechnic");
S(CompassTypeError, -8, "Compass type doesn't match expected type for HiTechnic compass");
S(I2CByteCountError, -9, "I2C byte count must be between 1 and 4");
S(AnalogTriggerLimitOrderError, -10, "AnalogTrigger limits error.  Lower limit > Upper Limit");
S(AnalogTriggerPulseOutputError, -11, "Attempted to read AnalogTrigger pulse output.");
S(TaskError, -12, "Task can't be started");
S(TaskIDError, -13, "Task error: Invalid ID.");
S(TaskDeletedError, -14, "Task error: Task already deleted.");
S(TaskOptionsError, -15, "Task error: Invalid options.");
S(TaskMemoryError, -16, "Task can't be started due to insufficient memory.");
S(TaskPriorityError, -17, "Task error: Invalid priority [1-255].");
S(DriveUninitialized, -18, "RobotDrive not initialized for the C interface");
S(CompressorNonMatching, -19, "Compressor slot/channel doesn't match previous instance");
S(CompressorAlreadyDefined, -20, "Creating a second compressor instance");
S(CompressorUndefined, -21, "Using compressor functions without defining compressor");
/*
 * Warnings
 */
S(SampleRateTooHigh, 1, "Analog module sample rate is too high");
S(VoltageOutOfRange, 2, "Voltage to convert to raw value is out of range [-10; 10]");
S(CompressorTaskError, 3, "Compressor task won't start");
S(LoopTimingError, 4, "Digital module loop timing is not the expected value");
S(NonBinaryDigitalValue, 5, "Digital output value is not 0 or 1");
S(IncorrectBatteryChannel, 6, "Battery measurement channel is not correct value");
S(BadJoystickIndex, 7, "Joystick index is out of range, should be 1-4");
S(BadJoystickAxis, 8, "Joystick axis is out of range");
S(InvalidMotorIndex, 9, "Motor index is out of range, should be 0-3");
S(DriverStationTaskError, 10, "Driver Station task won't start");

#endif
