// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __DIO_h__
#define __DIO_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tDIO : public tSystem
{
public:
   tDIO(unsigned char sys_index, tRioStatusCode *status);
   ~tDIO();

   static const unsigned char kNumSystems;

   static const unsigned int kDOAddresses [];
   static const unsigned int kFilterSelectAddresses [];
   static const unsigned int kFilterPeriodAddresses [];
   static const unsigned int kOutputEnableAddresses [];
   static const unsigned int kDIAddresses [];
   static const unsigned int kI2CDataReceivedAddresses [];
   static const unsigned int kI2CStatusAddresses [];
   static const unsigned int kSlowValueAddresses [];
   static const unsigned int kPWMPeriodScaleAddresses [];
   static const unsigned int kPulseAddresses [];
   static const unsigned int kI2CStartAddresses [];
   static const unsigned int kBFLAddresses [];
   static const unsigned int kPulseLengthAddresses [];
   static const unsigned int kI2CConfigAddresses [];
   static const unsigned int kPWMValueAddresses [];

   typedef
   union{
      struct{
         unsigned Period : 16;
         unsigned MinHigh : 16;
      };
      struct{
         unsigned value : 32;
      };
   } tPWMConfig;
   typedef
   union{
      struct{
         unsigned Transaction : 1;
         unsigned Done : 1;
      };
      struct{
         unsigned value : 2;
      };
   } tI2CStatus;
   typedef
   union{
      struct{
         unsigned RelayFwd : 8;
         unsigned RelayRev : 8;
         unsigned I2CHeader : 4;
      };
      struct{
         unsigned value : 20;
      };
   } tSlowValue;
   typedef
   union{
      struct{
         unsigned Address : 8;
         unsigned Register : 8;
         unsigned DataToSend : 8;
         unsigned Read : 1;
         unsigned BytesToRead : 2;
      };
      struct{
         unsigned value : 27;
      };
   } tI2CConfig;

   void writeDO(unsigned short value, tRioStatusCode *status);
   unsigned short readDO(tRioStatusCode *status);

   static const unsigned char kNumFilterSelectElements;
   void writeFilterSelect(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status);
   unsigned char readFilterSelect(unsigned char bitfield_index, tRioStatusCode *status);

   static const unsigned char kNumFilterPeriodElements;
   void writeFilterPeriod(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status);
   unsigned char readFilterPeriod(unsigned char bitfield_index, tRioStatusCode *status);

   void writeOutputEnable(unsigned short value, tRioStatusCode *status);
   unsigned short readOutputEnable(tRioStatusCode *status);

   unsigned short readDI(tRioStatusCode *status);

   unsigned int readI2CDataReceived(tRioStatusCode *status);

   tI2CStatus readI2CStatus(tRioStatusCode *status);
   unsigned char readI2CStatus_Transaction(tRioStatusCode *status);
   bool readI2CStatus_Done(tRioStatusCode *status);

   void writeSlowValue(tSlowValue value, tRioStatusCode *status);
   void writeSlowValue_RelayFwd(unsigned char value, tRioStatusCode *status);
   void writeSlowValue_RelayRev(unsigned char value, tRioStatusCode *status);
   void writeSlowValue_I2CHeader(unsigned char value, tRioStatusCode *status);
   tSlowValue readSlowValue(tRioStatusCode *status);
   unsigned char readSlowValue_RelayFwd(tRioStatusCode *status);
   unsigned char readSlowValue_RelayRev(tRioStatusCode *status);
   unsigned char readSlowValue_I2CHeader(tRioStatusCode *status);

   static const unsigned char kNumPWMPeriodScaleElements;
   void writePWMPeriodScale(unsigned char bitfield_index, unsigned char value, tRioStatusCode *status);
   unsigned char readPWMPeriodScale(unsigned char bitfield_index, tRioStatusCode *status);

   void writePulse(unsigned short value, tRioStatusCode *status);
   unsigned short readPulse(tRioStatusCode *status);

   void strobeI2CStart(tRioStatusCode *status);

   void writeBFL(bool value, tRioStatusCode *status);
   bool readBFL(tRioStatusCode *status);

   void writePulseLength(unsigned char value, tRioStatusCode *status);
   unsigned char readPulseLength(tRioStatusCode *status);

   void writeI2CConfig(tI2CConfig value, tRioStatusCode *status);
   void writeI2CConfig_Address(unsigned char value, tRioStatusCode *status);
   void writeI2CConfig_Register(unsigned char value, tRioStatusCode *status);
   void writeI2CConfig_DataToSend(unsigned char value, tRioStatusCode *status);
   void writeI2CConfig_Read(bool value, tRioStatusCode *status);
   void writeI2CConfig_BytesToRead(unsigned char value, tRioStatusCode *status);
   tI2CConfig readI2CConfig(tRioStatusCode *status);
   unsigned char readI2CConfig_Address(tRioStatusCode *status);
   unsigned char readI2CConfig_Register(tRioStatusCode *status);
   unsigned char readI2CConfig_DataToSend(tRioStatusCode *status);
   bool readI2CConfig_Read(tRioStatusCode *status);
   unsigned char readI2CConfig_BytesToRead(tRioStatusCode *status);


   static unsigned short readLoopTiming(tRioStatusCode *status);

   static void writePWMConfig(tPWMConfig value, tRioStatusCode *status);
   static void writePWMConfig_Period(unsigned short value, tRioStatusCode *status);
   static void writePWMConfig_MinHigh(unsigned short value, tRioStatusCode *status);
   static tPWMConfig readPWMConfig(tRioStatusCode *status);
   static unsigned short readPWMConfig_Period(tRioStatusCode *status);
   static unsigned short readPWMConfig_MinHigh(tRioStatusCode *status);


   static const unsigned char kNumPWMValueRegisters;
   void writePWMValue(unsigned char reg_index, unsigned char value, tRioStatusCode *status);
   unsigned char readPWMValue(unsigned char reg_index, tRioStatusCode *status);



private:
   unsigned char _SystemIndex;

   #define DIO_LoopTiming_ADDRESS 0x8380
   #define DIO_PWMConfig_ADDRESS 0x837C

   #define DIO0_DO_ADDRESS 0x8378
   #define DIO0_FilterSelect_ADDRESS 0x831C
   #define DIO0_FilterPeriod_ADDRESS 0x8320
   #define DIO0_OutputEnable_ADDRESS 0x8370
   #define DIO0_DI_ADDRESS 0x8374
   #define DIO0_I2CDataReceived_ADDRESS 0x833C
   #define DIO0_I2CStatus_ADDRESS 0x8334
   #define DIO0_SlowValue_ADDRESS 0x8330
   #define DIO0_PWMPeriodScale_ADDRESS 0x8344
   #define DIO0_Pulse_ADDRESS 0x8328
   #define DIO0_I2CStart_ADDRESS 0x8338
   #define DIO0_BFL_ADDRESS 0x832C
   #define DIO0_PulseLength_ADDRESS 0x8324
   #define DIO0_I2CConfig_ADDRESS 0x8340

   #define DIO0_PWMValue0_ADDRESS 0x836C
   #define DIO0_PWMValue1_ADDRESS 0x8368
   #define DIO0_PWMValue2_ADDRESS 0x8364
   #define DIO0_PWMValue3_ADDRESS 0x8360
   #define DIO0_PWMValue4_ADDRESS 0x835C
   #define DIO0_PWMValue5_ADDRESS 0x8358
   #define DIO0_PWMValue6_ADDRESS 0x8354
   #define DIO0_PWMValue7_ADDRESS 0x8350
   #define DIO0_PWMValue8_ADDRESS 0x834C
   #define DIO0_PWMValue9_ADDRESS 0x8348
   #define DIO1_DO_ADDRESS 0x8318
   #define DIO1_FilterSelect_ADDRESS 0x82BC
   #define DIO1_FilterPeriod_ADDRESS 0x82C0
   #define DIO1_OutputEnable_ADDRESS 0x8310
   #define DIO1_DI_ADDRESS 0x8314
   #define DIO1_I2CDataReceived_ADDRESS 0x82DC
   #define DIO1_I2CStatus_ADDRESS 0x82D4
   #define DIO1_SlowValue_ADDRESS 0x82D0
   #define DIO1_PWMPeriodScale_ADDRESS 0x82E4
   #define DIO1_Pulse_ADDRESS 0x82C8
   #define DIO1_I2CStart_ADDRESS 0x82D8
   #define DIO1_BFL_ADDRESS 0x82CC
   #define DIO1_PulseLength_ADDRESS 0x82C4
   #define DIO1_I2CConfig_ADDRESS 0x82E0

   #define DIO1_PWMValue0_ADDRESS 0x830C
   #define DIO1_PWMValue1_ADDRESS 0x8308
   #define DIO1_PWMValue2_ADDRESS 0x8304
   #define DIO1_PWMValue3_ADDRESS 0x8300
   #define DIO1_PWMValue4_ADDRESS 0x82FC
   #define DIO1_PWMValue5_ADDRESS 0x82F8
   #define DIO1_PWMValue6_ADDRESS 0x82F4
   #define DIO1_PWMValue7_ADDRESS 0x82F0
   #define DIO1_PWMValue8_ADDRESS 0x82EC
   #define DIO1_PWMValue9_ADDRESS 0x82E8

};

}
}

#endif // __DIO_h__
