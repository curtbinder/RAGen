// RAGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenDlg.h"
#include "AboutDlg.h"
#include "shlwapi.h"

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

void RAGenDlg::ChangeMenuA(UINT menuID)
{
	// Checks if the Reset Menu is in the list, if so, delete it and add on our reset menu
	CMenu Reset;
	Reset.LoadMenuA(menuID);
	int pos = -1;
	CMenu *pMenu = GetMenu()->GetSubMenu(1);
	int count = pMenu->GetMenuItemCount();
	if ( count != -1 )
	{
		CString s;
		for ( int i = 0; i < count; i++ )
		{
			pMenu->GetMenuString(i, s, MF_BYPOSITION);
			if ( s.CompareNoCase(_T("&Reset")) == 0 )
			{
				// found it, so delete it
				pMenu->DeleteMenu(i, MF_BYPOSITION);
				pos = i;
				break;
			}
		}
	}

	if ( pos >= 0 )
	{
		pMenu->InsertMenuA(pos+1, MF_POPUP, (UINT_PTR)Reset.GetSubMenu(0)->m_hMenu, _T("&Reset"));
	}
	else
	{
		pMenu->AppendMenuA(MF_POPUP, (UINT_PTR)Reset.GetSubMenu(0)->m_hMenu, _T("&Reset"));
	}
}

BOOL RAGenDlg::GetSketchFolder()
{
	BOOL bRet = FALSE;
	TCHAR szPath[MAX_PATH];
	_tcscpy_s(szPath, MAX_PATH, m_sOutputDirectory);
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
				_tcscpy_s(m_sOutputDirectory, MAX_PATH, szD);
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

void RAGenDlg::GetOutputFolder()
{
	BOOL bUseCurrentDirectory = FALSE;
	BOOL bUseRegistryFolder = TRUE;
	CString s = AfxGetApp()->GetProfileString(_T(""), _T("OutputDirectory"), _T(""));
	if ( s.IsEmpty() )
	{
		bUseRegistryFolder = FALSE;
	}
	else
	{
		_stprintf_s(m_sOutputDirectory, MAX_PATH, _T("%s"), s);
	}

	if ( ! bUseRegistryFolder )
	{
		// No folder is in the registry, so let's look it up
		if ( SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, m_sOutputDirectory)) )
		{
			// Got local directory, now let's look for arduino
			if ( ! GetSketchFolder() )
			{
				// failed to get sketch folder, so use current directory
				bUseCurrentDirectory = TRUE;
			} // else directory is set in GetSketchFolder
		}
		else
		{
			bUseCurrentDirectory = TRUE;
		}

		if ( bUseCurrentDirectory )
		{
			// Failed to locate and retrieve Sketchbook Folder, so use current directory
			DWORD dwD = sizeof(m_sOutputDirectory)/sizeof(TCHAR);
			GetCurrentDirectory(dwD, m_sOutputDirectory);
		}
	}
}

void RAGenDlg::UpdateSettings()
{
	// copy the values over
	m_Tabs.iSaveReg = iSaveReg;
	_tcscpy_s(m_Tabs.m_sOutputDirectory, MAX_PATH, m_sOutputDirectory);
	m_Tabs.UpdateSettingsForTabs();
}

BEGIN_MESSAGE_MAP(RAGenDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EDIT_SETTINGS, &RAGenDlg::OnEditSettings)
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

	GetOutputFolder();
	// locate arduino folder
	// get the registry prompt setting
	iSaveReg = AfxGetApp()->GetProfileIntA(_T(""), _T("RegistrySavePrompt"), 1);

	// copy the values over
	UpdateSettings();

	m_Tabs.Init();

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
//	CSettingsDlg dlgSettings;
//	dlgSettings.m_iSaveRegistry = iSaveReg;
//	dlgSettings.m_sSketchFolder = m_sOutputDirectory;
//	INT_PTR iRet = dlgSettings.DoModal();
//	if ( iRet == IDOK )
//	{
//		// if OK is pressed, we need to update the settings
//		iSaveReg = dlgSettings.m_iSaveRegistry;
//		_stprintf_s(m_sOutputDirectory, MAX_PATH, _T("%s"), dlgSettings.m_sSketchFolder);
//		// Save these values to the registry only if:
//		//    Always save or Prompt to save are selected, otherwise leave alone
//		if ( iSaveReg < 2 )
//		{
//			AfxGetApp()->WriteProfileString(_T(""), _T("OutputDirectory"), m_sOutputDirectory);
//			AfxGetApp()->WriteProfileInt(_T(""), _T("RegistrySavePrompt"), iSaveReg);
//		}
//		UpdateSettings();
//		UpdateData(FALSE);
//	}
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