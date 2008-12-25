// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Solenoid_h__
#define __Solenoid_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tSolenoid : public tSystem
{
public:
   tSolenoid(tRioStatusCode *status);
   ~tSolenoid();

   static const unsigned char kNumSystems;




   static void writeDO7_0(unsigned char value, tRioStatusCode *status);
   static unsigned char readDO7_0(tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define Solenoid_DO7_0_ADDRESS 0x84C0


};

}
}

#endif // __Solenoid_h__
