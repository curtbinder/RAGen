// RAGen.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenPropSheet.h"

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
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
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

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	SetRegistryKey(_T("Curt Binder"));

	// TODO process any command line arguments here and update settings appropriately

	CRAGenPropSheet dlg(_T("ReefAngel Generator"));
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
