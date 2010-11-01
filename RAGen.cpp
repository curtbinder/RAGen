// RAGen.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenDlg.h"
#include "GlobalVars.h"
#include "CmdLineParams.h"

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
	int iLaunch = NOT_SET;
	int iSave = NOT_SET;
	int iAppMode = NOT_SET;
	if ( info.TotalParams() > 0 )
	{
		iSave = info.GetSaveRegMode();
		iAppMode = info.GetAppMode();
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
		iAppMode = GetProfileInt(_T(""), _T("DevelopmentLibraries"), NORMAL_MODE);
	}
	// sanity checks for ranges
	if ( (iAppMode < NORMAL_MODE) || (iAppMode > DEV_MODE) )
	{
		iAppMode = NORMAL_MODE;
	}

	RAGenDlg dlg;
	m_pMainWnd = &dlg;

	// Set the modes and other stuff here before we show the window
	dlg.SetLaunchArduino(iLaunch);
	dlg.SetSaveRegistry(iSave);
	dlg.SetAppMode(iAppMode);
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
