// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Global_h__
#define __Global_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tGlobal : public tSystem
{
public:
   tGlobal(tRioStatusCode *status);
   ~tGlobal();

   static const unsigned char kNumSystems;




   static unsigned short readVersion(tRioStatusCode *status);

   static void writeFPGA_LED(bool value, tRioStatusCode *status);
   static bool readFPGA_LED(tRioStatusCode *status);

   static unsigned int readLocalTime(tRioStatusCode *status);

   static unsigned int readRevision(tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define Global_Version_ADDRESS 0x8118
   #define Global_FPGA_LED_ADDRESS 0x811C
   #define Global_LocalTime_ADDRESS 0x8110
   #define Global_Revision_ADDRESS 0x8114


};

}
}

#endif // __Global_h__
