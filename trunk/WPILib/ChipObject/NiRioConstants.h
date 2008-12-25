/**
    \file       NiRioConstants.h
    \author     Erik Hons <erik.hons@ni.com>
    \date       12/14/2004

    \brief Public constants for the RIO services

    © Copyright 2004. National Instruments. All rights reserved.
*/

#ifndef  ___NiRioConstants_H___
#define  ___NiRioConstants_H___

//  defines...
//  type declarations (typedefs)...

//
// Basic constants.
//

const tNIRIO_u32 kRioInvalid          = 0xffffffff;
const tNIRIO_u32 kRioMaxLen           = 256;
const tNIRIO_u32 kRioInvalidHandle    = 0;

//
// Device Access
//

typedef char tRioDeviceAccess;
const tRioDeviceAccess kRioDeviceAccessDeny  = '-';
const tRioDeviceAccess kRioDeviceAccessAllow = '+';

/**
      DevUserData registered data structure for non R-series devices that
      utilize RIO technology.
*/

const tNIRIO_u16 kRIODevUserDataKey  = 0x4352;  /// 'CR' for CompactRio

typedef struct {
   tNIRIO_u32 identifier;    /// Use kDevDeviceClassRIO.
   tNIRIO_u32 serialNumber;
} tRIODevUserData;

//  constants...

// Timeouts
const tNIRIO_u32 kRioTimeoutZero      = 0;
const tNIRIO_u32 kRioTimeoutInfinite  = 0xFFFFFFFFUL;

//
// Device attribute identifiers
//
// NOTE: *** Maintain the enum ordering for client compatibility. (e.g.: the
// RIO attribute ring control in the FPGA plug-in code. ***
//

// 32-bit attributes
// Name                        =  X, // AddedVersion: Comments
typedef enum {
   kRioInitialized                =  0UL, // 200
   kRioInterfaceNum               =  1UL, // 200
   kRioProductNum                 =  2UL, // 200
   kRioVendorNum                  =  3UL, // 200
   kRioSerialNum                  =  4UL, // 200
   kRioSignature                  =  5UL, // 200
   kRioRsrcType                   =  6UL, // 200
   kRioDeviceMgr                  =  7UL, // 200: Obsolete in 230
   kRioDefaultTimeout             =  8UL, // 200
   kRioLocalFifoRatio             =  9UL, // 200: Obsolete in 230

   // HACK HACK: PCI-SPECIFIC.
   kRioBusNum                     = 10UL, // 200
   kRioDeviceNum                  = 11UL, // 200
   kRioFuncNum                    = 12UL, // 200

   kRioRestrictedAccess           = 13UL, // 220: Obsolete in 230
   kRioCurrentVersion             = 14UL, // 220
   kRioOldestCompatibleVersion    = 15UL, // 220
   kRioClientIsBigEndian          = 16UL, // 220: kFalse means little-endian
   kRioFpgaInterruptControlOffset = 17UL, // 220

   kRioNumMemWindows              = 18UL, // 230

   // ------------- HACK HACK: Keep in sequential order Until IO Mgr ---
   // HACK HACK until we have the IO Manager.  DO NOT INCLUDE INTO THE
   // RING CONTROL!!!
   kRioMemBaseBar0                = 19UL, // 230
   kRioMemBaseBar1                = 20UL, // 230
   kRioMemSizeBar0                = 21UL, // 230
   kRioMemSizeBar1                = 22UL, // 230
   // --------------- End HACK HACK ------------------------------------

   kRioSessionState               = 23UL, // 230
   kRioPersonalityLockTimeout     = 24UL, // 230
   kRioAddressSpace               = 25UL, // 230

   kRioChassisNum                 = 27UL, // 230
   kRioSlotNum                    = 28UL, // 230
   kRioLocalFifoDefaultDepth      = 29UL, // 230

   kRioTriggerBusNum              = 30UL, // 230
   kRioTriggerReserveLine         = 31UL, // 230    
   kRioTriggerUnreserveLine       = 32UL, // 230    
   kRioTriggerReservedLines       = 33UL, // 230

   kRioIrqNodeReserve             = 34UL, // 230
   kRioFpgaInterruptEnable        = 35UL, // 230

   kRioIsItOkToDownload           = 36UL, // 230

   kRioFpgaResetOffset            = 37UL, // 230
   kRioFpgaResetWidthInBits       = 38UL, // 230
   kRioFpgaControlOffset          = 39UL, // 230

   kRioResetIfLastSession         = 40UL, // 230

   kRioHasDeviceAccess            = 41UL, // 230
} tRioDeviceAttr32;

// String attributes
typedef enum {
   kRioProductName            = 0UL,
   kRioWhatFpgaIsDoing        = 1UL,   // 230
   kRioResourceName           = 2UL,   // 230
} tRioDeviceAttrStr;

// Host attributes
typedef enum {
   kRioHostCurrentVersion          = 0UL,
   kRioHostOldestCompatibleVersion = 1UL,
   kRioHostRpcServerPort           = 2UL,
   kRioHostRpcTimeout              = 3UL, // seconds
   kRioHostDeviceDiscoveryTimeout  = 4UL,
   kRioHostHasDeviceAccess         = 5UL,
   kRioHostRpcSessionTimeout       = 6UL, // seconds
} tRioHostAttribute32;

typedef enum {
   kRioHostAliases       = 0UL,
   kRioHostAlias         = 1UL,
   kRioHostDeviceAccess  = 2UL,
   kRioHostRecentDevices = 3UL,
} tRioHostAttributeString;

const tNIRIO_u32 kRioDynamicRpcServerPort = 0;

//
// IO Window types 
//

const tNIRIO_u32 kRioAddressSpaceMite = 1;
const tNIRIO_u32 kRioAddressSpaceFpga = 2;

//
// Device block[Read|Write] attributes
//

const tNIRIO_u32 kRioIoAttributeAccessByteWidthMask      = 0x0F;
const tNIRIO_u32 kRioIoAttributeDestIncrement            = 0x10;
const tNIRIO_u32 kRioIoAttributeDustMiteNtFlashBitstream = 0x20;

//
// Event types
//

typedef enum {
   kRioEventInvalidEvent      = -1,
   kRioEventFirstEvent        = 0,
   kRioEventPCIInterrupt      = 0,
   kRioEventRemoval           = 1,
   kRioEventMaxNumberOfEvents = 2, // Add all other events before this one
} tRioEventType;

//
// Session states
//

typedef enum {
   kRioSSNothing     = 1,
   kRioSSExclusive   = 2,
   kRioSSInvariant   = 4,
   kRioSSOverride    = 6,
} tRioSessionState;


/// Device signature information.

// The lower 32 bits are divided by:
// bits 28-31  busType , see nRioBusType
// bits 16-27  TBD
// bits 8-15   bus (0 - 255 ),
// bits 3-7    device number (0-31),
// bits 0-2    function number (0-7)
//
/// RIO Bus types.
typedef enum {
   kRioBusTypePci = 0x00000001,
} tRioBusType;

const tNIRIO_u32 kRioBusTypeShift     = 28;
const tNIRIO_u32 kRioBusTypeMask      = 0xF;   // bus type range: 0 - 15 (4 bits)

/// Signature bus number shift
const tNIRIO_u32 kRioBusNumShift      = 8;
const tNIRIO_u32 kRioBusNumMask       = 0xFF;  // range: 0 - 255 (8 bits)

/// Signature device number shift
const tNIRIO_u32 kRioSocketNumShift   = 3;
const tNIRIO_u32 kRioSocketNumMask    = 0x1F;  // range: 0 - 31 (5 bits)

/// Signature function number shift
const tNIRIO_u32 kRioFunctionNumShift = 0;
const tNIRIO_u32 kRioFunctionNumMask  = 0x7;   // range: 0 - 7 (3 bits)

/// RIO Device categories.
typedef enum {
   kRioDeviceCRio    = 0x00000001UL,   //!< compactRIO device
   kRioDevicePxi     = 0x00000002UL,   //!< PXI device
   kRioDeviceFW      = 0x00000004UL,   //!< FireWire (1394) device
   kRioDeviceBB      = 0x00000008UL,   //!< BlueBonnet device
   kRioDeviceSync    = 0x73796E63UL,   //!< 'sync' (NI-PAL ID)
   kRioDeviceIMAQ    = 0x696D6171UL,   //!< 'imaq' (NI-PAL ID)
} tRioDeviceType;

//  declarations for globally-scoped globals...
//  prototypes...
//  inline methods and function macros...

#endif // ___NiRioConstants_H___
