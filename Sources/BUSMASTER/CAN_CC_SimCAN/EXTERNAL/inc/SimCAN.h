/******************************************************************************
//
// FILENAME:		SimCAN.h 
//
// DESCRIPTION:		The CAN interface.
//
// COPYRIGHT (c):	CrossControl 2015 
//
******************************************************************************/

#ifndef SIMCAN_H
#define SIMCAN_H

#include <windows.h>
#include <TCHAR.h>
#include "SimCAN_public.h"
#include "SimCanErrorCodes.h"

///
/// @defgroup api_c_cpp_simcan SimCAN
/// @ingroup api_c_cpp
/// @{
///

/// @cond

#ifdef _UNICODE
	#define CanOpen CanOpenW
#else
	#define CanOpen CanOpenA
#endif

/// @endcond

// Only defined when generating documentation.
#ifdef DOXYGEN
/// <summary><c>CanOpen</c> is defined as <c>CanOpenW</c> when <c>_UNICODE</c> and <c>UNICODE</c> are defined, otherwise <c>CanOpenA</c>.</summary>
#define CanOpen CanOpenA

#define CanOpen CanOpenW
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Opens the CAN interface with Normal User privilege.
/// </summary>
/// <remarks>
/// There is no restriction on the number of users with Normal User privilege for a specific interface. The caller may only send messages with CAN id's within the configured Normal User range. The caller may receive messages from the interface without <i>stealing</i> messages from others that have called <see cref="CanOpen"/>.
/// </remarks>
/// <param name="pNetName">The CAN net name, CAN1-CANn. UNICODE string, depending on if <c>_UNICODE</c> and <c>UNICODE</c> are defined the <see cref="CanOpen"/> macro is defined as <see cref="CanOpenW"/>.</param>
/// <returns>A handle to the opened interface or <c>NULL</c> if operation failed. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to open a <c>SimCan</c> interface and then close it.
/// @code{.cpp}
/// // _UNICODE and UNICODE are defined thus CanOpenW will get called.
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
CanHandle __stdcall
CanOpenW(
	LPCWSTR pNetName
	);

/// <summary>
/// Opens the CAN interface with Normal User privilege.
/// </summary>
/// <remarks>
/// There is no restriction on the number of users with Normal User privilege for a specific interface. The caller may only send messages with CAN id's within the configured Normal User range. The caller may receive messages from the interface without <i>stealing</i> messages from others that have called <see cref="CanOpen"/>.
/// </remarks>
/// <param name="pNetName">The CAN net name, CAN1-CANn. ANSI string, depending on if <c>_UNICODE</c> and <c>UNICODE</c> are defined the <see cref="CanOpen"/> macro is defined as <see cref="CanOpenA"/>.</param>
/// <returns>A handle to the opened interface or <c>NULL</c> if operation failed. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to open a <c>SimCan</c> interface and then close it.
/// @code{.cpp}
/// // _UNICODE and UNICODE are not defined thus CanOpenA will get called.
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// // Use CAN interface...
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
CanHandle __stdcall
CanOpenA(
	LPCSTR pNetName
	);

/// <summary>
/// Closes the CAN interface.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to open a <c>SimCan</c> interface and then close it.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// // Use CAN interface...
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanClose(
	CanHandle hInterface
	);

/// <summary>
/// Sends a message on the CAN interface.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="pCanMsg">A pointer to the message to send.</param>
/// <param name="dataLength">Number of data bytes to send.</param>
/// <param name="bRtr">Should be set to <c>TRUE</c> if message is to be sent as a remote frame.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to send a message on a <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// CanMsg msg = { 1, { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 } };
///
/// if(CanSend(hCan, &msg, 8, FALSE))
///   puts("Message successfully sent.");
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanSend(
	CanHandle hInterface,
	CanMsg *pCanMsg,
	DWORD dataLength,
	BOOL bRtr
	);

/// <summary>
/// Receives a message from the CAN interface.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="pCanMsg">A pointer to the received message.</param>
/// <param name="pDataLength">A pointer to the number of data bytes received.</param>
/// <param name="pCanMsgSel">A pointer to an array specifying a selection of which messages that should be received. The first element, (pCanMsgSel[0]), should specify the number of CAN message IDs in the array. If pCanMsgSel[0] is positive then any of IDs in the array will be received. If pCanMsgSel[0] is negative then any of IDs that is not in the array will be received. If any message is reqested then <c>NULL</c> should be supplied.</param>
/// <param name="frameTypeSel">Specifies which frame types that should be received. If frameTypeSel is set to <c>CAN_FRAME_STANDARD</c> then only standard frames matching pCanMsgSel are received. If frameTypeSel is set to <c>CAN_FRAME_EXTENDED</c> then only extended frames matching pCanMsgSel are received. If frameTypeSel is set to <c>CAN_FRAME_STANDARD | CAN_FRAME_EXTENDED</c> then either standard or extended frames matching pCanMsgSel are received. If frameTypeSel is also set to <c>CAN_FRAME_REMOTE</c> remote frames are received, if the xml-file is set accordingly.</param>
/// <param name="pFrameType">A pointer to the frame type of the received message. It can be either <c>CAN_FRAME_STANDARD</c> or <c>CAN_FRAME_EXTENDED</c>. pFrameType can ALSO be set to <c>CAN_FRAME_REMOTE</c> if the received frame was a remote frame.</param>
/// <param name="milliseconds">Specifies the time-out interval, in milliseconds. The function returns if the interval elapses, even if no messages are received. If milliseconds is zero, the function checks if there are any messages and returns immediately. If milliseconds is <c>INFINITE</c>, the function does not return until a message is received.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to receive a message from a <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// CanMsg msg;
/// CanFrameType frameType;
/// DWORD dataLength;
///
/// // Only receive messages with id 3 or 5.
/// CanMsgId canMsgSel[] = { 2, 3, 5 };
///
/// if(CanReceive(hCan, &msg, &dataLength, canMsgSel, CAN_FRAME_STANDARD, &frameType, 1000))
///   puts("Message successfully received.");
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanReceive(
	CanHandle hInterface,
	CanMsg *pCanMsg,
	LPDWORD pDataLength,
	CanMsgId *pCanMsgSel,
	CanFrameType frameTypeSel,
	CanFrameType *pFrameType,
	DWORD milliseconds
	);

/// <summary>
/// Adds a reply to a received remote frame.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="pCanMsg">A pointer to the message of the remote frame reply.</param>
/// <param name="dataLength">Number of data bytes in the remote frame reply.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to add a remote reply on a <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// CanMsg msg = { 10, { 0x10, 0x20, 0x30, 0, 0, 0, 0, 0 } };
///
/// if(CanAddRemoteReply(hCan, &msg, 3))
///   puts("Successfully added remote reply.");
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanAddRemoteReply(
	CanHandle hInterface,
	CanMsg *pCanMsg,
	DWORD dataLength
	);

/// <summary>
/// Removes a reply to a received remote frame.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="id">CAN message identifier of the remote frame that the reply is associated with.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to remove a remote reply on a <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// if(CanRemoveRemoteReply(hCan, 10))
///   puts("Successfully removed remote reply.");
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanRemoveRemoteReply(
	CanHandle hInterface,
	CanMsgId id
	);

/// <summary>
/// Enumerates remote frame replies.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="index">Specifies the index of the subkey to retrieve. This parameter should be zero for the first call to the <see cref="CanEnumRemoteReply"/> function and then, as long as <c>ERROR_SUCCESS</c> is returned, incremented for subsequent calls until <c>ERROR_NO_MORE_ITEMS</c> is returned.</param>
/// <param name="pCanMsg">A pointer to the message of the remote frame reply.</param>
/// <param name="pDataLength">A pointer to the number of data bytes of the remote frame reply.</param>
/// <param name="pFrameType">A pointer to theframe type of the remote frame reply</param>
/// <returns><c>ERROR_SUCCESS</c> if operation succeeded otherwise another error code.</returns>
/// <example>The following example shows how to iterate over all the remote replies on a <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// int index = 0;
/// CanMsg msg;
/// CanFrameType frameType;
/// DWORD dataLength;
///
/// while(CanEnumRemoteReply(hCan, index, &msg, &dataLength, &frameType) == ERROR_SUCCESS)
/// {
///   // Do something with remote reply.
///
///   index++;
/// }
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
DWORD __stdcall
CanEnumRemoteReply(
	CanHandle hInterface,
	ULONG index,
	CanMsg *pCanMsg,
	LPDWORD pDataLength,
	CanFrameType *pFrameType
	);

/// <summary>
/// Retrieves performance and error counters.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="pStatistics">A pointer to the performance and error counters.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to retrieve how many messages have been received since the <c>SimCan</c> interface was opened.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// // Some point later in time...
///
/// CanStatistics stats;
///
/// if(CanGetStatistics(hCan, &stats))
///   printf("Messages received: %d (%d data bytes in total)\n", stats.rxMsgCntr, stats.rxDataCntr);
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanGetStatistics(
	CanHandle hInterface,
	CanStatistics *pStatistics
	);

/// <summary>
/// Retrieves interface properties.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="pProperties">A pointer to the properties.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to check if extended frames are supported by the <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// CanProperties properties;
///
/// if(CanGetProperties(hCan, &properties))
/// {
///   if((properties.frameTypes & CAN_FRAME_EXTENDED) == CAN_FRAME_EXTENDED)
///     puts("Extended frames are supported by the CAN1 interface.");
///   else
///     puts("Extended frames are not supported by the CAN1 interface.");
/// }
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanGetProperties(
	CanHandle hInterface,
	CanProperties *pProperties
	);
	
/// <summary>
/// Retrieves the timestamp of the last received message.
/// </summary>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="pTimeStamp">A pointer to the time stamp.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to retrieve the timestamp of the last received message on the <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// // Some point later in time...
///
/// CanTimeStamp timeStamp;
///
/// if(CanGetLastTimeStamp(hCan, &timeStamp))
/// {
///   ULONGLONG ts = ((ULONGLONG)timeStamp.high << 32) | timeStamp.low;
/// 
///   printf("Timestamp of last received message: %llu\n", ts);
/// }
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall
CanGetLastTimeStamp(
	CanHandle hInterface,
	CanTimeStamp *pTimeStamp
	);

/// <summary>
/// Returns the handle to the CAN device.
/// </summary>
/// <remarks>
/// The handle is intended to be used in <c>DeviceIoControl</c> calls.
/// </remarks>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <returns>A handle to the CAN device if operation succeeded otherwise <c>INVALID_HANDLE_VALUE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to retrieve the CAN device handle of the <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// HANDLE deviceHandle = CanGetDeviceHandle(hCan);
///
/// if(deviceHandle != INVALID_HANDLE_VALUE)
///   puts("Successfully retrieved the CAN device handle.");
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
HANDLE __stdcall CanGetDeviceHandle(
  CanHandle hInterface
  );

/// <summary>
/// Registers a callback function that is called whenever a remote frame is received.
/// </summary>
/// <remarks>
/// This will only work if remote replies are handled by software or if the selected hardware supports remote callback.
/// </remarks>
/// <param name="hInterface">A handle to the opened interface.</param>
/// <param name="remoteCallback">Function pointer to the callback function. The function must be of the <see cref="SimCanRmr"/> type.</param>
/// <returns><c>TRUE</c> if operation succeeded otherwise <c>FALSE</c>. If operation failed then <c>GetLastError</c> can be used to get information about the error.</returns>
/// <example>The following example shows how to register a remote frame callback on the <c>SimCan</c> interface.
/// @code{.cpp}
/// CanHandle hCan = CanOpen(TEXT("CAN1"));
/// if(hCan == NULL)
///   return 0;
///
/// // Callback signature:
/// // BOOL CALLBACK RmrCallback(long netIndex, ULONG index);
///
/// if(CanRegisterRmrCallBack(hCan, RmrCallback))
///   puts("Remote frame callback registered successfully.");
///
/// if(!CanClose(hCan))
///   puts("Failed to close handle.");
/// @endcode
/// </example>
/// <seealso cref="CanClose"/>
/// <seealso cref="CanOpen"/>
BOOL __stdcall CanRegisterRmrCallBack(CanHandle hInterface,SimCanRmr remoteCallback);

#ifdef __cplusplus
}
#endif

///
/// @}
///

#endif /* SIMCAN_H */