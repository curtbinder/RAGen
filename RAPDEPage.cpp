// RAPDEPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAPDEPage.h"
#include "cb_FileVersion.h"


// RAPDEPage dialog

IMPLEMENT_DYNAMIC(RAPDEPage, CDialog)

RAPDEPage::RAPDEPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAPDEPage::IDD, pParent)
{
	fTemp = FALSE;
	fLogging = FALSE;
	LoadDeviceFunctions();
}

RAPDEPage::~RAPDEPage()
{
}

void RAPDEPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_PDE_TEMP_0, fTemp);
	DDX_Check(pDX, IDC_PDE_CK_LOGGING, fLogging);
}

BEGIN_MESSAGE_MAP(RAPDEPage, CDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PDE_PORT_1, &RAPDEPage::OnBnClickedPort1)
	ON_BN_CLICKED(IDC_PDE_PORT_2, &RAPDEPage::OnBnClickedPort2)
	ON_BN_CLICKED(IDC_PDE_PORT_3, &RAPDEPage::OnBnClickedPort3)
	ON_BN_CLICKED(IDC_PDE_PORT_4, &RAPDEPage::OnBnClickedPort4)
	ON_BN_CLICKED(IDC_PDE_PORT_5, &RAPDEPage::OnBnClickedPort5)
	ON_BN_CLICKED(IDC_PDE_PORT_6, &RAPDEPage::OnBnClickedPort6)
	ON_BN_CLICKED(IDC_PDE_PORT_7, &RAPDEPage::OnBnClickedPort7)
	ON_BN_CLICKED(IDC_PDE_PORT_8, &RAPDEPage::OnBnClickedPort8)
	ON_BN_CLICKED(IDC_PDE_CK_WM1, &RAPDEPage::OnBnClickedCkWm1)
	ON_BN_CLICKED(IDC_PDE_CK_WM2, &RAPDEPage::OnBnClickedCkWm2)
	ON_BN_CLICKED(IDC_PDE_CK_DP1, &RAPDEPage::OnBnClickedCkDp1)
	ON_BN_CLICKED(IDC_PDE_CK_DP2, &RAPDEPage::OnBnClickedCkDp2)
	ON_BN_CLICKED(IDC_PDE_CK_DUALATO, &RAPDEPage::OnBnClickedCkDualato)
	ON_BN_CLICKED(IDC_PDE_CK_SINGLEATOLOW, &RAPDEPage::OnBnClickedCkSingleatolow)
	ON_BN_CLICKED(IDC_PDE_CK_SINGLEATOHIGH, &RAPDEPage::OnBnClickedCkSingleatohigh)
	ON_BN_CLICKED(IDC_PDE_CK_ALWAYS_ON, &RAPDEPage::OnBnClickedCkAlwaysOn)
	ON_BN_CLICKED(IDC_PDE_CK_METALHALIDES, &RAPDEPage::OnBnClickedCkMetalhalides)
	ON_BN_CLICKED(IDC_PDE_CK_STDLIGHTS, &RAPDEPage::OnBnClickedCkStdlights)
	ON_BN_CLICKED(IDC_PDE_CK_HEATER, &RAPDEPage::OnBnClickedCkHeater)
	ON_BN_CLICKED(IDC_PDE_CK_CHILLER, &RAPDEPage::OnBnClickedCkChiller)
	ON_BN_CLICKED(IDC_PDE_CK_NOTUSED, &RAPDEPage::OnBnClickedCkNotused)
END_MESSAGE_MAP()


// RAPDEPage message handlers

BOOL RAPDEPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadDefaults();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void RAPDEPage::InitPorts()
{
	bCurrentPort = 1;
	fWM1 = FALSE;
	fWM2 = FALSE;
	fDP1 = FALSE;
	fDP2 = FALSE;
	fDualATO = FALSE;
	fSingleATOLow = FALSE;
	fSingleATOHigh = FALSE;
	// blank out the ports first before we populate them
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		Ports[i] = 0;
	}
}

void RAPDEPage::LoadDeviceFunctions()
{
	int d = IDC_PDE_CK_ALWAYS_ON;
	int i;
	for ( i = 0; i < MAX_DEVICES; i++, d++ )
	{
		Devices[i].id = d;
		switch ( d )
		{
		case IDC_PDE_CK_ALWAYS_ON:
			Devices[i].sRAFunction = _T("Relay.On");
			break;
		case IDC_PDE_CK_METALHALIDES:
			Devices[i].sRAFunction = _T("MHLights");
			break;
		case IDC_PDE_CK_STDLIGHTS:
			Devices[i].sRAFunction = _T("StandardLights");
			break;
		case IDC_PDE_CK_HEATER:
			Devices[i].sRAFunction = _T("StandardHeater");
			break;
		case IDC_PDE_CK_CHILLER:
			Devices[i].sRAFunction = _T("StandardFan");
			break;
		case IDC_PDE_CK_WM1:
			Devices[i].sRAFunction = _T("Wavemaker1");
			break;
		case IDC_PDE_CK_WM2:
			Devices[i].sRAFunction = _T("Wavemaker2");
			break;
		case IDC_PDE_CK_DP1:
			Devices[i].sRAFunction = _T("DosingPump1");
			break;
		case IDC_PDE_CK_DP2:
			Devices[i].sRAFunction = _T("DosingPump2");
			break;
		case IDC_PDE_CK_DUALATO:
			Devices[i].sRAFunction = _T("StandardATO");
			break;
		case IDC_PDE_CK_SINGLEATOLOW:
			Devices[i].sRAFunction = _T("SingleATOLow");
			break;
		case IDC_PDE_CK_SINGLEATOHIGH:
			Devices[i].sRAFunction = _T("SingleATOHigh");
			break;
		default:
		case IDC_PDE_CK_NOTUSED:
			Devices[i].sRAFunction = _T("");
			break;
		}
	}
}

void RAPDEPage::LoadDefaults()
{
	// Load the default values
	InitPorts();
	LoadDefaultPortDevices();
	fTemp = FALSE;  // set to Farenheit
	fLogging = FALSE;  // set to Not Log
	SetPortMode(Feeding, DEFAULT_FEEDINGMODE);
	SetPortMode(WaterChange, DEFAULT_WATERCHANGEMODE);
	SetPortMode(Overheat, DEFAULT_OVERHEAT);
	SetPortMode(LightsOn, DEFAULT_LIGHTSON);
	UpdateData(FALSE);
}

void RAPDEPage::GetPortMode(BYTE Mode, CString &sMode)
{
	// Creates the binary code for adding to the PDE file
	// binary code is stored in sMode
	int i;
	BYTE ports;
	switch ( Mode )
	{
	case Feeding:
		i = IDC_PDE_CK_FEEDING_1;
		ports = FeedingModePorts;
		break;
	case WaterChange:
		i = IDC_PDE_CK_WATER_1;
		ports = WaterChangeModePorts;
		break;
	case Overheat:
		i = IDC_PDE_CK_OVERHEAT_1;
		ports = OverheatPorts;
		break;
	case LightsOn:
		i = IDC_PDE_CK_LIGHTS_1;
		ports = LightsOnPorts;
		break;
	default:
		return;
		break;
	}

	int max = i+8;
	BYTE v = 0;
	CButton *pButton;
	sMode = _T("");
	for (; i < max; i++, v++ )
	{
		pButton = (CButton*)GetDlgItem(i);
		if ( pButton->GetCheck() == BST_CHECKED )
		{
			sMode.Insert(0, _T("1"));
		}
		else
		{
			sMode.Insert(0, _T("0"));
		}
	}
	sMode.Insert(0, _T("B"));
}

void RAPDEPage::SetPortMode(BYTE Mode, BYTE Ports)
{
	switch ( Mode )
	{
	case Feeding:
		FeedingModePorts = Ports;
		break;
	case WaterChange:
		WaterChangeModePorts = Ports;
		break;
	case Overheat:
		OverheatPorts = Ports;
		break;
	case LightsOn:
		LightsOnPorts = Ports;
		break;
	default:
		return;
		break;
	}
	UpdateDisplayPorts(Mode);
}

void RAPDEPage::UpdateDisplayPorts(BYTE Mode)
{
	// Updates the check boxes on the display
	// Only updates the mode passed in
	int i;
	BYTE ports;
	switch ( Mode )
	{
	case Feeding:
		i = IDC_PDE_CK_FEEDING_1;
		ports = FeedingModePorts;
		break;
	case WaterChange:
		i = IDC_PDE_CK_WATER_1;
		ports = WaterChangeModePorts;
		break;
	case Overheat:
		i = IDC_PDE_CK_OVERHEAT_1;
		ports = OverheatPorts;
		break;
	case LightsOn:
		i = IDC_PDE_CK_LIGHTS_1;
		ports = LightsOnPorts;
		break;
	default:
		return;
		break;
	}

	int max = i+8;
	BYTE v = 0;
	CButton *pButton;
	for (; i < max; i++, v++ )
	{
		pButton = (CButton*)GetDlgItem(i);
		if ( ports & (1<<v) )
		{
			pButton->SetCheck(BST_CHECKED);
		}
		else
		{
			pButton->SetCheck(BST_UNCHECKED);
		}
	}
	UpdateData(FALSE);
}

void RAPDEPage::RefreshModePorts()
{
	// Refresh the port variables based on the check boxes
	// Refreshes all the ports, only update before we write the value out since
	// there isn't any variable associated with each checkbox
	
	// loop through the four modes
	int modes[4] = {IDC_PDE_CK_FEEDING_1, IDC_PDE_CK_WATER_1, IDC_PDE_CK_OVERHEAT_1, IDC_PDE_CK_LIGHTS_1};
	int i, j;
	BYTE v, x;
	CButton* p;
	for ( i = 0; i < 4; i++ )
	{
		x = 0;
		for ( j = modes[i], v = 0; j < modes[i]+8; j++, v++ )
		{
			p = (CButton*)GetDlgItem(j);
			if ( p->GetCheck() == BST_CHECKED )
			{
				x += (1<<v);
			}
		}  // for j
		switch ( i )
		{
		case 0:
			FeedingModePorts = x;
			break;
		case 1:
			WaterChangeModePorts = x;
			break;
		case 2:
			OverheatPorts = x;
			break;
		case 3:
			LightsOnPorts = x;
			break;
		}
	}  // for i
}

void RAPDEPage::SetPortDevice(int Port, int Device)
{
	Ports[Port-1] = Device;
	UpdateDisplayDevice(Port);
}

int RAPDEPage::GetPortDevice(int Port)
{
	return Ports[Port-1];
}

void RAPDEPage::UpdateDisplayDevice(int Port)
{
	int device = GetPortDevice(Port);
	ToggleDeviceChecks(device);
	UpdateDeviceAvailability();
}

void RAPDEPage::UpdateDeviceAvailability()
{
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		// Set the device flags ON if we have the device checked
		ToggleDeviceFlag(Ports[i]);
	}

	// Toggle & Enable/Disable devices based on device passed in (which is selected device)
	GetDlgItem(IDC_PDE_CK_WM1)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_WM1, fWM1, fDP1));
	GetDlgItem(IDC_PDE_CK_WM2)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_WM2, fWM2, fDP2));
	GetDlgItem(IDC_PDE_CK_DP1)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_DP1, fDP1, fWM1));
	GetDlgItem(IDC_PDE_CK_DP2)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_DP2, fDP2, fWM2));

	if ( fSingleATOLow || fSingleATOHigh )
	{
		// a single switch is enabled somewhere
		// disable the dual ato device
		GetDlgItem(IDC_PDE_CK_DUALATO)->EnableWindow(FALSE);
		// determine if we need to show them enabled or not
		GetDlgItem(IDC_PDE_CK_SINGLEATOLOW)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_SINGLEATOLOW, fSingleATOLow, fSingleATOLow));
		GetDlgItem(IDC_PDE_CK_SINGLEATOHIGH)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_SINGLEATOHIGH, fSingleATOHigh, fSingleATOHigh));
	}
	else if ( fDualATO )
	{
		// dual switch is enabled somewhere
		// determine if we need to show it enabled or not
		GetDlgItem(IDC_PDE_CK_DUALATO)->EnableWindow(IsDeviceCkEnabled(IDC_PDE_CK_DUALATO, fDualATO, fDualATO));
		// disable the single ato devices
		GetDlgItem(IDC_PDE_CK_SINGLEATOLOW)->EnableWindow(FALSE);
		GetDlgItem(IDC_PDE_CK_SINGLEATOHIGH)->EnableWindow(FALSE);
	}
	else
	{
		// no ato switches enabled
		// enable all the ato devices
		GetDlgItem(IDC_PDE_CK_DUALATO)->EnableWindow();
		GetDlgItem(IDC_PDE_CK_SINGLEATOLOW)->EnableWindow();
		GetDlgItem(IDC_PDE_CK_SINGLEATOHIGH)->EnableWindow();
	}
}

BOOL RAPDEPage::IsDeviceCkEnabled(int Device, BOOL fDevFlag, BOOL fOppDevFlag)
{
	int nCurrentDevice = Ports[bCurrentPort-1];
	BOOL fRet;
	if ( fDevFlag )
	{
		// device enabled
		if ( nCurrentDevice == Device )
		{
			// device enabled on current port
			fRet = TRUE;
		}
		else
		{
			// device enabled elsewhere
			fRet = FALSE;
		}
	}
	else
	{
		// device not enabled
		if ( fOppDevFlag )
		{
			// opposite device enabled
			fRet = FALSE;
		}
		else
		{
			// device not selected and opposite device not enabled
			fRet = TRUE;
		}
	}
	return fRet;
}

void RAPDEPage::ToggleDeviceChecks(int Device)
{
	int i;
	CButton* p;
	for ( i = IDC_PDE_CK_ALWAYS_ON; i <= IDC_PDE_CK_NOTUSED; i++ )
	{
		p = (CButton*)GetDlgItem(i);
		if ( i == Device )
		{
			if ( p->GetCheck() != BST_CHECKED )
			{
				// if not already checked, check it
				p->SetCheck(BST_CHECKED);
				ToggleDeviceFlag(i);
			}
			/*
			else already checked, so don't check it again
			and also don't toggle the flag
			*/
		}
		else
		{
			if ( p->GetCheck() == BST_CHECKED )
			{
				/*
				Uncheck the checked device
				and untoggle it's flag
				*/
				p->SetCheck(BST_UNCHECKED);
				ToggleDeviceFlag(i, FALSE);
			}
			// else it's not checked, so don't do anything
		}
	}  // for i
	// update the check boxes
	UpdateData(FALSE);
}

void RAPDEPage::ToggleDeviceFlag(int Device, BOOL fValue /*= TRUE*/)
{
	switch ( Device )
	{
	case IDC_PDE_CK_WM1:
		fWM1 = fValue;
		break;
	case IDC_PDE_CK_WM2:
		fWM2 = fValue;
		break;
	case IDC_PDE_CK_DP1:
		fDP1 = fValue;
		break;
	case IDC_PDE_CK_DP2:
		fDP2 = fValue;
		break;
	case IDC_PDE_CK_SINGLEATOLOW:
		fSingleATOLow = fValue;
		break;
	case IDC_PDE_CK_SINGLEATOHIGH:
		fSingleATOHigh = fValue;
		break;
	case IDC_PDE_CK_DUALATO:
		fDualATO = fValue;
		break;
	default:
		break;
	}
}

void RAPDEPage::LoadDefaultPortDevices()
{
	SetPortDevice(1, DEFAULT_PORT1_DEVICE);
	SetPortDevice(2, DEFAULT_PORT2_DEVICE);
	SetPortDevice(3, DEFAULT_PORT3_DEVICE);
	SetPortDevice(4, DEFAULT_PORT4_DEVICE);
	SetPortDevice(5, DEFAULT_PORT5_DEVICE);
	SetPortDevice(6, DEFAULT_PORT6_DEVICE);
	SetPortDevice(7, DEFAULT_PORT7_DEVICE);
	SetPortDevice(8, DEFAULT_PORT8_DEVICE);
	SelectPort1();
}

void RAPDEPage::LookupDeviceFunction(int Device, CString &sFunction)
{
	sFunction = _T("");
	for ( int i = 0; i < MAX_DEVICES; i++ )
	{
		if ( Devices[i].id == Device )
		{
			sFunction = Devices[i].sRAFunction;
			break;
		}
	}
}

void RAPDEPage::SaveSettings()
{
	// saves the settings to the registry
	CString s;
	s.LoadStringA(IDS_PDE_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("FeedingModePorts"), FeedingModePorts);
	AfxGetApp()->WriteProfileInt(s, _T("WaterChangeModePorts"), WaterChangeModePorts);
	AfxGetApp()->WriteProfileInt(s, _T("OverheatPorts"), OverheatPorts);
	AfxGetApp()->WriteProfileInt(s, _T("LightsOnPorts"), LightsOnPorts);
	AfxGetApp()->WriteProfileInt(s, _T("Temp"), fTemp);
	AfxGetApp()->WriteProfileInt(s, _T("Logging"), fLogging);
	AfxGetApp()->WriteProfileInt(s, _T("Port1"), Ports[0]);
	AfxGetApp()->WriteProfileInt(s, _T("Port2"), Ports[1]);
	AfxGetApp()->WriteProfileInt(s, _T("Port3"), Ports[2]);
	AfxGetApp()->WriteProfileInt(s, _T("Port4"), Ports[3]);
	AfxGetApp()->WriteProfileInt(s, _T("Port5"), Ports[4]);
	AfxGetApp()->WriteProfileInt(s, _T("Port6"), Ports[5]);
	AfxGetApp()->WriteProfileInt(s, _T("Port7"), Ports[6]);
	AfxGetApp()->WriteProfileInt(s, _T("Port8"), Ports[7]);
}

void RAPDEPage::LoadSettings()
{
	// loads the settings from the registry
	CString s;
	s.LoadStringA(IDS_PDE_TAB);
	SetPortMode(Feeding, (BYTE)AfxGetApp()->GetProfileInt(s, _T("FeedingModePorts"), DEFAULT_FEEDINGMODE));
	SetPortMode(WaterChange, (BYTE)AfxGetApp()->GetProfileInt(s, _T("WaterChangeModePorts"), DEFAULT_WATERCHANGEMODE));
	SetPortMode(Overheat, (BYTE)AfxGetApp()->GetProfileInt(s, _T("OverheatPorts"), DEFAULT_OVERHEAT));
	SetPortMode(LightsOn, (BYTE)AfxGetApp()->GetProfileInt(s, _T("LightsOnPorts"), DEFAULT_LIGHTSON));
	fTemp = AfxGetApp()->GetProfileInt(s, _T("Temp"), FALSE);
	fLogging = AfxGetApp()->GetProfileInt(s, _T("Logging"), FALSE);
	SetPortDevice(1, AfxGetApp()->GetProfileInt(s, _T("Port1"), DEFAULT_PORT1_DEVICE));
	SetPortDevice(2, AfxGetApp()->GetProfileInt(s, _T("Port2"), DEFAULT_PORT2_DEVICE));
	SetPortDevice(3, AfxGetApp()->GetProfileInt(s, _T("Port3"), DEFAULT_PORT3_DEVICE));
	SetPortDevice(4, AfxGetApp()->GetProfileInt(s, _T("Port4"), DEFAULT_PORT4_DEVICE));
	SetPortDevice(5, AfxGetApp()->GetProfileInt(s, _T("Port5"), DEFAULT_PORT5_DEVICE));
	SetPortDevice(6, AfxGetApp()->GetProfileInt(s, _T("Port6"), DEFAULT_PORT6_DEVICE));
	SetPortDevice(7, AfxGetApp()->GetProfileInt(s, _T("Port7"), DEFAULT_PORT7_DEVICE));
	SetPortDevice(8, AfxGetApp()->GetProfileInt(s, _T("Port8"), DEFAULT_PORT8_DEVICE));
	UpdateData(FALSE);
}

void RAPDEPage::SelectPort1()
{
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_PDE_PORT_1, BM_CLICK));
	// uncheck current checked port
	CButton* p;
	int c;
	for ( int i = IDC_PDE_PORT_8; i > IDC_PDE_PORT_1; i-- )
	{
		p = (CButton*)GetDlgItem(i);
		c = p->GetCheck();
		if ( c == BST_CHECKED )
		{
			p->SetCheck(BST_UNCHECKED);
		}
	}
	p = (CButton*)GetDlgItem(IDC_PDE_PORT_1);
	p->SetCheck(BST_CHECKED);
}

BOOL RAPDEPage::WritePDE()
{
	BOOL bRet = FALSE;

	TRY
	{
		//CString sFilename;
		CString sFile;
		CString s;
		CString s1;
		CString sAutoGenHeader;
		CString sTab = _T("    ");
		BOOL fAddExtra = FALSE;
		BOOL fOnce = FALSE;
		int i, iRet;
		CTime t = CTime::GetCurrentTime();
		CFile f;
		SECURITY_ATTRIBUTES sa;

		sFilename.Format(_T("RA_%s"), t.Format(_T("%m%d%y_%H%M")));
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
// This version designed for v0.8.5 Beta 7 or later\r\n"), 
					cb_GetFileVersionString(AfxGetInstanceHandle()),
					t.Format(_T("%m/%d/%Y %H:%M")),
					sFilename);
		f.Write(sAutoGenHeader, sAutoGenHeader.GetLength());
		s = _T("\r\n\r\n\
#include <ReefAngel_Features.h>\r\n\
#include <ReefAngel_Globals.h>\r\n\
#include <Wire.h>\r\n\
#include <OneWire.h>\r\n\
#include <Time.h>\r\n\
#include <DS1307RTC.h>\r\n\
#include <ReefAngel_EEPROM.h>\r\n\
#include <ReefAngel_NokiaLCD.h>\r\n\
#include <ReefAngel_ATO.h>\r\n\
#include <ReefAngel_Joystick.h>\r\n\
#include <ReefAngel_LED.h>\r\n\
#include <ReefAngel_TempSensor.h>\r\n\
#include <ReefAngel_Relay.h>\r\n\
#include <ReefAngel_PWM.h>\r\n\
#include <ReefAngel_Timer.h>\r\n\
#include <ReefAngel_Memory.h>\r\n\
#include <ReefAngel.h>\r\n\
\r\n\
");
		f.Write(s, s.GetLength());
		if ( fLogging )
		{
			s = _T("\
// Timer used to indicate when to dump the parameters\r\n\
ReefAngel_TimerClass ParamTimer;\r\n\
");
			f.Write(s, s.GetLength());
		}
		s = _T("\
\r\n\
void setup()\r\n\
{\r\n\
    ReefAngel.Init();  //Initialize controller\r\n\
");
		f.Write(s, s.GetLength());
		// Set Celsius if needed
		if ( fTemp )
		{
			s = sTab + _T("ReefAngel.SetTemperatureUnit(1);  // set to Celsius Temperature\r\n");
			f.Write(s, s.GetLength());
		}

		if ( fLogging )
		{
			s = _T("\
    // Initialize and start the Parameter timer\r\n\
    ParamTimer.SetInterval(15);  // set interval to 15 seconds\r\n\
    ParamTimer.Start();\r\n\
");
			f.Write(s, s.GetLength());
		}

		// add in an extra line to separate first part between the modes
		s = _T("\r\n");
		f.Write(s, s.GetLength());

		// Toggle Ports, only write if they differ from defaults
		if ( FeedingModePorts != DEFAULT_FEEDINGMODE )
		{
			s = sTab + _T("ReefAngel.FeedingModePorts = ");
			f.Write(s, s.GetLength());
			GetPortMode(Feeding, s);
			s += _T(";\r\n");
			f.Write(s, s.GetLength());
			fAddExtra = TRUE;
		}
		if ( WaterChangeModePorts != DEFAULT_WATERCHANGEMODE )
		{
			s = sTab + _T("ReefAngel.WaterChangePorts = ");
			f.Write(s, s.GetLength());
			GetPortMode(WaterChange, s);
			s += _T(";\r\n");
			f.Write(s, s.GetLength());
			fAddExtra = TRUE;
		}
		if ( OverheatPorts != DEFAULT_OVERHEAT )
		{
			s = sTab + _T("ReefAngel.OverheatShutoffPorts = ");
			f.Write(s, s.GetLength());
			GetPortMode(Overheat, s);
			s += _T(";\r\n");
			f.Write(s, s.GetLength());
			fAddExtra = TRUE;
		}
		if ( LightsOnPorts != DEFAULT_LIGHTSON )
		{
			s = sTab + _T("ReefAngel.LightsOnPorts = ");
			f.Write(s, s.GetLength());
			GetPortMode(LightsOn, s);
			s += _T(";\r\n");
			f.Write(s, s.GetLength());
			fAddExtra = TRUE;
		}

		// Ports that are always on
		for ( i = 0; i < MAX_PORTS; i++ )
		{
			if ( Ports[i] == IDC_PDE_CK_ALWAYS_ON )
			{
				if ( !fOnce )
				{
					if ( fAddExtra )
					{
						s = _T("\r\n");
						f.Write(s, s.GetLength());
					}
					s = sTab + _T("// Ports that are always on\r\n");
					f.Write(s, s.GetLength());
					fOnce = TRUE;
				}
				LookupDeviceFunction(Ports[i], s);
				s1.Format(_T("%sReefAngel.%s(Port%d);\r\n"), sTab, s, i+1);
				f.Write(s1, s1.GetLength());
			}
		}
		s = _T("\
}\r\n\
\r\n\
void loop()\r\n\
{\r\n\
    ReefAngel.ShowInterface();\r\n\
\r\n\
    // Specific functions\r\n\
");
		f.Write(s, s.GetLength());
		// Specific functions
		for ( i = 0; i < MAX_PORTS; i++ )
		{
			if ( (Ports[i] == IDC_PDE_CK_ALWAYS_ON) ||
				 (Ports[i] == IDC_PDE_CK_NOTUSED) )
			{
				// skip the ports that are always on because they were handled above
				// also skip the ports that are not in use
				continue;
			}
			// Now we have a good port to use, so let's use it
			LookupDeviceFunction(Ports[i], s);
			s1.Format(_T("%sReefAngel.%s(Port%d);\r\n"), sTab, s, i+1);
			f.Write(s1, s1.GetLength());
		}

		// Add in the last bit of logging features
		if ( fLogging )
		{
			s = _T("\r\n\
    // Dump Params\r\n\
    if(ParamTimer.IsTriggered())\r\n\
    {\r\n\
        Serial.flush();\r\n\
	    Serial.print(\"<RA><T1>\");\r\n\
        Serial.print(ReefAngel.TempSensor.ReadTemperature(ReefAngel.TempSensor.addrT1));\r\n\
        Serial.print(\"</T1><T2>\");\r\n\
        Serial.print(ReefAngel.TempSensor.ReadTemperature(ReefAngel.TempSensor.addrT2));\r\n\
        Serial.print(\"</T2><T3>\");\r\n\
        Serial.print(ReefAngel.TempSensor.ReadTemperature(ReefAngel.TempSensor.addrT3));\r\n\
        Serial.print(\"</T3><PH>\");\r\n\
        Serial.print(ReefAngel.Params.PH);\r\n\
        Serial.print(\"</PH><R>\");\r\n\
        Serial.print(ReefAngel.Relay.RelayData,DEC);\r\n\
        Serial.print(\"</R><RON>\");\r\n\
        Serial.print(ReefAngel.Relay.RelayMaskOn,DEC);\r\n\
        Serial.print(\"</RON><ROFF>\");\r\n\
        Serial.print(ReefAngel.Relay.RelayMaskOff,DEC);\r\n\
        Serial.print(\"</ROFF></RA>\");\r\n\
        ParamTimer.Start();\r\n\
    }\r\n\
");
			f.Write(s, s.GetLength());
		}
		s = _T("}\r\n\r\n");
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

void RAPDEPage::OnBnClickedBtnGenerate()
{
	UpdateData();
	RefreshModePorts();
	if ( WritePDE() )
	{
		AfxGetApp()->GetMainWnd()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), LPARAM(IDS_SUCCESS_PDE));
		switch ( iSaveReg )
		{
		case 0:  // always save, no prompt
			SaveSettings();
			break;
		case 1:  // prompt to save
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
		//case 2:  // Never save
			break;
		}
	}
}

void RAPDEPage::OnResetAll()
{
	LoadDefaults();
}

void RAPDEPage::OnResetSaved()
{
	LoadSettings();
	SelectPort1();
	UpdateData(FALSE);
}

void RAPDEPage::OnResetPorts()
{
	UpdateData();
	InitPorts();
	LoadDefaultPortDevices();
	UpdateData(FALSE);
}

void RAPDEPage::OnResetTemperature()
{
	UpdateData();
	fTemp = FALSE;
	UpdateData(FALSE);
}

void RAPDEPage::OnResetLogging()
{
	UpdateData();
	fLogging = FALSE;
	UpdateData(FALSE);
}

void RAPDEPage::OnResetFeedingMode()
{
	UpdateData();
	SetPortMode(Feeding, DEFAULT_FEEDINGMODE);
}

void RAPDEPage::OnResetWaterChangeMode()
{
	UpdateData();
	SetPortMode(WaterChange, DEFAULT_WATERCHANGEMODE);
}

void RAPDEPage::OnResetOverheat()
{
	UpdateData();
	SetPortMode(Overheat, DEFAULT_OVERHEAT);
}

void RAPDEPage::OnResetLightsOn()
{
	UpdateData();
	SetPortMode(LightsOn, DEFAULT_LIGHTSON);
}

void RAPDEPage::OnBnClickedPort1()
{
	UpdateData();
	bCurrentPort = 1;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort2()
{
	UpdateData();
	bCurrentPort = 2;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort3()
{
	UpdateData();
	bCurrentPort = 3;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort4()
{
	UpdateData();
	bCurrentPort = 4;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort5()
{
	UpdateData();
	bCurrentPort = 5;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort6()
{
	UpdateData();
	bCurrentPort = 6;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort7()
{
	UpdateData();
	bCurrentPort = 7;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedPort8()
{
	UpdateData();
	bCurrentPort = 8;
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkWm1()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_WM1);
}

void RAPDEPage::OnBnClickedCkWm2()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_WM2);
}

void RAPDEPage::OnBnClickedCkDp1()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_DP1);
}

void RAPDEPage::OnBnClickedCkDp2()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_DP2);
}

void RAPDEPage::OnBnClickedCkDualato()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_DUALATO);
}

void RAPDEPage::OnBnClickedCkSingleatolow()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_SINGLEATOLOW);
}

void RAPDEPage::OnBnClickedCkSingleatohigh()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_SINGLEATOHIGH);
}

void RAPDEPage::OnBnClickedCkAlwaysOn()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_ALWAYS_ON);
}

void RAPDEPage::OnBnClickedCkMetalhalides()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_METALHALIDES);
}

void RAPDEPage::OnBnClickedCkStdlights()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_STDLIGHTS);
}

void RAPDEPage::OnBnClickedCkHeater()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_HEATER);
}

void RAPDEPage::OnBnClickedCkChiller()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_CHILLER);
}

void RAPDEPage::OnBnClickedCkNotused()
{
	UpdateData();
	SetPortDevice(bCurrentPort, IDC_PDE_CK_NOTUSED);
}
