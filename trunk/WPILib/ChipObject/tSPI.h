// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __SPI_h__
#define __SPI_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tSPI : public tSystem
{
public:
   tSPI(tRioStatusCode *status);
   ~tSPI();

   static const unsigned char kNumSystems;


   typedef
   union{
      struct{
         unsigned BusBitWidth : 8;
         unsigned ClockHalfPeriodDelay : 8;
         unsigned MSBfirst : 1;
         unsigned DataOnFalling : 1;
         unsigned LatchFirst : 1;
         unsigned LatchLast : 1;
         unsigned FramePolarity : 1;
         unsigned WriteOnly : 1;
      };
      struct{
         unsigned value : 22;
      };
   } tConfig;
   typedef
   union{
      struct{
         unsigned SCLK_Channel : 4;
         unsigned SCLK_Module : 1;
         unsigned MOSI_Channel : 4;
         unsigned MOSI_Module : 1;
         unsigned MISO_Channel : 4;
         unsigned MISO_Module : 1;
         unsigned SS_Channel : 4;
         unsigned SS_Module : 1;
      };
      struct{
         unsigned value : 20;
      };
   } tChannels;


   static void strobeReadReceivedData(tRioStatusCode *status);

   static void writeConfig(tConfig value, tRioStatusCode *status);
   static void writeConfig_BusBitWidth(unsigned char value, tRioStatusCode *status);
   static void writeConfig_ClockHalfPeriodDelay(unsigned char value, tRioStatusCode *status);
   static void writeConfig_MSBfirst(bool value, tRioStatusCode *status);
   static void writeConfig_DataOnFalling(bool value, tRioStatusCode *status);
   static void writeConfig_LatchFirst(bool value, tRioStatusCode *status);
   static void writeConfig_LatchLast(bool value, tRioStatusCode *status);
   static void writeConfig_FramePolarity(bool value, tRioStatusCode *status);
   static void writeConfig_WriteOnly(bool value, tRioStatusCode *status);
   static tConfig readConfig(tRioStatusCode *status);
   static unsigned char readConfig_BusBitWidth(tRioStatusCode *status);
   static unsigned char readConfig_ClockHalfPeriodDelay(tRioStatusCode *status);
   static bool readConfig_MSBfirst(tRioStatusCode *status);
   static bool readConfig_DataOnFalling(tRioStatusCode *status);
   static bool readConfig_LatchFirst(tRioStatusCode *status);
   static bool readConfig_LatchLast(tRioStatusCode *status);
   static bool readConfig_FramePolarity(tRioStatusCode *status);
   static bool readConfig_WriteOnly(tRioStatusCode *status);

   static void strobeReset(tRioStatusCode *status);

   static void writeDataToLoad(unsigned int value, tRioStatusCode *status);
   static unsigned int readDataToLoad(tRioStatusCode *status);

   static unsigned short readAvaliableToLoad(tRioStatusCode *status);

   static unsigned int readReceivedData(tRioStatusCode *status);

   static void writeChannels(tChannels value, tRioStatusCode *status);
   static void writeChannels_SCLK_Channel(unsigned char value, tRioStatusCode *status);
   static void writeChannels_SCLK_Module(unsigned char value, tRioStatusCode *status);
   static void writeChannels_MOSI_Channel(unsigned char value, tRioStatusCode *status);
   static void writeChannels_MOSI_Module(unsigned char value, tRioStatusCode *status);
   static void writeChannels_MISO_Channel(unsigned char value, tRioStatusCode *status);
   static void writeChannels_MISO_Module(unsigned char value, tRioStatusCode *status);
   static void writeChannels_SS_Channel(unsigned char value, tRioStatusCode *status);
   static void writeChannels_SS_Module(unsigned char value, tRioStatusCode *status);
   static tChannels readChannels(tRioStatusCode *status);
   static unsigned char readChannels_SCLK_Channel(tRioStatusCode *status);
   static unsigned char readChannels_SCLK_Module(tRioStatusCode *status);
   static unsigned char readChannels_MOSI_Channel(tRioStatusCode *status);
   static unsigned char readChannels_MOSI_Module(tRioStatusCode *status);
   static unsigned char readChannels_MISO_Channel(tRioStatusCode *status);
   static unsigned char readChannels_MISO_Module(tRioStatusCode *status);
   static unsigned char readChannels_SS_Channel(tRioStatusCode *status);
   static unsigned char readChannels_SS_Module(tRioStatusCode *status);

   static void strobeLoad(tRioStatusCode *status);

   static unsigned short readReceivedElements(tRioStatusCode *status);

   static void strobeClearReceivedData(tRioStatusCode *status);

   static bool readReceivedDataOverflow(tRioStatusCode *status);




private:
   unsigned char _SystemIndex;

   #define SPI_ReadReceivedData_ADDRESS 0x8138
   #define SPI_Config_ADDRESS 0x8150
   #define SPI_Reset_ADDRESS 0x8148
   #define SPI_DataToLoad_ADDRESS 0x8140
   #define SPI_AvaliableToLoad_ADDRESS 0x813C
   #define SPI_ReceivedData_ADDRESS 0x8134
   #define SPI_Channels_ADDRESS 0x814C
   #define SPI_Load_ADDRESS 0x8144
   #define SPI_ReceivedElements_ADDRESS 0x8130
   #define SPI_ClearReceivedData_ADDRESS 0x812C
   #define SPI_ReceivedDataOverflow_ADDRESS 0x8128


};

}
}

#endif // __SPI_h__
