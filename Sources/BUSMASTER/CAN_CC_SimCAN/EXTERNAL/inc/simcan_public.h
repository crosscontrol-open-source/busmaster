/******************************************************************************
//
// FILENAME:			SimCAN_public.h 
//
// DESCRIPTION:		Constants, structures, and function declarations shared 
//								between the interface and the dll.
//
// COPYRIGHT (c): CrossControl 2015 
//
******************************************************************************/

/******************************************************************************
// NESTING HEADER
******************************************************************************/
#ifndef SIMCAN_PUBLIC_H
#define SIMCAN_PUBLIC_H
/******************************************************************************
// INCLUDE FILES
******************************************************************************/
#include <windows.h>

///
/// @addtogroup api_c_cpp_simcan
/// @{
///

/******************************************************************************
// MANIFEST CONSTANTS
******************************************************************************/

/// <summary>Maximum data length of a CAN message.</summary>
#define	CAN_MAX_MSG_LENGTH		8
/// @cond
#define CAN_FRAME_INIT	   0x0
/// @endcond

/// <summary>Denotes a standard CAN frame. Can be used to specify which CAN frames to receive.</summary>
#define CAN_FRAME_STANDARD 0x1

/// <summary>Denotes an extended CAN frame. Can be used to specify which CAN frames to receive.</summary>
#define CAN_FRAME_EXTENDED 0x2

/// <summary>Denotes a remote CAN frame. Can be used to specify which CAN frames to receive.</summary>
#define CAN_FRAME_REMOTE   0x4

/// <summary>
/// A more descriptive name of a CAN frame type.
/// </summary>
typedef ULONG CanFrameType;

/******************************************************************************
// TYPES
******************************************************************************/

/// <summary>
/// A more descriptive name of a CAN message id.
/// </summary>
typedef ULONG CanMsgId;

/// <summary>
/// Callback type for remote reply callback.
/// </summary>
typedef BOOL (__stdcall *SimCanRmr)(long netIndex, ULONG index);

/// <summary>
/// A collection of CAN statistics.
/// </summary>
typedef struct _CanStatistics
{
  /// <summary>Number CAN messages received so far.</summary>
	ULONG	rxMsgCntr;

  /// <summary>Number of data bytes received so far.</summary>
	ULONG	rxDataCntr;

  /// <summary>Number CAN messages transmitted so far.</summary>
	ULONG	txMsgCntr;

  /// <summary>Number of data bytes transmitted so far.</summary>
	ULONG	txDataCntr;

  /// <summary>Number of times that the CAN controller has detected a receive overrun.</summary>
	ULONG	hwOvrnCntr;

  /// <summary>Number of times that the CAN controller has experienced a bus warning condition.</summary>
	ULONG	busWarnCntr;

  /// <summary>Number of times that the CAN controller has entered the bus off state.</summary>
	ULONG	busOffCntr;

  /// <summary>Number of overruns that have occured for a client application. If this occurs, the application needs to be optimized.</summary>
	ULONG	appOvrnCntr;

  /// <summary>Number of times that a overrun has occurred in the type-ahead receive fifo. If this occurs then the size of the type-ahead receive fifo needs to be increased, see configuration value <i>RxFifoSize</i>.</summary>
	ULONG	rxFifoOvrnCntr;

  /// <summary>Maximum number of messages that the type-ahead receive fifo have contained.</summary>
	ULONG	rxFifoMax;
} CanStatistics;

/// <summary>
/// A collection of CAN properties.
/// </summary>
typedef struct _CanProperties
{
  /// <summary>Interface types.</summary>
	ULONG interfaceTypes;

  /// <summary>Supported frametypes.</summary>
	ULONG	frameTypes; 
} CanProperties;

/// <summary>
/// CAN message structure.
/// </summary>
typedef struct _CanMsg
{
  /// <summary>Id of can message.</summary>
	CanMsgId id;

  /// <summary>Data of Can message.</summary>
	UCHAR data[CAN_MAX_MSG_LENGTH];
} CanMsg;

/// <summary>
/// 8-byte CAN time stamp.
/// </summary>
typedef struct _CanTimeStamp
{
  /// <summary>Low 4-bytes.</summary>
	ULONG low;

  /// <summary>High 4-bytes.</summary>
	ULONG high;
} CanTimeStamp;

/// <summary>
/// A more descriptive name of a CAN handle.
/// </summary>
typedef long CanHandle;

///
/// @}
///

#endif /* SIMCAN_PUBLIC_H */
