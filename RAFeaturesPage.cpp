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
	DDX_Check(pDX, IDC_FEATURES_CK_DOSINGPUMP_SETUP, m_bDosingPumpSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_WAVEMAKER_SETUP, m_bWavemakerSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_OVERHEAT_SETUP, m_bOverheatSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_DATE_TIME_SETUP, m_bDateTimeSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_VERSION_MENU, m_bVersionMenu);
	DDX_Check(pDX, IDC_FEATURES_CK_ATO_SETUP, m_bATOSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_METAL_HALIDE_SETUP, m_bMetalHalideSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_DIRECT_TEMP_SENSOR, m_bDirectTempSensor);
	DDX_Check(pDX, IDC_FEATURES_CK_DISPLAY_LED_PWM, m_bDisplayLEDPWM);
	DDX_Check(pDX, IDC_FEATURES_CK_WIFI, m_bWifi);
	DDX_Check(pDX, IDC_FEATURES_CK_ALTERNATE_FONT, m_bAlternateFont);
	DDX_Check(pDX, IDC_FEATURES_CK_SINGLE_ATO, m_bSingleATO);
	DDX_Check(pDX, IDC_FEATURES_CK_STANDARD_LIGHTS_SETUP, m_bStandardLightSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_REMOVE_ALL_LIGHTS, m_bRemoveAllLights);
	DDX_Check(pDX, IDC_FEATURES_CK_SAVE_RELAY_STATE, m_bSaveRelayState);
}


BEGIN_MESSAGE_MAP(RAFeaturesPage, CDialog)
	//}}AFX_MSG_MAP
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DISPLAY_IMAGES, &RAFeaturesPage::OnBnHotItemChangeCkDisplayImages)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SETUP_EXTRAS, &RAFeaturesPage::OnBnHotItemChangeCkSetupExtras)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DOSINGPUMP_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkDosingpumpSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_WAVEMAKER_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkWavemakerSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_OVERHEAT_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkOverheatSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DATE_TIME_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkDateTimeSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_VERSION_MENU, &RAFeaturesPage::OnBnHotItemChangeCkVersionMenu)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_ATO_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkAtoSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_METAL_HALIDE_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkMetalHalideSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DIRECT_TEMP_SENSOR, &RAFeaturesPage::OnBnHotItemChangeCkDirectTempSensor)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DISPLAY_LED_PWM, &RAFeaturesPage::OnBnHotItemChangeCkDisplayLedPwm)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_WIFI, &RAFeaturesPage::OnBnHotItemChangeCkWifi)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_ALTERNATE_FONT, &RAFeaturesPage::OnBnHotItemChangeCkAlternateFont)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SAVE_RELAY_STATE, &RAFeaturesPage::OnBnHotItemChangeCkSaveRelayState)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_STANDARD_LIGHTS_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkStandardLightsSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_REMOVE_ALL_LIGHTS, &RAFeaturesPage::OnBnHotItemChangeCkRemoveAllLights)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SINGLE_ATO, &RAFeaturesPage::OnBnHotItemChangeCkSingleAto)
END_MESSAGE_MAP()


// RAFeaturesPage message handlers

BOOL RAFeaturesPage::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void RAFeaturesPage::OnBnHotItemChangeCkDosingpumpSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_DOSINGPUMPSETUP);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkWavemakerSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_WAVEMAKERSETUP);
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

void RAFeaturesPage::OnBnHotItemChangeCkAtoSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_ATOSETUP);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkMetalHalideSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_METALHALIDESETUP);
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

void RAFeaturesPage::OnBnHotItemChangeCkStandardLightsSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_STANDARDLIGHTSETUP);
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

void RAFeaturesPage::OnBnHotItemChangeCkSingleAto(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_SINGLEATO);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnClickedBtnGenerate()
{
	// Generate to local directory initially
	UpdateData();
	if ( WriteFeatures() )
	{
		AfxGetApp()->GetMainWnd()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), LPARAM(IDS_SUCCESS_FEATURES));
		switch ( iSaveReg )
		{
		case ALWAYS:
			SaveFeatures();
			break;
		case PROMPT:
			{
				int iRet = AfxMessageBox(_T("Do you want to save these settings?"),
					MB_ICONINFORMATION | MB_YESNO);
				if ( iRet == IDYES )
				{
					// Save settings
					SaveFeatures();
				}
			}
			break;
		default:
		//case NeverSave:
			break;
		}
	}
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
	m_bDosingPumpSetup = AfxGetApp()->GetProfileInt(s, _T("DosingPumpSetup"), FALSE);
	m_bWavemakerSetup = AfxGetApp()->GetProfileInt(s, _T("WavemakerSetup"), TRUE);
	m_bOverheatSetup = AfxGetApp()->GetProfileInt(s, _T("OverheatSetup"), FALSE);
	m_bDateTimeSetup = AfxGetApp()->GetProfileInt(s, _T("DateTimeSetup"), TRUE);
	m_bVersionMenu = AfxGetApp()->GetProfileInt(s, _T("VersionMenu"), TRUE);
	m_bATOSetup = AfxGetApp()->GetProfileInt(s, _T("ATOSetup"), TRUE);
	m_bMetalHalideSetup = AfxGetApp()->GetProfileInt(s, _T("MetalHalideSetup"), TRUE);
	m_bDirectTempSensor = AfxGetApp()->GetProfileInt(s, _T("DirectTempSensor"), TRUE);
	m_bDisplayLEDPWM = AfxGetApp()->GetProfileInt(s, _T("DisplayLEDPWM"), TRUE);
	m_bWifi = AfxGetApp()->GetProfileInt(s, _T("Wifi"), FALSE);
	m_bAlternateFont = AfxGetApp()->GetProfileInt(s, _T("AlternateFont"), FALSE);
	m_bSingleATO = AfxGetApp()->GetProfileInt(s, _T("SingleATO"), FALSE);
	m_bStandardLightSetup = AfxGetApp()->GetProfileInt(s, _T("StandardLightSetup"), TRUE);
	m_bRemoveAllLights = AfxGetApp()->GetProfileInt(s, _T("RemoveAllLights"), FALSE);
	m_bSaveRelayState = AfxGetApp()->GetProfileInt(s, _T("SaveRelayState"), FALSE);
	UpdateData(FALSE);
}

void RAFeaturesPage::SaveFeatures()
{
	// Save values to registry after last generation
	CString s;
	s.LoadString(IDS_FEATURES_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("DisplayImages"), m_bDisplayImages);
	AfxGetApp()->WriteProfileInt(s, _T("SetupExtras"), m_bSetupExtras);
	AfxGetApp()->WriteProfileInt(s, _T("DosingPumpSetup"), m_bDosingPumpSetup);
	AfxGetApp()->WriteProfileInt(s, _T("WavemakerSetup"), m_bWavemakerSetup);
	AfxGetApp()->WriteProfileInt(s, _T("OverheatSetup"), m_bOverheatSetup);
	AfxGetApp()->WriteProfileInt(s, _T("DateTimeSetup"), m_bDateTimeSetup);
	AfxGetApp()->WriteProfileInt(s, _T("VersionMenu"), m_bVersionMenu);
	AfxGetApp()->WriteProfileInt(s, _T("ATOSetup"), m_bATOSetup);
	AfxGetApp()->WriteProfileInt(s, _T("MetalHalideSetup"), m_bMetalHalideSetup);
	AfxGetApp()->WriteProfileInt(s, _T("DirectTempSensor"), m_bDirectTempSensor);
	AfxGetApp()->WriteProfileInt(s, _T("DisplayLEDPWM"), m_bDisplayLEDPWM);
	AfxGetApp()->WriteProfileInt(s, _T("Wifi"), m_bWifi);
	AfxGetApp()->WriteProfileInt(s, _T("AlternateFont"), m_bAlternateFont);
	AfxGetApp()->WriteProfileInt(s, _T("SingleATO"), m_bSingleATO);
	AfxGetApp()->WriteProfileInt(s, _T("StandardLightSetup"), m_bStandardLightSetup);
	AfxGetApp()->WriteProfileInt(s, _T("RemoveAllLights"), m_bRemoveAllLights);
	AfxGetApp()->WriteProfileInt(s, _T("SaveRelayState"), m_bSaveRelayState);
}

void RAFeaturesPage::LoadDefaults()
{
	// Loads the default values
	m_bDisplayImages = TRUE;
	m_bSetupExtras = FALSE;
	m_bDosingPumpSetup = FALSE;
	m_bWavemakerSetup = TRUE;
	m_bOverheatSetup = FALSE;
	m_bDateTimeSetup = TRUE;
	m_bVersionMenu = TRUE;
	m_bATOSetup = TRUE;
	m_bMetalHalideSetup = TRUE;
	m_bDirectTempSensor = TRUE;
	m_bDisplayLEDPWM = TRUE;
	m_bWifi = FALSE;
	m_bAlternateFont = FALSE;
	m_bSingleATO = FALSE;
	m_bStandardLightSetup = TRUE;
	m_bRemoveAllLights = FALSE;
	m_bSaveRelayState = FALSE;
	UpdateData(FALSE);
}

BOOL RAFeaturesPage::WriteFeatures()
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
 * Copyright 2010 / Curt Binder\r\n\
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
		// we have an arduino directory, so we will utilize it
		sFile.Format(_T("%s\\libraries\\ReefAngel_Features\\"), m_sArduinoDirectory);
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
		if ( m_bDisplayImages )
		{
			s = _T("#define DisplayImages\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bSetupExtras )
		{
			s = _T("#define SetupExtras\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bDosingPumpSetup )
		{
			s = _T("#define DosingPumpSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bWavemakerSetup )
		{
			s = _T("#define WavemakerSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bOverheatSetup )
		{
			s = _T("#define OverheatSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bDateTimeSetup )
		{
			s = _T("#define DateTimeSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bVersionMenu )
		{
			s = _T("#define VersionMenu\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bATOSetup )
		{
			s = _T("#define ATOSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bMetalHalideSetup )
		{
			s = _T("#define MetalHalideSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bDirectTempSensor )
		{
			s = _T("#define DirectTempSensor\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bDisplayLEDPWM )
		{
			s = _T("#define DisplayLEDPWM\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bWifi )
		{
			s = _T("#define wifi\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bAlternateFont )
		{
			s = _T("#define AlternateFont\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bSingleATO )
		{
			s = _T("#define SingleATOSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bStandardLightSetup )
		{
			s = _T("#define StandardLightSetup\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bRemoveAllLights )
		{
			s = _T("#define RemoveAllLights\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_bSaveRelayState )
		{
			s = _T("#define SaveRelayState\r\n");
			f.Write(s, s.GetLength());
		}
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
