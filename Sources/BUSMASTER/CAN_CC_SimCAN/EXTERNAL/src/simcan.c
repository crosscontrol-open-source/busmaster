/******************************************************************************
//
// FILENAME:		simcan.c 
//
// DESCRIPTION:		The CAN interface.
//
// COPYRIGHT (c):	CrossControl 2015 
//
******************************************************************************/

#include <windows.h>
#include "SimCAN.h"
#include "SimCanErrorCodes.h"

/// @cond
#define DLLEXPORT __declspec(dllexport)

static HINSTANCE SimCANDll = NULL;
static const LPCTSTR SimCANDllNameC = TEXT("SimCan.dll"); 
BOOL isInitiated=FALSE;

#define sInit_Name				        "SimCanInit"
#define sOpen_Name				        "SimCanOpen"
#define sClose_Name				        "SimCanClose"
#define sSend_Name						"SimCanSend"
#define sReceive_Name					"SimCanReceive"
#define sAddRemoteReply_Name			"SimCanAddRemoteReply"
#define sRemoveRemoteReply_Name			"SimCanRemoveRemoteReply"
#define sGetStatistics_Name				"SimCanGetStatistics"
#define sGetLastTimeStamp_Name			"SimCanGetLastTimeStamp"
#define sGetProperties_Name				"SimCanGetProperties"
#define sEnumRemoteReply_Name			"SimCanEnumRemoteReply"
#define sRegisterRmrCallBack_Name		"SimCanRegisterRmrCallBack"
#define sShut_Name						"SimCanShutDown"
#define sGetDeviceHandle_Name			"SimCanGetDeviceHandle"

typedef DLLEXPORT BOOL		(__stdcall *sInit_PT)(void);
typedef DLLEXPORT BOOL		(__stdcall *sShut_PT)(void);
typedef DLLEXPORT CanHandle (__stdcall *sOpen_PT)(long);
typedef DLLEXPORT BOOL		(__stdcall *sClose_PT)(CanHandle);
typedef DLLEXPORT BOOL		(__stdcall *sSend_PT)(CanHandle,CanMsg *,DWORD,BOOL);
typedef DLLEXPORT BOOL		(__stdcall *sReceive_PT)(CanHandle,CanMsg *,LPDWORD,CanMsgId *,CanFrameType,CanFrameType*,DWORD);
typedef DLLEXPORT BOOL		(__stdcall *sAddRemoteReply_PT)(CanHandle,CanMsg*,DWORD);
typedef DLLEXPORT BOOL		(__stdcall *sRemoveRemoteReply_PT)(CanHandle,CanMsgId);
typedef DLLEXPORT BOOL		(__stdcall *sGetStatistics_PT)(CanHandle,CanStatistics*);
typedef DLLEXPORT BOOL		(__stdcall *sGetLastTimeStamp_PT)(CanHandle,CanTimeStamp*);
typedef DLLEXPORT BOOL		(__stdcall *sGetProperties_PT)(CanHandle,CanProperties*);
typedef DLLEXPORT DWORD		(__stdcall *sEnumRemoteReply_PT)(CanHandle,ULONG,CanMsg*,LPDWORD,CanFrameType*);
typedef DLLEXPORT BOOL		(__stdcall *sRegisterRmrCallBack_PT)(CanHandle ,SimCanRmr);
typedef DLLEXPORT HANDLE	(__stdcall *sGetDeviceHandle_PT)(CanHandle);


/***********************************
 * Internal functions
 ***********************************/

BOOL __stdcall _CanInit()
{
	static sInit_PT sInit_P = NULL;
	long err=ERROR_SUCCESS;	

	if (sInit_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sInit_P = (sInit_PT)GetProcAddress(SimCANDll, sInit_Name);   

		if (sInit_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanInit!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	if(sInit_P()){
		isInitiated=TRUE;
		return TRUE;
	}else{
		return FALSE;
	}
}

long getStrNumberW(LPCWSTR pNetName,ULONG len){
	//Assumes a name in the form CANXX, where XX is a number
	wchar_t netNameIndexStr[50];
	ULONG netNameIndex;
	
	ULONG j = len;
	ULONG k = 0; 

	if(wcslen(pNetName)<(len+1)){
		SetLastError(ERROR_BAD_ARGUMENTS);
		return -1;
	}
	while(pNetName[j] != '\0')
	{
		netNameIndexStr[k] = pNetName[j];
		j++;
		k++;
	}

	netNameIndexStr[k] = '\0';	
	netNameIndex = _wtoi(netNameIndexStr);

	SetLastError(ERROR_SUCCESS);
	return netNameIndex;
	
}

long getStrNumberA(LPCSTR pNetName,ULONG len){
	//Assumes a name in the form CANXX, where XX is a number

	char netNameIndexStr[50];
	ULONG netNameIndex;
	
	ULONG j = len;
	ULONG k = 0; 

	if(strlen(pNetName)<(len+1)){
		SetLastError(ERROR_BAD_ARGUMENTS);
		return -1;
	}


	while(pNetName[j] != '\0')
	{
		netNameIndexStr[k] = pNetName[j];
		j++;
		k++;
	}

	netNameIndexStr[k] = '\0';	
	netNameIndex = atoi(netNameIndexStr);

	SetLastError(ERROR_SUCCESS);
	return netNameIndex;
	
}

static CanHandle _CanOpen(long netIndex)
{
	static sOpen_PT sOpen_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated){
		if(!_CanInit()){
			if(GetLastError() != CAN_ERROR_ALREADY_INITIATED){
				return 0;
			}
		}
	}

	if (sOpen_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sOpen_P = (sOpen_PT)GetProcAddress(SimCANDll, sOpen_Name);   

		if (sOpen_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanOpen!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}
	return (CanHandle)sOpen_P(netIndex);
}
/// @endcond

/***********************************
 * API functions
 ***********************************/

/******************************************************************************
//
// FUNCTION:	CanOpenW
//
// DESCRIPTION:	Opens the CAN interface with Normal User privilege.
//				There is no restriction on the number of users with Normal User
//				privilege for a specific interface.
//				The caller may only send messages with CAN id's within the
//				configured Normal User range.
//				The caller may receive messages from the interface without
//				"stealing" messages from others that have called CanOpen.
//
// PARAMETERS:	pNetName	The CAN net name, CAN1-CANn.
//							UNICODE string.
//
// RETURNS:		A handle to the opened interface or NULL if operation failed.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//
******************************************************************************/

CanHandle __stdcall CanOpenW(LPCWSTR pNetName)
{
	return _CanOpen(getStrNumberW(pNetName,3));
}

/******************************************************************************
//
// FUNCTION:	CanOpenA
//
// DESCRIPTION:	Opens the CAN interface with Normal User privilege.
//				There is no restriction on the number of users with Normal User
//				privilege for a specific interface.
//				The caller may only send messages with CAN id's within the
//				configured Normal User range.
//				The caller may receive messages from the interface without
//				"stealing" messages from others that have called CanOpen.
//
// PARAMETERS:	pNetName	The CAN net name, CAN1-CANn.
//							ANSI string.
//
// RETURNS:		A handle to the opened interface or NULL if operation failed.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//
******************************************************************************/
CanHandle __stdcall CanOpenA(LPCSTR pNetName)
{
	return _CanOpen(getStrNumberA(pNetName,3));
}


/******************************************************************************
//
// FUNCTION:	CanClose
//
// DESCRIPTION:	Closes the CAN interface.
//
// PARAMETERS:	hInterface	A handle to the opened interface.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//
******************************************************************************/

BOOL __stdcall CanClose(CanHandle hInterface)
{
	static sClose_PT sClose_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;


	if (sClose_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sClose_P = (sClose_PT)GetProcAddress(SimCANDll, sClose_Name);   

		if (sClose_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanClose!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sClose_P(hInterface);
}


/******************************************************************************
//
// FUNCTION:	CanSend
//
// DESCRIPTION:	Sends a message on the CAN interface.
//
// PARAMETERS:	hInterface	A handle to the opened interface.
//				pCanMsg		A pointer to the message to send.
//				dataLength	The number of data bytes to send.
//				bRtr		Should be set to TRUE if message is to be sent as a
//							remote frame.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//				If the operation failed because of the interface was opened
//				with CanOpen and the CAN id of the message is outside the
//				Normal User range then GetLastError will return 
//				ERROR_ACCESS_DENIED.
//
******************************************************************************/

BOOL __stdcall CanSend(CanHandle hInterface,
					   CanMsg *pCanMsg,
					   DWORD dataLength,
					   BOOL bRtr
					   )
{
	static sSend_PT sSend_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sSend_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sSend_P = (sSend_PT)GetProcAddress(SimCANDll, sSend_Name);   

		if (sSend_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanSend!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sSend_P(hInterface, pCanMsg,dataLength,bRtr);
}


/******************************************************************************
//
// FUNCTION:	CanReceive
//
// DESCRIPTION:	Receives a message from the CAN interface.
//
// PARAMETERS:	hInterface		A handle to the opened interface.
//				pCanMsg			A pointer to the received message.
//				pDataLength		A pointer to the number of data bytes
//								received.
//				pCanMsgSel		A pointer to an array specifying a selection
//								of which messages that should be received.
//								The first element, (pCanMsgSel[0]), should
//								specify the number of CAN message IDs in the
//								array.
//								If pCanMsgSel[0] is positive then
//								any of IDs in the array will be received.
//								If pCanMsgSel[0] is negative then
//								any of IDs that is not in the array will be
//								received.
//								If any message is reqested then NULL should
//								be supplied.
//				milliseconds	Specifies the time-out interval, in
//								milliseconds.
//								The function returns if the interval elapses,
//								even if no messages are received.
//								If milliseconds is zero, the function checks
//								if there are any messages and returns
//								immediately.
//								If milliseconds is INFINITE, the function
//								does not return until a message is received.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//				If the operation failed because of that the time-out interval
//				expired then GetLastError will return ERROR_TIMEOUT.
//
******************************************************************************/

BOOL __stdcall CanReceive(CanHandle hInterface,
						  CanMsg *pCanMsg,
						  LPDWORD pDataLength,
						  CanMsgId *pCanMsgSel,
						  CanFrameType frameTypeSel,
						  CanFrameType *pFrameType,
						  DWORD milliseconds
						  )
{

	static sReceive_PT sReceive_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sReceive_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sReceive_P = (sReceive_PT)GetProcAddress(SimCANDll, sReceive_Name);   

		if (sReceive_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanReceive!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sReceive_P(hInterface,pCanMsg,pDataLength,pCanMsgSel,frameTypeSel,pFrameType,milliseconds);

}


/******************************************************************************
//
// FUNCTION:	CanAddRemoteReply
//
// DESCRIPTION:	Adds a reply to a received remote frame.
//
// PARAMETERS:	hInterface	A handle to the opened interface.
//				pCanMsg		A pointer to the message of the remote frame reply.
//				dataLength	The number of data bytes in the remote frame reply.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//				If the operation failed because the interface was opened with
//				CanOpen and the CAN id of the message is outside the Normal
//				User range then GetLastError will return ERROR_ACCESS_DENIED.
//				If the operation failed because there is no more room for more
//				remote replies then GetLastError will return
//				ERROR_NO_MORE_ITEMS
//
******************************************************************************/
BOOL __stdcall CanAddRemoteReply(
CanHandle hInterface,
CanMsg *pCanMsg,
DWORD dataLength
){
	static sAddRemoteReply_PT sAddRemoteReply_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sAddRemoteReply_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sAddRemoteReply_P = (sAddRemoteReply_PT)GetProcAddress(SimCANDll, sAddRemoteReply_Name);   

		if (sAddRemoteReply_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanAddRemoteReply!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sAddRemoteReply_P(hInterface, pCanMsg,dataLength);

}

/******************************************************************************
//
// FUNCTION:	CanRemoveRemoteReply
//
// DESCRIPTION:	Removes a reply to a received remote frame.
//
// PARAMETERS:	hInterface	A handle to the opened interface.
//				id			The CAN message identifier of the remote frame that
//							the reply is associated with.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//				If the operation failed because the remote frame reply
//				specified by id has never been added, then GetLastError will
//				return ERROR_NOT_FOUND.
//
******************************************************************************/
BOOL __stdcall CanRemoveRemoteReply(
CanHandle hInterface,
CanMsgId id
){

	static sRemoveRemoteReply_PT sRemoveRemoteReply_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sRemoveRemoteReply_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sRemoveRemoteReply_P = (sRemoveRemoteReply_PT)GetProcAddress(SimCANDll, sRemoveRemoteReply_Name);   

		if (sRemoveRemoteReply_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanRemoveRemoteReply!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sRemoveRemoteReply_P(hInterface, id);
}

/******************************************************************************
//
// FUNCTION:	CanEnumRemoteReply
//
// DESCRIPTION:	Enumerates remote frame replies.
//
// PARAMETERS:	hInterface	A handle to the opened interface.
//				index		Specifies the index of the subkey to retrieve.
//							This parameter should be zero for the first call to
//							the CanEnumRemoteReply function and then, as long
//							as ERROR_SUCCESS is returned, incremented for
//							subsequent calls until ERROR_NO_MORE_ITEMS are
//							returned.
//							returned and GetLastError returns . 
//				pCanMsg		A pointer to the returned message of the remote
//							frame reply.
//				pDataLength	A pointer to the returned number of data bytes of
//							data bytes in the remote frame reply.
//							received.
//				pFrameType	A pointer to the returned frame type of the remote
//							frame reply.
//
// RETURNS:		ERROR_SUCCESS or some error code.
//				If operation failed because there are no more remote frame
//				replies then ERROR_NO_MORE_ITEMS is returned.
//
******************************************************************************/
DWORD __stdcall CanEnumRemoteReply(
CanHandle hInterface,
ULONG index,
CanMsg *pCanMsg,
LPDWORD pDataLength,
CanFrameType *pFrameType
){

	static sEnumRemoteReply_PT sEnumRemoteReply_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return ERROR_ACCESS_DENIED;

	if (sEnumRemoteReply_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sEnumRemoteReply_P = (sEnumRemoteReply_PT)GetProcAddress(SimCANDll, sEnumRemoteReply_Name);   

		if (sEnumRemoteReply_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanEnumRemoteReply!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sEnumRemoteReply_P(hInterface, index, pCanMsg,pDataLength, pFrameType);

}

/******************************************************************************
//
// FUNCTION:	CanGetStatistics
//
// DESCRIPTION:	Returns performance and error counters.
//
// PARAMETERS:	hInterface		A handle to the opened interface.
//				pStatistics		A pointer to the performance and error
//								counters.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//
******************************************************************************/
BOOL __stdcall CanGetStatistics(
CanHandle hInterface,
CanStatistics *pStatistics
){
	static sGetStatistics_PT sGetStatistics_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sGetStatistics_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sGetStatistics_P = (sGetStatistics_PT)GetProcAddress(SimCANDll, sGetStatistics_Name);   

		if (sGetStatistics_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanGetStatistics!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sGetStatistics_P(hInterface, pStatistics);
}


BOOL __stdcall CanGetProperties(
CanHandle hInterface,
CanProperties *pProperties
){
	static sGetProperties_PT sGetProperties_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sGetProperties_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sGetProperties_P = (sGetProperties_PT)GetProcAddress(SimCANDll, sGetProperties_Name);   

		if (sGetProperties_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanGetProperties!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sGetProperties_P(hInterface, pProperties);

}

/******************************************************************************
//
// FUNCTION:	CanGetLastTimeStamp
//
// DESCRIPTION:	Returns the timestamp for the last received message.
//
// PARAMETERS:	hInterface		A handle to the opened interface.
//				pTimeStamp		A pointer to the time stamp.
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//
******************************************************************************/
BOOL __stdcall CanGetLastTimeStamp(
CanHandle hInterface,
CanTimeStamp *pTimeStamp
){

	static sGetLastTimeStamp_PT sGetLastTimeStamp_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sGetLastTimeStamp_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sGetLastTimeStamp_P = (sGetLastTimeStamp_PT)GetProcAddress(SimCANDll, sGetLastTimeStamp_Name);   

		if (sGetLastTimeStamp_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanGetLastTimeStamp!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sGetLastTimeStamp_P(hInterface, pTimeStamp);

}

/******************************************************************************
//
// FUNCTION:	CanGetDeviceHandle
//
// DESCRIPTION:	Returns the handle to the CAN device.
//				The handle is intended to be used in DeviceIoControl calls.
//
// PARAMETERS:	hInterface		A handle to the opened interface.
//
// RETURNS:		A handle to the CAN device or INVALID_HANDLE_VALUE if
//				operation failed.
//
******************************************************************************/
HANDLE __stdcall CanGetDeviceHandle(
CanHandle hInterface
){

	static sGetDeviceHandle_PT sGetDeviceHandle_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sGetDeviceHandle_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
				return INVALID_HANDLE_VALUE;
			}
		}

		sGetDeviceHandle_P = (sGetDeviceHandle_PT)GetProcAddress(SimCANDll, sGetDeviceHandle_Name);   

		if (sGetDeviceHandle_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanGetDeviceHandle!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return INVALID_HANDLE_VALUE;
		}
	}

	return sGetDeviceHandle_P(hInterface);

}

/******************************************************************************
//
// FUNCTION:	CanRegisterRmrCallback
//
// DESCRIPTION:	Registers a callback function that is called whenever a remote
//				frame is received. 
//				!!NOTE: This will only work if remote replies are handled by
//				software or if the selected hardware supports remote callback.
//
// PARAMETERS:	pNetName		The CAN net name, CAN1-CANn.
//								Either ANSI or UNICODE string , depending on if
//								_UNICODE and UNICODE is defined or not.
//
//				remoteCallBack	Function pointer to the callback function.
//								The function must be of the SimCanRmr type.
//								
//
// RETURNS:		TRUE if operation succeeded otherwise FALSE.
//				If operation failed then "GetLastError" can be used to get
//				information of the error.
//
******************************************************************************/
BOOL __stdcall CanRegisterRmrCallBack(
CanHandle hInterface,
SimCanRmr remoteCallback
)
{
	static sRegisterRmrCallBack_PT sRegisterRmrCallBack_P = NULL;
	long err=ERROR_SUCCESS;	

	if(!isInitiated)
		return FALSE;

	if (sRegisterRmrCallBack_P == NULL)
	{
		if (SimCANDll == NULL)
		{
			SimCANDll = LoadLibrary(SimCANDllNameC);
			if (SimCANDll == NULL)
			{
				err = GetLastError();
				MessageBox(NULL, TEXT("Failed to load SimCan.dll!"), TEXT("SimCan"), MB_OK);
				SetLastError(err);
        return(FALSE);
			}
		}

		sRegisterRmrCallBack_P = (sRegisterRmrCallBack_PT)GetProcAddress(SimCANDll, sRegisterRmrCallBack_Name);   

		if (sRegisterRmrCallBack_P == NULL)
		{
			err = GetLastError();
			MessageBox(NULL, TEXT("Failed to retrieve address of SimCanRegisterRmrCallBack!"), TEXT("SimCan"), MB_OK);
			SetLastError(err);
			return(FALSE);
		}
	}

	return sRegisterRmrCallBack_P(hInterface, remoteCallback);

}