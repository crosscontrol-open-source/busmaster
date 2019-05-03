/******************************************************************************
//
// FILENAME:		simcanerrorcodes.h 
//
// DESCRIPTION:		-
//
// COPYRIGHT (c):	CrossControl 2014 
//
******************************************************************************/
/// <summary></summary>
#ifndef CAN_ERROR_CODES_H
#define CAN_ERROR_CODES_H

/// <summary>Base for all CAN error codes.</summary>
#define CAN_ERROR_MSG_BASE 0x1f00
/// <summary>Operation succeeded.</summary>
#define CAN_OK							0	+ CAN_ERROR_MSG_BASE
/// <summary>Operation failed, general fault no specific error applicable.</summary>
#define CAN_FAIL						1	+ CAN_ERROR_MSG_BASE
/// <summary>The device is already opened.</summary>
#define CAN_ERROR_DEVICE_ALREADY_OPEN	2	+ CAN_ERROR_MSG_BASE
/// <summary>There are no more drivers.</summary>
#define CAN_ERROR_NO_MORE_DRIVER		3	+ CAN_ERROR_MSG_BASE
/// <summary>Can not find a callback function for receiving messages.</summary>
#define CAN_ERROR_NO_RCV_CALLBACK		4	+ CAN_ERROR_MSG_BASE
/// <summary>Failed creating thread.</summary>
#define CAN_ERROR_CREATING_THREAD		5	+ CAN_ERROR_MSG_BASE
/// <summary>Hardware is not responding.</summary>
#define CAN_ERROR_NO_CONTACT_HW			6	+ CAN_ERROR_MSG_BASE
/// <summary>Failed to send message to hardware.</summary>
#define CAN_ERROR_SEND_HW				7	+ CAN_ERROR_MSG_BASE
/// <summary>Failed to receive message from hardware.</summary>
#define CAN_ERROR_RECEIVE_HW			8	+ CAN_ERROR_MSG_BASE
/// <summary>Remote frame error.</summary>
#define CAN_ERROR_REMOTE_FRAME			9	+ CAN_ERROR_MSG_BASE
/// <summary>Bus off, the driver can not sense a net.</summary>
#define CAN_ERROR_BUSOFF				10	+ CAN_ERROR_MSG_BASE
/// <summary>No more free handles.</summary>
#define CAN_ERROR_NO_MORE_HANDLES		11	+ CAN_ERROR_MSG_BASE
/// <summary>The net does not exist.</summary>
#define CAN_ERROR_NO_MORE_NETS			12  + CAN_ERROR_MSG_BASE
/// <summary>The process was already initiated.</summary>
#define CAN_ERROR_ALREADY_INITIATED		13  + CAN_ERROR_MSG_BASE
/// <summary>The handle is bad, it may be an illegal handle or it is not opened.</summary>
#define CAN_ERROR_WRONG_HANDLE			14  + CAN_ERROR_MSG_BASE
/// <summary>The process is not initialized.</summary>
#define CAN_ERROR_NOT_INITIALIZED		15	+ CAN_ERROR_MSG_BASE
/// <summary>The dynamic connection failed.</summary>
#define CAN_ERROR_CONNECT_FAILED		16	+ CAN_ERROR_MSG_BASE
/// <summary>The hardware handle is bad, it may be an illegal handle or it is not opened.</summary>
#define CAN_ERROR_WRONG_HW_HANDLE		17  + CAN_ERROR_MSG_BASE
/// <summary>Bad receive type (0). Not sporadic (1) or periodic (2).</summary>
#define CAN_ERROR_BAD_CALLBACK_TYPE		18  + CAN_ERROR_MSG_BASE
/// <summary>Null handle provided. Open may have returned null.</summary>
#define CAN_ERROR_NULL_HANDLE			19  + CAN_ERROR_MSG_BASE
/// <summary>Trying to open illegal null net.</summary>
#define CAN_ERROR_NULL_NET				20  + CAN_ERROR_MSG_BASE
/// <summary>Failed to vaildate license.</summary>
#define CAN_ERROR_NO_LICENSE			21  + CAN_ERROR_MSG_BASE
/// <summary>Could not find an xml file.</summary>
#define CAN_ERROR_NO_XML_FILE			22  + CAN_ERROR_MSG_BASE
/// <summary>Could not load HwXML.dll.</summary>
#define CAN_ERROR_LOAD_HWXML			23  + CAN_ERROR_MSG_BASE
/// <summary>Could not create shared memory.</summary>
#define CAN_ERROR_SHARED_MEMORY			24  + CAN_ERROR_MSG_BASE
/// <summary>Disallowed configuration in the XML file.</summary>
#define CAN_ERROR_FAULTY_XML_FILE		25  + CAN_ERROR_MSG_BASE
/// <summary>Failed to load interface dll.</summary>
#define CAN_ERROR_LOAD_INTERFACE		26  + CAN_ERROR_MSG_BASE
/// <summary>Trying to send/receive bad frametype.</summary>
#define CAN_ERROR_FRAMETYPE				27  + CAN_ERROR_MSG_BASE
/// <summary>No more HW handles.</summary>
#define CAN_ERROR_NO_MORE_HW_HANDLE		28  + CAN_ERROR_MSG_BASE
/// <summary>Last message was affeted by fault injection packet loss.</summary>
#define CAN_ERROR_PACKET_LOSS			29  + CAN_ERROR_MSG_BASE
/// <summary>Problem related to IXXAT adapter.</summary>
#define CAN_ERROR_IXXAT			30  + CAN_ERROR_MSG_BASE
/// <summary>Rx queue empty/Tx queue full.</summary>
#define CAN_ERROR_IXXAT_RX_TX_QUEUE							31  + CAN_ERROR_MSG_BASE
/// <summary>Function could not be carried out due to HW or SW errors; check function of the PC/CAN-interface.</summary>
#define CAN_ERROR_IXXAT_HW_SW_FUNCTION						32  + CAN_ERROR_MSG_BASE
/// <summary>Function is not supported in this form (support-error).</summary>
#define CAN_ERROR_IXXAT_FUNCTION_NOT_SUPPORTED				33  + CAN_ERROR_MSG_BASE
/// <summary>Calling parameter(s) not correct or out of range.</summary>
#define CAN_ERROR_IXXAT_PARAMETERS							34  + CAN_ERROR_MSG_BASE
/// <summary>Resource error. Limits (memory, max. nbr of queues, etc.) has been exceeded.</summary>
#define CAN_ERROR_IXXAT_RESOURCE							35  + CAN_ERROR_MSG_BASE
/// <summary>Receive queue overrun.</summary>
#define CAN_ERROR_IXXAT_RECEIVE_QUEUE_OVERRUN				36  + CAN_ERROR_MSG_BASE
/// <summary>A CAN message couldn't be sent for a long time (cable error, wrong baud rate etc).</summary>
#define CAN_ERROR_IXXAT_MESSAGE_NOT_SENT					37  + CAN_ERROR_MSG_BASE
/// <summary>CAN fault Injection component initialization error.</summary>
#define CAN_ERROR_FAULT_INJECTION_INIT			        38  + CAN_ERROR_MSG_BASE
/// <summary>CAN fault Injection component error.</summary>
#define CAN_ERROR_FAULT_INJECTION_INTERNAL				39  + CAN_ERROR_MSG_BASE
/// <summary>Invalid fault type or fault registration data.</summary>
#define CAN_ERROR_FAULT_INJECTION_INVALID_FAULT_DATA	40  + CAN_ERROR_MSG_BASE
/// <summary>Maximum number of fault entries reached.</summary>
#define CAN_ERROR_FAULT_INJECTION_MAX_FAULT_ENTRIES		41  + CAN_ERROR_MSG_BASE
/// <summary>Fault Injection timer overflow.</summary>
#define CAN_ERROR_FAULT_INJECTION_TIMER_OVERFLOW		42  + CAN_ERROR_MSG_BASE
/// <summary>Fault Injection timer not initialized or not started.</summary>
#define CAN_ERROR_FAULT_INJECTION_TIMER_NOT_STARTED		43  + CAN_ERROR_MSG_BASE
/// <summary>Fault Injection timer error.</summary>
#define CAN_ERROR_FAULT_INJECTION_TIMER_OTHER			44  + CAN_ERROR_MSG_BASE
/// <summary>Fault Injection shared global data error.</summary>
#define CAN_ERROR_FAULT_INJECTION_GLOBAL_DATA			45  + CAN_ERROR_MSG_BASE
/// <summary>Invalid fault entry index.</summary>
#define CAN_ERROR_FAULT_INJECTION_INVALID_ENTRY_IDX		46  + CAN_ERROR_MSG_BASE
/// <summary>Invalid fault entry handle.</summary>
#define CAN_ERROR_FAULT_INJECTION_INVALID_FAULT_HANDLE	47 + CAN_ERROR_MSG_BASE
/// <summary>Problem related to KVASER adapter.</summary>
#define CAN_ERROR_KVASER			                    31  + CAN_ERROR_MSG_BASE
/// @cond

#define _SIZE_CAN_ERROR_STRUCT_			48
/// @endcond

/// <summary>Check whether or not the error is a CAN error.</summary>
#define IS_CAN_ERROR(x)			((x&CAN_ERROR_MSG_BASE) == CAN_ERROR_MSG_BASE)
/// <summary>Retrieve the CAN error description.</summary>
#define CAN_ERROR_MSG(x)		(IS_CAN_ERROR(x)?CanErrorMsg[x-CAN_ERROR_MSG_BASE]:TEXT("ERROR DESCRIPTION MISSING"))

/// <summary>Check whether or not the error is a CAN error.</summary>
#define IS_CAN_ERROR_A(x)			((x&CAN_ERROR_MSG_BASE) == CAN_ERROR_MSG_BASE)
/// <summary>Retrieve the CAN error description.</summary>
#define CAN_ERROR_MSG_A(x)		(IS_CAN_ERROR(x)?CanErrorMsgA[x-CAN_ERROR_MSG_BASE]:("ERROR DESCRIPTION MISSING"))

static const TCHAR CanErrorMsg[_SIZE_CAN_ERROR_STRUCT_][100] = {
	TEXT("Operation succeeded."),
	TEXT("Operation failed, General fault no specific error applicable."),
	TEXT("The device is already opened."),
	TEXT("There are no more drivers."),
	TEXT("Can not find a callback function for receiving messages."),
	TEXT("Failed creating thread."),
	TEXT("Hardware is not responding."),
	TEXT("Failed to send message to hardware."),
	TEXT("Failed to receive message from hardware."),
	TEXT("Remote Frame error."),
	TEXT("Bus off, the driver can not sense a net."),
	TEXT("No more free handles."),
	TEXT("The net does not exist."),
	TEXT("The process was already initiated."),
	TEXT("The handle is bad, it may be an illegal handle or it is not opened."),
	TEXT("The process is not initialized"),
	TEXT("The dynamic connection failed"),
	TEXT("The hardware handle is bad, it may be an illegal handle or it is not opened."), /*77 chars...*/
	TEXT("Bad receive type (0). Not sporadic (1) or periodic (2)."),
	TEXT("Null handle provided. Open may have returned null."),
	TEXT("Trying to open illegal null net \"CAN0\"."),
	TEXT("Failed to vaildate license."),
	TEXT("Could not find an xml file."),
	TEXT("Could not load HwXML.dll."),
	TEXT("Could not create shared memory."),
	TEXT("Disallowed configuration in the XML file."),
	TEXT("Failed to load interface dll."),
	TEXT("Trying to send/receive bad frametype."),
	TEXT("No more HW handles."),
	TEXT("Last message was affeted by fault injection packet loss."),
	TEXT("Problem related to IXXAT adapter."),
    TEXT("Rx queue empty/Tx queue full."),
    TEXT("Function could not be carried out due to HW or SW errors; check function of the PC/CAN-interface."),
    TEXT("Function is not supported in this form (support-error)."),
    TEXT("Calling parameter(s) not correct or out of range."),
    TEXT("Resource error. Limits (memory, max. nbr of queues, etc.) has been exceeded."),
    TEXT("Receive queue overrun."),
    TEXT("A CAN message couldn't be sent for a long time (cable error, wrong baud rate etc)."),
	TEXT("Can Fault Injection component initialization error."),
	TEXT("Can Fault Injection component error."),
	TEXT("Invalid fault type or fault registration data."),
	TEXT("Maximum number of fault entries reached."),
	TEXT("Fault Injection timer overflow."),
	TEXT("Fault Injection timer not initialized or not started."),
	TEXT("Fault Injection timer error."),
	TEXT("Fault Injection shared global data error."),
	TEXT("Invalid fault entry index."),
	TEXT("Invalid fault entry handle.")
};

static const char CanErrorMsgA[_SIZE_CAN_ERROR_STRUCT_][100] = {
	("Operation succeeded."),
	("Operation failed, General fault no specific error applicable."),
	("The device is already opened."),
	("There are no more drivers."),
	("Can not find a callback function for receiving messages."),
	("Failed creating thread."),
	("Hardware is not responding."),
	("Failed to send message to hardware."),
	("Failed to receive message from hardware."),
	("Remote Frame error."),
	("Bus off, the driver can not sense a net."),
	("No more free handles."),
	("The net does not exist."),
	("The process was already initiated."),
	("The handle is bad, it may be an illegal handle or it is not opened."),
	("The process is not initialized"),
	("The dynamic connection failed"),
	("The hardware handle is bad, it may be an illegal handle or it is not opened."), /*77 chars...*/
	("Bad receive type (0). Not sporadic (1) or periodic (2)."),
	("Null handle provided. Open may have returned null."),
	("Trying to open illegal null net \"CAN0\"."),
	("Failed to vaildate license."),
	("Could not find an xml file."),
	("Could not load HwXML.dll."),
	("Could not create shared memory."),
	("Disallowed configuration in the XML file."),
	("Failed to load interface dll."),
	("Trying to send/receive bad frametype."),
	("No more HW handles."),
	("Last message was affeted by fault injection packet loss."),
	("Problem related to IXXAT adapter."),
    ("Rx queue empty/Tx queue full."),
    ("Function could not be carried out due to HW or SW errors; check function of the PC/CAN-interface."),
    ("Function is not supported in this form (support-error)."),
    ("Calling parameter(s) not correct or out of range."),
    ("Resource error. Limits (memory, max. nbr of queues, etc.) has been exceeded."),
    ("Receive queue overrun."),
    ("A CAN message couldn't be sent for a long time (cable error, wrong baud rate etc)."),
	("Can Fault Injection component initialization error."),
	("Can Fault Injection component error."),
	("Invalid fault type or fault registration data."),
	("Maximum number of fault entries reached."),
	("Fault Injection timer overflow."),
	("Fault Injection timer not initialized or not started."),
	("Fault Injection timer error."),
	("Fault Injection shared global data error."),
	("Invalid fault entry index."),
	("Invalid fault entry handle.")
};

#endif
