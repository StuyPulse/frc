// Base class for generated chip objects
// Copyright (c) National Instruments 2008.  All Rights Reserved.

#ifndef __tSystem_h__
#define __tSystem_h__

#include "NiRio.h"
#include <vxWorks.h>

namespace nFPGA
{

class tSystem
{
public:
   tSystem(tRioStatusCode *status);
   ~tSystem();
   static void getFpgaGuid(unsigned *guid_ptr, tRioStatusCode *status);

protected:
   static tRioDeviceHandle _DeviceHandle;

private:
   void configDMA(tRioStatusCode *status);
   static int _ReferenceCount;
   static SEM_ID _ReferenceMutex;
};

}

#endif // __tSystem_h__
