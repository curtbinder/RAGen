// RAInternalMemoryPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAInternalMemoryPage.h"
#include "InternalMemoryDefaults.h"
#include "cb_FileVersion.h"
#include "GlobalVars.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// RAInternalMemoryPage dialog

RAInternalMemoryPage::RAInternalMemoryPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAInternalMemoryPage::IDD, pParent)
{
	fUse12Hour = TRUE;
	fDegF = TRUE;
	m_iATOLowIntervalTemp = 0;
	m_iATOHighIntervalTemp = 0;
	m_iWM1IntervalTemp = 0;
	m_iWM2IntervalTemp = 0;
}

void RAInternalMemoryPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_MH_DELAY, m_iMHDelay);
	DDV_MinMaxInt(pDX, m_iMHDelay, BYTE_MIN, BYTE_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_WM1_INTERVAL, m_iWM1Interval);
	DDV_MinMaxInt(pDX, m_iWM1Interval, WM_MIN, WM_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_WM2_INTERVAL, m_iWM2Interval);
	DDV_MinMaxInt(pDX, m_iWM2Interval, WM_MIN, WM_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_ACTINIC, m_iActinic);
	DDV_MinMaxInt(pDX, m_iActinic, PWM_MIN, PWM_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_DAYLIGHT, m_iDaylight);
	DDV_MinMaxInt(pDX, m_iDaylight, PWM_MIN, PWM_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_DP1_RUNTIME, m_iDP1RunTime);
	DDV_MinMaxInt(pDX, m_iDP1RunTime, BYTE_MIN, BYTE_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_DP2_RUNTIME, m_iDP2RunTime);
	DDV_MinMaxInt(pDX, m_iDP2RunTime, BYTE_MIN, BYTE_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_FEEDING, m_iFeeding);
	DDV_MinMaxInt(pDX, m_iFeeding, TIMEOUTS_MIN, TIMEOUTS_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_LCD, m_iLCD);
	DDV_MinMaxInt(pDX, m_iLCD, TIMEOUTS_MIN, TIMEOUTS_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_PH7, m_iPH7);
	DDV_MinMaxInt(pDX, m_iPH7, PH_MIN, PH_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_PH10, m_iPH10);
	DDV_MinMaxInt(pDX, m_iPH10, PH_MIN, PH_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_ATO_LOW_TIMEOUT, m_iATOLowTimeout);
	DDV_MinMaxInt(pDX, m_iATOLowTimeout, BYTE_MIN, BYTE_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_ATO_HIGH_TIMEOUT, m_iATOHighTimeout);
	DDV_MinMaxInt(pDX, m_iATOHighTimeout, BYTE_MIN, BYTE_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_ATO_LOW_INTERVAL, m_iATOLowInterval);
	DDV_MinMaxInt(pDX, m_iATOLowInterval, HR_MIN, HR_MAX);
	DDX_Text(pDX, IDC_MEMORY_EDIT_ATO_HIGH_INTERVAL, m_iATOHighInterval);
	DDV_MinMaxInt(pDX, m_iATOHighInterval, HR_MIN, HR_MAX);
}

BEGIN_MESSAGE_MAP(RAInternalMemoryPage, CDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MEMORY_CK_ATO_LOW_INTERVAL, &RAInternalMemoryPage::OnBnClickedCkAtoLowInterval)
	ON_BN_CLICKED(IDC_MEMORY_CK_ATO_HIGH_INTERVAL, &RAInternalMemoryPage::OnBnClickedCkAtoHighInterval)
	ON_BN_CLICKED(IDC_MEMORY_CK_WM1_ALWAYS_ON, &RAInternalMemoryPage::OnBnClickedCkWm1AlwaysOn)
	ON_BN_CLICKED(IDC_MEMORY_CK_WM2_ALWAYS_ON, &RAInternalMemoryPage::OnBnClickedCkWm2AlwaysOn)
END_MESSAGE_MAP()


// RAInternalMemoryPage message handlers

BOOL RAInternalMemoryPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitSpinners();
	InitTimeBoxes();
	InitTempBoxes();
	LoadDefaults();
	UpdateCheckBoxes();
	// Disable the Timeouts & PH stuff by default
	EnableTimeoutsPH(FALSE);
	UpdateData(FALSE);

	return TRUE;
}

void RAInternalMemoryPage::InitSpinners()
{
	// Set the Buddy Controls for the spinners
	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_MH_DELAY);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_MH_DELAY));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_WM1_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_WM1_INTERVAL));
	pSpin->SetRange32(WM_MIN, WM_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_WM2_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_WM2_INTERVAL));
	pSpin->SetRange32(WM_MIN, WM_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_ACTINIC);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_ACTINIC));
	pSpin->SetRange32(PWM_MIN, PWM_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_DAYLIGHT);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_DAYLIGHT));
	pSpin->SetRange32(PWM_MIN, PWM_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_ATO_LOW_TIMEOUT);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_ATO_LOW_TIMEOUT));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_ATO_LOW_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_ATO_LOW_INTERVAL));
	pSpin->SetRange32(HR_MIN, HR_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_ATO_HIGH_TIMEOUT);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_ATO_HIGH_TIMEOUT));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_ATO_HIGH_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_ATO_HIGH_INTERVAL));
	pSpin->SetRange32(HR_MIN, HR_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_DP1_RUNTIME);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_DP1_RUNTIME));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_DP2_RUNTIME);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_DP2_RUNTIME));
	pSpin->SetRange32(BYTE_MIN, BYTE_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_FEEDING);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_FEEDING));
	pSpin->SetRange32(TIMEOUTS_MIN, TIMEOUTS_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_LCD);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_LCD));
	pSpin->SetRange32(TIMEOUTS_MIN, TIMEOUTS_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_PH7);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_PH7));
	pSpin->SetRange32(PH_MIN, PH_MAX);
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_MEMORY_SPIN_PH10);
	pSpin->SetBuddy(GetDlgItem(IDC_MEMORY_EDIT_PH10));
	pSpin->SetRange32(PH_MIN, PH_MAX);
}

void RAInternalMemoryPage::InitTimeBoxes()
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
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_MH_ON);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_MH_OFF);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_STD_ON);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_STD_OFF);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_DP1_ON);
	pTime->SetFormat(sTimeFormat);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_DP2_ON);
	pTime->SetFormat(sTimeFormat);
}

void RAInternalMemoryPage::InitTempBoxes()
{
	CString s;
	char unit;
	double i, lowTemp, highTemp, lowOver, highOver;
	if ( fDegF )
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
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_ON);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_OFF);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_ON);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_OFF);
	for ( i = lowTemp; i <= highTemp; i += 0.1)
	{
		s.Format(_T("%0.1f%c%c"), i, DEG_SYMBOL, unit);
		pHOn->AddString(s);
		pHOff->AddString(s);
		pCOn->AddString(s);
		pCOff->AddString(s);
	}

	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_OVERHEAT);
	for ( i = lowOver; i <= highOver; i += 0.1 )
	{
		s.Format(_T("%0.1f%c%c"), i, DEG_SYMBOL, unit);
		pOverheat->AddString(s);
	}
}

void RAInternalMemoryPage::LoadDefaults()
{
	// set default values
	m_iMHDelay = DEFAULT_MH_DELAY;
	m_iWM1Interval = DEFAULT_WM1_INTERVAL;
	m_iWM2Interval = DEFAULT_WM2_INTERVAL;
	m_iActinic = DEFAULT_ACTINIC;
	m_iDaylight = DEFAULT_DAYLIGHT;
	m_iDP1RunTime = DEFAULT_DP1_RUN_TIME;
	m_iDP2RunTime = DEFAULT_DP2_RUN_TIME;
	m_iFeeding = DEFAULT_FEEDING_TIMER;
	m_iLCD = DEFAULT_LCD_TIMER;
	m_iPH7 = DEFAULT_PH7;
	m_iPH10 = DEFAULT_PH10;
	m_iATOLowTimeout = DEFAULT_ATO_LOW_TIMEOUT;
	m_iATOHighTimeout = DEFAULT_ATO_HIGH_TIMEOUT;
	m_iATOLowInterval = DEFAULT_ATO_LOW_INTERVAL;
	m_iATOHighInterval = DEFAULT_ATO_HIGH_INTERVAL;
	
	CDateTimeCtrl* pTime = NULL;
	CTime t(2010, 1, 1, DEFAULT_MH_ON_HOUR, DEFAULT_MH_ON_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_MH_ON);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_MH_OFF_HOUR, DEFAULT_MH_OFF_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_MH_OFF);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_STD_ON_HOUR, DEFAULT_STD_ON_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_STD_ON);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_STD_OFF_HOUR, DEFAULT_STD_OFF_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_STD_OFF);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_DP1_ON_HOUR, DEFAULT_DP1_ON_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_DP1_ON);
	pTime->SetTime(&t);
	t = CTime(2010, 1, 1, DEFAULT_DP2_ON_HOUR, DEFAULT_DP2_ON_MINUTE, 0);
	pTime = (CDateTimeCtrl*) GetDlgItem(IDC_MEMORY_TIME_DP2_ON);
	pTime->SetTime(&t);

	// Set the drop down menu values
	int hOn, hOff, cOn, cOff, o;
	if ( fDegF )
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
	CComboBox* pHOn = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_ON);
	pHOn->SetCurSel(hOn);
	CComboBox* pHOff = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_OFF);
	pHOff->SetCurSel(hOff);
	CComboBox* pCOn = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_ON);
	pCOn->SetCurSel(cOn);
	CComboBox* pCOff = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_OFF);
	pCOff->SetCurSel(cOff);
	CComboBox* pOverheat = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_OVERHEAT);
	pOverheat->SetCurSel(o);
}

void RAInternalMemoryPage::OnBnClickedCkAtoLowInterval()
{
	UpdateData();
	CButton* pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_ATO_LOW_INTERVAL);
	int ck = pCk->GetCheck();
	if ( ck == BST_CHECKED )
	{
		m_iATOLowIntervalTemp = m_iATOLowInterval;
		GetDlgItem(IDC_MEMORY_EDIT_ATO_LOW_INTERVAL)->EnableWindow(FALSE);
		m_iATOLowInterval = BYTE_MIN;
	}
	else
	{
		GetDlgItem(IDC_MEMORY_EDIT_ATO_LOW_INTERVAL)->EnableWindow();
		if ( m_iATOLowIntervalTemp > (BYTE_MIN+1) )
		{
			m_iATOLowInterval = m_iATOLowIntervalTemp;
		}
		else
		{
			m_iATOLowInterval = (BYTE_MIN+1);
		}
	}
	UpdateData(FALSE);
}

void RAInternalMemoryPage::OnBnClickedCkAtoHighInterval()
{
	UpdateData();
	CButton* pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_ATO_HIGH_INTERVAL);
	int ck = pCk->GetCheck();
	if ( ck == BST_CHECKED )
	{
		m_iATOHighIntervalTemp = m_iATOHighInterval;
		GetDlgItem(IDC_MEMORY_EDIT_ATO_HIGH_INTERVAL)->EnableWindow(FALSE);
		m_iATOHighInterval = BYTE_MIN;
	}
	else
	{
		GetDlgItem(IDC_MEMORY_EDIT_ATO_HIGH_INTERVAL)->EnableWindow();
		if ( m_iATOHighIntervalTemp > (BYTE_MIN+1) )
		{
			m_iATOHighInterval = m_iATOHighIntervalTemp;
		}
		else
		{
			m_iATOHighInterval = (BYTE_MIN+1);
		}
	}
	UpdateData(FALSE);
}

void RAInternalMemoryPage::OnBnClickedCkWm1AlwaysOn()
{
	UpdateData();
	CButton* pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_WM1_ALWAYS_ON);
	int ck = pCk->GetCheck();
	if ( ck == BST_CHECKED )
	{
		m_iWM1IntervalTemp = m_iWM1Interval;
		GetDlgItem(IDC_MEMORY_EDIT_WM1_INTERVAL)->EnableWindow(FALSE);
		m_iWM1Interval = WM_MIN;
	}
	else
	{
		GetDlgItem(IDC_MEMORY_EDIT_WM1_INTERVAL)->EnableWindow();
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

void RAInternalMemoryPage::OnBnClickedCkWm2AlwaysOn()
{
	UpdateData();
	CButton* pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_WM2_ALWAYS_ON);
	int ck = pCk->GetCheck();
	if ( ck == BST_CHECKED )
	{
		m_iWM2IntervalTemp = m_iWM2Interval;
		GetDlgItem(IDC_MEMORY_EDIT_WM2_INTERVAL)->EnableWindow(FALSE);
		m_iWM2Interval = WM_MIN;
	}
	else
	{
		GetDlgItem(IDC_MEMORY_EDIT_WM2_INTERVAL)->EnableWindow();
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

void RAInternalMemoryPage::OnEditTimeoutsPH()
{
	// if enabled, disable & vice versa
	BOOL bEnable = FALSE;

	// submenu 1 is the Edit menu
	CMenu *pMenu = AfxGetApp()->GetMainWnd()->GetMenu()->GetSubMenu(1);
	int count = pMenu->GetMenuItemCount();
	if ( count != -1 )
	{
		CString s;
		CString enable;
		CString disable;
		enable.LoadStringA(IDS_ENABLE_ADVANCED);
		disable.LoadStringA(IDS_DISABLE_ADVANCED);
		for ( int i = 0; i < count; i++ )
		{
			pMenu->GetMenuString(i, s, MF_BYPOSITION);
			if ( s.Compare(disable) == 0 )
			{
				bEnable = FALSE;
				UINT id = pMenu->GetMenuItemID(i);
				pMenu->ModifyMenuA(id, MF_BYCOMMAND, id, enable);
				break;
			}
			if ( s.Compare(enable) == 0 )
			{
				bEnable = TRUE;
				UINT id = pMenu->GetMenuItemID(i);
				pMenu->ModifyMenuA(id, MF_BYCOMMAND, id, disable);
				break;
			}
		}
	}
	EnableTimeoutsPH(bEnable);
}

void RAInternalMemoryPage::OnBnClickedBtnGenerate()
{
	// Generate to local directory initially
	UpdateData();
	if ( WriteValues() )
	{
		AfxGetApp()->GetMainWnd()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), LPARAM(IDS_SUCCESS_MEMORY));
		switch ( iSaveReg )
		{
		case 0:  // always save, no prompt
			SaveValues();
			break;
		case 1:  // prompt to save
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
		//case 2:  // Never save
			break;
		}
	}
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
		sFile.Format(_T("%s\\%s\\"), m_sSketchDirectory, sFilename);
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
		sFile += sFilename + _T(".pde");

		CFileException fe;
		if ( ! f.Open(sFile, CFile::modeCreate | CFile::modeWrite, &fe) )
		{
			// open failed, so throw exception
			AfxThrowFileException(fe.m_cause, fe.m_lOsError, fe.m_strFileName);
		}
		sAutoGenHeader.Format(_T("\
// Autogenerated file by RAGen (v%s), (%s)\r\n\
// %s.pde\r\n\
//\r\n\
// This file sets the default values to the Internal Memory\r\n\
//\r\n"), 
					cb_GetFileVersionString(AfxGetInstanceHandle()),
					t.Format(_T("%m/%d/%Y %H:%M")),
					sFilename);
		f.Write(sAutoGenHeader, sAutoGenHeader.GetLength());
		s = _T("\r\n\r\n\
#include <ReefAngel_Features.h>\r\n\
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
		f.Write(s, s.GetLength());
		s = _T("\
void setup()\r\n\
{\r\n\
    e.lcd_init();\r\n\
    e.lcd_clear(COLOR_WHITE,0,0,132,132);\r\n\
    e.lcd_BacklightOn();\r\n\r\n\
");
		f.Write(s, s.GetLength());
		// write all the settings here
		CDateTimeCtrl* p;
		p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_MH_ON);
		p->GetTime(t);
		s.Format(_T("    InternalMemory.MHOnHour_write(%d);\r\n    InternalMemory.MHOnMinute_write(%d);\r\n"), t.GetHour(), t.GetMinute());
		f.Write(s, s.GetLength());
		p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_MH_OFF);
		p->GetTime(t);
		s.Format(_T("    InternalMemory.MHOffHour_write(%d);\r\n    InternalMemory.MHOffMinute_write(%d);\r\n"), t.GetHour(), t.GetMinute());
		f.Write(s, s.GetLength());
		p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_STD_ON);
		p->GetTime(t);
		s.Format(_T("    InternalMemory.MHDelay_write(%d);\r\n"), m_iMHDelay);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.StdLightsOnHour_write(%d);\r\n    InternalMemory.StdLightsOnMinute_write(%d);\r\n"), t.GetHour(), t.GetMinute());
		f.Write(s, s.GetLength());
		p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_STD_OFF);
		p->GetTime(t);
		s.Format(_T("    InternalMemory.StdLightsOffHour_write(%d);\r\n    InternalMemory.StdLightsOffMinute_write(%d);\r\n"), t.GetHour(), t.GetMinute());
		f.Write(s, s.GetLength());		
		p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_DP1_ON);
		p->GetTime(t);
		s.Format(_T("    InternalMemory.DP1OnHour_write(%d);\r\n    InternalMemory.DP1OnMinute_write(%d);\r\n"), t.GetHour(), t.GetMinute());
		f.Write(s, s.GetLength());
		p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_DP2_ON);
		p->GetTime(t);
		s.Format(_T("    InternalMemory.DP2OnHour_write(%d);\r\n    InternalMemory.DP2OnMinute_write(%d);\r\n"), t.GetHour(), t.GetMinute());
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.DP1Timer_write(%d);\r\n"), m_iDP1RunTime);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.DP2Timer_write(%d);\r\n"), m_iDP2RunTime);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.ATOTimeout_write(%d);\r\n"), m_iATOLowTimeout);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.ATOHighTimeout_write(%d);\r\n"), m_iATOHighTimeout);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.ATOHourInterval_write(%d);\r\n"), m_iATOLowInterval);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.ATOHighHourInterval_write(%d);\r\n"), m_iATOHighInterval);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.FeedingTimer_write(%d);\r\n"), m_iFeeding);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.LCDTimer_write(%d);\r\n"), m_iLCD);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.LEDPWMActinic_write(%d);\r\n"), m_iActinic);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.LEDPWMDaylight_write(%d);\r\n"), m_iDaylight);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.WM1Timer_write(%d);\r\n"), m_iWM1Interval);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.WM2Timer_write(%d);\r\n"), m_iWM2Interval);
		f.Write(s, s.GetLength());
		
		int offset;
		if ( fDegF )
		{
			offset = DEG_F_OFFSET;
		}
		else
		{
			offset = DEG_C_OFFSET;
		}
		CComboBox* pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_ON);
		s.Format(_T("    InternalMemory.HeaterTempOn_write(%d);\r\n"), pC->GetCurSel()+offset);
		f.Write(s, s.GetLength());
		pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_OFF);
		s.Format(_T("    InternalMemory.HeaterTempOff_write(%d);\r\n"), pC->GetCurSel()+offset);
		f.Write(s, s.GetLength());
		pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_ON);
		s.Format(_T("    InternalMemory.ChillerTempOn_write(%d);\r\n"), pC->GetCurSel()+offset);
		f.Write(s, s.GetLength());
		pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_OFF);
		s.Format(_T("    InternalMemory.ChillerTempOff_write(%d);\r\n"), pC->GetCurSel()+offset);
		f.Write(s, s.GetLength());
		if ( fDegF )
		{
			offset = DEG_F_OVERHEAT_OFFSET;
		}
		else
		{
			offset = DEG_C_OVERHEAT_OFFSET;
		}
		pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_OVERHEAT);
		s.Format(_T("    InternalMemory.OverheatTemp_write(%d);\r\n"), pC->GetCurSel()+offset);
		f.Write(s, s.GetLength());
		
		s.Format(_T("    InternalMemory.PHMax_write(%d);\r\n"), m_iPH10);
		f.Write(s, s.GetLength());
		s.Format(_T("    InternalMemory.PHMin_write(%d);\r\n"), m_iPH7);
		f.Write(s, s.GetLength());

		s = _T("\
}\r\n\
\r\n\
void loop()\r\n\
{\r\n\
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
		f.Close();
		bRet = TRUE;
	}
	CATCH_ALL(e)
	{
		CString sBuffer;
		TCHAR szMsg[MAX_PATH];
		e->GetErrorMessage(szMsg, MAX_PATH);
		sBuffer.Format(_T("Unable to generate PDE file:\n\n"));
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
	CComboBox* pC;
	CTime t;
	CDateTimeCtrl* p;
	s.LoadString(IDS_MEMORY_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("MHDelay"), m_iMHDelay);
	AfxGetApp()->WriteProfileInt(s, _T("WM1Interval"), m_iWM1Interval);
	AfxGetApp()->WriteProfileInt(s, _T("WM2Interval"), m_iWM2Interval);
	AfxGetApp()->WriteProfileInt(s, _T("Actinic"), m_iActinic);
	AfxGetApp()->WriteProfileInt(s, _T("Daylight"), m_iDaylight);
	AfxGetApp()->WriteProfileInt(s, _T("DP1RunTime"), m_iDP1RunTime);
	AfxGetApp()->WriteProfileInt(s, _T("DP2RunTime"), m_iDP2RunTime);
	AfxGetApp()->WriteProfileInt(s, _T("Feeding"), m_iFeeding);
	AfxGetApp()->WriteProfileInt(s, _T("LCD"), m_iLCD);
	AfxGetApp()->WriteProfileInt(s, _T("PH7"), m_iPH7);
	AfxGetApp()->WriteProfileInt(s, _T("PH10"), m_iPH10);
	AfxGetApp()->WriteProfileInt(s, _T("ATOLowTimeout"), m_iATOLowTimeout);
	AfxGetApp()->WriteProfileInt(s, _T("ATOHighTimeout"), m_iATOHighTimeout);
	AfxGetApp()->WriteProfileInt(s, _T("ATOLowInterval"), m_iATOLowInterval);
	AfxGetApp()->WriteProfileInt(s, _T("ATOHighInterval"), m_iATOHighInterval);
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_MH_ON);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("MHOnHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("MHOnMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_MH_OFF);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("MHOffHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("MHOffMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_STD_ON);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("STDOnHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("STDOnMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_STD_OFF);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("STDOffHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("STDOffMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_DP1_ON);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("DP1OnHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("DP1OnMinute"), t.GetMinute());
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_DP2_ON);
	p->GetTime(t);
	AfxGetApp()->WriteProfileInt(s, _T("DP2OnHour"), t.GetHour());
	AfxGetApp()->WriteProfileInt(s, _T("DP2OnMinute"), t.GetMinute());
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_ON);
	AfxGetApp()->WriteProfileInt(s, _T("HeaterOnTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_OFF);
	AfxGetApp()->WriteProfileInt(s, _T("HeaterOffTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_ON);
	AfxGetApp()->WriteProfileInt(s, _T("ChillerOnTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_OFF);
	AfxGetApp()->WriteProfileInt(s, _T("ChillerOffTemp"), pC->GetCurSel());
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_OVERHEAT);
	AfxGetApp()->WriteProfileInt(s, _T("OverheatTemp"), pC->GetCurSel());
}

void RAInternalMemoryPage::LoadValues()
{
	CString s;
	CComboBox* pC;
	CTime t;
	CDateTimeCtrl* p;
	int h, m;
	s.LoadString(IDS_MEMORY_TAB);
	m_iMHDelay = AfxGetApp()->GetProfileInt(s, _T("MHDelay"), DEFAULT_MH_DELAY);
	m_iWM1Interval = AfxGetApp()->GetProfileInt(s, _T("WM1Interval"), DEFAULT_WM1_INTERVAL);
	m_iWM2Interval = AfxGetApp()->GetProfileInt(s, _T("WM2Interval"), DEFAULT_WM2_INTERVAL);
	m_iActinic = AfxGetApp()->GetProfileInt(s, _T("Actinic"), DEFAULT_ACTINIC);
	m_iDaylight = AfxGetApp()->GetProfileInt(s, _T("Daylight"), DEFAULT_DAYLIGHT);
	m_iDP1RunTime = AfxGetApp()->GetProfileInt(s, _T("DP1RunTime"), DEFAULT_DP1_RUN_TIME);
	m_iDP2RunTime = AfxGetApp()->GetProfileInt(s, _T("DP2RunTime"), DEFAULT_DP2_RUN_TIME);
	m_iFeeding = AfxGetApp()->GetProfileInt(s, _T("Feeding"), DEFAULT_FEEDING_TIMER);
	m_iLCD = AfxGetApp()->GetProfileInt(s, _T("LCD"), DEFAULT_LCD_TIMER);
	m_iPH7 = AfxGetApp()->GetProfileInt(s, _T("PH7"), DEFAULT_PH7);
	m_iPH10 = AfxGetApp()->GetProfileInt(s, _T("PH10"), DEFAULT_PH10);
	m_iATOLowTimeout = AfxGetApp()->GetProfileInt(s, _T("ATOLowTimeout"), DEFAULT_ATO_LOW_TIMEOUT);
	m_iATOHighTimeout = AfxGetApp()->GetProfileInt(s, _T("ATOHighTimeout"), DEFAULT_ATO_HIGH_TIMEOUT);
	m_iATOLowInterval = AfxGetApp()->GetProfileInt(s, _T("ATOLowInterval"), DEFAULT_ATO_LOW_INTERVAL);
	m_iATOHighInterval = AfxGetApp()->GetProfileInt(s, _T("ATOHighInterval"), DEFAULT_ATO_HIGH_INTERVAL);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_MH_ON);
	h = AfxGetApp()->GetProfileInt(s, _T("MHOnHour"), DEFAULT_MH_ON_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("MHOnMinute"), DEFAULT_MH_ON_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_MH_OFF);
	h = AfxGetApp()->GetProfileInt(s, _T("MHOffHour"), DEFAULT_MH_OFF_HOUR);
	m =	AfxGetApp()->GetProfileInt(s, _T("MHOffMinute"), DEFAULT_MH_OFF_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_STD_ON);
	h = AfxGetApp()->GetProfileInt(s, _T("STDOnHour"), DEFAULT_STD_ON_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("STDOnMinute"), DEFAULT_STD_ON_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_STD_OFF);
	h = AfxGetApp()->GetProfileInt(s, _T("STDOffHour"), DEFAULT_STD_OFF_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("STDOffMinute"), DEFAULT_STD_OFF_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);
	
	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_DP1_ON);
	h = AfxGetApp()->GetProfileInt(s, _T("DP1OnHour"), DEFAULT_DP1_ON_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("DP1OnMinute"), DEFAULT_DP1_ON_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);

	p = (CDateTimeCtrl*)GetDlgItem(IDC_MEMORY_TIME_DP2_ON);
	h = AfxGetApp()->GetProfileInt(s, _T("DP2OnHour"), DEFAULT_DP2_ON_HOUR);
	m = AfxGetApp()->GetProfileInt(s, _T("DP2OnMinute"), DEFAULT_DP2_ON_MINUTE);
	t = CTime(2010, 1, 1, h, m, 0);
	p->SetTime(&t);

	int hOn, hOff, cOn, cOff, o;
	if ( fDegF )
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
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_ON);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("HeaterOnTemp"), hOn));
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_HEATER_OFF);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("HeaterOffTemp"), hOff));
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_ON);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("ChillerOnTemp"), cOn));
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_CHILLER_OFF);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("ChillerOffTemp"), cOff));
	pC = (CComboBox*)GetDlgItem(IDC_MEMORY_CB_OVERHEAT);
	pC->SetCurSel(AfxGetApp()->GetProfileInt(s, _T("OverheatTemp"), o));
}

void RAInternalMemoryPage::EnableTimeoutsPH(BOOL bEnable)
{
	GetDlgItem(IDC_MEMORY_EDIT_FEEDING)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_EDIT_LCD)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_EDIT_PH7)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_EDIT_PH10)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_SPIN_FEEDING)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_SPIN_LCD)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_SPIN_PH7)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_SPIN_PH10)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_STATIC_FEEDING)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_STATIC_LCD)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_STATIC_PH7)->EnableWindow(bEnable);
	GetDlgItem(IDC_MEMORY_STATIC_PH10)->EnableWindow(bEnable);
}

void RAInternalMemoryPage::UpdateCheckBoxes()
{
	BOOL bEnable;
	CButton* pCk;

	pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_ATO_LOW_INTERVAL);
	if ( m_iATOLowInterval == BYTE_MIN )
	{
		pCk->SetCheck(BST_CHECKED);
		bEnable = FALSE;
	}
	else
	{
		pCk->SetCheck(BST_UNCHECKED);
		bEnable = TRUE;
	}
	GetDlgItem(IDC_MEMORY_EDIT_ATO_LOW_INTERVAL)->EnableWindow(bEnable);
	pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_ATO_HIGH_INTERVAL);
	if ( m_iATOHighInterval == BYTE_MIN )
	{
		pCk->SetCheck(BST_CHECKED);
		bEnable = FALSE;
	}
	else
	{
		pCk->SetCheck(BST_UNCHECKED);
		bEnable = TRUE;
	}
	GetDlgItem(IDC_MEMORY_EDIT_ATO_HIGH_INTERVAL)->EnableWindow(bEnable);
	pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_WM1_ALWAYS_ON);
	if ( m_iWM1Interval == WM_MIN )
	{
		pCk->SetCheck(BST_CHECKED);
		bEnable = FALSE;
	}
	else
	{
		pCk->SetCheck(BST_UNCHECKED);
		bEnable = TRUE;
	}
	GetDlgItem(IDC_MEMORY_EDIT_WM1_INTERVAL)->EnableWindow(bEnable);
	pCk = (CButton*)GetDlgItem(IDC_MEMORY_CK_WM2_ALWAYS_ON);
	if ( m_iWM2Interval == WM_MIN )
	{
		pCk->SetCheck(BST_CHECKED);
		bEnable = FALSE;
	}
	else
	{
		pCk->SetCheck(BST_UNCHECKED);
		bEnable = TRUE;
	}
	GetDlgItem(IDC_MEMORY_EDIT_WM2_INTERVAL)->EnableWindow(bEnable);
}

void RAInternalMemoryPage::OnResetAll()
{
	LoadDefaults();
	UpdateCheckBoxes();
	UpdateData(FALSE);
}

void RAInternalMemoryPage::OnResetSaved()
{
	LoadValues();
	UpdateCheckBoxes();
	UpdateData(FALSE);
}