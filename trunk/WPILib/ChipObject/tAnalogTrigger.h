// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __AnalogTrigger_h__
#define __AnalogTrigger_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tAnalogTrigger : public tSystem
{
public:
   tAnalogTrigger(unsigned char sys_index, tRioStatusCode *status);
   ~tAnalogTrigger();

   static const unsigned char kNumSystems;

   static const unsigned int kSourceSelectAddresses [];
   static const unsigned int kUpperLimitAddresses [];
   static const unsigned int kLowerLimitAddresses [];

   typedef
   union{
      struct{
         unsigned InHysteresis : 1;
         unsigned OverLimit : 1;
         unsigned Rising : 1;
         unsigned Falling : 1;
      };
      struct{
         unsigned value : 4;
      };
   } tOutput;
   typedef
   union{
      struct{
         unsigned Channel : 3;
         unsigned Module : 1;
         unsigned Averaged : 1;
         unsigned Filter : 1;
         unsigned FloatingRollover : 1;
         signed RolloverLimit : 8;
      };
      struct{
         unsigned value : 15;
      };
   } tSourceSelect;

   void writeSourceSelect(tSourceSelect value, tRioStatusCode *status);
   void writeSourceSelect_Channel(unsigned char value, tRioStatusCode *status);
   void writeSourceSelect_Module(unsigned char value, tRioStatusCode *status);
   void writeSourceSelect_Averaged(bool value, tRioStatusCode *status);
   void writeSourceSelect_Filter(bool value, tRioStatusCode *status);
   void writeSourceSelect_FloatingRollover(bool value, tRioStatusCode *status);
   void writeSourceSelect_RolloverLimit(signed short value, tRioStatusCode *status);
   tSourceSelect readSourceSelect(tRioStatusCode *status);
   unsigned char readSourceSelect_Channel(tRioStatusCode *status);
   unsigned char readSourceSelect_Module(tRioStatusCode *status);
   bool readSourceSelect_Averaged(tRioStatusCode *status);
   bool readSourceSelect_Filter(tRioStatusCode *status);
   bool readSourceSelect_FloatingRollover(tRioStatusCode *status);
   signed short readSourceSelect_RolloverLimit(tRioStatusCode *status);

   void writeUpperLimit(signed int value, tRioStatusCode *status);
   signed int readUpperLimit(tRioStatusCode *status);

   void writeLowerLimit(signed int value, tRioStatusCode *status);
   signed int readLowerLimit(tRioStatusCode *status);


   static const unsigned char kNumOutputElements;
   static tOutput readOutput(unsigned char bitfield_index, tRioStatusCode *status);
   static bool readOutput_InHysteresis(unsigned char bitfield_index, tRioStatusCode *status);
   static bool readOutput_OverLimit(unsigned char bitfield_index, tRioStatusCode *status);
   static bool readOutput_Rising(unsigned char bitfield_index, tRioStatusCode *status);
   static bool readOutput_Falling(unsigned char bitfield_index, tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define AnalogTrigger_Output_ADDRESS 0x83E4

   #define AnalogTrigger0_SourceSelect_ADDRESS 0x83E0
   #define AnalogTrigger0_UpperLimit_ADDRESS 0x83DC
   #define AnalogTrigger0_LowerLimit_ADDRESS 0x83D8

   #define AnalogTrigger1_SourceSelect_ADDRESS 0x83D4
   #define AnalogTrigger1_UpperLimit_ADDRESS 0x83D0
   #define AnalogTrigger1_LowerLimit_ADDRESS 0x83CC

   #define AnalogTrigger2_SourceSelect_ADDRESS 0x83C8
   #define AnalogTrigger2_UpperLimit_ADDRESS 0x83C4
   #define AnalogTrigger2_LowerLimit_ADDRESS 0x83C0

   #define AnalogTrigger3_SourceSelect_ADDRESS 0x83BC
   #define AnalogTrigger3_UpperLimit_ADDRESS 0x83B8
   #define AnalogTrigger3_LowerLimit_ADDRESS 0x83B4

   #define AnalogTrigger4_SourceSelect_ADDRESS 0x83B0
   #define AnalogTrigger4_UpperLimit_ADDRESS 0x83AC
   #define AnalogTrigger4_LowerLimit_ADDRESS 0x83A8

   #define AnalogTrigger5_SourceSelect_ADDRESS 0x83A4
   #define AnalogTrigger5_UpperLimit_ADDRESS 0x8394
   #define AnalogTrigger5_LowerLimit_ADDRESS 0x8390

   #define AnalogTrigger6_SourceSelect_ADDRESS 0x8398
   #define AnalogTrigger6_UpperLimit_ADDRESS 0x83A0
   #define AnalogTrigger6_LowerLimit_ADDRESS 0x839C

   #define AnalogTrigger7_SourceSelect_ADDRESS 0x838C
   #define AnalogTrigger7_UpperLimit_ADDRESS 0x8388
   #define AnalogTrigger7_LowerLimit_ADDRESS 0x8384


};

}
}

#endif // __AnalogTrigger_h__
