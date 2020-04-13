// file DeviceCommunication_CP2112.h
// 
// purpose:
// to implement communication with CP2112 device
// stand alone thread for communication

// interface

#pragma once

////////////////////////////////////////////////////////////
// includes
////////////////////////////////////////////////////////////
#include "afxwin.h"

#include "SLABCP2112.h"


////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////

#define VID										0
#define PID										0

#define MAX_WAIT_TIME_FOR_READ					50
#define MAX_WAIT_TIME_FOR_WRITE					50
#define MAX_NACK_CASES_FOR_READ					20

#define OP_STATUS_DEVICE_CLOSED					0x20

// Read OP errors
#define ERROR_COMPLETE_WITHOUT_ERRORS			0x00
#define ERROR_DEVICE_FAIL_WHILE_PERFORMING		0x01
#define ERROR_COMPLETE_WITH_ERRORS				0x02
#define ERROR_PROCESS_TIMEOUT					0x03
#define ERROR_ADDRESS_NAKED_THRESHOLD			0x04

#define ERROR_DEVICE_FAIL_WHILE_PERFORMING_REQUEST	0x10
#define ERROR_DEVICE_FAIL_WHILE_PERFORMING_FORCE	0x11
#define ERROR_DEVICE_FAIL_WHILE_PERFORMING_GET_DATA	0x12

#define ERROR_UNKNOWN_ERROR						0xFF


////////////////////////////////////////////////////////////
// typedefs
////////////////////////////////////////////////////////////

struct st_CP2112Conf
{
	BYTE ucDeviceNumber;
	BYTE ucBoardType;		// 0 = unknown, 1 = UniversalReader rev.1, 2 = SFPp TestBoard rev.2
	BYTE direction;			// NOTE: 0 = input, 1 = output
	BYTE mode;				// NOTE: 0 = open-drain, 1 = push-pull
	BYTE function;			// NOTE: 000 = no specFunct, 111 = all Enabled (Clk, Tx, Rx)
};


struct st_CP2112ErrStatus
{
	BOOL bLastOpenStatus;
	BYTE ucLastReportState;
	BYTE ucLastErrorS0;
	BYTE ucLastErrorS1;
};


struct st_CP2112WarnStatus
{
	BOOL bWarnFlag;
	BYTE usBusyCounter;
	BYTE usRetryCounter;
	BYTE usBusyNakedCases;
};


////////////////////////////////////////////////////////////
// externs
////////////////////////////////////////////////////////////

extern HID_SMBUS_DEVICE g_hidSmbus;
extern struct st_CP2112Conf g_stCP2112Conf;


////////////////////////////////////////////////////////////
// prototypes
////////////////////////////////////////////////////////////

// *** single proc perform ***
WORD DeviceCP2112_GetDeviceCount(void);
BYTE DeviceCP2112_GetIDString(WORD usIndex, char* strIDString);
BYTE DeviceCP2112_Open(WORD usIndex);
void DeviceCP2112_SetConfig(void);
BYTE DeviceCP2112_ReadLatch(void);
BYTE DeviceCP2112_ReadIIC_Request(BYTE ucSlaveAddr, WORD usCount);
BYTE DeviceCP2112_ReadIIC_RequestAddr(BYTE ucSlaveAddr, WORD ucByteAddr, WORD usCount);
BYTE DeviceCP2112_ReadIIC_GetData(BYTE* usReceivedCountInfo, BYTE v_buffer[HID_SMBUS_MAX_READ_RESPONSE_SIZE]);

// *** complex proc perform ***
// service
void DeviceCP2112_Reset(void);
BYTE DeviceCP2112_ReadIIC_ForceResponceCheck(WORD usCount);

// read
BYTE DeviceCP2112_ReadIIC_CURRENT_ADDRESS(BYTE ucSlaveAddr);
BYTE DeviceCP2112_ReadIIC_CURRENT_ADDRESS_SEQUENTIAL(BYTE ucSlaveAddr, WORD usCount);

// service
void DeviceCP2112_OpenStatusUpdate();
BOOL DeviceCP2112_GetUpdateOpenState();
BOOL DeviceCP2112_GetLastOpenState();