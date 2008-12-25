// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Counter_h__
#define __Counter_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tCounter : public tSystem
{
public:
   tCounter(unsigned char sys_index, tRioStatusCode *status);
   ~tCounter();

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
         unsigned UpSource_Channel : 4;
         unsigned UpSource_Module : 1;
         unsigned UpSource_AnalogTrigger : 1;
         unsigned DownSource_Channel : 4;
         unsigned DownSource_Module : 1;
         unsigned DownSource_AnalogTrigger : 1;
         unsigned IndexSource_Channel : 4;
         unsigned IndexSource_Module : 1;
         unsigned IndexSource_AnalogTrigger : 1;
         unsigned IndexActiveHigh : 1;
         unsigned UpRisingEdge : 1;
         unsigned UpFallingEdge : 1;
         unsigned DownRisingEdge : 1;
         unsigned DownFallingEdge : 1;
         unsigned Mode : 2;
         unsigned PulseLengthThreshold : 6;
      };
      struct{
         unsigned value : 31;
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
   void writeConfig_UpSource_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_UpSource_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_UpSource_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_DownSource_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_DownSource_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_DownSource_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_IndexSource_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_IndexSource_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_IndexSource_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_IndexActiveHigh(bool value, tRioStatusCode *status);
   void writeConfig_UpRisingEdge(bool value, tRioStatusCode *status);
   void writeConfig_UpFallingEdge(bool value, tRioStatusCode *status);
   void writeConfig_DownRisingEdge(bool value, tRioStatusCode *status);
   void writeConfig_DownFallingEdge(bool value, tRioStatusCode *status);
   void writeConfig_Mode(unsigned char value, tRioStatusCode *status);
   void writeConfig_PulseLengthThreshold(unsigned short value, tRioStatusCode *status);
   tConfig readConfig(tRioStatusCode *status);
   unsigned char readConfig_UpSource_Channel(tRioStatusCode *status);
   unsigned char readConfig_UpSource_Module(tRioStatusCode *status);
   bool readConfig_UpSource_AnalogTrigger(tRioStatusCode *status);
   unsigned char readConfig_DownSource_Channel(tRioStatusCode *status);
   unsigned char readConfig_DownSource_Module(tRioStatusCode *status);
   bool readConfig_DownSource_AnalogTrigger(tRioStatusCode *status);
   unsigned char readConfig_IndexSource_Channel(tRioStatusCode *status);
   unsigned char readConfig_IndexSource_Module(tRioStatusCode *status);
   bool readConfig_IndexSource_AnalogTrigger(tRioStatusCode *status);
   bool readConfig_IndexActiveHigh(tRioStatusCode *status);
   bool readConfig_UpRisingEdge(tRioStatusCode *status);
   bool readConfig_UpFallingEdge(tRioStatusCode *status);
   bool readConfig_DownRisingEdge(tRioStatusCode *status);
   bool readConfig_DownFallingEdge(tRioStatusCode *status);
   unsigned char readConfig_Mode(tRioStatusCode *status);
   unsigned short readConfig_PulseLengthThreshold(tRioStatusCode *status);

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


   #define Counter0_Output_ADDRESS 0x82AC
   #define Counter0_Config_ADDRESS 0x82B8
   #define Counter0_Reset_ADDRESS 0x82B0
   #define Counter0_TimerOutput_ADDRESS 0x82A4
   #define Counter0_Enable_ADDRESS 0x82B4
   #define Counter0_TimerConfig_ADDRESS 0x82A8

   #define Counter1_Output_ADDRESS 0x8294
   #define Counter1_Config_ADDRESS 0x82A0
   #define Counter1_Reset_ADDRESS 0x8298
   #define Counter1_TimerOutput_ADDRESS 0x828C
   #define Counter1_Enable_ADDRESS 0x829C
   #define Counter1_TimerConfig_ADDRESS 0x8290

   #define Counter2_Output_ADDRESS 0x827C
   #define Counter2_Config_ADDRESS 0x8288
   #define Counter2_Reset_ADDRESS 0x8280
   #define Counter2_TimerOutput_ADDRESS 0x8274
   #define Counter2_Enable_ADDRESS 0x8284
   #define Counter2_TimerConfig_ADDRESS 0x8278

   #define Counter3_Output_ADDRESS 0x8264
   #define Counter3_Config_ADDRESS 0x8270
   #define Counter3_Reset_ADDRESS 0x8268
   #define Counter3_TimerOutput_ADDRESS 0x825C
   #define Counter3_Enable_ADDRESS 0x826C
   #define Counter3_TimerConfig_ADDRESS 0x8260

   #define Counter4_Output_ADDRESS 0x824C
   #define Counter4_Config_ADDRESS 0x8258
   #define Counter4_Reset_ADDRESS 0x8250
   #define Counter4_TimerOutput_ADDRESS 0x8244
   #define Counter4_Enable_ADDRESS 0x8254
   #define Counter4_TimerConfig_ADDRESS 0x8248

   #define Counter5_Output_ADDRESS 0x8234
   #define Counter5_Config_ADDRESS 0x8240
   #define Counter5_Reset_ADDRESS 0x8238
   #define Counter5_TimerOutput_ADDRESS 0x822C
   #define Counter5_Enable_ADDRESS 0x823C
   #define Counter5_TimerConfig_ADDRESS 0x8230

   #define Counter6_Output_ADDRESS 0x821C
   #define Counter6_Config_ADDRESS 0x8228
   #define Counter6_Reset_ADDRESS 0x8220
   #define Counter6_TimerOutput_ADDRESS 0x8214
   #define Counter6_Enable_ADDRESS 0x8224
   #define Counter6_TimerConfig_ADDRESS 0x8218

   #define Counter7_Output_ADDRESS 0x8204
   #define Counter7_Config_ADDRESS 0x8210
   #define Counter7_Reset_ADDRESS 0x8208
   #define Counter7_TimerOutput_ADDRESS 0x81FC
   #define Counter7_Enable_ADDRESS 0x820C
   #define Counter7_TimerConfig_ADDRESS 0x8200


};

}
}

#endif // __Counter_h__
