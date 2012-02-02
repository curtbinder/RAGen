// RAGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenDlg.h"
#include "AboutDlg.h"
#include "SettingsDlg.h"
#include "shlwapi.h"
#include "GlobalVars.h"
#include "cb_FileOperations.h"
#include "ComPortFunctions.h"
#include "TestComPortsDlg.h"
#include "ComPortListDlg.h"
//#include "WebBannerDlg.h"
#include "WifiPasswordDlg.h"
#include "RAInternalMemoryPage.h"

static UINT auIDStatusBar[] = {
	ID_SEPARATOR,
	IDS_COMPORT
};

// RAGenDlg dialog

IMPLEMENT_DYNAMIC(RAGenDlg, CDialog)

RAGenDlg::RAGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RAGenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	fRestartRequired = FALSE;
	m_iStatusBarSize = sizeof(auIDStatusBar)/sizeof(UINT);
}

RAGenDlg::~RAGenDlg()
{
}

void RAGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tabs);
}

void RAGenDlg::SetStatus(LPCTSTR s)
{
	//SetDlgItemText(IDC_TEXT_STATUS, s);
	m_StatusBar.SetWindowText(s);
}

void RAGenDlg::ClearStatus()
{
	SetStatus(_T(""));
}

void RAGenDlg::SetStatusComPort(int port)
{
	CString s;
	s.Format(IDS_COMPORT, port);
	m_StatusBar.SetPaneText(1, s);
}

void RAGenDlg::ClearStatusComPort()
{
	m_StatusBar.SetPaneText(1, _T(""));
}

void RAGenDlg::ChangeMenu(UINT menuID)
{
	// Changes the Reset menu around appropriately on tab changes
	CMenu Reset;
	Reset.LoadMenuA(menuID);
	CString sReset;
	sReset.LoadStringA(IDS_RESET_MENU);
	CMenu *pMenu = GetMenu()->GetSubMenu(1);
	int pos = FindMenuItem(pMenu, sReset);

	if ( pos >= 0 )
	{
		pMenu->DeleteMenu(pos, MF_BYPOSITION);
		pMenu->InsertMenuA(pos, MF_POPUP, (UINT_PTR)Reset.GetSubMenu(0)->m_hMenu, sReset);
	}
	else
	{
		pMenu->AppendMenuA(MF_POPUP, (UINT_PTR)Reset.GetSubMenu(0)->m_hMenu, sReset);
	}

	if ( m_Tabs.IsStandardTab() )
	{
		// Standard tab, so remove the additional menu entries from Controller Menu
		// Get Controller Menu
		pMenu = GetMenu()->GetSubMenu(2);
		// Delete the last 5 entries
		UINT count = pMenu->GetMenuItemCount();
		for ( int i = 0; i <= 5; i++ )
		{
			pMenu->DeleteMenu(count-i, MF_BYPOSITION);
		}
	}
}

int RAGenDlg::FindMenuItem(CMenu* pMenu, LPCTSTR sMenu)
{
	int pos = -1;
	int count = pMenu->GetMenuItemCount();
	if ( count != -1 )
	{
		CString s;
		for ( int i = 0; i < count; i++ )
		{
			pMenu->GetMenuString(i, s, MF_BYPOSITION);
			if ( s.CompareNoCase(sMenu) == 0 )
			{
				// found it
				pos = i;
				break;
			}
		}
	}
	return pos;
}

void RAGenDlg::GetFolders()
{
	/*
	Sketchbook - Documents\Arduino
	Libraries - Documents\Arduino\libraries
	Arduino (for the executable) - Program Files\Reef Angel Controller
	If any of those folders do not exist, RAGen will automatically create them 
	*/

	/*
	TODO check on the install paths
Last installer I was not making the x86 vs x64 check and the installer was installing everything under Program Files/Reef Angel Controller.
This new installer is doing the check and will place the files in the appropriate folder.
So, for x86 it places on Program Files/Reef Angel Controller and for x64 it places on Program Files (x86)/Reef Angel Controller.
I'm pretty sure you can use these to get it to give you the right path.
Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86));
Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments));
	*/
	// Set Arduino folder
	if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, theApp.m_sArduinoDirectory)) )
	{
		PathAppend(theApp.m_sArduinoDirectory, _T("Reef Angel Controller"));
		if ( ! cb_IsDirectory(theApp.m_sArduinoDirectory) )
		{
			// Directory doesn't exist, so we need to create it
			if ( ! CreateDirectory(theApp.m_sArduinoDirectory, NULL) )
			{
				CString msg;
				msg.Format(_T("Error creating directory:\n\n%s\n\nSome functionality may not work."), theApp.m_sArduinoDirectory);
				AfxMessageBox(msg);
			}
		}
	}

	// Set Sketchbook folder
	if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, theApp.m_sSketchDirectory)) )
	{
		PathAppend(theApp.m_sSketchDirectory, _T("Arduino"));
		if ( ! cb_IsDirectory(theApp.m_sSketchDirectory) )
		{
			if ( ! CreateDirectory(theApp.m_sSketchDirectory, NULL) )
			{
				CString msg;
				msg.Format(_T("Error creating directory:\n\n%s\n\nSome functionality may not work."), theApp.m_sSketchDirectory);
				AfxMessageBox(msg);
			}
		}
	}

	// Set libraries folder
	_tcscpy_s(theApp.m_sLibraryDirectory, MAX_PATH, theApp.m_sSketchDirectory);
	PathAppend(theApp.m_sLibraryDirectory, _T("libraries"));
	if ( ! cb_IsDirectory(theApp.m_sLibraryDirectory) )
	{
		if ( ! CreateDirectory(theApp.m_sLibraryDirectory, NULL) )
		{
			CString msg;
			msg.Format(_T("Error creating directory:\n\n%s\n\nSome functionality may not work."), theApp.m_sLibraryDirectory);
			AfxMessageBox(msg);
		}
	}

	TRACE("Arduino:  '%s'\nSketchbook:  '%s'\nLibraries:  '%s'\n", theApp.m_sArduinoDirectory, theApp.m_sSketchDirectory, theApp.m_sLibraryDirectory);

	//s = AfxGetApp()->GetProfileString(_T(""), _T("SketchDirectory"), _T(""));
	//s = AfxGetApp()->GetProfileString(_T(""), _T("ArduinoDirectory"), _T(""));
	//s = AfxGetApp()->GetProfileString(_T(""), _T("LibrariesDirectory"), _T(""));
}

void RAGenDlg::UpdateSettings()
{
	m_Tabs.UpdateSettingsForTabs();
}

void RAGenDlg::UpdateLaunchButtonVisibility(int nCmdShow)
{
	if ( ! theApp.fHasArduinoExe )
	{
		GetDlgItem(IDC_BTN_LAUNCH)->ShowWindow(SW_HIDE);
		return;
	}
	GetDlgItem(IDC_BTN_LAUNCH)->ShowWindow(nCmdShow);
}

void RAGenDlg::CreateStatusBar()
{
	// Create status bar at the bottom of the dialog window
	if ( ! m_StatusBar.Create(this) )
	{
		return;
	}
	
	m_StatusBar.SetIndicators(auIDStatusBar, m_iStatusBarSize);
	ClearStatus();
	m_StatusBar.SetPaneInfo(0, m_StatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	ClearStatusComPort();

	// We need to resize the dialog to make room for control bars.
	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);
	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

BEGIN_MESSAGE_MAP(RAGenDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_EDIT_SETTINGS, &RAGenDlg::OnEditSettings)
	ON_COMMAND(ID_FILE_EXIT, &RAGenDlg::OnFileExit)
	ON_COMMAND(ID_FILE_RESTART, &RAGenDlg::OnFileRestart)
	ON_COMMAND(ID_CONTROLLER_FIND, &RAGenDlg::OnControllerFind)
	ON_COMMAND(ID_CONTROLLER_WEBBANNER, &RAGenDlg::OnControllerWebBanner)
	ON_COMMAND(ID_CONTROLLER_WIFIPASSWORD, &RAGenDlg::OnControllerPasswordProtectWifi)
	ON_COMMAND(ID_CONTROLLER_IMPORTFEATURESFROMFILE, &RAGenDlg::OnControllerImportFeatures)
	ON_COMMAND(ID_CONTROLLER_SHOWUNKNOWNFEATURES, &RAGenDlg::OnControllerShowUnknownFeatures)
	ON_COMMAND(ID_CONTROLLER_SHOWLIBRARYVERSION, &RAGenDlg::OnControllerShowLibraryVersion)
	ON_COMMAND(ID_CONTROLLER_INTERNALMEMORY, &RAGenDlg::OnControllerInternalMemory)
	ON_COMMAND(ID_HELP_ABOUT, &RAGenDlg::OnHelpAbout)
	ON_COMMAND(ID_RESET_ALL, &RAGenDlg::OnResetAll)
	ON_COMMAND(ID_RESET_SAVED, &RAGenDlg::OnResetSaved)
	ON_COMMAND(ID_RESET_PORTS, &RAGenDlg::OnResetPorts)
	ON_COMMAND(ID_RESET_TEMPERATURE, &RAGenDlg::OnResetTemp)
	ON_COMMAND(ID_RESET_LOGGING, &RAGenDlg::OnResetLogging)
	ON_COMMAND(ID_RESET_FEEDINGMODE, &RAGenDlg::OnResetFeedingMode)
	ON_COMMAND(ID_RESET_WATERCHANGEMODE, &RAGenDlg::OnResetWaterChangeMode)
	ON_COMMAND(ID_RESET_OVERHEAT, &RAGenDlg::OnResetOverheat)
	ON_COMMAND(ID_RESET_LIGHTSON, &RAGenDlg::OnResetLightsOn)
	ON_BN_CLICKED(IDC_BTN_GENERATE, &RAGenDlg::OnBnClickedBtnGenerate)
	ON_BN_CLICKED(IDC_BTN_LAUNCH, &RAGenDlg::OnBnClickedBtnLaunch)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &RAGenDlg::OnBnClickedClose)
END_MESSAGE_MAP()


// RAGenDlg message handlers

BOOL RAGenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CreateStatusBar();
	GetFolders();
	if ( cb_DoesArduinoExist(theApp.m_sArduinoDirectory) )
	{
		theApp.fHasArduinoExe = TRUE;
	}
	else
	{
		theApp.fHasArduinoExe = FALSE;
	}
	UpdateLaunchButtonVisibility(SW_HIDE);

	// set Development Libraries mode 
	if ( theApp.iAppMode == DEV_MODE )
	{
		m_Tabs.SetDeveloperMode();
	}

	// initialize the tabs
	m_Tabs.Init();

	// copy the values over
	UpdateSettings();

	return TRUE;
}

void RAGenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR RAGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void RAGenDlg::OnEditSettings()
{
	SettingsDlg dlg;
	dlg.m_iSaveRegistry = theApp.iSave;
	dlg.m_iLaunchArduino = theApp.iLaunch;
	dlg.m_iAppMode = theApp.iAppMode;
	dlg.m_iDevVersion = theApp.iDevVersion;
	dlg.m_fHasArduinoExe = theApp.fHasArduinoExe;
	dlg.m_sArduinoFolder = theApp.m_sArduinoDirectory;
	INT_PTR iRet = dlg.DoModal();
	if ( iRet == IDOK )
	{
		// if OK is pressed, we need to update the settings
		// update settings if needed
		if ( theApp.iSave != dlg.m_iSaveRegistry )
		{
			theApp.iSave = dlg.m_iSaveRegistry;
			AfxGetApp()->WriteProfileInt(_T(""), _T("RegistrySavePrompt"), theApp.iSave);
		}
		if ( theApp.iLaunch != dlg.m_iLaunchArduino )
		{
			theApp.iLaunch = dlg.m_iLaunchArduino;
			AfxGetApp()->WriteProfileInt(_T(""), _T("LaunchArduino"), theApp.iLaunch);
		}
		if ( theApp.iAppMode != dlg.m_iAppMode )
		{
			// update application mode if it's changed
			theApp.iAppMode = dlg.m_iAppMode;
			AfxGetApp()->WriteProfileInt(_T(""), _T("DevelopmentLibraries"), theApp.iAppMode);
			fRestartRequired = TRUE;
		}
		if ( theApp.iDevVersion != dlg.m_iDevVersion )
		{
			theApp.iDevVersion = dlg.m_iDevVersion;
			AfxGetApp()->WriteProfileInt(_T(""), _T("DevLibraryVersion"), theApp.iDevVersion);
		}
		theApp.fHasArduinoExe = dlg.m_fHasArduinoExe;

		theApp.AutoDetectLibraryVersion();

		UpdateSettings();
		UpdateData(FALSE);

		if ( fRestartRequired )
		{
			/*
			Prompt to restart the application
			if user cancels the restart, then update the window text
			*/
			CString s;
			int iRet;
			s = _T("A program restart is required to switch library mode.\n\nDo you want to restart now?");
			iRet = AfxMessageBox(s, MB_YESNO);
			if ( iRet == IDYES )
			{
				TRACE("Program restart initiated\n");
				PostMessage(WM_CLOSE);
			}
			else
			{
				// change status text to have - Restart Required
				TRACE("User declined to restart\n");
				AfxMessageBox(_T("The library mode will be switched the next time you run this program."));
				AfxGetApp()->m_pMainWnd->GetWindowText(s);
				s += _T(" - Restart Required to Switch Modes");
				AfxGetApp()->m_pMainWnd->SetWindowText(s);
				// to prevent program from starting back up after they close it
				fRestartRequired = FALSE;
				// insert restart menu item for ability to restart program if desired
				CMenu* pMenu = GetMenu()->GetSubMenu(0);
				pMenu->InsertMenuA(0, MF_BYPOSITION|MF_SEPARATOR);
				pMenu->InsertMenuA(0, MF_BYPOSITION|MF_STRING, ID_FILE_RESTART, _T("Res&tart"));
			}
		}
	}
}

void RAGenDlg::OnFileExit()
{
	PostMessage(WM_CLOSE);
}

void RAGenDlg::OnFileRestart()
{
	fRestartRequired = TRUE;
	PostMessage(WM_CLOSE);
}

void RAGenDlg::OnControllerFind()
{
	/*
	Searches for the controllers
	displays window while searching
	use custom struct for array (int, bool)
	display dialog box with list of available ports with whether or not controller was found
	defaults to first ra controller as primary/main controller
	sets the com port to the status bar
	*/
	Port* ports = NULL;
    int count = CountPorts();
	if ( count <= 0 )
	{
		AfxMessageBox(_T("No COM ports on this computer"));
		ClearStatusComPort();
		return;
	}
    ports = new Port[count];
	TRY
	{
		if ( ! FillPortsArray(ports) )
		{
			AfxMessageBox(_T("Error getting list of COM ports"));
			AfxThrowUserException();
		}
		TestComPortsDlg td;
		td.m_Ports = ports;
		td.m_iCount = count;
		if ( td.DoModal() == IDCANCEL )
		{
			// user cancelled so let's break out and return
			AfxThrowUserException();
		}
		// now we have a list of the ports
		int iFirstRA = 0;
		for ( int i = 0; i < count; i++ )
		{
			TRACE("%d - COM%d - %s\n", i, ports[i].iPort, (ports[i].fHasRA)?"ReefAngel":"None");
			if ( ports[i].fHasRA && (iFirstRA == 0) )
			{
				iFirstRA = ports[i].iPort;
			}
		}
		if ( iFirstRA > 0 )
		{
			SetStatusComPort(iFirstRA);
		}

		ComPortListDlg cp;
		cp.m_Ports = ports;
		cp.m_iCount = count;
		cp.DoModal();
	}
	CATCH_ALL(e)
	{
	}
	END_CATCH_ALL

	if ( ports )
	{
		delete [] ports;
	}
	ports = NULL;
	return;
}

void RAGenDlg::OnControllerWebBanner()
{
	// TODO web banner goes away, ONLY portal
	AfxMessageBox(_T("Portal configuration window goes here"));
}

void RAGenDlg::OnControllerPasswordProtectWifi()
{
	WifiPasswordDlg dlg;
	dlg.DoModal();
}

void RAGenDlg::OnControllerImportFeatures()
{
	// prompt to import features file
	CFileDialog dlg(TRUE, _T("*.h"), _T("ReefAngel_Features"));
	dlg.m_ofn.lpstrFilter = _T("Feature Files\0*.h\0\0");
	dlg.m_ofn.lpstrTitle = _T("Select Features file to import");
	if ( dlg.DoModal() == IDCANCEL )
	{
		// user cancelled
		return;
	}
	// process the file
	CString file;
	file = dlg.GetPathName();
	TRACE("OF:  '%s'\n", file);
	m_Tabs.ImportFeatures(dlg.GetPathName());
}

void RAGenDlg::OnControllerShowUnknownFeatures()
{
	m_Tabs.ShowUnknownFeatures();
}

void RAGenDlg::OnControllerShowLibraryVersion()
{
	CString version = ReadLibraryVersion(theApp.m_sLibraryDirectory);
	CString msg;
	msg.Format(_T("Installed library version information:\n\n\
Folder:  %s\n\n\
Version:  %s"), theApp.m_sLibraryDirectory, version);
	AfxMessageBox(msg, MB_ICONINFORMATION|MB_OK);
}

void RAGenDlg::OnControllerInternalMemory()
{
	RAInternalMemoryPage dlg;
	dlg.DoModal();
}

void RAGenDlg::OnHelpAbout()
{
	AboutDlg dlg;
	dlg.DoModal();
}

void RAGenDlg::OnBnClickedBtnGenerate()
{
	// Process the Generate Button Press
	m_Tabs.Generate();
	m_Tabs.CheckLaunch();
}

void RAGenDlg::OnBnClickedBtnLaunch()
{
	// Process the Launch Button Press
	m_Tabs.CheckLaunch(TRUE);
}

void RAGenDlg::OnResetAll()
{
	m_Tabs.ResetAll();
}

void RAGenDlg::OnResetSaved()
{
	m_Tabs.ResetSaved();
}

void RAGenDlg::OnResetPorts()
{
	m_Tabs.ResetPorts();
}

void RAGenDlg::OnResetTemp()
{
	m_Tabs.ResetTemp();
}

void RAGenDlg::OnResetLogging()
{
	m_Tabs.ResetLogging();
}

void RAGenDlg::OnResetFeedingMode()
{
	m_Tabs.ResetFeedingMode();
}

void RAGenDlg::OnResetWaterChangeMode()
{
	m_Tabs.ResetWaterChangeMode();
}

void RAGenDlg::OnResetOverheat()
{
	m_Tabs.ResetOverheat();
}

void RAGenDlg::OnResetLightsOn()
{
	m_Tabs.ResetLightsOn();
}

BOOL RAGenDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UINT id = LOWORD(wParam);
	if ( id == ID_CHANGE_MENU )
	{
		ChangeMenu((UINT)lParam);
		return TRUE;
	}
	if ( id == ID_SAVE_FEATURES )
	{
		m_Tabs.SaveFeatures();
		return TRUE;
	}
	if ( id == ID_UPDATE_STATUS )
	{
		if ( lParam == 0 )
		{
			// hide Launch Button
			UpdateLaunchButtonVisibility(SW_HIDE);
			ClearStatus();
			return TRUE;
		}
		CString s;
		CString s1;
		s.LoadStringA((UINT)lParam);
		m_Tabs.GetFilename(s1);
		if ( s1.IsEmpty() )
		{
			TRACE("Command: s1 EMPTY\n");
			// hide Launch Button
			UpdateLaunchButtonVisibility(SW_HIDE);
			SetStatus(s);
		}
		else
		{
			TRACE("Command: s1 has something\n");
			CString s2;
			CString ext;
			m_Tabs.GetFileExtension(ext);
			s2.Format(s, s1, ext);
			SetStatus(s2);
			// show Launch Button
			UpdateLaunchButtonVisibility(SW_SHOW);
		}
		return TRUE;
	}

	return CDialog::OnCommand(wParam, lParam);
}

void RAGenDlg::OnClose()
{
	if ( fRestartRequired )
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		TCHAR sApp[32768];

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		_stprintf_s(sApp, 32768, _T("%s.exe"), theApp.m_pszExeName);

		if ( ! CreateProcess(NULL, sApp, NULL, NULL, FALSE,
							0, NULL, NULL,
							&si, &pi) )
		{
			TRACE("Failed to restart\n");

			AfxMessageBox(_T("Failed to restart"), MB_ICONINFORMATION|MB_OK);
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	CDialog::OnClose();
}

void RAGenDlg::OnBnClickedClose()
{
	PostMessage(WM_CLOSE);
}
