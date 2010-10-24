// RAGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenDlg.h"
#include "AboutDlg.h"
#include "SettingsDlg.h"
#include "shlwapi.h"
#include "GlobalVars.h"

// RAGenDlg dialog

IMPLEMENT_DYNAMIC(RAGenDlg, CDialog)

RAGenDlg::RAGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RAGenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
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
	SetDlgItemText(IDC_TEXT_STATUS, s);
}

void RAGenDlg::ClearStatus()
{
	SetStatus(_T(""));
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

	CString sEnable;
	sEnable.LoadStringA(IDS_ENABLE_ADVANCED);
	if ( m_Tabs.IsMemoryTab() )
	{
		// insert Enable Menu right above the Reset Menu
		if ( pos == -1 )
		{
			pos = pMenu->GetMenuItemCount() - 1;
		}
		pMenu->InsertMenu(pos, MF_BYPOSITION|MF_STRING, ID_EDIT_ENABLE_ADVANCED, sEnable);
	}
	else
	{
		// delete Enable or Disable Menu
		CString sDisable;
		sDisable.LoadStringA(IDS_DISABLE_ADVANCED);
		pos = FindMenuItem(pMenu, sEnable);
		if ( pos >= 0 )
		{
			pMenu->DeleteMenu(pos, MF_BYPOSITION);
		}
		pos = FindMenuItem(pMenu, sDisable);
		if ( pos >= 0 )
		{
			pMenu->DeleteMenu(pos, MF_BYPOSITION);
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

BOOL RAGenDlg::GetSketchFolder()
{
	BOOL bRet = FALSE;
	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, MAX_PATH, m_sSketchDirectory);
	PathAppend(szPath, _T("Arduino\\preferences.txt"));
	// try to open file
	// search for 'sketchbook.path='
	TRY
	{
		CFile f;
		CFileException fe;
		if ( ! f.Open(szPath, CFile::modeRead, &fe) )
		{
			AfxThrowFileException(fe.m_cause, fe.m_lOsError, fe.m_strFileName);
		}
		// file open, so let's read in and look for sketchbook.path=
		TCHAR buf[MAX_PATH];
		DWORD dwRead;
		TCHAR *p;
		do
		{
			dwRead = f.Read(buf, MAX_PATH);
			p = _tcsstr(buf, _T("sketchbook.path="));
			if ( p != NULL && dwRead > 0)
			{
				int x = (int)strlen(_T("sketchbook.path="));
				TCHAR szD[MAX_PATH];
				TCHAR *q;
				q = _tcsstr(p, "\r\n");
				int s = (int)(q-(p+x));
				_tcsncpy_s(szD, MAX_PATH, p+x, s);
				TRACE("PATH=%s\n", szD);
				_tcscpy_s(m_sSketchDirectory, MAX_PATH, szD);
				bRet = TRUE;
			}
		} while ( dwRead > 0 );

		f.Close();
	}
	CATCH_ALL(e)
	{
		bRet = FALSE;
	}
	END_CATCH_ALL

	return bRet;
}

BOOL RAGenDlg::GetArduinoFolder(LPCTSTR sDir)
{
	BOOL bRet;
	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, MAX_PATH, m_sSketchDirectory);
	PathAppend(szPath, sDir);
	/*
	PathAppend(szPath, _T("arduino.exe"));

	HANDLE hFile;  
	hFile = CreateFile(szPath,
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL,
					   NULL);
	 
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		bRet = FALSE;
	}
	else
	{
		bRet = TRUE;
	}
	*/
	if ( SetCurrentDirectory(szPath) )
	{
		// now let's return to our previous directory
		SetCurrentDirectory(m_sCurrentDirectory);
		PathAppend(m_sSketchDirectory, sDir);
		bRet = TRUE;
	}
	else
	{
		// failed to change directory, not the right directory
		bRet = FALSE;
	}

	return bRet;
}

void RAGenDlg::GetFolders()
{
	BOOL bUseCurrentDirectory = TRUE;
	CString s;
	DWORD dwD = sizeof(m_sCurrentDirectory)/sizeof(TCHAR);
	GetCurrentDirectory(dwD, m_sCurrentDirectory);

	s = AfxGetApp()->GetProfileString(_T(""), _T("OutputDirectory"), _T(""));
	if ( s.IsEmpty() )
	{
		_tcscpy_s(m_sOutputDirectory, MAX_PATH, m_sCurrentDirectory);
	}
	else
	{
		_stprintf_s(m_sOutputDirectory, MAX_PATH, _T("%s"), s);
	}

	s = AfxGetApp()->GetProfileString(_T(""), _T("SketchDirectory"), _T(""));
	if ( s.IsEmpty() )
	{
		// No folder is in the registry, so let's look it up
		if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, m_sSketchDirectory)) )
		{
			// Got directory, search for sketch folder location
			if ( GetSketchFolder() )
			{
				// Found sketch folder
				bUseCurrentDirectory = FALSE;
			}
		}
	}
	else
	{
		_stprintf_s(m_sSketchDirectory, MAX_PATH, _T("%s"), s);
		bUseCurrentDirectory = FALSE;
	}
	if ( bUseCurrentDirectory )
	{
		_tcscpy_s(m_sSketchDirectory, MAX_PATH, m_sCurrentDirectory);
	}

	bUseCurrentDirectory = TRUE;
	s = AfxGetApp()->GetProfileString(_T(""), _T("ArduinoDirectory"), _T(""));
	if ( s.IsEmpty() )
	{
		// no directory, so locate arduino directory
		// First check PROGRAM_FILES/Reef Angel Controller
		if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, m_sArduinoDirectory)) )
		{
			if ( GetArduinoFolder(_T("Reef Angel Controller")) )
			{
				bUseCurrentDirectory = FALSE;
			}
		}

		if ( bUseCurrentDirectory )
		{
			// Check My Documents/Arduino folder
			if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, m_sArduinoDirectory)) )
			{
				if ( GetArduinoFolder(_T("Arduino")) )
				{
					bUseCurrentDirectory = FALSE;
				}
			}
		}
	}
	else
	{
		_stprintf_s(m_sArduinoDirectory, MAX_PATH, _T("%s"), s);
		bUseCurrentDirectory = FALSE;
	}
	if ( bUseCurrentDirectory )
	{
		_tcscpy_s(m_sArduinoDirectory, MAX_PATH, m_sCurrentDirectory);
	}
}

void RAGenDlg::UpdateSettings()
{
	// copy the values over
	m_Tabs.iSaveReg = iSaveReg;
	_tcscpy_s(m_Tabs.m_sOutputDirectory, MAX_PATH, m_sOutputDirectory);
	_tcscpy_s(m_Tabs.m_sCurrentDirectory, MAX_PATH, m_sCurrentDirectory);
	_tcscpy_s(m_Tabs.m_sSketchDirectory, MAX_PATH, m_sSketchDirectory);
	_tcscpy_s(m_Tabs.m_sArduinoDirectory, MAX_PATH, m_sArduinoDirectory);
	m_Tabs.UpdateSettingsForTabs();
}

BEGIN_MESSAGE_MAP(RAGenDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EDIT_SETTINGS, &RAGenDlg::OnEditSettings)
	ON_COMMAND(ID_EDIT_ENABLE_ADVANCED, &RAGenDlg::OnEditEnableAdvanced)
	ON_COMMAND(ID_FILE_EXIT, &RAGenDlg::OnFileExit)
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
END_MESSAGE_MAP()


// RAGenDlg message handlers

BOOL RAGenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetFolders();

	// initialize the tabs first
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
	dlg.m_iSaveRegistry = iSaveReg;
	dlg.m_sSketchFolder = m_sSketchDirectory;
	dlg.m_sArduinoFolder = m_sArduinoDirectory;
	INT_PTR iRet = dlg.DoModal();
	if ( iRet == IDOK )
	{
		// if OK is pressed, we need to update the settings
		iSaveReg = dlg.m_iSaveRegistry;
		_stprintf_s(m_sSketchDirectory, MAX_PATH, _T("%s"), dlg.m_sSketchFolder);
		_stprintf_s(m_sArduinoDirectory, MAX_PATH, _T("%s"), dlg.m_sArduinoFolder);
		// Save these values to the registry only if:
		//    Always save or Prompt to save are selected, otherwise leave alone
		if ( (iSaveReg == ALWAYS_SAVE) || (iSaveReg == PROMPT_SAVE) )
		{
			AfxGetApp()->WriteProfileString(_T(""), _T("OutputDirectory"), m_sOutputDirectory);
			AfxGetApp()->WriteProfileString(_T(""), _T("SketchDirectory"), m_sSketchDirectory);
			AfxGetApp()->WriteProfileString(_T(""), _T("ArduinoDirectory"), m_sArduinoDirectory);
			AfxGetApp()->WriteProfileInt(_T(""), _T("RegistrySavePrompt"), iSaveReg);
		}
		UpdateSettings();
		UpdateData(FALSE);
	}
}

void RAGenDlg::OnEditEnableAdvanced()
{
	m_Tabs.EnableAdvanced();
}

void RAGenDlg::OnFileExit()
{
	PostMessage(WM_CLOSE);
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
	if ( id == ID_UPDATE_STATUS )
	{
		if ( lParam == 0 )
		{
			ClearStatus();
			return TRUE;
		}
		CString s;
		CString s1;
		s.LoadStringA((UINT)lParam);
		m_Tabs.GetFilename(s1);
		if ( s1.IsEmpty() )
		{
			SetStatus(s);
		}
		else
		{
			CString s2;
			s2.Format(s, s1);
			SetStatus(s2);
		}
		return TRUE;
	}

	return CDialog::OnCommand(wParam, lParam);
}