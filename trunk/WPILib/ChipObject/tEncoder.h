// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Encoder_h__
#define __Encoder_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tEncoder : public tSystem
{
public:
   tEncoder(unsigned char sys_index, tRioStatusCode *status);
   ~tEncoder();

   static const unsigned char kNumSystems;

   static const unsigned int kOutputAddresses [];
   static const unsigned int kConfigAddresses [];
   static const unsigned int kResetAddresses [];
   static const unsigned int kTimerOutputAddresses [];
   static const unsigned int kEnableAddresses [];
   static const unsigned int kTimerConfigAddresses [];

   typedef
   union{
      struct{
         unsigned Direction : 1;
         signed Value : 31;
      };
      struct{
         unsigned value : 32;
      };
   } tOutput;
   typedef
   union{
      struct{
         unsigned ASource_Channel : 4;
         unsigned ASource_Module : 1;
         unsigned ASource_AnalogTrigger : 1;
         unsigned BSource_Channel : 4;
         unsigned BSource_Module : 1;
         unsigned BSource_AnalogTrigger : 1;
         unsigned IndexSource_Channel : 4;
         unsigned IndexSource_Module : 1;
         unsigned IndexSource_AnalogTrigger : 1;
         unsigned IndexActiveHigh : 1;
         unsigned Reverse : 1;
      };
      struct{
         unsigned value : 20;
      };
   } tConfig;
   typedef
   union{
      struct{
         unsigned Period : 24;
         unsigned Count : 7;
         unsigned Stalled : 1;
      };
      struct{
         unsigned value : 32;
      };
   } tTimerOutput;
   typedef
   union{
      struct{
         unsigned StallPeriod : 24;
         unsigned AverageSize : 7;
         unsigned UpdateWhenEmpty : 1;
      };
      struct{
         unsigned value : 32;
      };
   } tTimerConfig;

   tOutput readOutput(tRioStatusCode *status);
   bool readOutput_Direction(tRioStatusCode *status);
   signed int readOutput_Value(tRioStatusCode *status);

   void writeConfig(tConfig value, tRioStatusCode *status);
   void writeConfig_ASource_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_ASource_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_ASource_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_BSource_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_BSource_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_BSource_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_IndexSource_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_IndexSource_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_IndexSource_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_IndexActiveHigh(bool value, tRioStatusCode *status);
   void writeConfig_Reverse(bool value, tRioStatusCode *status);
   tConfig readConfig(tRioStatusCode *status);
   unsigned char readConfig_ASource_Channel(tRioStatusCode *status);
   unsigned char readConfig_ASource_Module(tRioStatusCode *status);
   bool readConfig_ASource_AnalogTrigger(tRioStatusCode *status);
   unsigned char readConfig_BSource_Channel(tRioStatusCode *status);
   unsigned char readConfig_BSource_Module(tRioStatusCode *status);
   bool readConfig_BSource_AnalogTrigger(tRioStatusCode *status);
   unsigned char readConfig_IndexSource_Channel(tRioStatusCode *status);
   unsigned char readConfig_IndexSource_Module(tRioStatusCode *status);
   bool readConfig_IndexSource_AnalogTrigger(tRioStatusCode *status);
   bool readConfig_IndexActiveHigh(tRioStatusCode *status);
   bool readConfig_Reverse(tRioStatusCode *status);

   void strobeReset(tRioStatusCode *status);

   tTimerOutput readTimerOutput(tRioStatusCode *status);
   unsigned int readTimerOutput_Period(tRioStatusCode *status);
   unsigned char readTimerOutput_Count(tRioStatusCode *status);
   bool readTimerOutput_Stalled(tRioStatusCode *status);

   void writeEnable(bool value, tRioStatusCode *status);
   bool readEnable(tRioStatusCode *status);

   void writeTimerConfig(tTimerConfig value, tRioStatusCode *status);
   void writeTimerConfig_StallPeriod(unsigned int value, tRioStatusCode *status);
   void writeTimerConfig_AverageSize(unsigned char value, tRioStatusCode *status);
   void writeTimerConfig_UpdateWhenEmpty(bool value, tRioStatusCode *status);
   tTimerConfig readTimerConfig(tRioStatusCode *status);
   unsigned int readTimerConfig_StallPeriod(tRioStatusCode *status);
   unsigned char readTimerConfig_AverageSize(tRioStatusCode *status);
   bool readTimerConfig_UpdateWhenEmpty(tRioStatusCode *status);





private:
   unsigned char _SystemIndex;


   #define Encoder0_Output_ADDRESS 0x81EC
   #define Encoder0_Config_ADDRESS 0x81F8
   #define Encoder0_Reset_ADDRESS 0x81F0
   #define Encoder0_TimerOutput_ADDRESS 0x81E4
   #define Encoder0_Enable_ADDRESS 0x81F4
   #define Encoder0_TimerConfig_ADDRESS 0x81E8

   #define Encoder1_Output_ADDRESS 0x81D4
   #define Encoder1_Config_ADDRESS 0x81E0
   #define Encoder1_Reset_ADDRESS 0x81D8
   #define Encoder1_TimerOutput_ADDRESS 0x81CC
   #define Encoder1_Enable_ADDRESS 0x81DC
   #define Encoder1_TimerConfig_ADDRESS 0x81D0

   #define Encoder2_Output_ADDRESS 0x81BC
   #define Encoder2_Config_ADDRESS 0x81C8
   #define Encoder2_Reset_ADDRESS 0x81C0
   #define Encoder2_TimerOutput_ADDRESS 0x81B4
   #define Encoder2_Enable_ADDRESS 0x81C4
   #define Encoder2_TimerConfig_ADDRESS 0x81B8

   #define Encoder3_Output_ADDRESS 0x81A4
   #define Encoder3_Config_ADDRESS 0x81B0
   #define Encoder3_Reset_ADDRESS 0x81A8
   #define Encoder3_TimerOutput_ADDRESS 0x819C
   #define Encoder3_Enable_ADDRESS 0x81AC
   #define Encoder3_TimerConfig_ADDRESS 0x81A0


};

}
}

#endif // __Encoder_h__
