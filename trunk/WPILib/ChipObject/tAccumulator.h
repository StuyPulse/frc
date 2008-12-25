// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Accumulator_h__
#define __Accumulator_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tAccumulator : public tSystem
{
public:
   tAccumulator(unsigned char sys_index, tRioStatusCode *status);
   ~tAccumulator();

   static const unsigned char kNumSystems;

   static const unsigned int kOutputAddresses [];
   static const unsigned int kCenterAddresses [];
   static const unsigned int kResetAddresses [];
   static const unsigned int kDeadbandAddresses [];

   typedef
   union{
      struct{
         unsigned long long Value;
         unsigned Count : 32;
      };
      struct{
         unsigned value : 32;
         unsigned value2 : 32;
         unsigned value3 : 32;
      };
   } tOutput;

   tOutput readOutput(tRioStatusCode *status);
   signed long long readOutput_Value(tRioStatusCode *status);
   unsigned int readOutput_Count(tRioStatusCode *status);

   void writeCenter(signed int value, tRioStatusCode *status);
   signed int readCenter(tRioStatusCode *status);

   void strobeReset(tRioStatusCode *status);

   void writeDeadband(signed int value, tRioStatusCode *status);
   signed int readDeadband(tRioStatusCode *status);





private:
   unsigned char _SystemIndex;


   #define Accumulator0_Output_ADDRESS 0x83FC
   #define Accumulator0_Center_ADDRESS 0x8404
   #define Accumulator0_Reset_ADDRESS 0x8400
   #define Accumulator0_Deadband_ADDRESS 0x83F8

   #define Accumulator1_Output_ADDRESS 0x83EC
   #define Accumulator1_Center_ADDRESS 0x83F4
   #define Accumulator1_Reset_ADDRESS 0x83F0
   #define Accumulator1_Deadband_ADDRESS 0x83E8


};

}
}

#endif // __Accumulator_h__
