// RAStdPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAStdPage.h"
#include "GlobalVars.h"
#include "InternalMemoryDefaults.h"


// RAStdPage dialog

IMPLEMENT_DYNAMIC(RAStdPage, CDialog)

RAStdPage::RAStdPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAStdPage::IDD, pParent)
{
	iSaveReg = PROMPT_SAVE;
	fUse12Hour = TRUE;
	m_iWM1IntervalTemp = 0;
	m_iWM2IntervalTemp = 0;
	fTemp = FALSE;
	fLogging = FALSE;
}

RAStdPage::~RAStdPage()
{
}

BOOL RAStdPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitSpinners();
	InitTimeBoxes();
	InitTempBoxes();
	LoadDefaults();
	UpdateData(FALSE);

	return TRUE;
}

void RAStdPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STD_EDIT_MH_DELAY, m_iMHDelay);
	DDV_MinMaxInt(pDX, m_iMHDelay, BYTE_MIN, BYTE_MAX);
	DDX_Text(pDX, IDC_STD_EDIT_WM1_INTERVAL, m_iWM1Interval);
	DDV_MinMaxInt(pDX, m_iWM1Interval, WM_MIN, WM_MAX);
	DDX_Text(pDX, IDC_STD_EDIT_WM2_INTERVAL, m_iWM2Interval);
	DDV_MinMaxInt(pDX, m_iWM2Interval, WM_MIN, WM_MAX);
	DDX_Text(pDX, IDC_STD_EDIT_FEEDING, m_iFeeding);
	DDV_MinMaxInt(pDX, m_iFeeding, TIMEOUTS_MIN, TIMEOUTS_MAX);
	DDX_Text(pDX, IDC_STD_EDIT_LCD, m_iLCD);
	DDV_MinMaxInt(pDX, m_iLCD, TIMEOUTS_MIN, TIMEOUTS_MAX);
	DDX_Text(pDX, IDC_STD_EDIT_ATO_TIMEOUT, m_iATOTimeout);
	DDV_MinMaxInt(pDX, m_iATOTimeout, BYTE_MIN, BYTE_MAX);
	DDX_Radio(pDX, IDC_STD_TEMP_0, fTemp);
	DDX_Check(pDX, IDC_STD_CK_LOGGING, fLogging);
}


BEGIN_MESSAGE_MAP(RAStdPage, CDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_STD_CK_WM1_ALWAYS_ON, &RAStdPage::OnBnClickedCkWm1AlwaysOn)
	ON_BN_CLICKED(IDC_STD_CK_WM2_ALWAYS_ON, &RAStdPage::OnBnClickedCkWm2AlwaysOn)
	ON_BN_CLICKED(IDC_STD_CK_ATO, &RAStdPage::OnBnClickedStdCkAto)
	ON_BN_CLICKED(IDC_STD_CK_STD_LIGHTS, &RAStdPage::OnBnClickedStdCkStdLights)
	ON_BN_CLICKED(IDC_STD_CK_MH_LIGHTS, &RAStdPage::OnBnClickedStdCkMhLights)
	ON_BN_CLICKED(IDC_STD_CK_WM2, &RAStdPage::OnBnClickedStdCkWm2)
	ON_BN_CLICKED(IDC_STD_CK_WM1, &RAStdPage::OnBnClickedStdCkWm1)
	ON_BN_CLICKED(IDC_STD_CK_CHILLER, &RAStdPage::OnBnClickedStdCkChiller)
	ON_BN_CLICKED(IDC_STD_CK_HEATER, &RAStdPage::OnBnClickedStdCkHeater)
	ON_BN_CLICKED(IDC_STD_TEMP_0, &RAStdPage::OnBnClickedStdTemp0)
	ON_BN_CLICKED(IDC_STD_TEMP_1, &RAStdPage::OnBnClickedStdTemp1)
END_MESSAGE_MAP()


// RAStdPage message handlers
void RAStdPage::InitSpinners()
{
	// Set the Buddy Controls for the spinners
	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_STD_SPIN_MH_DELAY);
	pSpin->SetBuddy(GetDlgItem(IDC_STD_EDIT_MH_DELAY));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_STD_SPIN_WM1_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_STD_EDIT_WM1_INTERVAL));
	pSpin->SetRange32(WM_MIN, WM_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_STD_SPIN_WM2_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_STD_EDIT_WM2_INTERVAL));
	pSpin->SetRange32(WM_MIN, WM_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_STD_SPIN_FEEDING);
	pSpin->SetBuddy(GetDlgItem(IDC_STD_EDIT_FEEDING));
	pSpin->SetRange32(TIMEOUTS_MIN, TIMEOUTS_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_STD_SPIN_LCD);
	pSpin->SetBuddy(GetDlgItem(IDC_STD_EDIT_LCD));
	pSpin->SetRange32(TIMEOUTS_MIN, TIMEOUTS_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_STD_SPIN_ATO_TIMEOUT);
	pSpin->SetBuddy(GetDlgItem(IDC_STD_EDIT_ATO_TIMEOUT));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
}

void RAStdPage::InitTimeBoxes()
{
	// Set the time format
	CString sTimeFormat;
	if ( fUse12Hour )
	{
		sTimeFormat = _T("h:mm tt");
	}
	else
	{
		sTimeFormat = _T("H:mm");
	}
	CDateTimeCtrl* pTime = NULL;
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_MH_ON);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_MH_OFF);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_STD_ON);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_STD_OFF);
	pTime->SetFormat(sTimeFormat);
}

void RAStdPage::InitTempBoxes()
{
	CString s;
	char unit;
	double i, lowTemp, highTemp, lowOver, highOver;
	if ( ! fTemp )
	{
		unit = 'F';
		lowTemp = DEG_F_LOW_TEMP;
		highTemp = DEG_F_HIGH_TEMP;
		lowOver = DEG_F_LOW_OVERHEAT_TEMP;
		highOver = DEG_F_HIGH_OVERHEAT_TEMP;
	}
	else
	{
		unit = 'C';
		lowTemp = DEG_C_LOW_TEMP;
		highTemp = DEG_C_HIGH_TEMP;
		lowOver = DEG_C_LOW_OVERHEAT_TEMP;
		highOver = DEG_C_HIGH_OVERHEAT_TEMP;
	}
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	// make sure the boxes are empty
	pHOn->ResetContent();
	pHOff->ResetContent();
	pCOn->ResetContent();
	pCOff->ResetContent();
	for ( i = lowTemp; i <= highTemp; i += 0.1)
	{
		s.Format(_T("%0.1f%c%c"), i, DEG_SYMBOL, unit);
		pHOn->AddString(s);
		pHOff->AddString(s);
		pCOn->AddString(s);
		pCOff->AddString(s);
	}

	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	// make sure the box is empty
	pOverheat->ResetContent();
	for ( i = lowOver; i <= highOver; i += 0.1 )
	{
		s.Format(_T("%0.1f%c%c"), i, DEG_SYMBOL, unit);
		pOverheat->AddString(s);
	}
}

void RAStdPage::LoadDefaults()
{
	// set default values
	BOOL fOldTemp = fTemp;
	fTemp = FALSE;  // set to Farenheit
	fLogging = FALSE;  // set to Not Log
	fDisableATO = FALSE;
	fDisableStdLights = FALSE;
	fDisableMHLights = FALSE;
	fDisableWM2 = FALSE;
	fDisableWM1 = FALSE;
	fDisableChiller = FALSE;
	fDisableHeater = FALSE;
	fDisableSump = FALSE;

	m_iMHDelay = DEFAULT_MH_DELAY;
	m_iWM1Interval = DEFAULT_WM1_INTERVAL;
	m_iWM2Interval = DEFAULT_WM2_INTERVAL;
	m_iFeeding = DEFAULT_FEEDING_TIMER;
	m_iLCD = DEFAULT_LCD_TIMER;
	m_iATOTimeout = DEFAULT_ATO_LOW_TIMEOUT;
	
	CDateTimeCtrl* pTime = NULL;
	CTime t(2010, 1, 1, DEFAULT_MH_ON_HOUR, DEFAULT_MH_ON_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_MH_ON);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_MH_OFF_HOUR, DEFAULT_MH_OFF_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_MH_OFF);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_STD_ON_HOUR, DEFAULT_STD_ON_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_STD_ON);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_STD_OFF_HOUR, DEFAULT_STD_OFF_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_STD_TIME_STD_OFF);
	pTime->SetTime(&t);

	// if the temp selection has changed, reset the temp boxes before we select anything
	if ( fOldTemp != fTemp )
	{
		InitTempBoxes();
	}

	// Set the drop down menu values
	int hOn, hOff, cOn, cOff, o;
	if ( ! fTemp )
	{
		hOn = DEFAULT_HEATER_ON_TEMP_F;
		hOff = DEFAULT_HEATER_OFF_TEMP_F;
		cOn = DEFAULT_CHILLER_ON_TEMP_F;
		cOff = DEFAULT_CHILLER_OFF_TEMP_F;
		o = DEFAULT_OVERHEAT_TEMP_F;
	}
	else
	{
		hOn = DEFAULT_HEATER_ON_TEMP_C;
		hOff = DEFAULT_HEATER_OFF_TEMP_C;
		cOn = DEFAULT_CHILLER_ON_TEMP_C;
		cOff = DEFAULT_CHILLER_OFF_TEMP_C;
		o = DEFAULT_OVERHEAT_TEMP_C;
	}
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	pHOn->SetCurSel(hOn);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	pHOff->SetCurSel(hOff);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	pCOn->SetCurSel(cOn);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	pCOff->SetCurSel(cOff);
	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	pOverheat->SetCurSel(o);
}

BOOL RAStdPage::WritePDE()
{
	return FALSE;
}

void RAStdPage::SaveSettings()
{
	UpdateData();
	CString s;
	CComboBox* pC;
	CTime t;
	CDateTimeCtrl* p;
	s.LoadString(IDS_STD_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("Temp"), fTemp);
	AfxGetApp()->WriteProfileInt(s, _T("Logging"), fLogging);
	AfxGetApp()->WriteProfileInt(s, _T("DisableATO"), fDisableATO);
	AfxGetApp()->WriteProfileInt(s, _T("DisableStdLights"), fDisableStdLights);
	AfxGetApp()->WriteProfileInt(s, _T("DisableMHLights"), fDisableMHLights);
	AfxGetApp()->WriteProfileInt(s, _T("DisableWM1"), fDisableWM1);
	AfxGetApp()->WriteProfileInt(s, _T("DisableWM2"), fDisableWM2);
	AfxGetApp()->WriteProfileInt(s, _T("DisableChiller"), fDisableChiller);
	AfxGetApp()->WriteProfileInt(s, _T("DisableHeater"), fDisableHeater);
	AfxGetApp()->WriteProfileInt(s, _T("DisableSump"), fDisableSump);

	AfxGetApp()->WriteProfileInt(s, _T("MHDelay"), m_iMHDelay);
	AfxGetApp()->WriteProfileInt(s, _T("WM1Interval"), m_iWM1Interval);
	AfxGetApp()->WriteProfileInt(s, _T("WM2Interval"), m_iWM2Interval);
	AfxGetApp()->WriteProfileInt(s, _T("Feeding"), m_iFeeding);
	AfxGetApp()->WriteProfileInt(s, _T("LCD"), m_iLCD);
	AfxGetApp()->WriteProfileInt(s, _T("ATOTimeout"), m_iATOTimeout);
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_MH_ON);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("MHOnHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("MHOnMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_MH_OFF);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("MHOffHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("MHOffMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_STD_ON);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("STDOnHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("STDOnMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_STD_OFF);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("STDOffHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("STDOffMinute"), t.GetMinute());
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	AfxGetApp()->WriteProfileInt(s, _T("HeaterOnTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	AfxGetApp()->WriteProfileInt(s, _T("HeaterOffTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	AfxGetApp()->WriteProfileInt(s, _T("ChillerOnTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	AfxGetApp()->WriteProfileInt(s, _T("ChillerOffTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	AfxGetApp()->WriteProfileInt(s, _T("OverheatTemp"), pC->GetCurSel());
}

void RAStdPage::LoadSettings()
{
	CString s;
	CComboBox* pC;
	CTime t;
	CDateTimeCtrl* p;
	int h, m;
	BOOL fOldTemp = fTemp;
	s.LoadString(IDS_STD_TAB);
	fTemp = AfxGetApp()->GetProfileInt(s, _T("Temp"), FALSE);
	fLogging = AfxGetApp()->GetProfileInt(s, _T("Logging"), FALSE);
	fDisableATO = AfxGetApp()->GetProfileInt(s, _T("DisableATO"), FALSE);
	fDisableStdLights = AfxGetApp()->GetProfileInt(s, _T("DisableStdLights"), FALSE);
	fDisableMHLights = AfxGetApp()->GetProfileInt(s, _T("DisableMHLights"), FALSE);
	fDisableWM1 = AfxGetApp()->GetProfileInt(s, _T("DisableWM1"), FALSE);
	fDisableWM2 = AfxGetApp()->GetProfileInt(s, _T("DisableWM2"), FALSE);
	fDisableChiller = AfxGetApp()->GetProfileInt(s, _T("DisableChiller"), FALSE);
	fDisableHeater = AfxGetApp()->GetProfileInt(s, _T("DisableHeater"), FALSE);
	fDisableSump = AfxGetApp()->GetProfileInt(s, _T("DisableSump"), FALSE);

	m_iMHDelay = AfxGetApp()->GetProfileInt(s, _T("MHDelay"), DEFAULT_MH_DELAY);
	m_iWM1Interval = AfxGetApp()->GetProfileInt(s, _T("WM1Interval"), DEFAULT_WM1_INTERVAL);
	m_iWM2Interval = AfxGetApp()->GetProfileInt(s, _T("WM2Interval"), DEFAULT_WM2_INTERVAL);
	m_iFeeding = AfxGetApp()->GetProfileInt(s, _T("Feeding"), DEFAULT_FEEDING_TIMER);
	m_iLCD = AfxGetApp()->GetProfileInt(s, _T("LCD"), DEFAULT_LCD_TIMER);
	m_iATOTimeout = AfxGetApp()->GetProfileInt(s, _T("ATOTimeout"), DEFAULT_ATO_LOW_TIMEOUT);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_MH_ON);
	h = AfxGetApp()->GetProfileInt(s, _T("MHOnHour"), DEFAULT_MH_ON_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("MHOnMinute"), DEFAULT_MH_ON_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_MH_OFF);
	h = AfxGetApp()->GetProfileInt(s, _T("MHOffHour"), DEFAULT_MH_OFF_HOUR);
	m =	AfxGetApp()->GetProfileInt(s, _T("MHOffMinute"), DEFAULT_MH_OFF_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_STD_ON);
	h = AfxGetApp()->GetProfileInt(s, _T("STDOnHour"), DEFAULT_STD_ON_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("STDOnMinute"), DEFAULT_STD_ON_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_STD_TIME_STD_OFF);
	h = AfxGetApp()->GetProfileInt(s, _T("STDOffHour"), DEFAULT_STD_OFF_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("STDOffMinute"), DEFAULT_STD_OFF_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	// if the temp selection has changed, reset the temp boxes before we select anything
	if ( fOldTemp != fTemp )
	{
		InitTempBoxes();
	}
	int hOn, hOff, cOn, cOff, o;
	if ( ! fTemp )
	{
		hOn = DEFAULT_HEATER_ON_TEMP_F;
		hOff = DEFAULT_HEATER_OFF_TEMP_F;
		cOn = DEFAULT_CHILLER_ON_TEMP_F;
		cOff = DEFAULT_CHILLER_OFF_TEMP_F;
		o = DEFAULT_OVERHEAT_TEMP_F;
	}
	else
	{
		hOn = DEFAULT_HEATER_ON_TEMP_C;
		hOff = DEFAULT_HEATER_OFF_TEMP_C;
		cOn = DEFAULT_CHILLER_ON_TEMP_C;
		cOff = DEFAULT_CHILLER_OFF_TEMP_C;
		o = DEFAULT_OVERHEAT_TEMP_C;
	}
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("HeaterOnTemp"), hOn));
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("HeaterOffTemp"), hOff));
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("ChillerOnTemp"), cOn));
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("ChillerOffTemp"), cOff));
	pC = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("OverheatTemp"), o));
}

void RAStdPage::UpdateTemperatureSelections(int hOn, int hOff, int cOn, int cOff, int o)
{
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	// convert the temps
	hOn = ConvertTemp(hOn, !fTemp);
	hOff = ConvertTemp(hOff, !fTemp);
	cOn = ConvertTemp(cOn, !fTemp);
	cOff = ConvertTemp(cOff, !fTemp);
	o = ConvertTemp(o, !fTemp);
	// update the displays
	pHOn->SetCurSel(hOn);
	pHOff->SetCurSel(hOff);
	pCOn->SetCurSel(cOn);
	pCOff->SetCurSel(cOff);
	pOverheat->SetCurSel(o);
}

int RAStdPage::ConvertTemp(int nTempOffset, BOOL fToF /*= TRUE*/)
{
	int iRet;
	float i, t;
	if ( fToF )
	{
		// display farenheit, convert from celcius
		// F = (C * 9 / 5) + 32
		i = (float)nTempOffset + DEG_C_OFFSET;
		i = i / 10;
		t = (i * 9 / 5) + 32;
		t = t * 10;
		iRet = (int)t - DEG_F_OFFSET;
	}
	else
	{
		// display celcuis, convert from farenheit
		// C = (F - 32) * 5 / 9
		i = (float)nTempOffset + DEG_F_OFFSET;
		i = i / 10;
		t = (i - 32) * 5 / 9;
		t = t * 10;
		iRet = (int)t - DEG_C_OFFSET;
	}
	return iRet;
}

void RAStdPage::RestorePorts()
{
	// Restores ports based on the flags, so the flags must be set appropriately before calling this function
	// Restore Ports and enable/disable appropriate windows
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_ATO);
	if ( fDisableATO )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_EDIT_ATO_TIMEOUT)->EnableWindow(!fDisableATO);
	GetDlgItem(IDC_STD_SPIN_ATO_TIMEOUT)->EnableWindow(!fDisableATO);

	pButton = (CButton*)GetDlgItem(IDC_STD_CK_STD_LIGHTS);
	if ( fDisableStdLights )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_TIME_STD_ON)->EnableWindow(!fDisableStdLights);
	GetDlgItem(IDC_STD_TIME_STD_OFF)->EnableWindow(!fDisableStdLights);
	
	pButton = (CButton*)GetDlgItem(IDC_STD_CK_MH_LIGHTS);
	if ( fDisableMHLights )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_TIME_MH_ON)->EnableWindow(!fDisableMHLights);
	GetDlgItem(IDC_STD_TIME_MH_OFF)->EnableWindow(!fDisableMHLights);
	GetDlgItem(IDC_STD_EDIT_MH_DELAY)->EnableWindow(!fDisableMHLights);
	GetDlgItem(IDC_STD_SPIN_MH_DELAY)->EnableWindow(!fDisableMHLights);
	
	pButton = (CButton*)GetDlgItem(IDC_STD_CK_WM2);
	if ( fDisableWM2 )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_EDIT_WM2_INTERVAL)->EnableWindow(!fDisableWM2);
	GetDlgItem(IDC_STD_SPIN_WM2_INTERVAL)->EnableWindow(!fDisableWM2);
	GetDlgItem(IDC_STD_CK_WM2_ALWAYS_ON)->EnableWindow(!fDisableWM2);
	
	pButton = (CButton*)GetDlgItem(IDC_STD_CK_WM1);
	if ( fDisableWM1 )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_EDIT_WM1_INTERVAL)->EnableWindow(!fDisableWM1);
	GetDlgItem(IDC_STD_SPIN_WM1_INTERVAL)->EnableWindow(!fDisableWM1);
	GetDlgItem(IDC_STD_CK_WM1_ALWAYS_ON)->EnableWindow(!fDisableWM1);
	
	pButton = (CButton*)GetDlgItem(IDC_STD_CK_CHILLER);
	if ( fDisableChiller )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_CB_CHILLER_ON)->EnableWindow(!fDisableChiller);
	GetDlgItem(IDC_STD_CB_CHILLER_OFF)->EnableWindow(!fDisableChiller);
	
	pButton = (CButton*)GetDlgItem(IDC_STD_CK_HEATER);
	if ( fDisableHeater )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
	GetDlgItem(IDC_STD_CB_HEATER_ON)->EnableWindow(!fDisableHeater);
	GetDlgItem(IDC_STD_CB_HEATER_OFF)->EnableWindow(!fDisableHeater);

	pButton = (CButton*)GetDlgItem(IDC_STD_CK_SUMP);
	if ( fDisableSump )
	{
		pButton->SetCheck(BST_CHECKED);
	}
	else
	{
		pButton->SetCheck(BST_UNCHECKED);
	}
}

void RAStdPage::OnBnClickedBtnGenerate()
{
	// Generate to local directory initially
	UpdateData();
	if ( WritePDE() )
	{
		AfxGetApp()->GetMainWnd()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), LPARAM(IDS_SUCCESS_STD));
		switch ( iSaveReg )
		{
		case ALWAYS_SAVE:
			SaveSettings();
			break;
		case PROMPT_SAVE:
			{
				int iRet = AfxMessageBox(_T("Do you want to save these settings?"),
					MB_ICONINFORMATION | MB_YESNO);
				if ( iRet == IDYES )
				{
					// Save settings
					SaveSettings();
				}
			}
			break;
		default:
			break;
		}
	}
}

void RAStdPage::OnResetAll()
{
	// Re-Enable all windows & Clear all check boxes
	LoadDefaults();
	RestorePorts();
	UpdateData(FALSE);
}

void RAStdPage::OnResetSaved()
{
	LoadSettings();
	RestorePorts();
	UpdateData(FALSE);
}

void RAStdPage::OnBnClickedCkWm1AlwaysOn()
{
	UpdateData();
	CButton* pCk = (CButton*)GetDlgItem(IDC_STD_CK_WM1_ALWAYS_ON);
	int ck = pCk->GetCheck();
	if ( ck == BST_CHECKED )
	{
		m_iWM1IntervalTemp = m_iWM1Interval;
		GetDlgItem(IDC_STD_EDIT_WM1_INTERVAL)->EnableWindow(FALSE);
		m_iWM1Interval = WM_MIN;
	}
	else
	{
		GetDlgItem(IDC_STD_EDIT_WM1_INTERVAL)->EnableWindow();
		if ( m_iWM1IntervalTemp > WM_MIN )
		{
			m_iWM1Interval = m_iWM1IntervalTemp;
		}
		else
		{
			// if the previous value was the minimum, set to default
			m_iWM1Interval = DEFAULT_WM1_INTERVAL;
		}
	}
	UpdateData(FALSE);
}

void RAStdPage::OnBnClickedCkWm2AlwaysOn()
{
	UpdateData();
	CButton* pCk = (CButton*)GetDlgItem(IDC_STD_CK_WM2_ALWAYS_ON);
	int ck = pCk->GetCheck();
	if ( ck == BST_CHECKED )
	{
		m_iWM2IntervalTemp = m_iWM2Interval;
		GetDlgItem(IDC_STD_EDIT_WM2_INTERVAL)->EnableWindow(FALSE);
		m_iWM2Interval = WM_MIN;
	}
	else
	{
		GetDlgItem(IDC_STD_EDIT_WM2_INTERVAL)->EnableWindow();
		if ( m_iWM2IntervalTemp > WM_MIN )
		{
			m_iWM2Interval = m_iWM2IntervalTemp;
		}
		else
		{
			// if the previous value was the minimum, set to default
			m_iWM2Interval = DEFAULT_WM2_INTERVAL;
		}
	}
	UpdateData(FALSE);
}

void RAStdPage::OnBnClickedStdCkAto()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_ATO);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_EDIT_ATO_TIMEOUT)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_SPIN_ATO_TIMEOUT)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdCkStdLights()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_STD_LIGHTS);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_TIME_STD_ON)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_TIME_STD_OFF)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdCkMhLights()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_MH_LIGHTS);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_TIME_MH_ON)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_TIME_MH_OFF)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_EDIT_MH_DELAY)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_SPIN_MH_DELAY)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdCkWm2()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_WM2);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_EDIT_WM2_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_SPIN_WM2_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_CK_WM2_ALWAYS_ON)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdCkWm1()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_WM1);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_EDIT_WM1_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_SPIN_WM1_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_CK_WM1_ALWAYS_ON)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdCkChiller()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_CHILLER);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_CB_CHILLER_ON)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_CB_CHILLER_OFF)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdCkHeater()
{
	UpdateData();
	BOOL bEnable = TRUE;
	CButton* pButton = (CButton*)GetDlgItem(IDC_STD_CK_HEATER);
	if ( pButton->GetCheck() == BST_CHECKED )
	{
		bEnable = FALSE;
	}
	GetDlgItem(IDC_STD_CB_HEATER_ON)->EnableWindow(bEnable);
	GetDlgItem(IDC_STD_CB_HEATER_OFF)->EnableWindow(bEnable);
}

void RAStdPage::OnBnClickedStdTemp0()
{
	// user clicked Farenheit
	int hOn, hOff, cOn, cOff, o;
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	hOn = pHOn->GetCurSel();
	hOff = pHOff->GetCurSel();
	cOn = pCOn->GetCurSel();
	cOff = pCOff->GetCurSel();
	o = pOverheat->GetCurSel();
	UpdateData();
	// grab current temperatures & convert to farenheit
	InitTempBoxes();
	UpdateTemperatureSelections(hOn, hOff, cOn, cOff, o);
}

void RAStdPage::OnBnClickedStdTemp1()
{
	// user clicked Celcius
	int hOn, hOff, cOn, cOff, o;
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_ON);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_STD_CB_HEATER_OFF);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_ON);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_STD_CB_CHILLER_OFF);
	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_STD_CB_OVERHEAT);
	hOn = pHOn->GetCurSel();
	hOff = pHOff->GetCurSel();
	cOn = pCOn->GetCurSel();
	cOff = pCOff->GetCurSel();
	o = pOverheat->GetCurSel();
	UpdateData();
	// grab current temperatures & convert to celcius
	InitTempBoxes();
	UpdateTemperatureSelections(hOn, hOff, cOn, cOff, o);
}
