// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SettingsDlg.h"
#include "cb_BrowseFolder.h"
#include "cb_FileOperations.h"
#include "shlwapi.h"

// SettingsDlg dialog

IMPLEMENT_DYNAMIC(SettingsDlg, CDialog)

SettingsDlg::SettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SettingsDlg::IDD, pParent)
	, m_iSaveRegistry(0)
	, m_iLaunchArduino(0)
	, m_iAppMode(0)
	, m_iDevVersion(0)
	, m_sArduinoFolder(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_fHasArduinoExe = FALSE;
}

SettingsDlg::~SettingsDlg()
{
}

void SettingsDlg::UpdateArduinoStatus()
{
	if ( cb_DoesArduinoExist(m_sArduinoFolder) )
	{
		SetDlgItemText(IDC_SETTINGS_TEXT_ARDUINO, _T("Found"));
		m_fHasArduinoExe = TRUE;
	}
	else
	{
		SetDlgItemText(IDC_SETTINGS_TEXT_ARDUINO, _T("MISSING"));
		m_fHasArduinoExe = FALSE;
	}
}

void SettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_SETTINGS_CB_REGISTRY, m_iSaveRegistry);
	DDX_CBIndex(pDX, IDC_SETTINGS_CB_LAUNCH, m_iLaunchArduino);
	DDX_CBIndex(pDX, IDC_SETTINGS_CB_APP_MODE, m_iAppMode);
	DDX_CBIndex(pDX, IDC_SETTINGS_CB_DEV_LIBRARIES, m_iDevVersion);
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_SETTINGS_BTN_CLEAR, &SettingsDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// SettingsDlg message handlers
BOOL SettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CString s;
#ifdef REEFANGEL_REG
	s.LoadString(IDS_REGISTRY_RA);
#else
	s.LoadString(IDS_REGISTRY_CB);
#endif  // REEFANGEL_REG
	SetDlgItemText(IDC_SETTINGS_TEXT_REGISTRY, s);
	UpdateArduinoStatus();
	return TRUE;
}

void SettingsDlg::OnOK()
{
	CDialog::OnOK();
}

void SettingsDlg::OnBnClickedBtnClear()
{
	// Clear settings from Registry
	int iRet = AfxMessageBox(_T("This will erase ALL saved settings in the Registry.\n\nAre you sure?"),
				MB_ICONINFORMATION|MB_YESNO);
	if ( iRet == IDYES )
	{
		// Clear registry settings
		DWORD dwRet;
		CString sMsg;
		CString s;
#ifdef REEFANGEL_REG
		s.LoadString(IDS_REGISTRY_RA_PATH);
#else
		s.LoadString(IDS_REGISTRY_CB_PATH);
#endif  // REEFANGEL_REG
		dwRet = SHDeleteKey(HKEY_CURRENT_USER, s);
		if ( dwRet == ERROR_SUCCESS )
		{
			// cleared
			sMsg = _T("Registry settings have been cleared.");
		}
		else
		{
			sMsg = _T("Unable to delete registry settings.");
		}
		AfxMessageBox(sMsg, MB_ICONINFORMATION|MB_OK);
	}
}
