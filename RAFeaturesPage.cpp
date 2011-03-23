// RAFeaturesPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAFeaturesPage.h"
#include "cb_FileVersion.h"
#include "GlobalVars.h"


// RAFeaturesPage dialog

IMPLEMENT_DYNAMIC(RAFeaturesPage, CDialog)

RAFeaturesPage::RAFeaturesPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAFeaturesPage::IDD, pParent)
{
}

RAFeaturesPage::~RAFeaturesPage()
{
}

void RAFeaturesPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_FEATURES_CK_DISPLAY_IMAGES, m_bDisplayImages);
	DDX_Check(pDX, IDC_FEATURES_CK_SETUP_EXTRAS, m_bSetupExtras);
	DDX_Check(pDX, IDC_FEATURES_CK_OVERHEAT_SETUP, m_bOverheatSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_DATE_TIME_SETUP, m_bDateTimeSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_VERSION_MENU, m_bVersionMenu);
	DDX_Check(pDX, IDC_FEATURES_CK_DIRECT_TEMP_SENSOR, m_bDirectTempSensor);
	DDX_Check(pDX, IDC_FEATURES_CK_DISPLAY_LED_PWM, m_bDisplayLEDPWM);
	DDX_Check(pDX, IDC_FEATURES_CK_WIFI, m_bWifi);
	DDX_Check(pDX, IDC_FEATURES_CK_ALTERNATE_FONT, m_bAlternateFont);
	DDX_Check(pDX, IDC_FEATURES_CK_REMOVE_ALL_LIGHTS, m_bRemoveAllLights);
	DDX_Check(pDX, IDC_FEATURES_CK_SAVE_RELAY_STATE, m_bSaveRelayState);
	DDX_Check(pDX, IDC_FEATURES_CK_EXPANSION_MODULE, m_bExpansionModule);
	DDX_Check(pDX, IDC_FEATURES_CK_DOSINGINTERVAL_SETUP, m_bDosingIntervalSetup);
}


BEGIN_MESSAGE_MAP(RAFeaturesPage, CDialog)
	//}}AFX_MSG_MAP
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DISPLAY_IMAGES, &RAFeaturesPage::OnBnHotItemChangeCkDisplayImages)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SETUP_EXTRAS, &RAFeaturesPage::OnBnHotItemChangeCkSetupExtras)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_OVERHEAT_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkOverheatSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DATE_TIME_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkDateTimeSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_VERSION_MENU, &RAFeaturesPage::OnBnHotItemChangeCkVersionMenu)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DIRECT_TEMP_SENSOR, &RAFeaturesPage::OnBnHotItemChangeCkDirectTempSensor)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DISPLAY_LED_PWM, &RAFeaturesPage::OnBnHotItemChangeCkDisplayLedPwm)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_WIFI, &RAFeaturesPage::OnBnHotItemChangeCkWifi)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_ALTERNATE_FONT, &RAFeaturesPage::OnBnHotItemChangeCkAlternateFont)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SAVE_RELAY_STATE, &RAFeaturesPage::OnBnHotItemChangeCkSaveRelayState)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_REMOVE_ALL_LIGHTS, &RAFeaturesPage::OnBnHotItemChangeCkRemoveAllLights)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_EXPANSION_MODULE, &RAFeaturesPage::OnBnHotItemChangeCkExpansionModule)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DOSINGINTERVAL_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkDosingIntervalSetup)
END_MESSAGE_MAP()


// RAFeaturesPage message handlers

BOOL RAFeaturesPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// disable the alternate font check box
	GetDlgItem(IDC_FEATURES_CK_ALTERNATE_FONT)->ShowWindow(SW_HIDE);

	LoadDefaults();
	ClearDescription();

	return TRUE;
}

void RAFeaturesPage::OnBnHotItemChangeCkDisplayImages(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_DISPLAYIMAGES);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkSetupExtras(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_SETUPEXTRAS);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkOverheatSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_OVERHEATSETUP);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkDateTimeSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_DATETIMESETUP);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkVersionMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_VERSIONMENU);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkDirectTempSensor(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_DIRECTTEMPSENSOR);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkDisplayLedPwm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_DISPLAYLEDPWM);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkWifi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_WIFI);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkAlternateFont(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_ALTERNATEFONT);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkSaveRelayState(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_SAVERELAYSTATE);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkRemoveAllLights(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_REMOVEALLLIGHTS);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkExpansionModule(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_EXPANSIONMODULE);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkDosingIntervalSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_DOSINGINTERVALSETUP);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnResetAll()
{
	LoadDefaults();
}

void RAFeaturesPage::OnResetSaved()
{
	LoadFeatures();
}

void RAFeaturesPage::ClearDescription()
{
	SetDlgItemText(IDC_FEATURES_TEXT_DESCRIPTION, _T("Move mouse over features to get descriptions."));
}

void RAFeaturesPage::SetDescription(UINT id)
{
	CString s;
	s.LoadString(id);
	SetDlgItemText(IDC_FEATURES_TEXT_DESCRIPTION, s);
}

void RAFeaturesPage::LoadFeatures()
{
	// Restore values from registry after last generation
	CString s;
	s.LoadStringA(IDS_FEATURES_TAB);
	m_bDisplayImages = AfxGetApp()->GetProfileInt(s, _T("DisplayImages"), TRUE);
	m_bSetupExtras = AfxGetApp()->GetProfileInt(s, _T("SetupExtras"), FALSE);
	m_bOverheatSetup = AfxGetApp()->GetProfileInt(s, _T("OverheatSetup"), FALSE);
	m_bDateTimeSetup = AfxGetApp()->GetProfileInt(s, _T("DateTimeSetup"), TRUE);
	m_bVersionMenu = AfxGetApp()->GetProfileInt(s, _T("VersionMenu"), TRUE);
	m_bDirectTempSensor = AfxGetApp()->GetProfileInt(s, _T("DirectTempSensor"), TRUE);
	m_bDisplayLEDPWM = AfxGetApp()->GetProfileInt(s, _T("DisplayLEDPWM"), TRUE);
	m_bWifi = AfxGetApp()->GetProfileInt(s, _T("Wifi"), FALSE);
	m_bAlternateFont = AfxGetApp()->GetProfileInt(s, _T("AlternateFont"), FALSE);
	m_bRemoveAllLights = AfxGetApp()->GetProfileInt(s, _T("RemoveAllLights"), FALSE);
	m_bSaveRelayState = AfxGetApp()->GetProfileInt(s, _T("SaveRelayState"), FALSE);
	m_bExpansionModule = AfxGetApp()->GetProfileInt(s, _T("ExpansionModule"), FALSE);
	m_bDosingIntervalSetup = AfxGetApp()->GetProfileInt(s, _T("DosingIntervalSetup"), FALSE);
	UpdateData(FALSE);
}

void RAFeaturesPage::SaveFeatures(Features fs)
{
	// Save values to registry after last generation
	CString s;
	s.LoadString(IDS_FEATURES_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("DisplayImages"), fs.fDisplayImages);
	AfxGetApp()->WriteProfileInt(s, _T("SetupExtras"), fs.fSetupExtras);
	AfxGetApp()->WriteProfileInt(s, _T("OverheatSetup"), fs.fOverheatSetup);
	AfxGetApp()->WriteProfileInt(s, _T("DateTimeSetup"), fs.fDateTimeSetup);
	AfxGetApp()->WriteProfileInt(s, _T("VersionMenu"), fs.fVersionMenu);
	AfxGetApp()->WriteProfileInt(s, _T("DirectTempSensor"), fs.fDirectTempSensor);
	AfxGetApp()->WriteProfileInt(s, _T("DisplayLEDPWM"), fs.fDisplayLEDPWM);
	AfxGetApp()->WriteProfileInt(s, _T("Wifi"), fs.fWifi);
	AfxGetApp()->WriteProfileInt(s, _T("AlternateFont"), fs.fAlternateFont);
	AfxGetApp()->WriteProfileInt(s, _T("RemoveAllLights"), fs.fRemoveAllLights);
	AfxGetApp()->WriteProfileInt(s, _T("SaveRelayState"), fs.fSaveRelayState);
	AfxGetApp()->WriteProfileInt(s, _T("ExpansionModule"), fs.fExpansionModule);
	AfxGetApp()->WriteProfileInt(s, _T("DosingIntervalSetup"), fs.fDosingIntervalSetup);
}

void RAFeaturesPage::LoadDefaults()
{
	// Loads the default values
	m_bDisplayImages = TRUE;
	m_bSetupExtras = FALSE;
	m_bOverheatSetup = FALSE;
	m_bDateTimeSetup = TRUE;
	m_bVersionMenu = TRUE;
	m_bDirectTempSensor = TRUE;
	m_bDisplayLEDPWM = TRUE;
	m_bWifi = FALSE;
	m_bAlternateFont = FALSE;
	m_bRemoveAllLights = FALSE;
	m_bSaveRelayState = FALSE;
	m_bExpansionModule = FALSE;
	m_bDosingIntervalSetup = FALSE;
	UpdateData(FALSE);
}

void RAFeaturesPage::UpdateFeaturesStruct(Features& fs)
{
	UpdateData();
	fs.fDisplayImages = m_bDisplayImages;
	fs.fSetupExtras = m_bSetupExtras;
	fs.fOverheatSetup = m_bOverheatSetup;
	fs.fDateTimeSetup = m_bDateTimeSetup;
	fs.fVersionMenu = m_bVersionMenu;
	fs.fDirectTempSensor = m_bDirectTempSensor;
	fs.fDisplayLEDPWM = m_bDisplayLEDPWM;
	fs.fWifi = m_bWifi;
	fs.fAlternateFont = m_bAlternateFont;
	fs.fRemoveAllLights = m_bRemoveAllLights;
	fs.fSaveRelayState = m_bSaveRelayState;
	fs.fExpansionModule = m_bExpansionModule;
	fs.fDosingIntervalSetup = m_bDosingIntervalSetup;

	// these features are set based on PDE page selection, so blank them out
	fs.fDosingPumpSetup = FALSE;
	fs.fWavemakerSetup = FALSE;
	fs.fATOSetup = FALSE;
	fs.fSingleATO = FALSE;
	fs.fMetalHalideSetup = FALSE;
	fs.fStandardLightSetup = FALSE;
}

BOOL RAFeaturesPage::WriteFeatures(Features fs, LPCTSTR sLibraryFolder)
{
	BOOL bRet = FALSE;

	TRY
	{
		CString s;
		CTime t = CTime::GetCurrentTime();
		CString sAutoGenHeader;
		sAutoGenHeader.Format(_T("// AutoGenerated file by RAGen (v%s), (%s)\r\n\r\n"),
				cb_GetFileVersionString(AfxGetInstanceHandle()),
				t.Format("%m/%d/%Y %H:%M"));
		CString sHeader = _T("\
/*\r\n\
 * Copyright 2010-11 Curt Binder\r\n\
 *\r\n\
 * Licensed under the Apache License, Version 2.0 (the \"License\")\r\n\
 * you may not use this file except in compliance with the License.\r\n\
 * You may obtain a copy of the License at\r\n\
 *\r\n\
 * http://www.apache.org/licenses/LICENSE-2.0\r\n\
 *\r\n\
 * Unless required by applicable law or agreed to in writing, software\r\n\
 * distributed under the License is distributed on an \"AS IS\" BASIS,\r\n\
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\r\n\
 * See the License for the specific language governing permissions and\r\n\
 * limitations under the License.\r\n\
 */\r\n\
\r\n\r\n\
#ifndef __REEFANGEL_FEATURES_H__\r\n\
#define __REEFANGEL_FEATURES_H__\r\n\
\r\n\r\n\
");
		CString sFooter = _T("\r\n\r\n#endif  // __REEFANGEL_FEATURES_H__\r\n");
		CString sFile;
		sFile.Format(_T("%s\\ReefAngel_Features\\"), sLibraryFolder);
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = FALSE;
		int iRet = SHCreateDirectoryEx(NULL, sFile, &sa);
		if ( iRet != ERROR_SUCCESS )
		{
			DWORD dw = GetLastError();
			if ( (dw != ERROR_FILE_EXISTS) && (dw != ERROR_ALREADY_EXISTS) )
			{
				// An unknown error has occurred
				AfxThrowUserException();
			}
		}
		sFile += _T("ReefAngel_Features.h");
		CFile f;
		f.Open(sFile, CFile::modeCreate | CFile::modeWrite);
		f.Write(sAutoGenHeader, sAutoGenHeader.GetLength());
		f.Write(sHeader, sHeader.GetLength());
		GetEnabledFeaturesList(fs, s);
		f.Write(s, s.GetLength());
		f.Write(sFooter, sFooter.GetLength());
		f.Close();
		bRet = TRUE;
	}
	CATCH_ALL(e)
	{
		CString sBuffer;
		TCHAR szMsg[255];
		e->GetErrorMessage(szMsg, 255);
		sBuffer.Format(_T("Unable to generate ReefAngel_Features.h:\n\n"));
		sBuffer += szMsg;
		AfxMessageBox(sBuffer, MB_ICONINFORMATION);
		bRet = FALSE;
	}
	END_CATCH_ALL

	return bRet;
}


