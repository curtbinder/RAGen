// RAFeaturesPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAFeaturesPage.h"
#include "cb_FileVersion.h"
#include "GlobalVars.h"
#include "InternalMemoryDefaults.h"


// RAFeaturesPage dialog

IMPLEMENT_DYNAMIC(RAFeaturesPage, CDialog)

RAFeaturesPage::RAFeaturesPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAFeaturesPage::IDD, pParent)
{
	m_sUnknownFeatures = _T("");
}

RAFeaturesPage::~RAFeaturesPage()
{
}

void RAFeaturesPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FEATURES_TREE, m_tree);
}


BEGIN_MESSAGE_MAP(RAFeaturesPage, CDialog)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, IDC_FEATURES_TREE, &RAFeaturesPage::OnTvnSelchangedFeaturesTree)
END_MESSAGE_MAP()


// RAFeaturesPage message handlers

BOOL RAFeaturesPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadFeatures();

	InitTree();

	ClearDescription();

	return TRUE;
}

void RAFeaturesPage::InitTree()
{
	m_tree.ModifyStyle(0, TVS_NOHSCROLL);

	HTREEITEM root;
	HTREEITEM setup;
	HTREEITEM menu;
	HTREEITEM exp;
	HTREEITEM screen;
	HTREEITEM hi;
	CString s;
	m_efd[0].uID = 0;
	m_efd[0].sDefine = _T("");
	root = m_tree.InsertItem(_T("Features"));
	m_tree.SetItemData(root, (DWORD)0);
	hi = m_tree.InsertItem(_T("Wifi"), root);
	m_efd[1].uID = IDS_FEATURES_WIFI;
	m_efd[1].sDefine = _T("wifi");
	m_tree.SetItemData(hi, (DWORD)1);
	hi = m_tree.InsertItem(_T("Watchdog Timer"), root);
	m_efd[2].uID = IDS_FEATURES_WDT;
	m_efd[2].sDefine = _T("WDT");
	m_tree.SetItemData(hi, (DWORD)2);

	setup = m_tree.InsertItem(_T("Setup Menus"), root);
	m_tree.SetItemData(setup, (DWORD)0);
	hi = m_tree.InsertItem(_T("Overheat Setup"), setup);
	m_efd[3].uID = IDS_FEATURES_OVERHEATSETUP;
	m_efd[3].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)3);
	hi = m_tree.InsertItem(_T("Date / Time Setup"), setup);
	m_efd[4].uID = IDS_FEATURES_DATETIMESETUP;
	m_efd[4].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)4);
	hi = m_tree.InsertItem(_T("Dosing Repeat Setup"), setup);
	m_efd[5].uID = IDS_FEATURES_DOSINGINTERVALSETUP;
	m_efd[5].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)5);
	hi = m_tree.InsertItem(_T("Setup Extras"), setup);
	m_efd[6].uID = IDS_FEATURES_SETUPEXTRAS;
	m_efd[6].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)6);

	menu = m_tree.InsertItem(_T("Menu System"), root);
	m_tree.SetItemData(menu, (DWORD)0);
	hi = m_tree.InsertItem(_T("Simple Menu"), menu);
	m_efd[7].uID = IDS_FEATURES_SIMPLEMENU;
	m_efd[7].sDefine = _T("SIMPLE_MENU");
	m_tree.SetItemData(hi, (DWORD)7);
	hi = m_tree.InsertItem(_T("Custom Menu"), menu);
	m_efd[8].uID = IDS_FEATURES_CUSTOMMENU;
	m_efd[8].sDefine = _T("CUSTOM_MENU");
	m_tree.SetItemData(hi, (DWORD)8);

	exp = m_tree.InsertItem(_T("Expansion Modules"), root);
	m_tree.SetItemData(exp, (DWORD)0);
	hi = m_tree.InsertItem(_T("Expansion Relays"), exp);
	m_efd[9].uID = IDS_FEATURES_EXPANSIONMODULE;
	m_efd[9].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)9);
	hi = m_tree.InsertItem(_T("PWM"), exp);
	m_efd[10].uID = IDS_FEATURES_PWMEXPANSION;
	m_efd[10].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)10);
	hi = m_tree.InsertItem(_T("Salinity"), exp);
	m_efd[11].uID = 0;
	m_efd[11].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)11);
	hi = m_tree.InsertItem(_T("ORP"), exp);
	m_efd[12].uID = 0;
	m_efd[13].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)12);
	hi = m_tree.InsertItem(_T("AI LED"), exp);
	m_efd[13].uID = 0;
	m_efd[13].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)13);
	hi = m_tree.InsertItem(_T("RF"), exp);
	m_efd[14].uID = 0;
	m_efd[14].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)14);

	screen = m_tree.InsertItem(_T("Screen Options"), root);
	m_tree.SetItemData(screen, (DWORD)0);
	hi = m_tree.InsertItem(_T("Custom Main Screen"), screen);
	m_efd[15].uID = IDS_FEATURES_CUSTOMMAIN;
	m_efd[15].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)15);
	hi = m_tree.InsertItem(_T("Display Images"), screen);
	m_efd[16].uID = IDS_FEATURES_DISPLAYIMAGES;
	m_efd[16].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)16);
	hi = m_tree.InsertItem(_T("Version Menu"), screen);
	m_efd[17].uID = IDS_FEATURES_VERSIONMENU;
	m_efd[17].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)17);
	hi = m_tree.InsertItem(_T("Display LED PWM"), screen);
	m_efd[18].uID = IDS_FEATURES_DISPLAYLEDPWM;
	m_efd[18].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)18);
	hi = m_tree.InsertItem(_T("Remove All Lights"), screen);
	m_efd[19].uID = IDS_FEATURES_REMOVEALLLIGHTS;
	m_efd[19].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)19);
	hi = m_tree.InsertItem(_T("Custom Colors"), screen);
	m_efd[20].uID = IDS_FEATURES_COLORSPDE;
	m_efd[20].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)20);

	hi = m_tree.InsertItem(_T("ATO Logging"), root);
	m_efd[21].uID = IDS_FEATURES_ATOLOGGING;
	m_efd[21].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)21);
	hi = m_tree.InsertItem(_T("Exceed Flagging"), root);
	m_efd[22].uID = IDS_FEATURES_EXCEEDFLAG;
	m_efd[22].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)22);
	hi = m_tree.InsertItem(_T("Direct Temp Sensor"), root);
	m_efd[23].uID = IDS_FEATURES_DIRECTTEMPSENSOR;
	m_efd[23].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)23);
	hi = m_tree.InsertItem(_T("Save Relay State"), root);
	m_efd[24].uID = IDS_FEATURES_SAVERELAYSTATE;
	m_efd[24].sDefine = _T("");
	m_tree.SetItemData(hi, (DWORD)24);

	// expand all the levels
	m_tree.Expand(root, TVE_EXPAND);
	m_tree.Expand(setup, TVE_EXPAND);
	m_tree.Expand(menu, TVE_EXPAND);
	m_tree.Expand(screen, TVE_EXPAND);
	m_tree.Expand(exp, TVE_EXPAND);

	m_tree.SelectItem(root);
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
	SetDlgItemTextA(IDC_FEATURES_TEXT_DESCRIPTION, _T("Click on features to get descriptions."));
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
	g_Features.fDisplayImages = AfxGetApp()->GetProfileInt(s, _T("DisplayImages"), TRUE);
	g_Features.fSetupExtras = AfxGetApp()->GetProfileInt(s, _T("SetupExtras"), FALSE);
	g_Features.fOverheatSetup = AfxGetApp()->GetProfileInt(s, _T("OverheatSetup"), FALSE);
	g_Features.fDateTimeSetup = AfxGetApp()->GetProfileInt(s, _T("DateTimeSetup"), TRUE);
	g_Features.fVersionMenu = AfxGetApp()->GetProfileInt(s, _T("VersionMenu"), TRUE);
	g_Features.fDirectTempSensor = AfxGetApp()->GetProfileInt(s, _T("DirectTempSensor"), TRUE);
	g_Features.fDisplayLEDPWM = AfxGetApp()->GetProfileInt(s, _T("DisplayLEDPWM"), TRUE);
	g_Features.fWifi = AfxGetApp()->GetProfileInt(s, _T("Wifi"), TRUE);
	g_Features.fAlternateFont = AfxGetApp()->GetProfileInt(s, _T("AlternateFont"), FALSE);
	g_Features.fRemoveAllLights = AfxGetApp()->GetProfileInt(s, _T("RemoveAllLights"), FALSE);
	g_Features.fSaveRelayState = AfxGetApp()->GetProfileInt(s, _T("SaveRelayState"), FALSE);
	g_Features.fExpansionModule = AfxGetApp()->GetProfileInt(s, _T("ExpansionModule"), FALSE);
	g_Features.fDosingIntervalSetup = AfxGetApp()->GetProfileInt(s, _T("DosingIntervalSetup"), FALSE);
	g_Features.fWDT = AfxGetApp()->GetProfileInt(s, _T("Watchdog"), FALSE);
	g_Features.fCustomMenu = AfxGetApp()->GetProfileInt(s, _T("CustomMenu"), FALSE);
	g_Features.iCustomMenuEntries = AfxGetApp()->GetProfileInt(s, _T("CustomMenuEntries"), MENU_DEFAULT);
	g_Features.fSimpleMenu = AfxGetApp()->GetProfileInt(s, _T("SimpleMenu"), TRUE);
	g_Features.fPWMExpansion = AfxGetApp()->GetProfileInt(s, _T("PWMExpansion"), FALSE);
	g_Features.fCustomMain = AfxGetApp()->GetProfileInt(s, _T("CustomMain"), FALSE);
	g_Features.fColorsPDE = AfxGetApp()->GetProfileInt(s, _T("ColorsPDE"), FALSE);
	g_Features.fAtoLogging = AfxGetApp()->GetProfileInt(s, _T("ATOLogging"), FALSE);
	g_Features.fExceedFlags = AfxGetApp()->GetProfileInt(s, _T("ExceedFlags"), FALSE);
	g_Features.fSalinity = AfxGetApp()->GetProfileInt(s, _T("SalinityExpansion"), FALSE);
	g_Features.fRF = AfxGetApp()->GetProfileInt(s, _T("RFExpansion"), FALSE);
	g_Features.fORP = AfxGetApp()->GetProfileInt(s, _T("ORPExpansion"), FALSE);
	g_Features.fIO = AfxGetApp()->GetProfileInt(s, _T("IOExpansion"), FALSE);
	g_Features.fAI = AfxGetApp()->GetProfileInt(s, _T("AILed"), FALSE);
	UpdateData(FALSE);
}

void RAFeaturesPage::SaveFeatures(/*Features fs*/)
{
	// TODO remove parameter
	// Save values to registry after last generation
	CString s;
	s.LoadString(IDS_FEATURES_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("DisplayImages"), g_Features.fDisplayImages);
	AfxGetApp()->WriteProfileInt(s, _T("SetupExtras"), g_Features.fSetupExtras);
	AfxGetApp()->WriteProfileInt(s, _T("OverheatSetup"), g_Features.fOverheatSetup);
	AfxGetApp()->WriteProfileInt(s, _T("DateTimeSetup"), g_Features.fDateTimeSetup);
	AfxGetApp()->WriteProfileInt(s, _T("VersionMenu"), g_Features.fVersionMenu);
	AfxGetApp()->WriteProfileInt(s, _T("DirectTempSensor"), g_Features.fDirectTempSensor);
	AfxGetApp()->WriteProfileInt(s, _T("DisplayLEDPWM"), g_Features.fDisplayLEDPWM);
	AfxGetApp()->WriteProfileInt(s, _T("Wifi"), g_Features.fWifi);
	AfxGetApp()->WriteProfileInt(s, _T("AlternateFont"), g_Features.fAlternateFont);
	AfxGetApp()->WriteProfileInt(s, _T("RemoveAllLights"), g_Features.fRemoveAllLights);
	AfxGetApp()->WriteProfileInt(s, _T("SaveRelayState"), g_Features.fSaveRelayState);
	AfxGetApp()->WriteProfileInt(s, _T("ExpansionModule"), g_Features.fExpansionModule);
	AfxGetApp()->WriteProfileInt(s, _T("DosingIntervalSetup"), g_Features.fDosingIntervalSetup);
	AfxGetApp()->WriteProfileInt(s, _T("Watchdog"), g_Features.fWDT);
	AfxGetApp()->WriteProfileInt(s, _T("CustomMenu"), g_Features.fCustomMenu);
	AfxGetApp()->WriteProfileInt(s, _T("CustomMenuEntries"), g_Features.iCustomMenuEntries);
	AfxGetApp()->WriteProfileInt(s, _T("SimpleMenu"), g_Features.fSimpleMenu);
	AfxGetApp()->WriteProfileInt(s, _T("PWMExpansion"), g_Features.fPWMExpansion);
	AfxGetApp()->WriteProfileInt(s, _T("CustomMain"), g_Features.fCustomMain);
	AfxGetApp()->WriteProfileInt(s, _T("ColorsPDE"), g_Features.fColorsPDE);
	AfxGetApp()->WriteProfileInt(s, _T("ATOLogging"), g_Features.fAtoLogging);
	AfxGetApp()->WriteProfileInt(s, _T("ExceedFlags"), g_Features.fExceedFlags);
	AfxGetApp()->WriteProfileInt(s, _T("SalinityExpansion"), g_Features.fSalinity);
	AfxGetApp()->WriteProfileInt(s, _T("RFExpansion"), g_Features.fRF);
	AfxGetApp()->WriteProfileInt(s, _T("ORPExpansion"), g_Features.fORP);
	AfxGetApp()->WriteProfileInt(s, _T("IOExpansion"), g_Features.fIO);
	AfxGetApp()->WriteProfileInt(s, _T("AILed"), g_Features.fAI);
}

void RAFeaturesPage::LoadDefaults()
{
	// Loads the default values
	g_Features.fDisplayImages = TRUE;
	g_Features.fSetupExtras = FALSE;
	g_Features.fOverheatSetup = FALSE;
	g_Features.fDateTimeSetup = TRUE;
	g_Features.fVersionMenu = TRUE;
	g_Features.fDirectTempSensor = TRUE;
	g_Features.fDisplayLEDPWM = TRUE;
	g_Features.fWifi = TRUE;
	g_Features.fAlternateFont = FALSE;
	g_Features.fRemoveAllLights = FALSE;
	g_Features.fSaveRelayState = FALSE;
	g_Features.fExpansionModule = FALSE;
	g_Features.iInstalledExpansionModules = 0;
	g_Features.fDosingIntervalSetup = FALSE;
	g_Features.fWDT = FALSE;
	g_Features.fCustomMenu = FALSE;
	g_Features.iCustomMenuEntries = MENU_DEFAULT;
	g_Features.fSimpleMenu = TRUE;
	g_Features.fPWMExpansion = FALSE;
	g_Features.fCustomMain = FALSE;
	g_Features.fColorsPDE = FALSE;
	g_Features.fAtoLogging = FALSE;
	g_Features.fExceedFlags = FALSE;
	g_Features.fSalinity = FALSE;
	g_Features.fRF = FALSE;
	g_Features.fORP = FALSE;
	g_Features.fIO = FALSE;
	g_Features.fAI = FALSE;
	UpdateData(FALSE);
}

void RAFeaturesPage::UpdateFeaturesStruct(BOOL fResetPDEFeatures /*= TRUE*/)
{
	// TODO remove Features parameter
	// TODO update global Features based on items checked
	UpdateData();
	/*
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
	fs.fWDT = m_bWDT;
	fs.fCustomMenu = m_bCustomMenu;
	fs.iCustomMenuEntries = m_iCustomMenuEntries;
	fs.fSimpleMenu = m_bSimpleMenu;
	fs.fPWMExpansion = m_bPWMExpansion;
	fs.fCustomMain = m_bCustomMain;
	fs.fColorsPDE = m_bColorsPDE;
	fs.fAtoLogging = m_bAtoLogging;
	fs.fExceedFlags = m_bExceedFlags;
	fs.fSalinity = m_fSalinity;
	fs.fRF = m_fRF;
	fs.fORP = m_fORP;
	fs.fIO = m_fIO;
	fs.fAI = m_fAI;

	if ( fResetPDEFeatures || m_bSimpleMenu || m_bCustomMenu )
	{
		// these features are set based on PDE page selection, so blank them out
		fs.fDosingPumpSetup = FALSE;
		fs.fWavemakerSetup = FALSE;
		fs.fATOSetup = FALSE;
		fs.fSingleATO = FALSE;
		fs.fMetalHalideSetup = FALSE;
		fs.fStandardLightSetup = FALSE;
	}
	*/
}

BOOL RAFeaturesPage::WriteFeatures(Features fs, LPCTSTR sLibraryFolder)
{
	// TODO remove Features parameter
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
 * Copyright 2010-12 Curt Binder\r\n\
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
		// if we have any additional features, prompt if the user wants to keep them or not
		if ( ! m_sUnknownFeatures.IsEmpty() )
		{
			s.Format(_T("Additional unrecognized features found.\n\n%s\nDo you want to keep them in your Features file?\n(Yes - keeps, No - clears & cannot be undone)"),
				m_sUnknownFeatures);
			if ( AfxMessageBox(s, MB_ICONQUESTION|MB_YESNO) == IDNO )
			{
				m_sUnknownFeatures = _T("");
			}
			else
			{
				f.Write(m_sUnknownFeatures, m_sUnknownFeatures.GetLength());
			}
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

BOOL RAFeaturesPage::ReadFeatures(CString sFeaturesFile)
{
	// TRUE if successfully read, FALSE otherwise
	BOOL fRet = TRUE;

	TRY
	{
		CString sCompleteFile;
		sCompleteFile = ReadEntireFile(sFeaturesFile);
		if ( sCompleteFile.IsEmpty() )
		{
			AfxThrowUserException();
		}

		// clear out all the existing values
		ClearFeatures();
		// now process the file
		/*
		Search for #define
		when found, look at the previous 2 chars
			if they are //, then we ignore the #define line and move on
			if they are a space, tab, \r\n, then we process the define statement
		process the #define
			grab the chars between spaces and save the text
			if the text requires a parameter, then read the parameter in
		*/
		int pos = 0;
		int npos = 0;
		CString sTokenString;
		sTokenString.LoadString(IDS_NEWLINE);
		CString sWhiteSpace;
		sWhiteSpace.LoadString(IDS_WHITESPACE);
		CString sCRLF;
		sCRLF.LoadString(IDS_CRLF);
		CString token;
		CString token2;
		token = sCompleteFile.Tokenize(sTokenString, pos);
		while ( token != _T("") )
		{
			// process token
			token.TrimLeft(sWhiteSpace);
			token.TrimRight(sCRLF);
			// split the line up into spaces if it begins with #define
			if ( token.Left(7) == _T("#define") )
			{
				token = token.Mid(7);
				// have a define line
				npos = 0;
				int count = 0;
				CString ptoken = _T("");
				token2 = token.Tokenize(sWhiteSpace, npos);
				while ( token2 != _T("") )
				{
					TRACE("t:  '%s'\n", token2);
					count++;
					if ( count == 1 )
					{
						ProcessFeature(token2);
						ptoken = token2;
					} else 
					{
						if ( count == 2 )
						{
							ProcessFeature(ptoken, token2);
						}
					}
					token2 = token.Tokenize(sWhiteSpace, npos);
				}
			}
			token = sCompleteFile.Tokenize(sTokenString, pos);
		}

		UpdateData(FALSE);
	}
	CATCH_ALL(e)
	{
		CString sBuffer;
		TCHAR szMsg[255];
		e->GetErrorMessage(szMsg, 255);
		sBuffer.Format(_T("Unable to read Features file:\n\n"));
		sBuffer += szMsg;
		//AfxMessageBox(sBuffer, MB_ICONINFORMATION);
		TRACE("%s", sBuffer);
		fRet = FALSE;
	}
	END_CATCH_ALL

	return fRet;
}

void RAFeaturesPage::ShowUnknownFeatures()
{
	CString s;
	if ( m_sUnknownFeatures.IsEmpty() )
	{
		s = _T("No unknown Features.");
	}
	else
	{
		s.Format(_T("Additional unrecognized features found:\n\n%s"), m_sUnknownFeatures);
	}
	AfxMessageBox(s, MB_ICONINFORMATION|MB_OK);
}

void RAFeaturesPage::ProcessFeature(CString sFeature, CString sValue /*= _T("")*/)
{
	if ( sFeature == _T("__REEFANGEL_FEATURES__") )
	{
		// skip this because it's for the features file itself
	} else if ( sFeature == _T("DisplayImages") )
	{
		g_Features.fDisplayImages = TRUE;
	} else if ( sFeature == _T("WavemakerSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("DosingPumpSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("DosingPumpIntervalSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("OverheatSetup") )
	{
		g_Features.fOverheatSetup = TRUE;
	} else if ( sFeature == _T("DateTimeSetup") )
	{
		g_Features.fDateTimeSetup = TRUE;
	} else if ( sFeature == _T("VersionMenu") )
	{
		g_Features.fVersionMenu = TRUE;
	} else if ( sFeature == _T("ATOSetup") ) 
	{
		// controlled via the installed device
	} else if ( sFeature == _T("RemoveAllLights") )
	{
		g_Features.fRemoveAllLights = TRUE;
	} else if ( sFeature == _T("MetalHalideSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("StandardLightSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("DirectTempSensor") )
	{
		g_Features.fDirectTempSensor = TRUE;
	} else if ( sFeature == _T("SaveRelayState") )
	{
		g_Features.fSaveRelayState = TRUE;
	} else if ( sFeature == _T("wifi") )
	{
		g_Features.fWifi = TRUE;
	} else if ( sFeature == _T("DisplayLEDPWM") )
	{
		g_Features.fDisplayLEDPWM = TRUE;
	} else if ( (sFeature == _T("PWMEXPANSION")) ||
				(sFeature == _T("PWMExpansion")) ||		// old style
				(sFeature == _T("PWMExpansionRelay")) ) // old style
	{
		g_Features.fPWMExpansion = TRUE;
	} else if ( sFeature == _T("SingleATOSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("COLORS_PDE") )
	{
		g_Features.fColorsPDE = TRUE;
	} else if ( sFeature == _T("RelayExp") )
	{
		g_Features.fExpansionModule = TRUE;
		g_Features.iInstalledExpansionModules = 1;
	} else if ( sFeature == _T("InstalledRelayExpansionModules") )
	{
		g_Features.iInstalledExpansionModules = atoi(sValue);
	} else if ( sFeature == _T("CUSTOM_MAIN") )
	{
		g_Features.fCustomMain = TRUE;
	} else if ( sFeature == _T("SIMPLE_MENU") )
	{
		g_Features.fSimpleMenu = TRUE;
	} else if ( sFeature == _T("CUSTOM_MENU") )
	{
		g_Features.fCustomMenu = TRUE;
	} else if ( sFeature == _T("CUSTOM_MENU_ENTRIES") )
	{
		g_Features.iCustomMenuEntries = atoi(sValue);
	} else if ( (sFeature == _T("FONT_8x8")) ||
				(sFeature == _T("FONT_8x16")) ||
				(sFeature == _T("FONT_12x16")) ||
				(sFeature == _T("NUMBERS_8x8")) ||
				(sFeature == _T("NUMBERS_8x16")) ||
				(sFeature == _T("NUMBERS_12x16")) ||
				(sFeature == _T("NUMBERS_16x16")) ||
				(sFeature == _T("WDT_FORCE")) || 
				(sFeature == _T("SALINITYEXPANSION")) ||
				(sFeature == _T("RFEXPANSION")) || 
				(sFeature == _T("__PLUS_SPECIAL_WIFI__")) )
	{
		// add the unknown feature to the list
		CString s;
		s.Format(_T("#define %s\r\n"), sFeature.GetBuffer());
		m_sUnknownFeatures += s;
	} else if ( sFeature == _T("ENABLE_EXCEED_FLAGS") )
	{
		g_Features.fExceedFlags = TRUE;
	} else if ( sFeature == _T("ENABLE_ATO_LOGGING") )
	{
		g_Features.fAtoLogging = TRUE;
	} else if ( sFeature == _T("WDT") )
	{
		g_Features.fWDT = TRUE;
	}
}

void RAFeaturesPage::ClearFeatures()
{
	g_Features.fDisplayImages = FALSE;
	g_Features.fSetupExtras = FALSE;
	g_Features.fOverheatSetup = FALSE;
	g_Features.fDateTimeSetup = FALSE;
	g_Features.fVersionMenu = FALSE;
	g_Features.fDirectTempSensor = FALSE;
	g_Features.fDisplayLEDPWM = FALSE;
	g_Features.fWifi = FALSE;
	g_Features.fRemoveAllLights = FALSE;
	g_Features.fSaveRelayState = FALSE;
	g_Features.fExpansionModule = FALSE;
	g_Features.fDosingIntervalSetup = FALSE;
	g_Features.fWDT = FALSE;
	g_Features.fCustomMenu = FALSE;
	g_Features.fSimpleMenu = FALSE;
	g_Features.fPWMExpansion = FALSE;
	g_Features.fCustomMain = FALSE;
	g_Features.fColorsPDE = FALSE;
	g_Features.fAtoLogging = FALSE;
	g_Features.fExceedFlags = FALSE;
	g_Features.iCustomMenuEntries = 1;
	g_Features.iInstalledExpansionModules = 0;
}

void RAFeaturesPage::OnTvnSelchangedFeaturesTree(NMHDR * /*pNMHDR*/, LRESULT *pResult)
{
	HTREEITEM i = m_tree.GetSelectedItem();
	DWORD index = (DWORD)m_tree.GetItemData(i);
	TRACE("Desc:  %s, %d\n", m_efd[index].sDefine, m_efd[index].uID);
	if ( m_efd[index].uID == 0 )
	{
		ClearDescription();
	}
	else 
	{
		SetDescription(m_efd[index].uID);
	}

	*pResult = 0;
}
