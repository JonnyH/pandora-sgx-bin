/**********************************************************************
 *
 * Copyright(c) 2008 Imagination Technologies Ltd. All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope it will be useful but, except 
 * as otherwise stated in writing, without any warranty; without even the 
 * implied warranty of merchantability or fitness for a particular purpose. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * Imagination Technologies Ltd. <gpl-support@imgtec.com>
 * Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK 
 *
 ******************************************************************************/

#ifndef _DBGDRVIF_
#define _DBGDRVIF_

#include "ioctldef.h"

#define DEBUG_CAPMODE_FRAMED			0x00000001
#define DEBUG_CAPMODE_CONTINUOUS		0x00000002
#define DEBUG_CAPMODE_HOTKEY			0x00000004

#define DEBUG_OUTMODE_STANDARDDBG		0x00000001
#define DEBUG_OUTMODE_MONO				0x00000002
#define DEBUG_OUTMODE_STREAMENABLE		0x00000004
#define DEBUG_OUTMODE_ASYNC				0x00000008
#define DEBUG_OUTMODE_SGXVGA            0x00000010

#define DEBUG_FLAGS_USE_NONPAGED_MEM	0x00000001
#define DEBUG_FLAGS_NO_BUF_EXPANDSION	0x00000002
#define DEBUG_FLAGS_ENABLESAMPLE		0x00000004

#define DEBUG_FLAGS_TEXTSTREAM			0x80000000

#define DEBUG_LEVEL_0					0x00000001
#define DEBUG_LEVEL_1					0x00000003
#define DEBUG_LEVEL_2					0x00000007
#define DEBUG_LEVEL_3					0x0000000F
#define DEBUG_LEVEL_4					0x0000001F
#define DEBUG_LEVEL_5					0x0000003F
#define DEBUG_LEVEL_6					0x0000007F
#define DEBUG_LEVEL_7					0x000000FF
#define DEBUG_LEVEL_8					0x000001FF
#define DEBUG_LEVEL_9					0x000003FF
#define DEBUG_LEVEL_10					0x000007FF
#define DEBUG_LEVEL_11					0x00000FFF

#define DEBUG_LEVEL_SEL0				0x00000001
#define DEBUG_LEVEL_SEL1				0x00000002
#define DEBUG_LEVEL_SEL2				0x00000004
#define DEBUG_LEVEL_SEL3				0x00000008
#define DEBUG_LEVEL_SEL4				0x00000010
#define DEBUG_LEVEL_SEL5				0x00000020
#define DEBUG_LEVEL_SEL6				0x00000040
#define DEBUG_LEVEL_SEL7				0x00000080
#define DEBUG_LEVEL_SEL8				0x00000100
#define DEBUG_LEVEL_SEL9				0x00000200
#define DEBUG_LEVEL_SEL10				0x00000400
#define DEBUG_LEVEL_SEL11				0x00000800

#define DEBUG_SERVICE_IOCTL_BASE		0x800
#define DEBUG_SERVICE_CREATESTREAM		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x01, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_DESTROYSTREAM		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x02, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_GETSTREAM			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x03, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_WRITESTRING		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x04, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_READSTRING		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x05, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_WRITE				CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x06, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_READ				CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x07, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_SETDEBUGMODE		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x08, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_SETDEBUGOUTMODE	CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x09, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_SETDEBUGLEVEL		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x0A, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_SETFRAME			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x0B, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_GETFRAME			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x0C, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_OVERRIDEMODE		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x0D, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_DEFAULTMODE		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x0E, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_GETSERVICETABLE	CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x0F, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_WRITE2			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x10, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_WRITESTRINGCM		CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x11, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_WRITECM			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x12, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_SETMARKER			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x13, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_GETMARKER			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x14, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_ISCAPTUREFRAME	CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x15, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_WRITELF			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x16, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define DEBUG_SERVICE_READLF			CTL_CODE(FILE_DEVICE_UNKNOWN, DEBUG_SERVICE_IOCTL_BASE + 0x17, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _DBG_IN_CREATESTREAM_ {
	IMG_UINT32 ui32Pages;
	IMG_UINT32 ui32CapMode;
	IMG_UINT32 ui32OutMode;
	IMG_CHAR *pszName;
} DBG_IN_CREATESTREAM, *PDBG_IN_CREATESTREAM;

typedef struct _DBG_IN_FINDSTREAM_ {
	IMG_BOOL bResetStream;
	IMG_CHAR *pszName;
} DBG_IN_FINDSTREAM, *PDBG_IN_FINDSTREAM;

typedef struct _DBG_IN_WRITESTRING_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Level;
	IMG_CHAR *pszString;
} DBG_IN_WRITESTRING, *PDBG_IN_WRITESTRING;

typedef struct _DBG_IN_READSTRING_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32StringLen;
	IMG_CHAR *pszString;
} DBG_IN_READSTRING, *PDBG_IN_READSTRING;

typedef struct _DBG_IN_SETDEBUGMODE_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Mode;
	IMG_UINT32 ui32Start;
	IMG_UINT32 ui32End;
	IMG_UINT32 ui32SampleRate;
} DBG_IN_SETDEBUGMODE, *PDBG_IN_SETDEBUGMODE;

typedef struct _DBG_IN_SETDEBUGOUTMODE_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Mode;
} DBG_IN_SETDEBUGOUTMODE, *PDBG_IN_SETDEBUGOUTMODE;

typedef struct _DBG_IN_SETDEBUGLEVEL_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Level;
} DBG_IN_SETDEBUGLEVEL, *PDBG_IN_SETDEBUGLEVEL;

typedef struct _DBG_IN_SETFRAME_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Frame;
} DBG_IN_SETFRAME, *PDBG_IN_SETFRAME;

typedef struct _DBG_IN_WRITE_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Level;
	IMG_UINT32 ui32TransferSize;
	IMG_UINT8 *pui8InBuffer;
} DBG_IN_WRITE, *PDBG_IN_WRITE;

typedef struct _DBG_IN_READ_ {
	IMG_VOID *pvStream;
	IMG_BOOL bReadInitBuffer;
	IMG_UINT32 ui32OutBufferSize;
	IMG_UINT8 *pui8OutBuffer;
} DBG_IN_READ, *PDBG_IN_READ;

typedef struct _DBG_IN_OVERRIDEMODE_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Mode;
} DBG_IN_OVERRIDEMODE, *PDBG_IN_OVERRIDEMODE;

typedef struct _DBG_IN_ISCAPTUREFRAME_ {
	IMG_VOID *pvStream;
	IMG_BOOL bCheckPreviousFrame;
} DBG_IN_ISCAPTUREFRAME, *PDBG_IN_ISCAPTUREFRAME;

typedef struct _DBG_IN_SETMARKER_ {
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Marker;
} DBG_IN_SETMARKER, *PDBG_IN_SETMARKER;

typedef struct _DBG_IN_WRITE_LF_ {
	IMG_UINT32 ui32Flags;
	IMG_VOID *pvStream;
	IMG_UINT32 ui32Level;
	IMG_UINT32 ui32BufferSize;
	IMG_UINT8 *pui8InBuffer;
} DBG_IN_WRITE_LF, *PDBG_IN_WRITE_LF;

#define WRITELF_FLAGS_RESETBUF		0x00000001

typedef struct _DBG_STREAM_ {
	struct _DBG_STREAM_ *psNext;
	struct _DBG_STREAM_ *psInitStream;
	IMG_BOOL bInitPhaseComplete;
	IMG_UINT32 ui32Flags;
	IMG_UINT32 ui32Base;
	IMG_UINT32 ui32Size;
	IMG_UINT32 ui32RPtr;
	IMG_UINT32 ui32WPtr;
	IMG_UINT32 ui32DataWritten;
	IMG_UINT32 ui32CapMode;
	IMG_UINT32 ui32OutMode;
	IMG_UINT32 ui32DebugLevel;
	IMG_UINT32 ui32DefaultMode;
	IMG_UINT32 ui32Start;
	IMG_UINT32 ui32End;
	IMG_UINT32 ui32Current;
	IMG_UINT32 ui32Access;
	IMG_UINT32 ui32SampleRate;
	IMG_UINT32 ui32Reserved;
	IMG_UINT32 ui32Timeout;
	IMG_UINT32 ui32Marker;
	IMG_CHAR szName[30];
} DBG_STREAM, *PDBG_STREAM;

typedef struct _DBGKM_SERVICE_TABLE_ {
	IMG_UINT32 ui32Size;
	IMG_VOID *(IMG_CALLCONV * pfnCreateStream) (IMG_CHAR * pszName,
						    IMG_UINT32 ui32CapMode,
						    IMG_UINT32 ui32OutMode,
						    IMG_UINT32 ui32Flags,
						    IMG_UINT32 ui32Pages);
	 IMG_VOID(IMG_CALLCONV * pfnDestroyStream) (PDBG_STREAM psStream);
	IMG_VOID *(IMG_CALLCONV * pfnFindStream) (IMG_CHAR * pszName,
						  IMG_BOOL bResetInitBuffer);
	 IMG_UINT32(IMG_CALLCONV * pfnWriteString) (PDBG_STREAM psStream,
						    IMG_CHAR * pszString,
						    IMG_UINT32 ui32Level);
	 IMG_UINT32(IMG_CALLCONV * pfnReadString) (PDBG_STREAM psStream,
						   IMG_CHAR * pszString,
						   IMG_UINT32 ui32Limit);
	 IMG_UINT32(IMG_CALLCONV * pfnWriteBIN) (PDBG_STREAM psStream,
						 IMG_UINT8 * pui8InBuf,
						 IMG_UINT32 ui32InBuffSize,
						 IMG_UINT32 ui32Level);
	 IMG_UINT32(IMG_CALLCONV * pfnReadBIN) (PDBG_STREAM psStream,
						IMG_BOOL bReadInitBuffer,
						IMG_UINT32 ui32OutBufferSize,
						IMG_UINT8 * pui8OutBuf);
	 IMG_VOID(IMG_CALLCONV * pfnSetCaptureMode) (PDBG_STREAM psStream,
						     IMG_UINT32 ui32CapMode,
						     IMG_UINT32 ui32Start,
						     IMG_UINT32 ui32Stop,
						     IMG_UINT32 ui32SampleRate);
	 IMG_VOID(IMG_CALLCONV * pfnSetOutputMode) (PDBG_STREAM psStream,
						    IMG_UINT32 ui32OutMode);
	 IMG_VOID(IMG_CALLCONV * pfnSetDebugLevel) (PDBG_STREAM psStream,
						    IMG_UINT32 ui32DebugLevel);
	 IMG_VOID(IMG_CALLCONV * pfnSetFrame) (PDBG_STREAM psStream,
					       IMG_UINT32 ui32Frame);
	 IMG_UINT32(IMG_CALLCONV * pfnGetFrame) (PDBG_STREAM psStream);
	 IMG_VOID(IMG_CALLCONV * pfnOverrideMode) (PDBG_STREAM psStream,
						   IMG_UINT32 ui32Mode);
	 IMG_VOID(IMG_CALLCONV * pfnDefaultMode) (PDBG_STREAM psStream);
	 IMG_UINT32(IMG_CALLCONV * pfnDBGDrivWrite2) (PDBG_STREAM psStream,
						      IMG_UINT8 * pui8InBuf,
						      IMG_UINT32 ui32InBuffSize,
						      IMG_UINT32 ui32Level);
	 IMG_UINT32(IMG_CALLCONV * pfnWriteStringCM) (PDBG_STREAM psStream,
						      IMG_CHAR * pszString,
						      IMG_UINT32 ui32Level);
	 IMG_UINT32(IMG_CALLCONV * pfnWriteBINCM) (PDBG_STREAM psStream,
						   IMG_UINT8 * pui8InBuf,
						   IMG_UINT32 ui32InBuffSize,
						   IMG_UINT32 ui32Level);
	 IMG_VOID(IMG_CALLCONV * pfnSetMarker) (PDBG_STREAM psStream,
						IMG_UINT32 ui32Marker);
	 IMG_UINT32(IMG_CALLCONV * pfnGetMarker) (PDBG_STREAM psStream);
	 IMG_VOID(IMG_CALLCONV * pfnEndInitPhase) (PDBG_STREAM psStream);
	 IMG_UINT32(IMG_CALLCONV * pfnIsCaptureFrame) (PDBG_STREAM psStream,
						       IMG_BOOL
						       bCheckPreviousFrame);
	 IMG_UINT32(IMG_CALLCONV * pfnWriteLF) (PDBG_STREAM psStream,
						IMG_UINT8 * pui8InBuf,
						IMG_UINT32 ui32InBuffSize,
						IMG_UINT32 ui32Level,
						IMG_UINT32 ui32Flags);
	 IMG_UINT32(IMG_CALLCONV * pfnReadLF) (PDBG_STREAM psStream,
					       IMG_UINT32 ui32OutBuffSize,
					       IMG_UINT8 * pui8OutBuf);
	 IMG_UINT32(IMG_CALLCONV * pfnGetStreamOffset) (PDBG_STREAM psStream);
	 IMG_VOID(IMG_CALLCONV * pfnSetStreamOffset) (PDBG_STREAM psStream,
						      IMG_UINT32
						      ui32StreamOffset);
	 IMG_UINT32(IMG_CALLCONV *
		    pfnIsLastCaptureFrame) (PDBG_STREAM psStream);
} DBGKM_SERVICE_TABLE, *PDBGKM_SERVICE_TABLE;

#endif
