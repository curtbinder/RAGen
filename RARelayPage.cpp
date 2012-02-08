// RARelayPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RARelayPage.h"
#include "cb_FileVersion.h"
#include "GlobalVars.h"
#include "WifiPasswordDlg.h"
#include "InternalMemoryDefaults.h"
#include "Controller.h"


// RARelayPage dialog

IMPLEMENT_DYNAMIC(RARelayPage, CDialog)

RARelayPage::RARelayPage(CWnd* pParent /*=NULL*/)
	: CDialog(RARelayPage::IDD, pParent)
{
	sFeatureList = _T("");
	fUseDPRepeat = FALSE;
}

RARelayPage::~RARelayPage()
{
}

void RARelayPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(RARelayPage, CDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RELAY_PORT_1, &RARelayPage::OnBnClickedPort1)
	ON_BN_CLICKED(IDC_RELAY_PORT_2, &RARelayPage::OnBnClickedPort2)
	ON_BN_CLICKED(IDC_RELAY_PORT_3, &RARelayPage::OnBnClickedPort3)
	ON_BN_CLICKED(IDC_RELAY_PORT_4, &RARelayPage::OnBnClickedPort4)
	ON_BN_CLICKED(IDC_RELAY_PORT_5, &RARelayPage::OnBnClickedPort5)
	ON_BN_CLICKED(IDC_RELAY_PORT_6, &RARelayPage::OnBnClickedPort6)
	ON_BN_CLICKED(IDC_RELAY_PORT_7, &RARelayPage::OnBnClickedPort7)
	ON_BN_CLICKED(IDC_RELAY_PORT_8, &RARelayPage::OnBnClickedPort8)
	ON_BN_CLICKED(IDC_RELAY_CK_WM1, &RARelayPage::OnBnClickedCkWm1)
	ON_BN_CLICKED(IDC_RELAY_CK_WM2, &RARelayPage::OnBnClickedCkWm2)
	ON_BN_CLICKED(IDC_RELAY_CK_DP1, &RARelayPage::OnBnClickedCkDp1)
	ON_BN_CLICKED(IDC_RELAY_CK_DP2, &RARelayPage::OnBnClickedCkDp2)
	ON_BN_CLICKED(IDC_RELAY_CK_DUALATO, &RARelayPage::OnBnClickedCkDualato)
	ON_BN_CLICKED(IDC_RELAY_CK_SINGLEATOLOW, &RARelayPage::OnBnClickedCkSingleatolow)
	ON_BN_CLICKED(IDC_RELAY_CK_SINGLEATOHIGH, &RARelayPage::OnBnClickedCkSingleatohigh)
	ON_BN_CLICKED(IDC_RELAY_CK_ALWAYS_ON, &RARelayPage::OnBnClickedCkAlwaysOn)
	ON_BN_CLICKED(IDC_RELAY_CK_METALHALIDES, &RARelayPage::OnBnClickedCkMetalhalides)
	ON_BN_CLICKED(IDC_RELAY_CK_STDLIGHTS, &RARelayPage::OnBnClickedCkStdlights)
	ON_BN_CLICKED(IDC_RELAY_CK_HEATER, &RARelayPage::OnBnClickedCkHeater)
	ON_BN_CLICKED(IDC_RELAY_CK_CHILLER, &RARelayPage::OnBnClickedCkChiller)
	ON_BN_CLICKED(IDC_RELAY_CK_DELAYON, &RARelayPage::OnBnClickedCkDelayedOn)
	ON_BN_CLICKED(IDC_RELAY_CK_NOTUSED, &RARelayPage::OnBnClickedCkNotused)
	ON_EN_CHANGE(IDC_RELAY_EDIT_DELAY_ON, &RARelayPage::OnEnChangePdeEditDelayOn)
END_MESSAGE_MAP()


// RARelayPage message handlers

BOOL RARelayPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_RELAY_SPIN_DELAY_ON);
	pSpin->SetBuddy(GetDlgItem(IDC_RELAY_EDIT_DELAY_ON));
	pSpin->SetRange32(1, BYTE_MAX);

	// have to load the defaults first which initializes the boxes
	// and loads in the default values before we can restore the settings
	InitPorts();
	LoadSettings();
	SelectPort1();
	SetPortMode(a_Controller.Relay.Feeding, DEFAULT_FEEDINGMODE);
	SetPortMode(a_Controller.Relay.WaterChange, DEFAULT_WATERCHANGEMODE);
	SetPortMode(a_Controller.Relay.Overheat, DEFAULT_OVERHEAT);
	SetPortMode(a_Controller.Relay.LightsOn, DEFAULT_LIGHTSON);
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void RARelayPage::InitPorts()
{
	bCurrentPort = 1;
	fWM1 = FALSE;
	fWM2 = FALSE;
	fDP1 = FALSE;
	fDP2 = FALSE;
	fDualATO = FALSE;
	fSingleATOLow = FALSE;
	fSingleATOHigh = FALSE;
}

void RARelayPage::LoadDefaults()
{
	// Load the default values
	InitPorts();
	LoadDefaultPortDevices();
	SetPortMode(a_Controller.Relay.Feeding, DEFAULT_FEEDINGMODE);
	SetPortMode(a_Controller.Relay.WaterChange, DEFAULT_WATERCHANGEMODE);
	SetPortMode(a_Controller.Relay.Overheat, DEFAULT_OVERHEAT);
	SetPortMode(a_Controller.Relay.LightsOn, DEFAULT_LIGHTSON);
	UpdateData(FALSE);
}

void RARelayPage::SetPortMode(BYTE Mode, BYTE Ports)
{
	a_Controller.Relay.SetPortMode(Mode, Ports);
	UpdateDisplayPorts(Mode);
}

void RARelayPage::UpdateDisplayPorts(BYTE Mode)
{
	// Updates the check boxes on the display
	// Only updates the mode passed in
	int i;
	BYTE ports;
	switch ( Mode )
	{
	case a_Controller.Relay.Feeding:
		i = IDC_RELAY_CK_FEEDING_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.Feeding);
		break;
	case a_Controller.Relay.WaterChange:
		i = IDC_RELAY_CK_WATER_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.WaterChange);
		break;
	case a_Controller.Relay.Overheat:
		i = IDC_RELAY_CK_OVERHEAT_1;
		ports = a_Controller.Relay.GetPortModes(a_Controller.Relay.Overheat);
		break;
	case a_Controller.Relay.LightsOn:
		i = IDC_RELAY_CK_LIGHTS_1;
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

void RARelayPage::RefreshModePorts()
{
	// Refresh the port variables based on the check boxes
	// Refreshes all the ports, only update before we write the value out since
	// there isn't any variable associated with each checkbox
	
	// loop through the four modes
	int modes[4] = {IDC_RELAY_CK_FEEDING_1, IDC_RELAY_CK_WATER_1, IDC_RELAY_CK_OVERHEAT_1, IDC_RELAY_CK_LIGHTS_1};
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
			a_Controller.Relay.SetPortMode(a_Controller.Relay.Feeding, x);
			break;
		case 1:
			a_Controller.Relay.SetPortMode(a_Controller.Relay.WaterChange, x);
			break;
		case 2:
			a_Controller.Relay.SetPortMode(a_Controller.Relay.Overheat, x);
			break;
		case 3:
			a_Controller.Relay.SetPortMode(a_Controller.Relay.LightsOn, x);
			break;
		}
	}  // for i
}

void RARelayPage::UpdateDisplayDevice(int Port)
{
	int device = a_Controller.Relay.GetPortDevice(Port);
	// always update the delay value on changing ports no matter if it's selected or not
	SetDlgItemInt(IDC_RELAY_EDIT_DELAY_ON, a_Controller.Relay.GetPortDelay(Port));
	ToggleDeviceChecks(device);
	UpdateDeviceAvailability();
}

void RARelayPage::UpdateDeviceAvailability()
{
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		// Set the device flags ON if we have the device checked
		ToggleDeviceFlag(a_Controller.Relay.GetPortDevice(i+1));
	}

	// Toggle & Enable/Disable devices based on device passed in (which is selected device)
	GetDlgItem(IDC_RELAY_CK_WM1)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_WM1, fWM1, fDP1));
	GetDlgItem(IDC_RELAY_CK_WM2)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_WM2, fWM2, fDP2));
	GetDlgItem(IDC_RELAY_CK_DP1)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_DP1, fDP1, fWM1));
	GetDlgItem(IDC_RELAY_CK_DP2)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_DP2, fDP2, fWM2));

	if ( fSingleATOLow || fSingleATOHigh )
	{
		// a single switch is enabled somewhere
		// disable the dual ato device
		GetDlgItem(IDC_RELAY_CK_DUALATO)->EnableWindow(FALSE);
		// determine if we need to show them enabled or not
		GetDlgItem(IDC_RELAY_CK_SINGLEATOLOW)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_SINGLEATOLOW, fSingleATOLow, fSingleATOLow));
		GetDlgItem(IDC_RELAY_CK_SINGLEATOHIGH)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_SINGLEATOHIGH, fSingleATOHigh, fSingleATOHigh));
	}
	else if ( fDualATO )
	{
		// dual switch is enabled somewhere
		// determine if we need to show it enabled or not
		GetDlgItem(IDC_RELAY_CK_DUALATO)->EnableWindow(IsDeviceCkEnabled(IDC_RELAY_CK_DUALATO, fDualATO, fDualATO));
		// disable the single ato devices
		GetDlgItem(IDC_RELAY_CK_SINGLEATOLOW)->EnableWindow(FALSE);
		GetDlgItem(IDC_RELAY_CK_SINGLEATOHIGH)->EnableWindow(FALSE);
	}
	else
	{
		// no ato switches enabled
		// enable all the ato devices
		GetDlgItem(IDC_RELAY_CK_DUALATO)->EnableWindow();
		GetDlgItem(IDC_RELAY_CK_SINGLEATOLOW)->EnableWindow();
		GetDlgItem(IDC_RELAY_CK_SINGLEATOHIGH)->EnableWindow();
	}
}

BOOL RARelayPage::IsDeviceCkEnabled(int Device, BOOL fDevFlag, BOOL fOppDevFlag)
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

void RARelayPage::ToggleDeviceChecks(int Device)
{
	int i;
	CButton* p;
	for ( i = IDC_RELAY_CK_ALWAYS_ON; i <= IDC_RELAY_CK_NOTUSED; i++ )
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

void RARelayPage::ToggleDeviceFlag(int Device, BOOL fValue /*= TRUE*/)
{
	switch ( Device )
	{
	case IDC_RELAY_CK_WM1:
		fWM1 = fValue;
		break;
	case IDC_RELAY_CK_WM2:
		fWM2 = fValue;
		break;
	case IDC_RELAY_CK_DP1:
		fDP1 = fValue;
		break;
	case IDC_RELAY_CK_DP2:
		fDP2 = fValue;
		break;
	case IDC_RELAY_CK_SINGLEATOLOW:
		fSingleATOLow = fValue;
		break;
	case IDC_RELAY_CK_SINGLEATOHIGH:
		fSingleATOHigh = fValue;
		break;
	case IDC_RELAY_CK_DUALATO:
		fDualATO = fValue;
		break;
	default:
		break;
	}
}

void RARelayPage::LoadDefaultPortDevices()
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

void RARelayPage::SaveSettings()
{
	// saves the settings to the registry
	CString s;
	s.LoadStringA(IDS_PDE_TAB);
	AfxGetApp()->WriteProfileInt(s, _T("FeedingModePorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.Feeding));
	AfxGetApp()->WriteProfileInt(s, _T("WaterChangeModePorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.WaterChange));
	AfxGetApp()->WriteProfileInt(s, _T("OverheatPorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.Overheat));
	AfxGetApp()->WriteProfileInt(s, _T("LightsOnPorts"), a_Controller.Relay.GetPortModes(a_Controller.Relay.LightsOn));
	//AfxGetApp()->WriteProfileInt(s, _T("Temp"), fTemp);
	//AfxGetApp()->WriteProfileInt(s, _T("WebBanner"), fBanner);
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

void RARelayPage::LoadSettings()
{
	// loads the settings from the registry
	CString s;
	s.LoadStringA(IDS_PDE_TAB);
	SetPortMode(a_Controller.Relay.Feeding, (BYTE)AfxGetApp()->GetProfileInt(s, _T("FeedingModePorts"), DEFAULT_FEEDINGMODE));
	SetPortMode(a_Controller.Relay.WaterChange, (BYTE)AfxGetApp()->GetProfileInt(s, _T("WaterChangeModePorts"), DEFAULT_WATERCHANGEMODE));
	SetPortMode(a_Controller.Relay.Overheat, (BYTE)AfxGetApp()->GetProfileInt(s, _T("OverheatPorts"), DEFAULT_OVERHEAT));
	SetPortMode(a_Controller.Relay.LightsOn, (BYTE)AfxGetApp()->GetProfileInt(s, _T("LightsOnPorts"), DEFAULT_LIGHTSON));
//	fTemp = AfxGetApp()->GetProfileInt(s, _T("Temp"), FALSE);
//	fBanner = AfxGetApp()->GetProfileInt(s, _T("WebBanner"), FALSE);
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

void RARelayPage::SelectPort1()
{
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_RELAY_PORT_1, BM_CLICK));
	// uncheck current checked port
	CButton* p;
	int c;
	for ( int i = IDC_RELAY_PORT_8; i > IDC_RELAY_PORT_1; i-- )
	{
		p = (CButton*)GetDlgItem(i);
		c = p->GetCheck();
		if ( c == BST_CHECKED )
		{
			p->SetCheck(BST_UNCHECKED);
		}
	}
	p = (CButton*)GetDlgItem(IDC_RELAY_PORT_1);
	p->SetCheck(BST_CHECKED);
}

void RARelayPage::MenuRemoveUnusedFeatures()
{
	a_Controller.Features.CleanupFeatures();
}

BOOL RARelayPage::WritePDE()
{
	return a_Controller.WriteFile();
}

void RARelayPage::UpdatePDEFeatures()
{
	// These ports are updated based on the devices enabled on the ports
	// Since we are always looping through all the ports and updating the values, 
	// we need to turn them off initially and then turn them on if a device is assigned to a port
	// This is to prevent additional features from being enabled if we turn off a feature.
	a_Controller.Features.ClearINOFeatures();

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
			case IDC_RELAY_CK_METALHALIDES:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.METAL_HALIDE_SETUP, TRUE);
				break;
			case IDC_RELAY_CK_STDLIGHTS:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.STANDARD_LIGHT_SETUP, TRUE);
				break;
			case IDC_RELAY_CK_WM1:
			case IDC_RELAY_CK_WM2:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.WAVEMAKER_SETUP, TRUE);
				break;
			case IDC_RELAY_CK_DP1:
			case IDC_RELAY_CK_DP2:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.DOSING_PUMP_SETUP, TRUE);
				break;
			case IDC_RELAY_CK_SINGLEATOLOW:
			case IDC_RELAY_CK_SINGLEATOHIGH:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.SINGLE_ATO, TRUE);
			case IDC_RELAY_CK_DUALATO:
				a_Controller.Features.SetFeatureValue(a_Controller.Features.ATO_SETUP, TRUE);
				break;
		}
	}

	// if we have simple_menu or custom_menu defined, we need to remove the unused features
	MenuRemoveUnusedFeatures();

	// Get a list of the features used for this file
	CString s;
	sFeatureList = _T("\r\n/* The following features are enabled for this File: \r\n");
	s = a_Controller.Features.GetEnabledList();
	sFeatureList += s;
	sFeatureList += _T("*/\r\n");
}

void RARelayPage::OnBnClickedBtnGenerate()
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

void RARelayPage::OnResetAll()
{
	LoadDefaults();
}

void RARelayPage::OnResetSaved()
{
	LoadSettings();
	SelectPort1();
	UpdateData(FALSE);
}

void RARelayPage::OnResetPorts()
{
	UpdateData();
	InitPorts();
	LoadDefaultPortDevices();
	UpdateData(FALSE);
}

void RARelayPage::OnResetFeedingMode()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.Feeding, DEFAULT_FEEDINGMODE);
}

void RARelayPage::OnResetWaterChangeMode()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.WaterChange, DEFAULT_WATERCHANGEMODE);
}

void RARelayPage::OnResetOverheat()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.Overheat, DEFAULT_OVERHEAT);
}

void RARelayPage::OnResetLightsOn()
{
	UpdateData();
	SetPortMode(a_Controller.Relay.LightsOn, DEFAULT_LIGHTSON);
}

void RARelayPage::OnBnClickedPort1()
{
	UpdateData();
	bCurrentPort = 1;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort2()
{
	UpdateData();
	bCurrentPort = 2;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort3()
{
	UpdateData();
	bCurrentPort = 3;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort4()
{
	UpdateData();
	bCurrentPort = 4;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort5()
{
	UpdateData();
	bCurrentPort = 5;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort6()
{
	UpdateData();
	bCurrentPort = 6;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort7()
{
	UpdateData();
	bCurrentPort = 7;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedPort8()
{
	UpdateData();
	bCurrentPort = 8;
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkWm1()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_WM1);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkWm2()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_WM2);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkDp1()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_DP1);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkDp2()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_DP2);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkDualato()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_DUALATO);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkSingleatolow()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_SINGLEATOLOW);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkSingleatohigh()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_SINGLEATOHIGH);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkAlwaysOn()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_ALWAYS_ON);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkMetalhalides()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_METALHALIDES);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkStdlights()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_STDLIGHTS);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkHeater()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_HEATER);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkChiller()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_CHILLER);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkNotused()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_NOTUSED);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnBnClickedCkDelayedOn()
{
	UpdateData();
	a_Controller.Relay.SetPortDevice(bCurrentPort, IDC_RELAY_CK_DELAYON);
	UpdateDisplayDevice(bCurrentPort);
}

void RARelayPage::OnEnChangePdeEditDelayOn()
{
	a_Controller.Relay.SetPortDelay(bCurrentPort, GetDlgItemInt(IDC_RELAY_EDIT_DELAY_ON));
}
