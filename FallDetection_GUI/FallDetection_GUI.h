
// FallDetection_GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFallDetection_GUIApp:
// See FallDetection_GUI.cpp for the implementation of this class
//

class CFallDetection_GUIApp : public CWinApp
{
public:
	CFallDetection_GUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFallDetection_GUIApp theApp;