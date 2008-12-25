// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Watchdog_h__
#define __Watchdog_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tWatchdog : public tSystem
{
public:
   tWatchdog(tRioStatusCode *status);
   ~tWatchdog();

   static const unsigned char kNumSystems;


   typedef
   union{
      struct{
         unsigned SystemActive : 1;
         unsigned Alive : 1;
      };
      struct{
         unsigned value : 2;
      };
   } tStatus;


   static tStatus readStatus(tRioStatusCode *status);
   static bool readStatus_SystemActive(tRioStatusCode *status);
   static bool readStatus_Alive(tRioStatusCode *status);

   static void strobeFeed(tRioStatusCode *status);

   static void strobeKill(tRioStatusCode *status);

   static void writeImmortal(bool value, tRioStatusCode *status);
   static bool readImmortal(tRioStatusCode *status);

   static void writeExpiration(unsigned int value, tRioStatusCode *status);
   static unsigned int readExpiration(tRioStatusCode *status);

   static unsigned int readTimer(tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define Watchdog_Status_ADDRESS 0x84EC
   #define Watchdog_Feed_ADDRESS 0x84E8
   #define Watchdog_Kill_ADDRESS 0x84E4
   #define Watchdog_Immortal_ADDRESS 0x84D8
   #define Watchdog_Expiration_ADDRESS 0x84DC
   #define Watchdog_Timer_ADDRESS 0x84E0


};

}
}

#endif // __Watchdog_h__
