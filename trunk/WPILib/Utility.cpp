/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "Utility.h"

#define WPI_STATUS_DEFINE_STRINGS
#include "WPIStatus.h"

#include "ChipObject.h"
#include <dbgLib.h>
#include <stdio.h>
#include <sysSymTbl.h>

#define DBG_DEMANGLE_PRINT_LEN 256  /* Num chars of demangled names to print */

extern "C"
{
	extern char *	cplusDemangle (char *source, char *dest, INT32 n);
}

char *wpiGetLabel(UINT addr, INT32 *found = NULL)
{
	INT32 pVal;
	SYM_TYPE pType;
	char name[MAX_SYS_SYM_LEN + 1];
	static char label[DBG_DEMANGLE_PRINT_LEN + 1 + 11];
	bzero(label, DBG_DEMANGLE_PRINT_LEN + 1 + 11);

	if (symFindByValue(sysSymTbl, addr, name, &pVal, &pType) == OK)
	{
		cplusDemangle(name, label, sizeof(label) - 11);
		if ((UINT)pVal != addr)
		{
			sprintf(&label[strlen(label)], "+0x%04x", addr-pVal);
			if (found) *found = 2;
		}
		else
		{
			if (found) *found = 1;
		}
	}
	else
	{
		sprintf(label, "0x%04x", addr);
		if (found) *found = 0;
	}

	return label;
}
/*
static void wpiTracePrint(INSTR *caller, INT32 func, INT32 nargs, INT32 *args, INT32 taskId, BOOL isKernelAdrs)
{
	char buf [MAX_SYS_SYM_LEN * 2];
	INT32 ix;
	INT32 len = 0;
	len += sprintf (&buf [len], "%s <%#010x>: ", wpiGetLabel((UINT)caller), (INT32)caller);
	len += sprintf (&buf [len], "%s <%#010x> (", wpiGetLabel((UINT)func), func);
	for (ix = 0; ix < nargs; ix++)
	{
		if (ix != 0)
			len += sprintf (&buf [len], ", ");
		len += sprintf (&buf [len], "%#x", args [ix]);
	}
	len += sprintf (&buf [len], ")\n");

	printf(buf);
}
*/
static void wpiCleanTracePrint(INSTR *caller, INT32 func, INT32 nargs, INT32 *args, INT32 taskId, BOOL isKernelAdrs)
{
	char buf [MAX_SYS_SYM_LEN];
	INT32 ix;
	INT32 len = 0;
	INT32 nameFound = 0;
	INT32 params = 0;
	INT32 totalnargs = nargs;
	char *funcName = wpiGetLabel((UINT)func, &nameFound);
	// Ignore names that are not exact symbol address matches.
	if (nameFound != 1) return;

	// Ignore internal function name matches.
	if (strncmp(funcName, "wpi_assert", 10) == 0) return;
	if (strncmp(funcName, "wpi_fatal", 9) == 0) return;

	// Find the number of arguments in the name string.
	char *start = strchr(funcName, '(');
	char *end = strrchr(funcName, ')');
	if (start + 1 != end && start != NULL)
	{
		do
		{
			params++;
			if(strncmp(start+1, "bool", 4) == 0 || strncmp(start+2, "bool", 4) == 0)
			{
				totalnargs++;
			}
			start = strchr(start + 1, ',');
		}
		while(start < end && start != NULL);
	}
	char *funcNameEnd = strchr(funcName, '(');
	*funcNameEnd = 0;
	len += sprintf (&buf [len], funcName);

	// If this is a member function, print out the this pointer value.
	if (totalnargs - params == 1)
	{
		len += sprintf (&buf [len], "<this=%#x>", args [0]);
	}

	// Print out the argument values.
	len += sprintf (&buf [len], "(");
	for (ix = totalnargs - params; ix < nargs; ix++)
	{
		if (ix != totalnargs - params)
			len += sprintf (&buf [len], ", ");
		len += sprintf (&buf [len], "%#x", args [ix]);
	}
	len += sprintf (&buf [len], ")\n");

	printf(buf);
}

extern "C"
{
	extern void trcStack(REG_SET* pRegs, FUNCPTR printRtn, INT32 tid);
}

static INT32 wpiStackTask(INT32 taskId)
{
	taskDelay(1);
	tt(taskId);

	REG_SET regs;
	taskRegsGet(taskId, &regs);
	printf("\n\nCustom stack trace!\n\n");
	trcStack(&regs, (FUNCPTR) wpiCleanTracePrint, taskId);

	// The task should be resumed because it had to be suspended to get the stack trace.
	taskResume(taskId);
	return 0;
}

static void wpiSelfTrace(void)
{
	INT32 priority=100;
	taskPriorityGet(0, &priority);
	taskSpawn("FRCStackTraceTask",
					priority + 1,				// priority
					VX_FP_TASK,					// floating point C++ context save
					64000,						// stack size
					(FUNCPTR)wpiStackTask,	// function to be called
					taskIdSelf(),0,0,0,0,0,0,0,0,0);	// parameters
}

static bool stackTraceEnabled = false;
static bool suspendOnAssertEnabled = false;

/**
 * Enable Stack trace after asserts.
 */
void wpi_stackTraceEnable(bool enabled)
{
	stackTraceEnabled = enabled;
}

/**
 * Enable suspend on asssert.
 * If enabled, the user task will be suspended whenever an assert fails. This
 * will allow the user to attach to the task with the debugger and examine variables
 * around the failure.
 */
void wpi_suspendOnAssertEnabled(bool enabled)
{
	suspendOnAssertEnabled = enabled;
}

static void wpi_handleTracing(void)
{
	if (stackTraceEnabled)
	{
		printf("\n-----------<Stack Trace>----------------\n");
		wpiSelfTrace();
		// Task must be suspended for the stack trace to work.
		taskSuspend(0);
	}
	printf("\n");
}

/**
 * Assert implementation.
 * This allows breakpoints to be set on an assert.
 * The users don't call this, but instead use the wpi_assert macro in Utility.h.
 */
void wpi_assert_impl(bool conditionValue, const char *conditionText, const char *fileName,
		UINT32 lineNumber, const char *funcName)
{
	if (!conditionValue)
	{
		printf("\n\n>>>>Assert \"%s\" failed in %s() in %s at line %d\n",
				conditionText, funcName, fileName, lineNumber);
		wpi_handleTracing();
		if (suspendOnAssertEnabled) taskSuspend(0);
	}
}


/**
 * Assert status clean implementation.
 * This allows breakpoints to be set on an assert.
 * This allows the fatal status to be printed.
 * The users don't call this, but instead use the wpi_assertCleanStatus macro in Utility.h.
 */
void wpi_assertCleanStatus_impl(INT32 status, const char *fileName, UINT32 lineNumber, const char *funcName)
{
	if (status != 0)
	{
		printf("\n\n>>>>%s: status == %d (0x%08X) in %s() in %s at line %d\n",
				status < 0 ? "ERROR" : "WARNING", status, (UINT32)status, funcName, fileName, lineNumber);
		wpi_handleTracing();
		if (suspendOnAssertEnabled) taskSuspend(0);
	}
}

void wpi_fatal_impl(const INT32 statusCode, const char *statusString,
					const char *fileName, UINT32 lineNumber, const char *funcName)
{
	printf("\n\n>>>>Fatal error \"%s\" in %s() in %s at line %d\n",
			statusString, funcName, fileName, lineNumber);
	wpi_handleTracing();
}


/**
 * Return the FPGA Version number.
 * For now, expect this to be 2009.
 * @return FPGA Version number.
 */
UINT16 GetFPGAVersion(void)
{
	tRioStatusCode status = 0;
	UINT16 version = tGlobal::readVersion(&status); 
	wpi_assertCleanStatus(status);
	return version;
}

/**
 * Return the FPGA Revision number.
 * The format of the revision is 3 numbers.
 * The 12 most significant bits are the Major Revision.
 * the next 8 bits are the Minor Revision.
 * The 12 least significant bits are the Build Number.
 * @return FPGA Revision number.
 */
UINT32 GetFPGARevision(void)
{
	tRioStatusCode status = 0;
	UINT32 revision = tGlobal::readRevision(&status);
	wpi_assertCleanStatus(status);
	return revision;
}

/**
 * Read the microsecond timer from the FPGA.
 * 
 * @return The current time in microseconds according to the FPGA.
 */
UINT32 GetFPGATime(void)
{
	tRioStatusCode status = 0;
	UINT32 time = tGlobal::readLocalTime(&status);
	wpi_assertCleanStatus(status);
	return time;
}

// RT hardware access functions exported from ni_emb.out
extern "C"
{
	INT32 UserSwitchInput(INT32 nSwitch);
	INT32 LedInput(INT32 led);
	INT32 LedOutput(INT32 led, INT32 value);
}

/**
 * Read the value of the USER1 DIP switch on the cRIO.
 */
INT32 GetRIOUserSwitch(void)
{
	INT32 switchValue = UserSwitchInput(0);
	wpi_assert(switchValue >= 0);
	return switchValue > 0;
}

/**
 * Set the state of the USER1 status LED on the cRIO.
 */
void SetRIOUserLED(UINT32 state)
{
	LedOutput(0, state > 0);
}

/**
 * Get the current state of the USER1 status LED on the cRIO.
 * @return The curent state of the USER1 LED.
 */
INT32 GetRIOUserLED(void)
{
	return LedInput(0);
}

/**
 * Toggle the state of the USER1 status LED on the cRIO.
 * @return The new state of the USER1 LED.
 */
INT32 ToggleRIOUserLED(void)
{
	INT32 ledState = !GetRIOUserLED();
	SetRIOUserLED(ledState);
	return ledState;
}

/**
 * Set the state of the FPGA status LED on the cRIO.
 */
void SetRIO_FPGA_LED(UINT32 state)
{
	tRioStatusCode status = 0;
	tGlobal::writeFPGA_LED(state, &status);
}

/**
 * Get the current state of the FPGA status LED on the cRIO.
 * @return The curent state of the FPGA LED.
 */
INT32 GetRIO_FPGA_LED(void)
{
	tRioStatusCode status = 0;
	return tGlobal::readFPGA_LED(&status);
}

/**
 * Toggle the state of the FPGA status LED on the cRIO.
 * @return The new state of the FPGA LED.
 */
INT32 ToggleRIO_FPGA_LED(void)
{
	INT32 ledState = !GetRIO_FPGA_LED();
	SetRIO_FPGA_LED(ledState);
	return ledState;
}

