// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __DMA_h__
#define __DMA_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tDMA : public tSystem
{
public:
   tDMA(tRioStatusCode *status);
   ~tDMA();

   static const unsigned char kNumSystems;


   typedef
   union{
      struct{
         unsigned Pause : 1;
         unsigned Enable_AI0_Low : 1;
         unsigned Enable_AI0_High : 1;
         unsigned Enable_AIAveraged0_Low : 1;
         unsigned Enable_AIAveraged0_High : 1;
         unsigned Enable_AI1_Low : 1;
         unsigned Enable_AI1_High : 1;
         unsigned Enable_AIAveraged1_Low : 1;
         unsigned Enable_AIAveraged1_High : 1;
         unsigned Enable_Accumulator0 : 1;
         unsigned Enable_Accumulator1 : 1;
         unsigned Enable_DI : 1;
         unsigned Enable_AnalogTriggers : 1;
         unsigned Enable_Counters_Low : 1;
         unsigned Enable_Counters_High : 1;
         unsigned Enable_CounterTimers_Low : 1;
         unsigned Enable_CounterTimers_High : 1;
         unsigned Enable_Encoders : 1;
         unsigned Enable_EncoderTimers : 1;
         unsigned ExternalClock : 1;
         unsigned ExternalClockSource_Channel : 4;
         unsigned ExternalClockSource_Module : 1;
         unsigned ExternalClockSource_AnalogTrigger : 1;
         unsigned RisingEdge : 1;
         unsigned FallingEdge : 1;
      };
      struct{
         unsigned value : 28;
      };
   } tConfig;


   static void writeRate(unsigned int value, tRioStatusCode *status);
   static unsigned int readRate(tRioStatusCode *status);

   static void writeConfig(tConfig value, tRioStatusCode *status);
   static void writeConfig_Pause(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AI0_Low(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AI0_High(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AIAveraged0_Low(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AIAveraged0_High(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AI1_Low(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AI1_High(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AIAveraged1_Low(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AIAveraged1_High(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_Accumulator0(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_Accumulator1(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_DI(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_AnalogTriggers(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_Counters_Low(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_Counters_High(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_CounterTimers_Low(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_CounterTimers_High(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_Encoders(bool value, tRioStatusCode *status);
   static void writeConfig_Enable_EncoderTimers(bool value, tRioStatusCode *status);
   static void writeConfig_ExternalClock(bool value, tRioStatusCode *status);
   static void writeConfig_ExternalClockSource_Channel(unsigned char value, tRioStatusCode *status);
   static void writeConfig_ExternalClockSource_Module(unsigned char value, tRioStatusCode *status);
   static void writeConfig_ExternalClockSource_AnalogTrigger(bool value, tRioStatusCode *status);
   static void writeConfig_RisingEdge(bool value, tRioStatusCode *status);
   static void writeConfig_FallingEdge(bool value, tRioStatusCode *status);
   static tConfig readConfig(tRioStatusCode *status);
   static bool readConfig_Pause(tRioStatusCode *status);
   static bool readConfig_Enable_AI0_Low(tRioStatusCode *status);
   static bool readConfig_Enable_AI0_High(tRioStatusCode *status);
   static bool readConfig_Enable_AIAveraged0_Low(tRioStatusCode *status);
   static bool readConfig_Enable_AIAveraged0_High(tRioStatusCode *status);
   static bool readConfig_Enable_AI1_Low(tRioStatusCode *status);
   static bool readConfig_Enable_AI1_High(tRioStatusCode *status);
   static bool readConfig_Enable_AIAveraged1_Low(tRioStatusCode *status);
   static bool readConfig_Enable_AIAveraged1_High(tRioStatusCode *status);
   static bool readConfig_Enable_Accumulator0(tRioStatusCode *status);
   static bool readConfig_Enable_Accumulator1(tRioStatusCode *status);
   static bool readConfig_Enable_DI(tRioStatusCode *status);
   static bool readConfig_Enable_AnalogTriggers(tRioStatusCode *status);
   static bool readConfig_Enable_Counters_Low(tRioStatusCode *status);
   static bool readConfig_Enable_Counters_High(tRioStatusCode *status);
   static bool readConfig_Enable_CounterTimers_Low(tRioStatusCode *status);
   static bool readConfig_Enable_CounterTimers_High(tRioStatusCode *status);
   static bool readConfig_Enable_Encoders(tRioStatusCode *status);
   static bool readConfig_Enable_EncoderTimers(tRioStatusCode *status);
   static bool readConfig_ExternalClock(tRioStatusCode *status);
   static unsigned char readConfig_ExternalClockSource_Channel(tRioStatusCode *status);
   static unsigned char readConfig_ExternalClockSource_Module(tRioStatusCode *status);
   static bool readConfig_ExternalClockSource_AnalogTrigger(tRioStatusCode *status);
   static bool readConfig_RisingEdge(tRioStatusCode *status);
   static bool readConfig_FallingEdge(tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define DMA_Rate_ADDRESS 0x8158
   #define DMA_Config_ADDRESS 0x8154


};

}
}

#endif // __DMA_h__
