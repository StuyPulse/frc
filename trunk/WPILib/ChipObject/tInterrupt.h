// Copyright (c) National Instruments 2008.  All Rights Reserved.
// Do Not Edit... this file is generated!

#ifndef __Interrupt_h__
#define __Interrupt_h__

#include "tSystem.h"

namespace nFPGA
{
namespace n306F586FB5ADD059CDB0429821CA506D
{

class tInterrupt : public tSystem
{
public:
   tInterrupt(unsigned char sys_index, tRioStatusCode *status);
   ~tInterrupt();

   static const unsigned char kNumSystems;

   static const unsigned int kTimeStampAddresses [];
   static const unsigned int kConfigAddresses [];

   typedef
   union{
      struct{
         unsigned Source_Channel : 4;
         unsigned Source_Module : 1;
         unsigned Source_AnalogTrigger : 1;
         unsigned RisingEdge : 1;
         unsigned FallingEdge : 1;
         unsigned WaitForAck : 1;
      };
      struct{
         unsigned value : 9;
      };
   } tConfig;

   unsigned int readTimeStamp(tRioStatusCode *status);

   void writeConfig(tConfig value, tRioStatusCode *status);
   void writeConfig_Source_Channel(unsigned char value, tRioStatusCode *status);
   void writeConfig_Source_Module(unsigned char value, tRioStatusCode *status);
   void writeConfig_Source_AnalogTrigger(bool value, tRioStatusCode *status);
   void writeConfig_RisingEdge(bool value, tRioStatusCode *status);
   void writeConfig_FallingEdge(bool value, tRioStatusCode *status);
   void writeConfig_WaitForAck(bool value, tRioStatusCode *status);
   tConfig readConfig(tRioStatusCode *status);
   unsigned char readConfig_Source_Channel(tRioStatusCode *status);
   unsigned char readConfig_Source_Module(tRioStatusCode *status);
   bool readConfig_Source_AnalogTrigger(tRioStatusCode *status);
   bool readConfig_RisingEdge(tRioStatusCode *status);
   bool readConfig_FallingEdge(tRioStatusCode *status);
   bool readConfig_WaitForAck(tRioStatusCode *status);





private:
   unsigned char _SystemIndex;


   #define Interrupt0_TimeStamp_ADDRESS 0x8194
   #define Interrupt0_Config_ADDRESS 0x8198

   #define Interrupt1_TimeStamp_ADDRESS 0x818C
   #define Interrupt1_Config_ADDRESS 0x8190

   #define Interrupt2_TimeStamp_ADDRESS 0x8184
   #define Interrupt2_Config_ADDRESS 0x8188

   #define Interrupt3_TimeStamp_ADDRESS 0x817C
   #define Interrupt3_Config_ADDRESS 0x8180

   #define Interrupt4_TimeStamp_ADDRESS 0x8174
   #define Interrupt4_Config_ADDRESS 0x8178

   #define Interrupt5_TimeStamp_ADDRESS 0x816C
   #define Interrupt5_Config_ADDRESS 0x8170

   #define Interrupt6_TimeStamp_ADDRESS 0x8164
   #define Interrupt6_Config_ADDRESS 0x8168

   #define Interrupt7_TimeStamp_ADDRESS 0x815C
   #define Interrupt7_Config_ADDRESS 0x8160


};

}
}

#endif // __Interrupt_h__
