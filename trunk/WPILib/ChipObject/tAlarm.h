// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Alarm_h__
#define __Alarm_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tAlarm : public tSystem
{
public:
   tAlarm(tRioStatusCode *status);
   ~tAlarm();

   static const unsigned char kNumSystems;




   static void writeTriggerTime(unsigned int value, tRioStatusCode *status);
   static unsigned int readTriggerTime(tRioStatusCode *status);

   static void writeEnable(bool value, tRioStatusCode *status);
   static bool readEnable(tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define Alarm_TriggerTime_ADDRESS 0x8124
   #define Alarm_Enable_ADDRESS 0x8120


};

}
}

#endif // __Alarm_h__
