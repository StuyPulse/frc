/*---------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							 */
/* Open Source Software - may be modified and shared by FRC teams. The code  */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib. */
/*---------------------------------------------------------------------------*/

#ifndef UTILITY_H_
#define UTILITY_H_

#include <taskLib.h>

#define wpi_assert(condition) wpi_assert_impl(condition, #condition, __FILE__, __LINE__, __FUNCTION__)
#define wpi_assertCleanStatus(status) wpi_assertCleanStatus_impl(status, __FILE__, __LINE__, __FUNCTION__)
void wpi_assert_impl(bool conditionValue, const char *conditionText, const char *fileName, UINT32 lineNumber, const char *funcName);
void wpi_assertCleanStatus_impl(INT32 status, const char *fileName, UINT32 lineNumber, const char *funcName);

#define wpi_fatal(error) wpi_fatal_impl(wpi_v_##error, wpi_s_##error, __FILE__, __LINE__, __FUNCTION__)
void wpi_fatal_impl(const INT32 statusCode, const char *statusString, const char *fileName, UINT32 lineNumber, const char *funcName);

void wpi_suspendOnAssertEnabled(bool enabled);
void wpi_stackTraceEnable(bool enabled);

UINT16 GetFPGAVersion(void);
UINT32 GetFPGARevision(void);
UINT32 GetFPGATime(void);
INT32 GetRIOUserSwitch(void);
void SetRIOUserLED(UINT32 state);
INT32 GetRIOUserLED(void);
INT32 ToggleRIOUserLED(void);
void SetRIO_FPGA_LED(UINT32 state);
INT32 GetRIO_FPGA_LED(void);
INT32 ToggleRIO_FPGA_LED(void);

#endif // UTILITY_H_
