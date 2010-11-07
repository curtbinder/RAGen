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
	, m_sSketchFolder(_T(""))
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
}


BEGIN_MESSAGE_MAP(SettingsDlg, CDialog)
	ON_BN_CLICKED(IDC_SETTINGS_SKETCH_BTN_BROWSE, &SettingsDlg::OnBnClickedSketchBtnBrowse)
	ON_BN_CLICKED(IDC_SETTINGS_ARDUINO_BTN_BROWSE, &SettingsDlg::OnBnClickedArduinoBtnBrowse)
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
	SetDlgItemText(IDC_SETTINGS_SKETCH_FOLDER, m_sSketchFolder);
	SetDlgItemText(IDC_SETTINGS_ARDUINO_FOLDER, m_sArduinoFolder);
	UpdateArduinoStatus();
	return TRUE;
}

void SettingsDlg::OnOK()
{
	GetDlgItemText(IDC_SETTINGS_SKETCH_FOLDER, m_sSketchFolder);
	if ( m_sSketchFolder.IsEmpty() )
	{
		AfxMessageBox(_T("You must specify a directory for sketches."), MB_ICONINFORMATION|MB_OK);
		return;
	}
	// validate folder and make sure it's a writable folder, if not don't exit
	if ( ! cb_IsFolderWritable(m_sSketchFolder) )
	{
		CString s;
		s.Format(_T("Invalid folder:\n\n%s\n\nPlease select another sketch folder."), m_sSketchFolder);
		AfxMessageBox(s, MB_ICONINFORMATION|MB_OK);
		return;
	}
	GetDlgItemText(IDC_SETTINGS_ARDUINO_FOLDER, m_sArduinoFolder);
	if ( m_sArduinoFolder.IsEmpty() )
	{
		AfxMessageBox(_T("You must specify an arduino directory."), MB_ICONINFORMATION|MB_OK);
		return;
	}
	// validate folder and make sure it exists, if not don't exit
	if ( ! cb_IsDirectory(m_sArduinoFolder) )
	{
		CString s;
		s.Format(_T("Invalid folder:\n\n%s\n\nPlease select another arduino folder."), m_sArduinoFolder);
		AfxMessageBox(s, MB_ICONINFORMATION|MB_OK);
		return;
	}
	CDialog::OnOK();
}

void SettingsDlg::OnBnClickedSketchBtnBrowse()
{
	TCHAR szFolder[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	
	if ( ! cb_BrowseFolder(m_hWnd, szFolder, _T("Please select Sketchbook Folder"), szPath) )
	{
		// an error occurred or use cancelled for whatever reason, so break out
		return;
	}
	m_sSketchFolder.Format(_T("%s"), szPath);
	SetDlgItemText(IDC_SETTINGS_SKETCH_FOLDER, m_sSketchFolder);
}

void SettingsDlg::OnBnClickedArduinoBtnBrowse()
{
	TCHAR szFolder[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	
	if ( ! cb_BrowseFolder(m_hWnd, szFolder, _T("Please select Arduino Folder"), szPath) )
	{
		// an error occurred or use cancelled for whatever reason, so break out
		return;
	}
	m_sArduinoFolder.Format(_T("%s"), szPath);
	SetDlgItemText(IDC_SETTINGS_ARDUINO_FOLDER, m_sArduinoFolder);
	UpdateArduinoStatus();
}

void SettingsDlg::OnBnClickedBtnClear()
{
	// Clear settings from Registry
	int iRet = AfxMessageBox(_T("This will erase ALL saved settings in Registry.\n\nAre you sure?"),
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
