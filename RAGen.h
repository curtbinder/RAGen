// RAGen.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRAGenApp:
// See RAGen.cpp for the implementation of this class
//

class CRAGenApp : public CWinApp
{
public:
	CRAGenApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	// public variables
	TCHAR m_sSketchDirectory[MAX_PATH];  //!< Sketch directory
	TCHAR m_sArduinoDirectory[MAX_PATH];  //!< Arduino directory
	TCHAR m_sLibraryDirectory[MAX_PATH];  //!< Libraries directory
	TCHAR m_sCurrentDirectory[MAX_PATH];  //!< Current directory
	int iSave;  //!< Variable for saving to registry, 0 - always, 1 - prompt, 2 - never
	int iLaunch;
	int iAppMode;  //!< Application mode, 0 - normal, 1 - development libraries
	int iDevVersion;  //!< 0 - autodetect, 1 - force 0.8.x, 2 - force 0.9.x or later
	BOOL fHasArduinoExe;
	BOOL f09xDev;

	void AutoDetectLibraryVersion();
};

extern CRAGenApp theApp;