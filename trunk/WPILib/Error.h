/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef _ERROR_H
#define _ERROR_H

#include "ChipObject/NiRio.h"
#include <VxWorks.h>
#include <string>

//  Forward declarations
class ErrorBase;

/**
 * Error object represents a library error.
 */
class Error
{
public:
    typedef tRioStatusCode Code;

	Error(void);
	~Error(void);
	Code GetCode(void) const;
	const char *GetMessage(void) const;
	const char *GetFilename(void) const;
	UINT32 GetLineNumber(void) const;
    const ErrorBase* GetOriginatingObject(void) const;
	void Clear(void);
	void Set(Code code, const char* filename, UINT32 lineNumber, const ErrorBase* originatingObject);

private:
	Code m_code;
	std::string m_message;
    std::string m_filename;
	UINT32 m_lineNumber;
    const ErrorBase* m_originatingObject;
};

#endif

