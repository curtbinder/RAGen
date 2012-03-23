// RAGen.h : main header file
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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
	BOOL fHasArduinoExe;
};

extern CRAGenApp theApp;