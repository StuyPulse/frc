// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __AI_h__
#define __AI_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tAI : public tSystem
{
public:
   tAI(unsigned char sys_index, tRioStatusCode *status);
   ~tAI();

   static const unsigned char kNumSystems;

   static const unsigned int kConfigAddresses [];
   static const unsigned int kCalOKAddresses [];
   static const unsigned int kScanListAddresses [];
   static const unsigned int kAverageBitsAddresses [];
   static const unsigned int kLoopTimingAddresses [];
   static const unsigned int kOversampleBitsAddresses [];
   static const unsigned int kOffsetAddresses [];
   static const unsigned int kLSBWeightAddresses [];

   typedef
   union{
      struct{
         unsigned Channel : 3;
         unsigned Module : 1;
         unsigned Averaged : 1;
      };
      struct{
         unsigned value : 5;
      };
   } tReadSelect;
   typedef
   union{
      struct{
         unsigned ScanSize : 3;
         unsigned ConvertRate : 26;
      };
      struct{
         unsigned value : 29;
      };
   } tConfig;

   void writeConfig(tConfig value, tRioStatusCode *status);
   void writeConfig_ScanSize(unsigned char value, tRioStatusCode *status);
   void writeConfig_ConvertRate(unsigned int value, tRioStatusCode *status);
   tConfig readConfig(tRioStatusCode *status);
   unsigned char readConfig_ScanSize(tRioStatusCode *status);
   unsigned int readConfig_ConvertRate(tRioStatusCode *status);

   bool readCalOK(tRioStatusCode *status);

   static const unsigned char kNumScanListElements;
   void writeScanList(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status);
   unsigned char readScanList(unsigned char bitfield_index, tRioStatusCode *status);

   static const unsigned char kNumAverageBitsElements;
   void writeAverageBits(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status);
   unsigned char readAverageBits(unsigned char bitfield_index, tRioStatusCode *status);

   unsigned int readLoopTiming(tRioStatusCode *status);

   static const unsigned char kNumOversampleBitsElements;
   void writeOversampleBits(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status);
   unsigned char readOversampleBits(unsigned char bitfield_index, tRioStatusCode *status);


   static signed int readOutput(tRioStatusCode *status);

   static void writeReadSelect(tReadSelect value, tRioStatusCode *status);
   static void writeReadSelect_Channel(unsigned char value, tRioStatusCode *status);
   static void writeReadSelect_Module(unsigned char value, tRioStatusCode *status);
   static void writeReadSelect_Averaged(bool value, tRioStatusCode *status);
   static tReadSelect readReadSelect(tRioStatusCode *status);
   static unsigned char readReadSelect_Channel(tRioStatusCode *status);
   static unsigned char readReadSelect_Module(tRioStatusCode *status);
   static bool readReadSelect_Averaged(tRioStatusCode *status);

   static void strobeLatchOutput(tRioStatusCode *status);


   static const unsigned char kNumOffsetRegisters;
   signed int readOffset(unsigned char reg_index, tRioStatusCode *status);

   static const unsigned char kNumLSBWeightRegisters;
   unsigned int readLSBWeight(unsigned char reg_index, tRioStatusCode *status);



private:
   unsigned char _SystemIndex;

   #define AI_Output_ADDRESS 0x84B4
   #define AI_ReadSelect_ADDRESS 0x84BC
   #define AI_LatchOutput_ADDRESS 0x84B8

   #define AI0_Config_ADDRESS 0x8470
   #define AI0_CalOK_ADDRESS 0x810C
   #define AI0_ScanList_ADDRESS 0x846C
   #define AI0_AverageBits_ADDRESS 0x8464
   #define AI0_LoopTiming_ADDRESS 0x8460
   #define AI0_OversampleBits_ADDRESS 0x8468

   #define AI0_Offset0_ADDRESS 0x84B0
   #define AI0_Offset1_ADDRESS 0x84AC
   #define AI0_Offset2_ADDRESS 0x84A8
   #define AI0_Offset3_ADDRESS 0x84A4
   #define AI0_Offset4_ADDRESS 0x84A0
   #define AI0_Offset5_ADDRESS 0x849C
   #define AI0_Offset6_ADDRESS 0x8498
   #define AI0_Offset7_ADDRESS 0x8494
   #define AI0_LSBWeight0_ADDRESS 0x8490
   #define AI0_LSBWeight1_ADDRESS 0x848C
   #define AI0_LSBWeight2_ADDRESS 0x8488
   #define AI0_LSBWeight3_ADDRESS 0x8484
   #define AI0_LSBWeight4_ADDRESS 0x8480
   #define AI0_LSBWeight5_ADDRESS 0x847C
   #define AI0_LSBWeight6_ADDRESS 0x8478
   #define AI0_LSBWeight7_ADDRESS 0x8474
   #define AI1_Config_ADDRESS 0x8418
   #define AI1_CalOK_ADDRESS 0x845C
   #define AI1_ScanList_ADDRESS 0x8414
   #define AI1_AverageBits_ADDRESS 0x840C
   #define AI1_LoopTiming_ADDRESS 0x8408
   #define AI1_OversampleBits_ADDRESS 0x8410

   #define AI1_Offset0_ADDRESS 0x8458
   #define AI1_Offset1_ADDRESS 0x8454
   #define AI1_Offset2_ADDRESS 0x8450
   #define AI1_Offset3_ADDRESS 0x844C
   #define AI1_Offset4_ADDRESS 0x8448
   #define AI1_Offset5_ADDRESS 0x8444
   #define AI1_Offset6_ADDRESS 0x8440
   #define AI1_Offset7_ADDRESS 0x843C
   #define AI1_LSBWeight0_ADDRESS 0x8438
   #define AI1_LSBWeight1_ADDRESS 0x8434
   #define AI1_LSBWeight2_ADDRESS 0x8430
   #define AI1_LSBWeight3_ADDRESS 0x842C
   #define AI1_LSBWeight4_ADDRESS 0x8428
   #define AI1_LSBWeight5_ADDRESS 0x8424
   #define AI1_LSBWeight6_ADDRESS 0x8420
   #define AI1_LSBWeight7_ADDRESS 0x841C

};

}
}

#endif // __AI_h__
