// RAPDEPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAPDEPage.h"
#include "cb_FileVersion.h"
#include "GlobalVars.h"
#include "WebBannerDlg.h"
#include "WifiPasswordDlg.h"
#include "InternalMemoryDefaults.h"
#include "Controller.h"


// RAPDEPage dialog

IMPLEMENT_DYNAMIC(RAPDEPage, CDialog)

RAPDEPage::RAPDEPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAPDEPage::IDD, pParent)
{
	fTemp = FALSE;
	fBanner = FALSE;
	fCustomMenu = FALSE;
	iCustomMenuEntries = MENU_DEFAULT;
	fCustomMain = FALSE;
	fColorsPDE = FALSE;
	sFeatureList = _T("");
	fUseDPRepeat = FALSE;
	//LoadDeviceFunctions();
}

RAPDEPage::~RAPDEPage()
{
}

void RAPDEPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_PDE_TEMP_0, fTemp);
	DDX_Check(pDX, IDC_PDE_CK_WEB, fBanner);
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
	ON_BN_CLICKED(IDC_PDE_CK_DELAYON, &RAPDEPage::OnBnClickedCkDelayedOn)
	ON_BN_CLICKED(IDC_PDE_CK_NOTUSED, &RAPDEPage::OnBnClickedCkNotused)
	ON_EN_CHANGE(IDC_PDE_EDIT_DELAY_ON, &RAPDEPage::OnEnChangePdeEditDelayOn)
END_MESSAGE_MAP()


// RAPDEPage message handlers

BOOL RAPDEPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_PDE_SPIN_DELAY_ON);
	pSpin->SetBuddy(GetDlgItem(IDC_PDE_EDIT_DELAY_ON));
	pSpin->SetRange32(1, BYTE_MAX);

	// have to load the defaults first which initializes the boxes
	// and loads in the default values before we can restore the settings
	//LoadDefaults();
	InitPorts();
	LoadSettings();
	SelectPort1();
	fTemp = FALSE;  // set to Fahrenheit
	fBanner = FALSE;  // set to disable web banner
	fCustomMenu = FALSE;
	iCustomMenuEntries = MENU_DEFAULT;
	fCustomMain = FALSE;
	fColorsPDE = FALSE;
	SetPortMode(a_Controller.Relay.Feeding, DEFAULT_FEEDINGMODE);
	SetPortMode(a_Controller.Relay.WaterChange, DEFAULT_WATERCHANGEMODE);
	SetPortMode(a_Controller.Relay.Overheat, DEFAULT_OVERHEAT);
	SetPortMode(a_Controller.Relay.LightsOn, DEFAULT_LIGHTSON);
	UpdateData(FALSE);

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
	//for ( int i = 0; i < MAX_PORTS; i++ )
	//{
	//	Ports[i] = 0;
	//	Delays[i] = DEFAULT_DELAY_MINUTES;
	//}
}
/*
void RAPDEPage::LoadDeviceFunctions()
{
	// TODO make global Controller devices
	int d = IDC_PDE_CK_ALWAYS_ON;
	int i;
	for ( i = 0; i < MAX_DEVICES; i++, d++ )
	{
		Devices[i].id = d;
		switch ( d )
		{
		case IDC_PDE_CK_DELAYON:
			Devices[i].sRAFunction = _T("Relay.DelayedOn");
			break;
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
*/

void RAPDEPage::LoadDefaults()
{
	// Load the default values
	InitPorts();
	LoadDefaultPortDevices();
	fTemp = FALSE;  // set to Fahrenheit
	fBanner = FALSE;  // set to disable web banner
	fCustomMenu = FALSE;
	iCustomMenuEntries = MENU_DEFAULT;
	fCustomMain = FALSE;
	fColorsPDE = FALSE;
	SetPortMode(a_Controller.Relay.Feeding, DEFAULT_FEEDINGMODE);
	SetPortMode(a_Controller.Relay.WaterChange, DEFAULT_WATERCHANGEMODE);
	SetPortMode(a_Controller.Relay.Overheat, DEFAULT_OVERHEAT);
	SetPortMode(a_Controller.Relay.LightsOn, DEFAULT_LIGHTSON);
	UpdateData(FALSE);
}

void RAPDEPage::GetPortMode(BYTE Mode, CString &sMode)
{
	// Creates the binary code for adding to the PDE file
	// binary code is stored in sMode
	int i;
	//BYTE ports;
	switch ( Mode )
	{
	case a_Controller.Relay.Feeding:
		i = IDC_PDE_CK_FEEDING_1;
		//ports = a_Controller.Relay.FeedingModePorts;
		break;
	case a_Controller.Relay.WaterChange:
		i = IDC_PDE_CK_WATER_1;
		//ports = a_Controller.Relay.WaterChangeModePorts;
		break;
	case a_Controller.Relay.Overheat:
		i = IDC_PDE_CK_OVERHEAT_1;
		//ports = a_Controller.Relay.OverheatPorts;
		break;
	case a_Controller.Relay.LightsOn:
		i = IDC_PDE_CK_LIGHTS_1;
		//ports = a_Controller.Relay.LightsOnPorts;
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
	/*
	switch ( Mode )
	{
	case a_Controller.Relay.Feeding:
		FeedingModePorts = Ports;
		break;
	case a_Controller.Relay.WaterChange:
		WaterChangeModePorts = Ports;
		break;
	case a_Controller.Relay.Overheat:
		OverheatPorts = Ports;
		break;
	case a_Controller.Relay.LightsOn:
		LightsOnPorts = Ports;
		break;
	default:
		return;
		break;
	}
	*/
	a_Controller.Relay.SetPortMode(Mode, Ports);
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
	case a_Controller.Relay.Feeding:
		i = IDC_PDE_CK_FEEDING_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.Feeding);
		break;
	case a_Controller.Relay.WaterChange:
		i = IDC_PDE_CK_WATER_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.WaterChange);
		break;
	case a_Controller.Relay.Overheat:
		i = IDC_PDE_CK_OVERHEAT_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.Overheat);
		break;
	case a_Controller.Relay.LightsOn:
		i = IDC_PDE_CK_LIGHTS_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.LightsOn);
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
			//FeedingModePorts = x;
			a_Controller.Relay.SetPortMode(a_Controller.Relay.Feeding, x);
			break;
		case 1:
			///WaterChangeModePorts = x;
			a_Controller.Relay.SetPortMode(a_Controller.Relay.WaterChange, x);
			break;
		case 2:
			//OverheatPorts = x;
			a_Controller.Relay.SetPortMode(a_Controller.Relay.Overheat, x);
			break;
		case 3:
			//LightsOnPorts = x;
			a_Controller.Relay.SetPortMode(a_Controller.Relay.LightsOn, x);
			break;
		}
	}  // for i
}
/*
void RAPDEPage::SetPortDevice(int Port, int Device, int Delay)
{
	Ports[Port-1] = Device;
	if ( Delay > 0 )
	{
		Delays[Port-1] = Delay;
	}
	a_Controller.Relay.SetPortDevice(Port, Device, Delay);
	UpdateDisplayDevice(Port);
}
*/
/*
int RAPDEPage::GetPortDevice(int Port)
{
	return Ports[Port-1];
}
*/

void RAPDEPage::UpdateDisplayDevice(int Port)
{
	int device = a_Controller.Relay.GetPortDevice(Port);
	// always update the delay value on changing ports no matter if it's selected or not
	SetDlgItemInt(IDC_PDE_EDIT_DELAY_ON, a_Controller.Relay.GetPortDelay(Port));
	ToggleDeviceChecks(device);
	UpdateDeviceAvailability();
}

void RAPDEPage::UpdateDeviceAvailability()
{
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		// Set the device flags ON if we have the device checked
		ToggleDeviceFlag(a_Controller.Relay.GetPortDevice(i+1));
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
	int nCurrentDevice = a_Controller.Relay.GetPortDevice(bCurrentPort);
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
	a_Controller.Relay.SetPortDevice(1, DEFAULT_PORT1_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(2, DEFAULT_PORT2_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(3, DEFAULT_PORT3_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(4, DEFAULT_PORT4_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(5, DEFAULT_PORT5_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(6, DEFAULT_PORT6_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(7, DEFAULT_PORT7_DEVICE, DEFAULT_DELAY_MINUTES);
	a_Controller.Relay.SetPortDevice(8, DEFAULT_PORT8_DEVICE, DEFAULT_DELAY_MINUTES);
	SelectPort1();
}

/*
void RAPDEPage::LookupDeviceFunction(int Device, CString &sFunction)
{
	sFunction = _T("");
	for ( int i = 0; i < MAX_DEVICES; i++ )
	{
		if ( Devices[i].id == Device )
		{
			if ( (Device == IDC_PDE_CK_DP1) ||
				 (Device == IDC_PDE_CK_DP2) )
			{
				// For Dosing Pumps, if the user chose to use the Repeat Interval
				// Then let's switch things around and choose the Repeat Interval instead
				// of the standard dosing pump if they chose to use a dosing pump
				if ( fUseDPRepeat )
				{
					if ( Device == IDC_PDE_CK_DP1 )
					{
						sFunction = _T("DosingPumpRepeat1");
					}
					else
					{
						sFunction = _T("DosingPumpRepeat2");
					}
				}
				else
				{
					sFunction = Devices[i].sRAFunction;
				}
			}
			else
			{
				sFunction = Devices[i].sRAFunction;
			}
			break;
		}
	}
}
*/

void RAPDEPage::SaveSettings()
{
	// saves the settings to the registry
	CString s;
	s.LoadStringA(IDS_PDE_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("FeedingModePorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.Feeding));
	AfxGetApp()->WriteProfileInt(s, _T("WaterChangeModePorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.WaterChange));
	AfxGetApp()->WriteProfileInt(s, _T("OverheatPorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.Overheat));
	AfxGetApp()->WriteProfileInt(s, _T("LightsOnPorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.LightsOn));
	AfxGetApp()->WriteProfileInt(s, _T("Temp"), fTemp);
	AfxGetApp()->WriteProfileInt(s, _T("WebBanner"), fBanner);
	AfxGetApp()->WriteProfileInt(s, _T("Port1"), a_Controller.Relay.GetPortDevice(1));
	AfxGetApp()->WriteProfileInt(s, _T("Port2"), a_Controller.Relay.GetPortDevice(2));
	AfxGetApp()->WriteProfileInt(s, _T("Port3"), a_Controller.Relay.GetPortDevice(3));
	AfxGetApp()->WriteProfileInt(s, _T("Port4"), a_Controller.Relay.GetPortDevice(4));
	AfxGetApp()->WriteProfileInt(s, _T("Port5"), a_Controller.Relay.GetPortDevice(5));
	AfxGetApp()->WriteProfileInt(s, _T("Port6"), a_Controller.Relay.GetPortDevice(6));
	AfxGetApp()->WriteProfileInt(s, _T("Port7"), a_Controller.Relay.GetPortDevice(7));
	AfxGetApp()->WriteProfileInt(s, _T("Port8"), a_Controller.Relay.GetPortDevice(8));
	AfxGetApp()->WriteProfileInt(s, _T("Delay1"), a_Controller.Relay.GetPortDelay(1));
	AfxGetApp()->WriteProfileInt(s, _T("Delay2"), a_Controller.Relay.GetPortDelay(2));
	AfxGetApp()->WriteProfileInt(s, _T("Delay3"), a_Controller.Relay.GetPortDelay(3));
	AfxGetApp()->WriteProfileInt(s, _T("Delay4"), a_Controller.Relay.GetPortDelay(4));
	AfxGetApp()->WriteProfileInt(s, _T("Delay5"), a_Controller.Relay.GetPortDelay(5));
	AfxGetApp()->WriteProfileInt(s, _T("Delay6"), a_Controller.Relay.GetPortDelay(6));
	AfxGetApp()->WriteProfileInt(s, _T("Delay7"), a_Controller.Relay.GetPortDelay(7));
	AfxGetApp()->WriteProfileInt(s, _T("Delay8"), a_Controller.Relay.GetPortDelay(8));
}

void RAPDEPage::LoadSettings()
{
	// loads the settings from the registry
	CString s;
	s.LoadStringA(IDS_PDE_TAB);
	SetPortMode(a_Controller.Relay.Feeding, (BYTE)AfxGetApp()->GetProfileInt(s, _T("FeedingModePorts"), DEFAULT_FEEDINGMODE));
	SetPortMode(a_Controller.Relay.WaterChange, (BYTE)AfxGetApp()->GetProfileInt(s, _T("WaterChangeModePorts"), DEFAULT_WATERCHANGEMODE));
	SetPortMode(a_Controller.Relay.Overheat, (BYTE)AfxGetApp()->GetProfileInt(s, _T("OverheatPorts"), DEFAULT_OVERHEAT));
	SetPortMode(a_Controller.Relay.LightsOn, (BYTE)AfxGetApp()->GetProfileInt(s, _T("LightsOnPorts"), DEFAULT_LIGHTSON));
	fTemp = AfxGetApp()->GetProfileInt(s, _T("Temp"), FALSE);
	fBanner = AfxGetApp()->GetProfileInt(s, _T("WebBanner"), FALSE);
	a_Controller.Relay.SetPortDevice(1, AfxGetApp()->GetProfileInt(s, _T("Port1"), DEFAULT_PORT1_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay1"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(2, AfxGetApp()->GetProfileInt(s, _T("Port2"), DEFAULT_PORT2_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay2"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(3, AfxGetApp()->GetProfileInt(s, _T("Port3"), DEFAULT_PORT3_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay3"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(4, AfxGetApp()->GetProfileInt(s, _T("Port4"), DEFAULT_PORT4_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay4"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(5, AfxGetApp()->GetProfileInt(s, _T("Port5"), DEFAULT_PORT5_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay5"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(6, AfxGetApp()->GetProfileInt(s, _T("Port6"), DEFAULT_PORT6_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay6"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(7, AfxGetApp()->GetProfileInt(s, _T("Port7"), DEFAULT_PORT7_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay7"), DEFAULT_DELAY_MINUTES));
	a_Controller.Relay.SetPortDevice(8, AfxGetApp()->GetProfileInt(s, _T("Port8"), DEFAULT_PORT8_DEVICE),
					 AfxGetApp()->GetProfileInt(s, _T("Delay8"), DEFAULT_DELAY_MINUTES));
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

void RAPDEPage::MenuRemoveUnusedFeatures()
{
	a_Controller.Features.CleanupFeatures();
}

BOOL RAPDEPage::WritePDE()
{
	return a_Controller.WriteFile();
	/*
	BOOL bRet = FALSE;

	TRY
	{
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
		WebBannerInfo wi;
		if ( fBanner )
		{
			LoadWebBannerInfoDefaults(wi);
		}

		sFilename.Format(_T("RA_%s"), t.Format(_T("%m%d%y_%H%M")));
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
		if ( theApp.f09xDev )
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
//\r\n"), 
					cb_GetFileVersionString(AfxGetInstanceHandle()),
					t.Format(_T("%m/%d/%Y %H:%M")),
					sFilename, sFileExtension);
		if ( theApp.f09xDev ) 
		{
			sAutoGenHeader += _T("// This version designed for v0.9.0 or later\r\n");
		}
		else
		{
			sAutoGenHeader += _T("// This version designed for v0.8.5 Beta 17 or later\r\n");
		}
		f.Write(sAutoGenHeader, sAutoGenHeader.GetLength());
		// Write features list
		f.Write(sFeatureList, sFeatureList.GetLength());
		s = _T("\r\n\r\n#include <ReefAngel_Features.h>\r\n");
		if ( theApp.f09xDev )
		{
			if ( fColorsPDE )
			{
				// if the colors PDE is enabled, add these in
				s += _T("\
#include <RA_Colors.h>\r\n\
#include <RA_CustomColors.h>\r\n");
			}
			s += _T("\
#include <Globals.h>\r\n\
#include <RA_Wifi.h>\r\n\
#include <Wire.h>\r\n\
#include <OneWire.h>\r\n\
#include <Time.h>\r\n\
#include <DS1307RTC.h>\r\n\
#include <InternalEEPROM.h>\r\n\
#include <RA_NokiaLCD.h>\r\n\
#include <RA_ATO.h>\r\n\
#include <RA_Joystick.h>\r\n\
#include <LED.h>\r\n\
#include <RA_TempSensor.h>\r\n\
#include <Relay.h>\r\n\
#include <PWM.h>\r\n\
#include <Timer.h>\r\n\
#include <Memory.h>\r\n\
#include <ReefAngel.h>\r\n\
\r\n\
");
		}
		else
		{
			if ( fColorsPDE )
			{
				// if the colors PDE is enabled, add these in
				s += _T("\
#include <ReefAngel_Colors.h>\r\n\
#include <ReefAngel_CustomColors.h>\r\n");
			}
			s += _T("\
#include <ReefAngel_Globals.h>\r\n\
#include <ReefAngel_Wifi.h>\r\n\
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
		}
		f.Write(s, s.GetLength());

		if ( theApp.f09xDev )
		{
			if ( fCustomMenu )
			{
				// Custom Menu requires avr/pgmspace.h
				s = _T("#include <avr/pgmspace.h>\r\n");
				f.Write(s, s.GetLength());
			}
		}
		else
		{
			if ( fBanner || fCustomMenu )
			{
				// Banner & Custom Menu require avr/pgmspace.h
				s = _T("#include <avr/pgmspace.h>\r\n");
				f.Write(s, s.GetLength());
			}
			if ( fBanner )
			{
				s.Format(_T("\
// Labels for the web banner\r\n\
%s\r\n\
"), GetWebBannerInfoString(wi));
				f.Write(s, s.GetLength());
			}
		}

		if ( fCustomMenu )
		{
			// Create the custom menu here
			int i;
			CString labels = _T("");
			CString menu = _T("PROGMEM const char *menu_items[] = {\r\n");
			CString functions = _T("");
			for ( i = 0; i < iCustomMenuEntries; i++ )
			{
				s1.Format(_T("prog_char menu%d_label[] PROGMEM = \"Item %d\";\r\n"), i, i+1);
				labels += s1;
				s1.Format(_T("menu%d_label%c "), i, (i+1==iCustomMenuEntries)?' ':',');
				menu += s1;
				s1.Format(_T("void MenuEntry%d()\r\n\
{\r\n\
	ReefAngel.DisplayMenuEntry(\"Item %d\");\r\n\
}\r\n"), i+1, i+1);
				functions += s1;
			}
			menu += _T("};\r\n\r\n");
			functions += _T("\r\n");
			f.Write(labels, labels.GetLength());
			f.Write(menu, menu.GetLength());
			f.Write(functions, functions.GetLength());
		}

		if ( fCustomMain )
		{
			// Create the custom main screen here
			s = _T("\
void DrawCustomMain()\r\n\
{\r\n\
	// the graph is drawn/updated when we exit the main menu &\r\n\
	// when the parameters are saved\r\n\
	ReefAngel.LCD.DrawDate(6, 112);\r\n\
	pingSerial();\r\n\
#if defined DisplayLEDPWM && ! defined RemoveAllLights\r\n\
	ReefAngel.LCD.DrawMonitor(15, 60, ReefAngel.Params,\r\n\
		ReefAngel.PWM.GetDaylightValue(), ReefAngel.PWM.GetActinicValue());\r\n\
#else // defined DisplayLEDPWM && ! defined RemoveAllLights\r\n\
	ReefAngel.LCD.DrawMonitor(15, 60, ReefAngel.Params);\r\n\
#endif // defined DisplayLEDPWM && ! defined RemoveAllLights\r\n\
	pingSerial();\r\n\
	byte TempRelay = ReefAngel.Relay.RelayData;\r\n\
	TempRelay &= ReefAngel.Relay.RelayMaskOff;\r\n\
	TempRelay |= ReefAngel.Relay.RelayMaskOn;\r\n\
	ReefAngel.LCD.DrawOutletBox(12, 93, TempRelay);\r\n\
}\r\n\
\r\n\
void DrawCustomGraph()\r\n\
{\r\n\
	ReefAngel.LCD.DrawGraph(5, 5);\r\n\
}\r\n\
\r\n");
			f.Write(s, s.GetLength());
		}

		s = _T("\
\r\n\
void setup()\r\n\
{\r\n\
    ReefAngel.Init();  //Initialize controller\r\n\
");
		f.Write(s, s.GetLength());
		// Add in Custom Menu if enabled
		if ( fCustomMenu )
		{
			s = sTab + _T("ReefAngel.InitMenu(pgm_read_word(&(menu_items[0])),SIZE(menu_items));\r\n");
			f.Write(s, s.GetLength());
		}
		// Set Celsius if needed
		if ( fTemp )
		{
			s = sTab + _T("ReefAngel.SetTemperatureUnit(1);  // set to Celsius Temperature\r\n");
			f.Write(s, s.GetLength());
		}
		// Set password protection, if added
		if ( IsPasswordProtected() )
		{
			s = sTab + GetWifiAuthenticationString();
			f.Write(s, s.GetLength());
		}

		// web banner timer
		if ( fBanner )
		{
			if ( theApp.f09xDev )
			{
				s.Format(_T("\
    // Initialize and start the web banner timer\r\n\
	ReefAngel.LoadWebBanner(\"%s\");\r\n"),
				wi.sID);
			}
			else
			{
				s = _T("\
    // Initialize and start the web banner timer\r\n\
    ReefAngel.LoadWebBanner(pgm_read_word(&(webbanner_items[0])), SIZE(webbanner_items));\r\n");
			}
			f.Write(s, s.GetLength());
			s.Format(_T("\
    ReefAngel.Timer[4].SetInterval(%d);  // set interval to %d seconds\r\n\
    ReefAngel.Timer[4].Start();\r\n\
"), wi.nInterval, wi.nInterval);
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
			if ( Ports[i] == IDC_PDE_CK_DELAYON )
			{
				s1.Format(_T("%sReefAngel.%s(Port%d, %d);\r\n"), sTab, s, i+1, Delays[i]);
			}
			else
			{
				s1.Format(_T("%sReefAngel.%s(Port%d);\r\n"), sTab, s, i+1);
			}
			f.Write(s1, s1.GetLength());
		}

		// Add in the web banner stuff
		if ( fBanner )
		{
			s = _T("\r\n\
    // Web Banner stuff\r\n\
    if(ReefAngel.Timer[4].IsTriggered())\r\n\
    {\r\n\
        ReefAngel.Timer[4].Start();\r\n\
        ReefAngel.WebBanner();\r\n\
    }\r\n\
");
			f.Write(s, s.GetLength());
		}
		
		// add showinterface to the end
		s = _T("\r\n\
	ReefAngel.ShowInterface();\r\n\
}\r\n\r\n");
		f.Write(s, s.GetLength());
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
	*/
}

void RAPDEPage::UpdatePDEFeatures()
{
	// These ports are updated based on the devices enabled on the ports
	// Since we are always looping through all the ports and updating the values, 
	// we need to turn them off initially and then turn them on if a device is assigned to a port
	// This is to prevent additional features from being enabled if we turn off a feature.
	a_Controller.Features.ClearINOFeatures();

	// check if we need to override the DosingPump with DosingPumpRepeat
	if ( a_Controller.Features.GetFeatureValue(a_Controller.Features.DOSING_INTERVAL_SETUP) )
	{
		fUseDPRepeat = TRUE;
	}
	else
	{
		fUseDPRepeat = FALSE;
	}
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		if ( (a_Controller.Relay.IsPortAlwaysOn(i)) ||
			 (a_Controller.Relay.IsPortNotUsed(i)) )
		{
			// skip the ports that are always on because they were handled above
			// also skip the ports that are not in use
			continue;
		}
		// we have a good port to work with, so check it against the features to enable
		switch ( a_Controller.Relay.GetPortDevice(i) )
		{
			case IDC_PDE_CK_METALHALIDES:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.METAL_HALIDE_SETUP, TRUE);
				break;
			case IDC_PDE_CK_STDLIGHTS:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.STANDARD_LIGHT_SETUP, TRUE);
				break;
			case IDC_PDE_CK_WM1:
			case IDC_PDE_CK_WM2:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.WAVEMAKER_SETUP, TRUE);
				break;
			case IDC_PDE_CK_DP1:
			case IDC_PDE_CK_DP2:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.DOSING_PUMP_SETUP, TRUE);
				break;
			case IDC_PDE_CK_SINGLEATOLOW:
			case IDC_PDE_CK_SINGLEATOHIGH:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.SINGLE_ATO, TRUE);
			case IDC_PDE_CK_DUALATO:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.ATO_SETUP, TRUE);
				break;
		}
	}

	// Update settings in PDE class used for generating the PDE file
	fCustomMenu = a_Controller.Features.GetFeatureValue(a_Controller.Features.CUSTOM_MENU);
	iCustomMenuEntries = a_Controller.Features.iCustomMenuEntries;
	fCustomMain = a_Controller.Features.GetFeatureValue(a_Controller.Features.CUSTOM_MAIN);
	fColorsPDE = a_Controller.Features.GetFeatureValue(a_Controller.Features.CUSTOM_COLORS);

	// if we have simple_menu or custom_menu defined, we need to remove the unused features
	MenuRemoveUnusedFeatures();

	// Get a list of the features used for this file
	CString s;
	sFeatureList = _T("\r\n/* The following features are enabled for this File: \r\n");
	s = a_Controller.Features.GetEnabledList();
	sFeatureList += s;
	sFeatureList += _T("*/\r\n");
}

void RAPDEPage::OnBnClickedBtnGenerate()
{
	UpdateData();
	RefreshModePorts();
	if ( WritePDE() )
	{
		AfxGetApp()->GetMainWnd()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), LPARAM(IDS_SUCCESS_GENERATE));
		switch ( theApp.iSave )
		{
		case ALWAYS:
			// save the features first
			AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, MAKEWPARAM(ID_SAVE_FEATURES, 0), 0);
			SaveSettings();
			break;
		case PROMPT:
			{
				int iRet = AfxMessageBox(_T("Do you want to save these settings?"),
					MB_ICONINFORMATION | MB_YESNO);
				if ( iRet == IDYES )
				{
					// save the features first
					AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND, MAKEWPARAM(ID_SAVE_FEATURES, 0), 0);
					// Save settings
					SaveSettings();
				}
			}
			break;
		default:
		//case NeverSave:
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
	fBanner = FALSE;
	UpdateData(FALSE);
}

void RAPDEPage::OnResetFeedingMode()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.Feeding, DEFAULT_FEEDINGMODE);
}

void RAPDEPage::OnResetWaterChangeMode()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.WaterChange, DEFAULT_WATERCHANGEMODE);
}

void RAPDEPage::OnResetOverheat()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.Overheat, DEFAULT_OVERHEAT);
}

void RAPDEPage::OnResetLightsOn()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.LightsOn, DEFAULT_LIGHTSON);
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
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_WM1);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkWm2()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_WM2);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkDp1()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_DP1);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkDp2()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_DP2);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkDualato()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_DUALATO);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkSingleatolow()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_SINGLEATOLOW);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkSingleatohigh()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_SINGLEATOHIGH);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkAlwaysOn()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_ALWAYS_ON);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkMetalhalides()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_METALHALIDES);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkStdlights()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_STDLIGHTS);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkHeater()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_HEATER);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkChiller()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_CHILLER);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkNotused()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_NOTUSED);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnBnClickedCkDelayedOn()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_PDE_CK_DELAYON);
	UpdateDisplayDevice(bCurrentPort);
}

void RAPDEPage::OnEnChangePdeEditDelayOn()
{
	a_Controller.Relay.SetPortDelay(bCurrentPort, GetDlgItemInt(IDC_PDE_EDIT_DELAY_ON));
}
