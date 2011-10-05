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
	DDX_Check(pDX, IDC_FEATURES_CK_DISPLAY_IMAGES, m_bDisplayImages);
	DDX_Check(pDX, IDC_FEATURES_CK_SETUP_EXTRAS, m_bSetupExtras);
	DDX_Check(pDX, IDC_FEATURES_CK_OVERHEAT_SETUP, m_bOverheatSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_DATE_TIME_SETUP, m_bDateTimeSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_VERSION_MENU, m_bVersionMenu);
	DDX_Check(pDX, IDC_FEATURES_CK_DIRECT_TEMP_SENSOR, m_bDirectTempSensor);
	DDX_Check(pDX, IDC_FEATURES_CK_DISPLAY_LED_PWM, m_bDisplayLEDPWM);
	DDX_Check(pDX, IDC_FEATURES_CK_WIFI, m_bWifi);
	//DDX_Check(pDX, IDC_FEATURES_CK_ALTERNATE_FONT, m_bAlternateFont);
	DDX_Check(pDX, IDC_FEATURES_CK_REMOVE_ALL_LIGHTS, m_bRemoveAllLights);
	DDX_Check(pDX, IDC_FEATURES_CK_SAVE_RELAY_STATE, m_bSaveRelayState);
	DDX_Check(pDX, IDC_FEATURES_CK_EXPANSION_MODULE, m_bExpansionModule);
	DDX_Check(pDX, IDC_FEATURES_CK_DOSINGINTERVAL_SETUP, m_bDosingIntervalSetup);
	DDX_Check(pDX, IDC_FEATURES_CK_ENABLE_ATO_LOGGING, m_bAtoLogging);
	DDX_Check(pDX, IDC_FEATURES_CK_ENABLE_EXCEED_FLAG, m_bExceedFlags);
	DDX_Check(pDX, IDC_FEATURES_CK_WDT, m_bWDT);
	DDX_Check(pDX, IDC_FEATURES_CK_CUSTOM_MENU, m_bCustomMenu);
	DDX_Check(pDX, IDC_FEATURES_CK_SIMPLE_MENU, m_bSimpleMenu);
	DDX_Check(pDX, IDC_FEATURES_CK_CUSTOM_MAIN, m_bCustomMain);
	DDX_Check(pDX, IDC_FEATURES_CK_COLORS_PDE, m_bColorsPDE);
	DDX_Check(pDX, IDC_FEATURES_CK_PWMEXPANSION, m_bPWMExpansion);
	DDX_Text(pDX, IDC_EDIT_ENTRIES, m_iCustomMenuEntries);
	DDV_MinMaxInt(pDX, m_iCustomMenuEntries, MENU_MIN, MENU_MAX);
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
	//ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_ALTERNATE_FONT, &RAFeaturesPage::OnBnHotItemChangeCkAlternateFont)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SAVE_RELAY_STATE, &RAFeaturesPage::OnBnHotItemChangeCkSaveRelayState)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_REMOVE_ALL_LIGHTS, &RAFeaturesPage::OnBnHotItemChangeCkRemoveAllLights)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_EXPANSION_MODULE, &RAFeaturesPage::OnBnHotItemChangeCkExpansionModule)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_DOSINGINTERVAL_SETUP, &RAFeaturesPage::OnBnHotItemChangeCkDosingIntervalSetup)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_ENABLE_ATO_LOGGING, &RAFeaturesPage::OnBnHotItemChangeCkAtoLogging)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_ENABLE_EXCEED_FLAG, &RAFeaturesPage::OnBnHotItemChangeCkExceedFlag)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_WDT, &RAFeaturesPage::OnBnHotItemChangeCkWdt)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_CUSTOM_MENU, &RAFeaturesPage::OnBnHotItemChangeCkCustomMenu)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_SIMPLE_MENU, &RAFeaturesPage::OnBnHotItemChangeCkSimpleMenu)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_CUSTOM_MAIN, &RAFeaturesPage::OnBnHotItemChangeCkCustomMain)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_COLORS_PDE, &RAFeaturesPage::OnBnHotItemChangeCkColorsPde)
	ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_FEATURES_CK_PWMEXPANSION, &RAFeaturesPage::OnBnHotItemChangeCkPwmExpansion)
END_MESSAGE_MAP()


// RAFeaturesPage message handlers

BOOL RAFeaturesPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	// disable the alternate font check box
	//GetDlgItem(IDC_FEATURES_CK_ALTERNATE_FONT)->ShowWindow(SW_HIDE);
	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ENTRIES);
	pSpin->SetBuddy(GetDlgItem(IDC_EDIT_ENTRIES));
	pSpin->SetRange32(1, 9);

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

void RAFeaturesPage::OnBnHotItemChangeCkAtoLogging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_ATOLOGGING);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkExceedFlag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_EXCEEDFLAG);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkWdt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_WDT);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkCustomMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_CUSTOMMENU);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkSimpleMenu(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_SIMPLEMENU);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkCustomMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_CUSTOMMAIN);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkColorsPde(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_COLORSPDE);
	}
	else if ( pHotItem->dwFlags & HICF_LEAVING )
	{
		ClearDescription();
	}
	*pResult = 0;
}

void RAFeaturesPage::OnBnHotItemChangeCkPwmExpansion(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	if ( pHotItem->dwFlags & HICF_ENTERING )
	{
		SetDescription(IDS_FEATURES_PWMEXPANSION);
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
	m_bWifi = AfxGetApp()->GetProfileInt(s, _T("Wifi"), TRUE);
	m_bAlternateFont = AfxGetApp()->GetProfileInt(s, _T("AlternateFont"), FALSE);
	m_bRemoveAllLights = AfxGetApp()->GetProfileInt(s, _T("RemoveAllLights"), FALSE);
	m_bSaveRelayState = AfxGetApp()->GetProfileInt(s, _T("SaveRelayState"), FALSE);
	m_bExpansionModule = AfxGetApp()->GetProfileInt(s, _T("ExpansionModule"), FALSE);
	m_bDosingIntervalSetup = AfxGetApp()->GetProfileInt(s, _T("DosingIntervalSetup"), FALSE);
	m_bWDT = AfxGetApp()->GetProfileInt(s, _T("Watchdog"), FALSE);
	m_bCustomMenu = AfxGetApp()->GetProfileInt(s, _T("CustomMenu"), FALSE);
	m_iCustomMenuEntries = AfxGetApp()->GetProfileInt(s, _T("CustomMenuEntries"), MENU_DEFAULT);
	m_bSimpleMenu = AfxGetApp()->GetProfileInt(s, _T("SimpleMenu"), TRUE);
	m_bPWMExpansion = AfxGetApp()->GetProfileInt(s, _T("PWMExpansion"), FALSE);
	m_bCustomMain = AfxGetApp()->GetProfileInt(s, _T("CustomMain"), FALSE);
	m_bColorsPDE = AfxGetApp()->GetProfileInt(s, _T("ColorsPDE"), FALSE);
	m_bAtoLogging = AfxGetApp()->GetProfileInt(s, _T("ATOLogging"), FALSE);
	m_bExceedFlags = AfxGetApp()->GetProfileInt(s, _T("ExceedFlags"), FALSE);
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
	AfxGetApp()->WriteProfileInt(s, _T("Watchdog"), fs.fWDT);
	AfxGetApp()->WriteProfileInt(s, _T("CustomMenu"), fs.fCustomMenu);
	AfxGetApp()->WriteProfileInt(s, _T("CustomMenuEntries"), fs.iCustomMenuEntries);
	AfxGetApp()->WriteProfileInt(s, _T("SimpleMenu"), fs.fSimpleMenu);
	AfxGetApp()->WriteProfileInt(s, _T("PWMExpansion"), fs.fPWMExpansion);
	AfxGetApp()->WriteProfileInt(s, _T("CustomMain"), fs.fCustomMain);
	AfxGetApp()->WriteProfileInt(s, _T("ColorsPDE"), fs.fColorsPDE);
	AfxGetApp()->WriteProfileInt(s, _T("ATOLogging"), fs.fAtoLogging);
	AfxGetApp()->WriteProfileInt(s, _T("ExceedFlags"), fs.fExceedFlags);
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
	m_bWifi = TRUE;
	m_bAlternateFont = FALSE;
	m_bRemoveAllLights = FALSE;
	m_bSaveRelayState = FALSE;
	m_bExpansionModule = FALSE;
	m_iInstalledExpansionModules = 0;
	m_bDosingIntervalSetup = FALSE;
	m_bWDT = FALSE;
	m_bCustomMenu = FALSE;
	m_iCustomMenuEntries = MENU_DEFAULT;
	m_bSimpleMenu = TRUE;
	m_bPWMExpansion = FALSE;
	m_bCustomMain = FALSE;
	m_bColorsPDE = FALSE;
	m_bAtoLogging = FALSE;
	m_bExceedFlags = FALSE;
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
	fs.fWDT = m_bWDT;
	fs.fCustomMenu = m_bCustomMenu;
	fs.iCustomMenuEntries = m_iCustomMenuEntries;
	fs.fSimpleMenu = m_bSimpleMenu;
	fs.fPWMExpansion = m_bPWMExpansion;
	fs.fCustomMain = m_bCustomMain;
	fs.fColorsPDE = m_bColorsPDE;
	fs.fAtoLogging = m_bAtoLogging;
	fs.fExceedFlags = m_bExceedFlags;

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
		CFile f;
		if ( ! f.Open(sFeaturesFile, CFile::modeRead | CFile::shareDenyWrite) )
		{
			TRACE("Invalid file:  %s\n", sFeaturesFile);
			return FALSE;
		}
		CString sCompleteFile = _T("");
		DWORD dwRead;
		char buf[1024];
		do
		{
			dwRead = f.Read(buf, 1024);
			sCompleteFile.Append(buf, dwRead);
		} while ( dwRead > 0 );
		f.Close();

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
		CString sTokenString = _T("\n");
		CString sWhiteSpace = _T("\t ");
		CString token;
		CString token2;
		token = sCompleteFile.Tokenize(sTokenString, pos);
		while ( token != _T("") )
		{
			// process token
			token.TrimLeft(sWhiteSpace);
			token.TrimRight(_T("\r\n"));
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
		m_bDisplayImages = TRUE;
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
		m_bOverheatSetup = TRUE;
	} else if ( sFeature == _T("DateTimeSetup") )
	{
		m_bDateTimeSetup = TRUE;
	} else if ( sFeature == _T("VersionMenu") )
	{
		m_bVersionMenu = TRUE;
	} else if ( sFeature == _T("ATOSetup") ) 
	{
		// controlled via the installed device
	} else if ( sFeature == _T("RemoveAllLights") )
	{
		m_bRemoveAllLights = TRUE;
	} else if ( sFeature == _T("MetalHalideSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("StandardLightSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("DirectTempSensor") )
	{
		m_bDirectTempSensor = TRUE;
	} else if ( sFeature == _T("SaveRelayState") )
	{
		m_bSaveRelayState = TRUE;
	} else if ( sFeature == _T("wifi") )
	{
		m_bWifi = TRUE;
	} else if ( sFeature == _T("DisplayLEDPWM") )
	{
		m_bDisplayLEDPWM = TRUE;
	} else if ( (sFeature == _T("PWMEXPANSION")) ||
				(sFeature == _T("PWMExpansion")) ||		// old style
				(sFeature == _T("PWMExpansionRelay")) ) // old style
	{
		m_bPWMExpansion = TRUE;
	} else if ( sFeature == _T("SingleATOSetup") )
	{
		// controlled via the installed device
	} else if ( sFeature == _T("COLORS_PDE") )
	{
		m_bColorsPDE = TRUE;
	} else if ( sFeature == _T("RelayExp") )
	{
		m_bExpansionModule = TRUE;
		m_iInstalledExpansionModules = 1;
	} else if ( sFeature == _T("InstalledRelayExpansionModules") )
	{
		m_iInstalledExpansionModules = atoi(sValue);
	} else if ( sFeature == _T("CUSTOM_MAIN") )
	{
		m_bCustomMain = TRUE;
	} else if ( sFeature == _T("SIMPLE_MENU") )
	{
		m_bSimpleMenu = TRUE;
	} else if ( sFeature == _T("CUSTOM_MENU") )
	{
		m_bCustomMenu = TRUE;
	} else if ( sFeature == _T("CUSTOM_MENU_ENTRIES") )
	{
		m_iCustomMenuEntries = atoi(sValue);
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
		m_bExceedFlags = TRUE;
	} else if ( sFeature == _T("ENABLE_ATO_LOGGING") )
	{
		m_bAtoLogging = TRUE;
	} else if ( sFeature == _T("WDT") )
	{
		m_bWDT = TRUE;
	}
}

void RAFeaturesPage::ClearFeatures()
{
	m_bDisplayImages = FALSE;
	m_bSetupExtras = FALSE;
	m_bOverheatSetup = FALSE;
	m_bDateTimeSetup = FALSE;
	m_bVersionMenu = FALSE;
	m_bDirectTempSensor = FALSE;
	m_bDisplayLEDPWM = FALSE;
	m_bWifi = FALSE;
	m_bAlternateFont = FALSE;
	m_bRemoveAllLights = FALSE;
	m_bSaveRelayState = FALSE;
	m_bExpansionModule = FALSE;
	m_bDosingIntervalSetup = FALSE;
	m_bWDT = FALSE;
	m_bCustomMenu = FALSE;
	m_bSimpleMenu = FALSE;
	m_bPWMExpansion = FALSE;
	m_bCustomMain = FALSE;
	m_bColorsPDE = FALSE;
	m_bAtoLogging = FALSE;
	m_bExceedFlags = FALSE;
	m_iCustomMenuEntries = 1;
	m_iInstalledExpansionModules = 0;
}
