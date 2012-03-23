// RAInternalMemoryPage.cpp : implementation file
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "GlobalVars.h"
#include "RAGen.h"
#include "RAInternalMemoryPage.h"
#include "InternalMemoryDefaults.h"
#include "cb_FileVersion.h"
#include "Controller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// RAInternalMemoryPage dialog
IMPLEMENT_DYNAMIC(RAInternalMemoryPage, CDialog)

RAInternalMemoryPage::RAInternalMemoryPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAInternalMemoryPage::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_iLocationIndex = 0;
}

void RAInternalMemoryPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_MEMORY_CB_LOCATIONS, m_iLocationIndex);
}

BEGIN_MESSAGE_MAP(RAInternalMemoryPage, CDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MEMORY_BTN_GENERATE, &RAInternalMemoryPage::OnBnClickedBtnGenerate)
	ON_BN_CLICKED(IDC_MEMORY_BTN_LAUNCH, &RAInternalMemoryPage::OnBnClickedBtnLaunch)
	ON_CBN_SELCHANGE(IDC_MEMORY_CB_LOCATIONS, &RAInternalMemoryPage::OnCbnSelchangeMemoryCbLocations)
END_MESSAGE_MAP()


// RAInternalMemoryPage message handlers

BOOL RAInternalMemoryPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString s;
	s.LoadString(IDS_MEMORY_TITLE);
	SetDlgItemText(IDC_MEMORY_TITLE, s);
	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_SPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_SPIN));
	InitDefaultsArray();
	LoadDefaults();
	LoadValues();
	InitLocationBox();
	// Hide launch button
	GetDlgItem(IDC_MEMORY_BTN_LAUNCH)->ShowWindow(SW_HIDE);
	SetStatus("");
	UpdateData(FALSE);

	return TRUE;
}

int RAInternalMemoryPage::GetMaxLocations()
{
	int r;
	if ( a_Controller.IsLatestDevVersion() )
	{
		r = MAX_LOCATIONS;
	}
	else
	{
		// libraries 0.8.5.X only go up to RFDuration
		r = RFDURATION+1;
	}
	return r;
}

void RAInternalMemoryPage::InitDefaultsArray()
{
	// set default values
	int o, hn, hf, cn, cf;
	if ( a_Controller.IsCelsius() )
	{
		o = DEFAULT_OVERHEAT_TEMP_C;
		hn = DEFAULT_HEATER_ON_TEMP_C;
		hf = DEFAULT_HEATER_OFF_TEMP_C;
		cn = DEFAULT_CHILLER_ON_TEMP_C;
		cf = DEFAULT_CHILLER_OFF_TEMP_C;
	}
	else
	{
		o = DEFAULT_OVERHEAT_TEMP_F;
		hn = DEFAULT_HEATER_ON_TEMP_F;
		hf = DEFAULT_HEATER_OFF_TEMP_F;
		cn = DEFAULT_CHILLER_ON_TEMP_F;
		cf = DEFAULT_CHILLER_OFF_TEMP_F;
	}
	// defaults
	m_Defaults[MHONHOUR] = DEFAULT_MH_ON_HOUR;
	m_Defaults[MHONMINUTE] = DEFAULT_MH_ON_MINUTE;
	m_Defaults[MHOFFHOUR] = DEFAULT_MH_OFF_HOUR;
	m_Defaults[MHOFFMINUTE] = DEFAULT_MH_OFF_MINUTE;
	m_Defaults[STDLIGHTSONHOUR] = DEFAULT_STD_ON_HOUR;
	m_Defaults[STDLIGHTSONMINUTE] = DEFAULT_STD_ON_MINUTE;
	m_Defaults[STDLIGHTSOFFHOUR] = DEFAULT_STD_OFF_HOUR;
	m_Defaults[STDLIGHTSOFFMINUTE] = DEFAULT_STD_OFF_MINUTE;
	m_Defaults[WM1TIMER] = DEFAULT_WM1_INTERVAL;
	m_Defaults[WM2TIMER] = DEFAULT_WM2_INTERVAL;
	m_Defaults[DP1TIMER] = DEFAULT_DP1_RUN_TIME;
	m_Defaults[DP2TIMER] = DEFAULT_DP2_RUN_TIME;
	m_Defaults[FEEDINGTIMER] = DEFAULT_FEEDING_TIMER;
	m_Defaults[LCDTIMER] = DEFAULT_LCD_TIMER;
	m_Defaults[OVERHEATTEMP] = o;
	m_Defaults[LEDPWMDAYLIGHT] = DEFAULT_DAYLIGHT;
	m_Defaults[LEDPWMACTINIC] = DEFAULT_ACTINIC;
	m_Defaults[HEATERTEMPON] = hn;
	m_Defaults[HEATERTEMPOFF] = hf;
	m_Defaults[CHILLERTEMPON] = cn;
	m_Defaults[CHILLERTEMPOFF] = cf;
	m_Defaults[ATOTIMEOUT] = DEFAULT_ATO_LOW_TIMEOUT;
	m_Defaults[PHMAX] = DEFAULT_PH10;
	m_Defaults[PHMIN] = DEFAULT_PH7;
	m_Defaults[MHDELAY] = DEFAULT_MH_DELAY;
	m_Defaults[DP1ONHOUR] = DEFAULT_DP1_ON_HOUR;
	m_Defaults[DP1ONMINUTE] = DEFAULT_DP1_ON_MINUTE;
	m_Defaults[DP2ONHOUR] = DEFAULT_DP2_ON_HOUR;
	m_Defaults[DP2ONMINUTE] = DEFAULT_DP2_ON_MINUTE;
	m_Defaults[ATOHOURINTERVAL] = DEFAULT_ATO_LOW_INTERVAL;
	m_Defaults[ATOHIGHHOURINTERVAL] = DEFAULT_ATO_HIGH_INTERVAL;
	m_Defaults[ATOHIGHTIMEOUT] = DEFAULT_ATO_HIGH_TIMEOUT;
	m_Defaults[DP1REPEATINTERVAL] = 0;
	m_Defaults[DP2REPEATINTERVAL] = 0;
	m_Defaults[SALMAX] = DEFAULT_SAL_MAX;
	m_Defaults[PWMSLOPESTARTD] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEENDD] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATIOND] = DEFAULT_PWM_DURATION;
	m_Defaults[PWMSLOPESTARTA] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEENDA] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATIONA] = DEFAULT_PWM_DURATION;
	m_Defaults[RFMODE] = 0;
	m_Defaults[RFSPEED] = DEFAULT_RF_SPEED;
	m_Defaults[RFDURATION] = DEFAULT_RF_DURATION;
	m_Defaults[PWMSLOPESTART0] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEEND0] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATION0] = DEFAULT_PWM_DURATION;
	m_Defaults[PWMSLOPESTART1] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEEND1] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATION1] = DEFAULT_PWM_DURATION;
	m_Defaults[PWMSLOPESTART2] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEEND2] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATION2] = DEFAULT_PWM_DURATION;
	m_Defaults[PWMSLOPESTART3] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEEND3] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATION3] = DEFAULT_PWM_DURATION;
	m_Defaults[PWMSLOPESTART4] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEEND4] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATION4] = DEFAULT_PWM_DURATION;
	m_Defaults[PWMSLOPESTART5] = DEFAULT_PWM_START_PERCENT;
	m_Defaults[PWMSLOPEEND5] = DEFAULT_PWM_END_PERCENT;
	m_Defaults[PWMSLOPEDURATION5] = DEFAULT_PWM_DURATION;
}

void RAInternalMemoryPage::InitLocationBox()
{
	int max_locations = GetMaxLocations();

	CComboBox* pLoc = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_LOCATIONS);
	for ( int i = 0; i < max_locations; i++ )
	{
		pLoc->AddString(m_Locations[i].sLabel);
	}
	pLoc->SetCurSel(0);
	ChangeControlRanges(0);
	UpdateValueControls(0);
	EnableValueControls(0);
}

void RAInternalMemoryPage::EnableValueControls(int iLocation)
{
	BOOL fEnable = m_Locations[iLocation].fComboBox;

	// Spin list
	GetDlgItem(IDC_MEMORY_TEXT_SPIN)->EnableWindow(!fEnable);
	GetDlgItem(IDC_MEMORY_EDIT_SPIN)->EnableWindow(!fEnable);
	GetDlgItem(IDC_MEMORY_SPIN_SPIN)->EnableWindow(!fEnable);

	// Combo box list
	GetDlgItem(IDC_MEMORY_TEXT_LIST)->EnableWindow(fEnable);
	GetDlgItem(IDC_MEMORY_CB_LIST)->EnableWindow(fEnable);
}

void RAInternalMemoryPage::UpdateValueControls(int iLocation)
{
	// update the controls to have the values stored
	if ( m_Locations[iLocation].fComboBox )
	{
		CComboBox* p = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_LIST);
		p->SetCurSel(m_Locations[iLocation].value);
	}
	else
	{
		SetDlgItemInt(IDC_MEMORY_EDIT_SPIN, m_Locations[iLocation].value);
	}
}

void RAInternalMemoryPage::ChangeControlRanges(int iLocation)
{
	// change the ranges of the controls based on the memory location
	if ( m_Locations[iLocation].fComboBox )
	{
		// set the values
		CComboBox* p = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_LIST);
		p->ResetContent();
		CString s;
		char unit;
		double i, lowTemp, highTemp; //, lowOver, highOver;
		if ( a_Controller.IsCelsius() )
		{
			unit = 'C';
			if ( iLocation == OVERHEATTEMP )
			{
				lowTemp = DEG_C_LOW_OVERHEAT_TEMP;
				highTemp = DEG_C_HIGH_OVERHEAT_TEMP;
			}
			else
			{
				lowTemp = DEG_C_LOW_TEMP;
				highTemp = DEG_C_HIGH_TEMP;
			}
		}
		else
		{
			unit = 'F';
			if ( iLocation == OVERHEATTEMP )
			{
				lowTemp = DEG_F_LOW_OVERHEAT_TEMP;
				highTemp = DEG_F_HIGH_OVERHEAT_TEMP;
			}
			else
			{
				lowTemp = DEG_F_LOW_TEMP;
				highTemp = DEG_F_HIGH_TEMP;
			}
		}
		double c;
		for ( i = lowTemp, c = 0; i <= highTemp; i += 0.1, c++)
		{
			s.Format(_T("%0.1f%c%c"), i, DEG_SYMBOL, unit);
			p->AddString(s);
		}
		TRACE("Count: %f\n", c);
	}
	else
	{
		CSpinButtonCtrl* pSpin;
		pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_SPIN);
		int min, max;
		switch ( iLocation ) 
		{
		default:
			min = BYTE_MIN;
			max = BYTE_MAX;
			break;
		case RFMODE:
			min = 0;
			max = 9;
			break;
		case DP1REPEATINTERVAL:
		case DP2REPEATINTERVAL:
		case SALMAX:
		case RFDURATION:
			min = 0;
			max = SHRT_MAX;
			break;
		case WM1TIMER:
		case WM2TIMER:
			min = WM_MIN;
			max = WM_MAX;
			break;
		case MHONHOUR:
		case MHOFFHOUR:
		case STDLIGHTSONHOUR:
		case STDLIGHTSOFFHOUR:
		case ATOHOURINTERVAL:
		case ATOHIGHHOURINTERVAL:
			min = HR_MIN;
			max = HR_MAX;
			break;
		case MHONMINUTE:
		case MHOFFMINUTE:
		case STDLIGHTSONMINUTE:
		case STDLIGHTSOFFMINUTE:
			min = MIN_MIN;
			max = MIN_MAX;
			break;
		case LEDPWMDAYLIGHT:
		case LEDPWMACTINIC:
		case PWMSLOPESTARTD:
		case PWMSLOPESTARTA:
		case PWMSLOPESTART0:
		case PWMSLOPESTART1:
		case PWMSLOPESTART2:
		case PWMSLOPESTART3:
		case PWMSLOPESTART4:
		case PWMSLOPESTART5:
		case PWMSLOPEENDD:
		case PWMSLOPEENDA:
		case PWMSLOPEEND0:
		case PWMSLOPEEND1:
		case PWMSLOPEEND2:
		case PWMSLOPEEND3:
		case PWMSLOPEEND4:
		case PWMSLOPEEND5:
		case RFSPEED:
			min = PWM_MIN;
			max = PWM_MAX;
			break;
		case PHMAX:
		case PHMIN:
			min = PH_MIN;
			max = PH_MAX;
			break;
		case FEEDINGTIMER:
		case LCDTIMER:
			min = TIMEOUTS_MIN;
			max = TIMEOUTS_MAX;
			break;
		}
		pSpin->SetRange32(min, max);
	}
}

void RAInternalMemoryPage::SetMemoryLocation(int iLocation, CString sLabel, CString sFunction, int iValue, BOOL fCombo)
{
	m_Locations[iLocation].sLabel = sLabel;
	m_Locations[iLocation].sFunction = sFunction;
	m_Locations[iLocation].value = iValue;
	m_Locations[iLocation].fComboBox = fCombo;
}

void RAInternalMemoryPage::SetMemoryValue(int iLocation, int iValue)
{
	m_Locations[iLocation].value = iValue;
}

void RAInternalMemoryPage::LoadDefaults()
{
	// Initialize the memory
	SetMemoryLocation(MHONHOUR, _T("MH On Hour"), _T("MHOnHour_write"), m_Defaults[MHONHOUR], FALSE);
	SetMemoryLocation(MHONMINUTE, _T("MH On Minute"), _T("MHOnMinute_write"), m_Defaults[MHONMINUTE], FALSE);
	SetMemoryLocation(MHOFFHOUR, _T("MH Off Hour"), _T("MHOffHour_write"), m_Defaults[MHOFFHOUR], FALSE);
	SetMemoryLocation(MHOFFMINUTE, _T("MH Off Minute"), _T("MHOffMinute_write"), m_Defaults[MHOFFMINUTE], FALSE);
	SetMemoryLocation(STDLIGHTSONHOUR, _T("StdLights On Hour"), _T("StdLightsOnHour_write"), m_Defaults[STDLIGHTSONHOUR], FALSE);
	SetMemoryLocation(STDLIGHTSONMINUTE, _T("StdLights On Minute"), _T("StdLightsOnMinute_write"), m_Defaults[STDLIGHTSONMINUTE], FALSE);
	SetMemoryLocation(STDLIGHTSOFFHOUR, _T("StdLights Off Hour"), _T("StdLightsOffHour_write"), m_Defaults[STDLIGHTSOFFHOUR], FALSE);
	SetMemoryLocation(STDLIGHTSOFFMINUTE, _T("StdLights Off Minute"), _T("StdLightsOffMinute_write"), m_Defaults[STDLIGHTSOFFMINUTE], FALSE);
	SetMemoryLocation(WM1TIMER, _T("Wavemaker 1 Timer"), _T("WM1Timer_write"), m_Defaults[WM1TIMER], FALSE);
	SetMemoryLocation(WM2TIMER, _T("Wavemaker 2 Timer"), _T("WM2Timer_write"), m_Defaults[WM2TIMER], FALSE);
	SetMemoryLocation(DP1TIMER, _T("Dosing Pump 1 Timer"), _T("DP1Timer_write"), m_Defaults[DP1TIMER], FALSE);
	SetMemoryLocation(DP2TIMER, _T("Dosing Pump 2 Timer"), _T("DP2Timer_write"), m_Defaults[DP2TIMER], FALSE);
	SetMemoryLocation(FEEDINGTIMER, _T("Feeding Mode Timer"), _T("FeedingTimer_write"), m_Defaults[FEEDINGTIMER], FALSE);
	SetMemoryLocation(LCDTIMER, _T("LCD Timeout"), _T("LCDTimer_write"), m_Defaults[LCDTIMER], FALSE);
	SetMemoryLocation(OVERHEATTEMP, _T("Overheat Temp"), _T("OverheatTemp_write"), m_Defaults[OVERHEATTEMP], TRUE);
	SetMemoryLocation(LEDPWMDAYLIGHT, _T("Daylight PWM Value"), _T("LEDPWMDaylight_write"), m_Defaults[LEDPWMDAYLIGHT], FALSE);
	SetMemoryLocation(LEDPWMACTINIC, _T("Actinic PWM Value"), _T("LEDPWMActinic_write"), m_Defaults[LEDPWMACTINIC], FALSE);
	SetMemoryLocation(HEATERTEMPON, _T("Heater On Temp"), _T("HeaterTempOn_write"), m_Defaults[HEATERTEMPON], TRUE);
	SetMemoryLocation(HEATERTEMPOFF, _T("Heater Off Temp"), _T("HeaterTempOff_write"), m_Defaults[HEATERTEMPOFF], TRUE);
	SetMemoryLocation(CHILLERTEMPON, _T("Chiller On Temp"), _T("ChillerTempOn_write"), m_Defaults[CHILLERTEMPON], TRUE);
	SetMemoryLocation(CHILLERTEMPOFF, _T("Chiller Off Temp"), _T("ChillerTempOff_write"), m_Defaults[CHILLERTEMPOFF], TRUE);
	SetMemoryLocation(ATOTIMEOUT, _T("ATO Timeout"), _T("ATOTimeout_write"), m_Defaults[ATOTIMEOUT], FALSE);
	SetMemoryLocation(PHMAX, _T("PH Max value (PH10)"), _T("PHMax_write"), m_Defaults[PHMAX], FALSE);
	SetMemoryLocation(PHMIN, _T("PH Min value (PH7)"), _T("PHMin_write"), m_Defaults[PHMIN], FALSE);
	SetMemoryLocation(MHDELAY, _T("MH Delay"), _T("MHDelay_write"), m_Defaults[MHDELAY], FALSE);
	SetMemoryLocation(DP1ONHOUR, _T("Dosing Pump 1 On Hour"), _T("DP1OnHour_write"), m_Defaults[DP1ONHOUR], FALSE);
	SetMemoryLocation(DP1ONMINUTE, _T("Dosing Pump 1 On Minute"), _T("DP1OnMinute_write"), m_Defaults[DP1ONMINUTE], FALSE);
	SetMemoryLocation(DP2ONHOUR, _T("Dosing Pump 2 On Hour"), _T("DP2OnHour_write"), m_Defaults[DP2ONHOUR], FALSE);
	SetMemoryLocation(DP2ONMINUTE, _T("Dosing Pump 2 On Minute"), _T("DP2OnMinute_write"), m_Defaults[DP2ONMINUTE], FALSE);
	SetMemoryLocation(ATOHOURINTERVAL, _T("ATO Hour Interval"), _T("ATOHourInterval_write"), m_Defaults[ATOHOURINTERVAL], FALSE);
	SetMemoryLocation(ATOHIGHHOURINTERVAL, _T("ATO High Hour Interval"), _T("ATOHighHourInterval_write"), m_Defaults[ATOHIGHHOURINTERVAL], FALSE);
	SetMemoryLocation(ATOHIGHTIMEOUT, _T("ATO High Timeout"), _T("ATOHighTimeout_write"), m_Defaults[ATOHIGHTIMEOUT], FALSE);
	SetMemoryLocation(DP1REPEATINTERVAL, _T("Dosing Pump 1 Repeat Interval"), _T("DP1RepeatInterval_write"), m_Defaults[DP1REPEATINTERVAL], FALSE);
	SetMemoryLocation(DP2REPEATINTERVAL, _T("Dosing Pump 2 Repeat Interval"), _T("DP2RepeatInterval_write"), m_Defaults[DP2REPEATINTERVAL], FALSE);
	SetMemoryLocation(SALMAX, _T("Salinity Max"), _T("SalMax_write"), m_Defaults[SALMAX], FALSE);
	SetMemoryLocation(PWMSLOPESTARTD, _T("PWM Slope Daylight Start %"), _T("PWMSlopeStartD_write"), m_Defaults[PWMSLOPESTARTD], FALSE);
	SetMemoryLocation(PWMSLOPEENDD, _T("PWM Slope Daylight End %"), _T("PWMSlopeEndD_write"), m_Defaults[PWMSLOPEENDD], FALSE);
	SetMemoryLocation(PWMSLOPEDURATIOND, _T("PWM Slope Daylight Duration"), _T("PWMSlopeDurationD_write"), m_Defaults[PWMSLOPEDURATIOND], FALSE);
	SetMemoryLocation(PWMSLOPESTARTA, _T("PWM Slope Actinic Start %"), _T("PWMSlopeStartA_write"), m_Defaults[PWMSLOPESTARTA], FALSE);
	SetMemoryLocation(PWMSLOPEENDA, _T("PWM Slope Actinic End %"), _T("PWMSlopeEndA_write"), m_Defaults[PWMSLOPEENDA], FALSE);
	SetMemoryLocation(PWMSLOPEDURATIONA, _T("PWM Slope Actinic Duration"), _T("PWMSlopeDurationA_write"), m_Defaults[PWMSLOPEDURATIONA], FALSE);
	SetMemoryLocation(RFMODE, _T("RF Mode"), _T("RFMode_write"), m_Defaults[RFMODE], FALSE);
	SetMemoryLocation(RFSPEED, _T("RF Speed"), _T("RFSpeed_write"), m_Defaults[RFSPEED], FALSE);
	SetMemoryLocation(RFDURATION, _T("RF Duration"), _T("RFDuration_write"), m_Defaults[RFDURATION], FALSE);
	SetMemoryLocation(PWMSLOPESTART0, _T("PWM Slope Exp Ch 0 Start %"), _T("PWMSlopeStart0_write"), m_Defaults[PWMSLOPESTART0], FALSE);
	SetMemoryLocation(PWMSLOPEEND0, _T("PWM Slope Exp Ch 0 End %"), _T("PWMSlopeEnd0_write"), m_Defaults[PWMSLOPEEND0], FALSE);
	SetMemoryLocation(PWMSLOPEDURATION0, _T("PWM Slope Exp Ch 0 Duration"), _T("PWMSlopeDuration0_write"), m_Defaults[PWMSLOPEDURATION0], FALSE);
	SetMemoryLocation(PWMSLOPESTART1, _T("PWM Slope Exp Ch 1 Start %"), _T("PWMSlopeStart1_write"), m_Defaults[PWMSLOPESTART1], FALSE);
	SetMemoryLocation(PWMSLOPEEND1, _T("PWM Slope Exp Ch 1 End %"), _T("PWMSlopeEnd1_write"), m_Defaults[PWMSLOPEEND1], FALSE);
	SetMemoryLocation(PWMSLOPEDURATION1, _T("PWM Slope Exp Ch 1 Duration"), _T("PWMSlopeDuration1_write"), m_Defaults[PWMSLOPEDURATION1], FALSE);
	SetMemoryLocation(PWMSLOPESTART2, _T("PWM Slope Exp Ch 2 Start %"), _T("PWMSlopeStart2_write"), m_Defaults[PWMSLOPESTART2], FALSE);
	SetMemoryLocation(PWMSLOPEEND2, _T("PWM Slope Exp Ch 2 End %"), _T("PWMSlopeEnd2_write"), m_Defaults[PWMSLOPEEND2], FALSE);
	SetMemoryLocation(PWMSLOPEDURATION2, _T("PWM Slope Exp Ch 2 Duration"), _T("PWMSlopeDuration2_write"), m_Defaults[PWMSLOPEDURATION2], FALSE);
	SetMemoryLocation(PWMSLOPESTART3, _T("PWM Slope Exp Ch 3 Start %"), _T("PWMSlopeStart3_write"), m_Defaults[PWMSLOPESTART3], FALSE);
	SetMemoryLocation(PWMSLOPEEND3, _T("PWM Slope Exp Ch 3 End %"), _T("PWMSlopeEnd3_write"), m_Defaults[PWMSLOPEEND3], FALSE);
	SetMemoryLocation(PWMSLOPEDURATION3, _T("PWM Slope Exp Ch 3 Duration"), _T("PWMSlopeDuration3_write"), m_Defaults[PWMSLOPEDURATION3], FALSE);
	SetMemoryLocation(PWMSLOPESTART4, _T("PWM Slope Exp Ch 4 Start %"), _T("PWMSlopeStart4_write"), m_Defaults[PWMSLOPESTART4], FALSE);
	SetMemoryLocation(PWMSLOPEEND4, _T("PWM Slope Exp Ch 4 End %"), _T("PWMSlopeEnd4_write"), m_Defaults[PWMSLOPEEND4], FALSE);
	SetMemoryLocation(PWMSLOPEDURATION4, _T("PWM Slope Exp Ch 4 Duration"), _T("PWMSlopeDuration4_write"), m_Defaults[PWMSLOPEDURATION4], FALSE);
	SetMemoryLocation(PWMSLOPESTART5, _T("PWM Slope Exp Ch 5 Start %"), _T("PWMSlopeStart5_write"), m_Defaults[PWMSLOPESTART5], FALSE);
	SetMemoryLocation(PWMSLOPEEND5, _T("PWM Slope Exp Ch 5 End %"), _T("PWMSlopeEnd5_write"), m_Defaults[PWMSLOPEEND5], FALSE);
	SetMemoryLocation(PWMSLOPEDURATION5, _T("PWM Slope Exp Ch 5 Duration"), _T("PWMSlopeDuration5_write"), m_Defaults[PWMSLOPEDURATION5], FALSE);
}

void RAInternalMemoryPage::OnBnClickedBtnGenerate()
{
	SaveCurrentValue();
	UpdateData();
	if ( WriteValues() )
	{
		SetStatus(IDS_SUCCESS_GENERATE);
		switch ( theApp.iSave )
		{
		case ALWAYS:  // always save, no prompt
			SaveValues();
			break;
		case PROMPT:  // prompt to save
			{
				int iRet = AfxMessageBox(_T("Do you want to save these settings?"),
					MB_ICONINFORMATION | MB_YESNO);
				if ( iRet == IDYES )
				{
					// Save settings
					SaveValues();
				}
			}
			break;
		default:
		//case NEVER:  // Never save
			break;
		}

		if ( theApp.fHasArduinoExe )
		{
			// show launch button only if Arduino is installed
			GetDlgItem(IDC_MEMORY_BTN_LAUNCH)->ShowWindow(SW_SHOW);
		}
	}
}

void RAInternalMemoryPage::OnBnClickedBtnLaunch()
{
	if ( ! theApp.fHasArduinoExe )
	{
		AfxMessageBox(_T("Arduino not installed, unable to launch"));
		return;
	}
	LaunchArduino(sFilename);
}

void RAInternalMemoryPage::OnCbnSelchangeMemoryCbLocations()
{
	SaveCurrentValue();
	UpdateData();

	// update the controls
	ChangeControlRanges(m_iLocationIndex);
	UpdateValueControls(m_iLocationIndex);
	EnableValueControls(m_iLocationIndex);
}

void RAInternalMemoryPage::SaveCurrentValue()
{
	// Store existing value location
	int t;
	if ( m_Locations[m_iLocationIndex].fComboBox )
	{
		// store the currently selected value
		CComboBox* p = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_LIST);
		t = p->GetCurSel();
	}
	else
	{
		t = (int)GetDlgItemInt(IDC_MEMORY_EDIT_SPIN);
	}
	TRACE("Change Locations:  (%d) - %d\n", m_iLocationIndex, t);
	SetMemoryValue(m_iLocationIndex, t);
}

BOOL RAInternalMemoryPage::WriteValues()
{
	BOOL bRet = FALSE;

	TRY
	{
		CString sFile;
		CString s;
		CString sAutoGenHeader;
		int iRet;
		CTime t = CTime::GetCurrentTime();
		CFile f;
		SECURITY_ATTRIBUTES sa;

		sFilename.Format(_T("Memory_%s"), t.Format(_T("%m%d%y_%H%M")));
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = FALSE;
		sFile.Format(_T("%s\\%s\\"), theApp.m_sSketchDirectory, sFilename);
		iRet = SHCreateDirectoryEx(NULL, sFile, &sa);
		if ( iRet != ERROR_SUCCESS )
		{
			DWORD dw = GetLastError();
			if ( (dw != ERROR_FILE_EXISTS) && (dw != ERROR_ALREADY_EXISTS) )
			{
				// An unknown error has occurred
				AfxThrowUserException();
			}
		}
		if ( a_Controller.IsLatestDevVersion() )
		{
			sFileExtension.LoadString(IDS_INO_EXTENSION);
		} else
		{
			sFileExtension.LoadString(IDS_PDE_EXTENSION);
		}
		sFile += sFilename + sFileExtension;

		CFileException fe;
		if ( ! f.Open(sFile, CFile::modeCreate | CFile::modeWrite, &fe) )
		{
			// open failed, so throw exception
			AfxThrowFileException(fe.m_cause, fe.m_lOsError, fe.m_strFileName);
		}
		sAutoGenHeader.Format(_T("\
// Autogenerated file by RAGen (v%s), (%s)\r\n\
// %s%s\r\n\
//\r\n\
// This file sets the default values to the Internal Memory\r\n\
//\r\n"), 
					cb_GetFileVersionString(AfxGetInstanceHandle()),
					t.Format(_T("%m/%d/%Y %H:%M")),
					sFilename, sFileExtension);
		f.Write(sAutoGenHeader, sAutoGenHeader.GetLength());
		s = _T("\r\n\r\n#include <ReefAngel_Features.h>\r\n");
		if ( a_Controller.IsLatestDevVersion() )
		{
			if ( a_Controller.Features.GetFeatureValue(a_Controller.Features.CUSTOM_COLORS) )
			{
				// if the colors PDE is enabled, add these in
				s += _T("\
#include <RA_Colors.h>\r\n\
#include <RA_CustomColors.h>\r\n");
			}
			s += _T("\
#include <Globals.h>\r\n\
#include <Time.h>\r\n\
#include <OneWire.h>\r\n\
#include <RA_NokiaLCD.h>\r\n\
#include <avr/pgmspace.h>\r\n\
#include <InternalEEPROM.h>\r\n\
#include <Wire.h>\r\n\
#include <Memory.h>\r\n\
\r\n\r\n\
RA_NokiaLCD e;\r\n\
\r\n\
");
		} 
		else
		{
			s += _T("\
#include <ReefAngel_Globals.h>\r\n\
#include <Time.h>\r\n\
#include <OneWire.h>\r\n\
#include <Phillips6610LCDInv.h>\r\n\
#include <avr/pgmspace.h>\r\n\
#include <ReefAngel_EEPROM.h>\r\n\
\r\n\r\n\
Phillips6610LCDInv e;\r\n\
\r\n\
");
		}
		f.Write(s, s.GetLength());
		s = _T("\
void setup()\r\n\
{\r\n");
		f.Write(s, s.GetLength());
		if ( a_Controller.IsLatestDevVersion() )
		{
			s = _T("\
    e.Init();\r\n\
    e.Clear(COLOR_WHITE,0,0,132,132);\r\n\
    e.BacklightOn();\r\n\r\n");
		}
		else
		{
			s = _T("\
    e.lcd_init();\r\n\
    e.lcd_clear(COLOR_WHITE,0,0,132,132);\r\n\
    e.lcd_BacklightOn();\r\n\r\n");
		}
		f.Write(s, s.GetLength());
		// write all the settings here

		int max_locations = GetMaxLocations();
		int v;
		int offset;
		for ( int i = 0; i < max_locations; i++ )
		{
			v = m_Locations[i].value;
			if ( m_Locations[i].fComboBox )
			{
				// for temperatures, add in the offset to get the correct value
				if ( i == OVERHEATTEMP )
				{
					if ( a_Controller.IsCelsius() )
					{
						offset = DEG_C_OVERHEAT_OFFSET;
					}
					else
					{
						offset = DEG_F_OVERHEAT_OFFSET;
					}
				}
				else
				{
					if ( a_Controller.IsCelsius() )
					{
						offset = DEG_C_OFFSET;
					}
					else
					{
						offset = DEG_F_OFFSET;
					}
				}
				v += offset;
			}
			s.Format(_T("    InternalMemory.%s(%d);\r\n"), m_Locations[i].sFunction, v);
			f.Write(s, s.GetLength());
		}

		if ( a_Controller.IsLatestDevVersion() )
		{
			s = _T("    InternalMemory.IMCheck_write(0x5241494D);\r\n");
			f.Write(s, s.GetLength());
		}

		s = _T("\
}\r\n\
\r\n\
void loop()\r\n\
{\r\n");
		f.Write(s, s.GetLength());
		if ( a_Controller.IsLatestDevVersion() )
		{
			s = _T("\
    // display success screen\r\n\
    e.DrawText(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*2, \"Internal Memory Set\");\r\n\
    e.DrawText(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*4, \"Now load your\");\r\n\
    e.DrawText(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*5, \"   RA code file\");\r\n\
    delay(5000);\r\n\
}\r\n");
			f.Write(s, s.GetLength());
		}
		else 
		{
			s = _T("\
    // display the values\r\n\
    char buf[128];\r\n\
    sprintf(buf, \"MH %2d:%02d-%2d:%02d,%d\", InternalMemory.MHOnHour_read(), InternalMemory.MHOnMinute_read(),\r\n\
                                         InternalMemory.MHOffHour_read(), InternalMemory.MHOffMinute_read(),\r\n\
                                         InternalMemory.MHDelay_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW, buf);\r\n\
    sprintf(buf, \"Std %2d:%02d-%2d:%02d\", InternalMemory.StdLightsOnHour_read(), InternalMemory.StdLightsOnMinute_read(),\r\n\
                                          InternalMemory.StdLightsOffHour_read(), InternalMemory.StdLightsOffMinute_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*2, buf);\r\n\
    sprintf(buf, \"LED A: %d%% D: %d%%\", InternalMemory.LEDPWMActinic_read(), InternalMemory.LEDPWMDaylight_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*3, buf);\r\n\
    sprintf(buf, \"WM1: %ds\", InternalMemory.WM1Timer_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*4, buf);\r\n\
    sprintf(buf, \"WM2: %ds\", InternalMemory.WM2Timer_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*5, buf);\r\n\
    sprintf(buf, \"F: %ds\", InternalMemory.FeedingTimer_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*6, buf);\r\n\
    sprintf(buf, \"S: %ds\", InternalMemory.LCDTimer_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*7, buf);\r\n\
    sprintf(buf, \"H On: %d -> %d\", InternalMemory.HeaterTempOn_read(), InternalMemory.HeaterTempOff_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*9, buf);\r\n\
    sprintf(buf, \"C On: %d -> %d\", InternalMemory.ChillerTempOn_read(), InternalMemory.ChillerTempOff_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*10, buf);\r\n\
    sprintf(buf, \"PH %d - %d\", InternalMemory.PHMax_read(), InternalMemory.PHMin_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*11, buf);\r\n\
\r\n\
    delay(10000);\r\n\
    e.lcd_clear(COLOR_WHITE,0,0,132,132);\r\n\
\r\n\
    sprintf(buf, \"OH: %dF\", InternalMemory.OverheatTemp_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW, buf);\r\n\
    sprintf(buf, \"ATO L: %ds (%dh)\", InternalMemory.ATOTimeout_read(), InternalMemory.ATOHourInterval_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*2, buf);\r\n\
    sprintf(buf, \"ATO H: %ds (%dh)\", InternalMemory.ATOHighTimeout_read(), InternalMemory.ATOHighHourInterval_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*3, buf);\r\n\
\r\n\
    sprintf(buf, \"DP1: %2d:%02d\", InternalMemory.DP1OnHour_read(), InternalMemory.DP1OnMinute_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*5, buf);\r\n\
    sprintf(buf, \"     %ds\", InternalMemory.DP1Timer_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*6, buf);\r\n\
    sprintf(buf, \"DP2: %2d:%02d\", InternalMemory.DP2OnHour_read(), InternalMemory.DP2OnMinute_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*7, buf);\r\n\
    sprintf(buf, \"     %ds\", InternalMemory.DP2Timer_read());\r\n\
    e.lcd_draw_text(COLOR_BLACK, COLOR_WHITE, MENU_START_COL, MENU_START_ROW*8, buf);\r\n\
\r\n\
    delay(10000);\r\n\
    e.lcd_clear(COLOR_WHITE,0,0,132,132);\r\n\
}\r\n\r\n\
");
			f.Write(s, s.GetLength());
		}
		f.Close();
		bRet = TRUE;
	}
	CATCH_ALL(e)
	{
		CString sBuffer;
		TCHAR szMsg[MAX_PATH];
		e->GetErrorMessage(szMsg, MAX_PATH);
		sBuffer.Format(_T("Unable to generate file:\n\n"));
		sBuffer += szMsg;
		AfxMessageBox(sBuffer, MB_ICONINFORMATION);
		bRet = FALSE;
	}
	END_CATCH_ALL

	return bRet;
}

void RAInternalMemoryPage::SaveValues()
{
	UpdateData();
	CString s;
	s.LoadString(IDS_MEMORY_TAB);
	int max_locations = GetMaxLocations();

	for ( int i = 0; i < max_locations; i++ )
	{
		AfxGetApp()->WriteProfileInt(s, m_Locations[i].sFunction, m_Locations[i].value);
	}
}

void RAInternalMemoryPage::LoadValues()
{
	CString s;
	s.LoadString(IDS_MEMORY_TAB);
	int max_locations = GetMaxLocations();
	int v;

	for ( int i = 0; i < max_locations; i++ )
	{
		v = AfxGetApp()->GetProfileInt(s, m_Locations[i].sFunction, m_Defaults[i]);
		TRACE("%s - %d\n", m_Locations[i].sFunction, v);
		SetMemoryValue(i, v);
	}
}

void RAInternalMemoryPage::SetStatus(UINT id)
{
	CString s;
	s.LoadString(id);
	CString s2;
	s2.Format(s, sFilename, sFileExtension);
	SetStatus(s2);
}

void RAInternalMemoryPage::SetStatus(LPCSTR s)
{
	SetDlgItemText(IDC_MEMORY_STATUS, s);
}
/*
void RAInternalMemoryPage::OnResetAll()
{
	LoadDefaults();
	UpdateData(FALSE);
}

void RAInternalMemoryPage::OnResetSaved()
{
	LoadValues();
	UpdateData(FALSE);
}
*/