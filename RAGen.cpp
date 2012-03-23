// RAGen.cpp : Defines the class behaviors for the application.
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenDlg.h"
#include "GlobalVars.h"
#include "CmdLineParams.h"
#include "Controller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRAGenApp

BEGIN_MESSAGE_MAP(CRAGenApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRAGenApp construction

CRAGenApp::CRAGenApp()
{
}


// The one and only CRAGenApp object

CRAGenApp theApp;


// CRAGenApp initialization

BOOL CRAGenApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Change the registry key under which our settings are stored
#ifdef REEFANGEL_REG
	SetRegistryKey(_T("Reef Angel"));
#else
	SetRegistryKey(_T("Curt Binder"));
#endif  // REEFANGEL_REG

	// TODO process any command line arguments here and update settings appropriately
	CmdLineParams info;
	ParseCommandLine(info);
	iLaunch = NOT_SET;
	iSave = NOT_SET;
	iAppMode = NOT_SET;

	if ( info.TotalParams() > 0 )
	{
		iSave = info.GetSaveRegMode();
		iAppMode = info.GetAppMode();
		a_Controller.SetDevLibVersion(info.GetDevVersionMode());
	}

	if ( iSave == NOT_SET )
	{
		// get the registry prompt setting only if it's not been set from commandline
		iSave = GetProfileInt(_T(""), _T("RegistrySavePrompt"), PROMPT);
	}
	// sanity checks for ranges
	if ( (iSave > NEVER) || (iSave < ALWAYS) )
	{
		iSave = PROMPT;
	}

	if ( iLaunch == NOT_SET )
	{
		iLaunch = GetProfileInt(_T(""), _T("LaunchArduino"), PROMPT);
	}
	if ( (iLaunch > NEVER) || (iLaunch < ALWAYS) )
	{
		iLaunch = PROMPT;
	}

	if ( iAppMode == NOT_SET )
	{
		iAppMode = GetProfileInt(_T(""), _T("DevelopmentLibraries"), DEV_MODE);
	}
	// sanity checks for ranges
	if ( (iAppMode < NORMAL_MODE) || (iAppMode > DEV_MODE) )
	{
		iAppMode = NORMAL_MODE;
	}

	if ( a_Controller.GetDevLibVersion() == NOT_SET )
	{
		a_Controller.SetDevLibVersion(GetProfileInt(_T(""), _T("DevLibraryVersion"), AUTODETECT));
	}
	if ( (a_Controller.GetDevLibVersion() < AUTODETECT) || (a_Controller.GetDevLibVersion() > FORCE_09X) )
	{
		a_Controller.SetDevLibVersion(AUTODETECT);
	}

	RAGenDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
