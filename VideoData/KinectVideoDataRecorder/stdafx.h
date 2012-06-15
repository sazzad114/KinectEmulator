/************************************************************************
*                                                                       *
*   stdafx.h -- include file for standard system and project includes   *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
* This code is licensed under the terms of the                          *
* Microsoft Kinect for Windows SDK (Beta) from Microsoft Research       *
* License Agreement: http://research.microsoft.com/KinectSDK-ToU        *
*                                                                       *
************************************************************************/

#pragma once
#include<afxcoll.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <ole2.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

extern TCHAR g_szAppTitle[];

#pragma comment (lib, "d3d9.lib")
#pragma comment ( lib, "winmm.lib" )

//#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
//#include <afxdisp.h>        // MFC Automation classes
//#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
//#endif // _AFX_NO_AFXCMN_SUPPORT

