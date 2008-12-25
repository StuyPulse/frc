/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef _ERROR_BASE_H
#define _ERROR_BASE_H

#include <VxWorks.h>
#include "ChipObject.h"
#include "Error.h"
#include  <semlib.h>

/// Use this macro to set the error.
#define wpi_setError(errorBase, code)   (errorBase).SetError(code, __FILE__, __LINE__)

/**
 * Base class for most objects.
 * ErrorBase is the base class for most objects since it holds the generated error
 * for that object. In addition, there is a single instance of a global error object
 */
class ErrorBase
{
public:
	ErrorBase(void);
	virtual ~ErrorBase(void);
	virtual Error& GetError(void);
	virtual const Error& GetError(void) const;
	virtual void SetError(Error::Code code, const char* filename, UINT32 lineNumber) const;
    virtual void ClearError(void);
    virtual bool StatusIsFatal(void) const;
    static Error& GetGlobalError();
protected:
    //  TODO: Get rid of status when rest of the code does not need it
    tRioStatusCode status;
	mutable Error error;
    static SEM_ID globalErrorMutex;
	static Error globalError;
};

#endif
