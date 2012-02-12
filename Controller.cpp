#include "StdAfx.h"
#include "Resource.h"
#include "Controller.h"
#include "RAGen.h"
//#include "WebBannerDlg.h"
#include "PortalDlg.h"
#include "cb_FileVersion.h"
#include "WifiPasswordDlg.h"

// The Controller
CController a_Controller;


CController::CController(void)
{
	m_sFilename = _T("");
	m_sExtension = _T("");
	m_fPortal = FALSE;
	m_fTemp = FALSE;
	m_iDevVersion = NOT_SET;
	m_fLatestDev = FALSE;
	m_fAddPWMSlope = FALSE;
	LoadDeviceFunctions();
	//m_sWifiUsername = _T("");
	//m_sWifiPassword = _T("");
}

CController::~CController(void)
{
}

CString CController::LookupDeviceFunction(int Device)
{
	CString s = _T("");
	for ( int i = 0; i < MAX_DEVICES; i++ )
	{
		if ( Devices[i].id == Device )
		{
			if ( (Device == IDC_RELAY_CK_DP1) ||
				 (Device == IDC_RELAY_CK_DP2) )
			{
				// For Dosing Pumps, if the user chose to use the Repeat Interval
				// Then let's switch things around and choose the Repeat Interval instead
				// of the standard dosing pump if they chose to use a dosing pump
				if ( Features.GetFeatureValue(Features.DOSING_INTERVAL_SETUP) )
				{
					if ( Device == IDC_RELAY_CK_DP1 )
					{
						s = _T("DosingPumpRepeat1");
					}
					else
					{
						s = _T("DosingPumpRepeat2");
					}
				}
				else
				{
					s = Devices[i].sRAFunction;
				}
			}
			else
			{
				s = Devices[i].sRAFunction;
			}
			break;
		}
	}
	return s;
}

void CController::AutodetectVersion(CString sLibraryFolder)
{
	// Call this function on app start and after settings changed
	ASSERT(!sLibraryFolder.IsEmpty());
	switch ( m_iDevVersion )
	{
	default:
	case AUTODETECT:
		TRACE("Lib Dir:  %s\n", sLibraryFolder);
		m_fLatestDev = AutodetectDevVersion(sLibraryFolder);
		break;
	case FORCE_08X:
		m_fLatestDev = FALSE;
		break;
	case FORCE_09X:
		m_fLatestDev = TRUE;
		break;
	}
}

void CController::LoadDeviceFunctions()
{
	int d = IDC_RELAY_CK_ALWAYS_ON;
	int i;
	for ( i = 0; i < MAX_DEVICES; i++, d++ )
	{
		Devices[i].id = d;
		switch ( d )
		{
		case IDC_RELAY_CK_DELAYON:
			Devices[i].sRAFunction = _T("Relay.DelayedOn");
			break;
		case IDC_RELAY_CK_ALWAYS_ON:
			Devices[i].sRAFunction = _T("Relay.On");
			break;
		case IDC_RELAY_CK_METALHALIDES:
			Devices[i].sRAFunction = _T("MHLights");
			break;
		case IDC_RELAY_CK_STDLIGHTS:
			Devices[i].sRAFunction = _T("StandardLights");
			break;
		case IDC_RELAY_CK_HEATER:
			Devices[i].sRAFunction = _T("StandardHeater");
			break;
		case IDC_RELAY_CK_CHILLER:
			Devices[i].sRAFunction = _T("StandardFan");
			break;
		case IDC_RELAY_CK_WM1:
			Devices[i].sRAFunction = _T("Wavemaker1");
			break;
		case IDC_RELAY_CK_WM2:
			Devices[i].sRAFunction = _T("Wavemaker2");
			break;
		case IDC_RELAY_CK_DP1:
			Devices[i].sRAFunction = _T("DosingPump1");
			break;
		case IDC_RELAY_CK_DP2:
			Devices[i].sRAFunction = _T("DosingPump2");
			break;
		case IDC_RELAY_CK_DUALATO:
			Devices[i].sRAFunction = _T("StandardATO");
			break;
		case IDC_RELAY_CK_SINGLEATOLOW:
			Devices[i].sRAFunction = _T("SingleATOLow");
			break;
		case IDC_RELAY_CK_SINGLEATOHIGH:
			Devices[i].sRAFunction = _T("SingleATOHigh");
			break;
		default:
		case IDC_RELAY_CK_NOTUSED:
			Devices[i].sRAFunction = _T("");
			break;
		}
	}
	for ( i = 0; i < MAX_DEVICES; i++ )
	{
		TRACE("Device %d:  %s\n", i, Devices[i].sRAFunction);
	}
}
/*
void CController::SetWifiUP(CString sUser, CString sPassword)
{
	m_sWifiUsername = sUser;
	m_sWifiPassword = sPassword;
}

CString CController::GetWifiString()
{
	CString s;
	return s;
}
*/

BOOL CController::WriteFile()
{
	BOOL bRet = FALSE;

	TRY
	{
		CString sFile;
		int iRet;
		CTime t = CTime::GetCurrentTime();
		CFile f;
		SECURITY_ATTRIBUTES sa;

		GenerateFilename(t);

		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = FALSE;
		sFile.Format(_T("%s\\%s\\"), theApp.m_sSketchDirectory, m_sFilename);
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
		sFile += m_sFilename + m_sExtension;

		CFileException fe;
		if ( ! f.Open(sFile, CFile::modeCreate | CFile::modeWrite, &fe) )
		{
			// open failed, so throw exception
			AfxThrowFileException(fe.m_cause, fe.m_lOsError, fe.m_strFileName);
		}

		GenerateHeader(f, t);

		WriteIncludes(f);

		WriteCustomMenu(f);

		WriteCustomMain(f);

		WriteSetup(f);

		WriteLoop(f);

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

void CController::GenerateFilename(CTime &t)
{
	m_sFilename.Format(_T("RA_%s"), t.Format(_T("%m%d%y_%H%M")));

	if ( IsLatestDevVersion() )
	{
		m_sExtension.LoadString(IDS_INO_EXTENSION);
	} else
	{
		m_sExtension.LoadString(IDS_PDE_EXTENSION);
	}
}

void CController::GenerateHeader(CFile &f, CTime &t)
{
	CString s;
	s.Format(_T("\
// Autogenerated file by RAGen (v%s), (%s)\r\n\
// %s%s\r\n\
//\r\n"), 
				cb_GetFileVersionString(AfxGetInstanceHandle()),
				t.Format(_T("%m/%d/%Y %H:%M")),
				m_sFilename, m_sExtension);
	if ( IsLatestDevVersion() ) 
	{
		s += _T("// This version designed for v0.9.0 or later\r\n");
	}
	else
	{
		s += _T("// This version designed for v0.8.5 Beta 17 or later\r\n");
	}
	f.Write(s, s.GetLength());

	// Write features list
	s = _T("\r\n/* The following features are enabled for this File: \r\n");
	s += Features.GetEnabledList();
	s += _T("*/\r\n");
	f.Write(s, s.GetLength());
}

void CController::WriteIncludes(CFile &f)
{
	CString s;

	s = _T("\r\n\r\n#include <ReefAngel_Features.h>\r\n");
	if ( IsLatestDevVersion() )
	{
		if ( Features.GetFeatureValue(Features.CUSTOM_COLORS) )
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
#include <RA_PWM.h>\r\n\
#include <Timer.h>\r\n\
#include <Memory.h>\r\n\
");
		if ( Features.GetFeatureValue(Features.SALINITY) )
		{
			s += _T("#include <Salinity.h>\r\n");
		}
		if ( Features.GetFeatureValue(Features.RF) )
		{
			s += _T("#include <RF.h>\r\n");
		}
		if ( Features.GetFeatureValue(Features.ORP) )
		{
			s += _T("#include <ORP.h>\r\n");
		}
		if ( Features.GetFeatureValue(Features.IO) )
		{
			s += _T("#include <IO.h>\r\n");
		}
		if ( Features.GetFeatureValue(Features.AI) )
		{
			s += _T("#include <AI.h>\r\n");
		}
	}
	else
	{
		if ( Features.GetFeatureValue(Features.CUSTOM_COLORS) )
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
");
		if ( Features.GetFeatureValue(Features.SALINITY) )
		{
			s += _T("#include <ReefAngel_Salinity.h>\r\n");
		}
		if ( Features.GetFeatureValue(Features.RF) )
		{
			s += _T("#include <ReefAngel_RF.h>\r\n");
		}
		if ( Features.GetFeatureValue(Features.AI) )
		{
			s += _T("#include <ReefAngel_AI.h>\r\n");
		}
	}
	s += _T("#include <ReefAngel.h>\r\n\r\n");
	f.Write(s, s.GetLength());

	// Custom code comment goes here
	s = _T("\
////// Place global variable code below here\r\n\
\r\n\r\n\
////// Place global variable code above here\r\n\r\n");
	f.Write(s, s.GetLength());
}

void CController::WriteCustomMenu(CFile &f)
{
	CString s;

	if ( Features.GetFeatureValue(Features.CUSTOM_MENU) )
	{
		// TODO use CustomMenu class
		// Create the custom menu here
		// Custom Menu requires avr/pgmspace.h
		s = _T("#include <avr/pgmspace.h>\r\n");
		f.Write(s, s.GetLength());
		int i;
		CString labels = _T("");
		CString menu = _T("PROGMEM const char *menu_items[] = {\r\n");
		CString functions = _T("");
		for ( i = 0; i < Features.iCustomMenuEntries; i++ )
		{
			s.Format(_T("prog_char menu%d_label[] PROGMEM = \"Item %d\";\r\n"), i, i+1);
			labels += s;
			s.Format(_T("menu%d_label%c "), i, (i+1==Features.iCustomMenuEntries)?' ':',');
			menu += s;
			s.Format(_T("void MenuEntry%d()\r\n\
{\r\n\
    ReefAngel.DisplayMenuEntry(\"Item %d\");\r\n\
}\r\n"), i+1, i+1);
			functions += s;
		}
		menu += _T("};\r\n\r\n");
		functions += _T("\r\n");
		f.Write(labels, labels.GetLength());
		f.Write(menu, menu.GetLength());
		f.Write(functions, functions.GetLength());
	}
}

void CController::WriteCustomMain(CFile &f)
{
	CString s;
	if ( Features.GetFeatureValue(Features.CUSTOM_MAIN) )
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
}

void CController::WriteSetup(CFile &f)
{
	CString s, s1;
	CString sTab = _T("    ");
	s = _T("\
\r\n\
void setup()\r\n\
{\r\n\
    // This must be the first line\r\n\
    ReefAngel.Init();  //Initialize controller\r\n\
");
	f.Write(s, s.GetLength());
	// Add in Custom Menu if enabled
	if ( Features.GetFeatureValue(Features.CUSTOM_MENU) )
	{
		s = sTab + _T("// Initialize the custom menu\r\n") +
			sTab + _T("ReefAngel.InitMenu(pgm_read_word(&(menu_items[0])),SIZE(menu_items));\r\n");
		f.Write(s, s.GetLength());
	}
	// Set Celsius if needed
	if ( m_fTemp )
	{
		s = sTab + _T("ReefAngel.SetTemperatureUnit(1);  // set to Celsius Temperature\r\n");
		f.Write(s, s.GetLength());
	}
	// Set password protection, if added
	if ( IsPasswordProtected() )
	{
		// TODO Update Wifi Authentication message
		s = sTab + _T("// This password protects your controller\r\n") +
			sTab + _T("// Android app, iPhone/iPad app, Portal, Status app will not work if set\r\n") +
			sTab + GetWifiAuthenticationString();
		f.Write(s, s.GetLength());
	}

	// add in an extra line to separate first part between the modes
	s = _T("\r\n");
	f.Write(s, s.GetLength());

	BOOL fAddExtraLineSpace = FALSE;
	// Toggle Ports, only write if they differ from defaults
	if ( Relay.GetPortModes(Relay.Feeding) != DEFAULT_FEEDINGMODE )
	{
		s = sTab + _T("// Ports toggled in Feeding Mode\r\n") + 
			sTab + _T("ReefAngel.FeedingModePorts = ");
		f.Write(s, s.GetLength());
		if ( IsLatestDevVersion() )
		{
			s = Relay.GetPortModeText(Relay.Feeding);
		}
		else
		{
			s = Relay.GetPortMode(Relay.Feeding);
		}
		s += _T(";\r\n");
		f.Write(s, s.GetLength());
		fAddExtraLineSpace = TRUE;
	}
	if ( Relay.GetPortModes(Relay.WaterChange) != DEFAULT_WATERCHANGEMODE )
	{
		s = sTab + _T("// Ports toggled in Water Change Mode\r\n") + 
			sTab + _T("ReefAngel.WaterChangePorts = ");
		f.Write(s, s.GetLength());
		if ( IsLatestDevVersion() )
		{
			s = Relay.GetPortModeText(Relay.WaterChange);
		}
		else
		{
			s = Relay.GetPortMode(Relay.WaterChange);
		}
		s += _T(";\r\n");
		f.Write(s, s.GetLength());
		fAddExtraLineSpace = TRUE;
	}
	if ( Relay.GetPortModes(Relay.Overheat) != DEFAULT_OVERHEAT )
	{
		s = sTab + _T("// Ports turned off when Overheat temperature exceeded\r\n") + 
			sTab + _T("ReefAngel.OverheatShutoffPorts = ");
		f.Write(s, s.GetLength());
		if ( IsLatestDevVersion() )
		{
			s = Relay.GetPortModeText(Relay.Overheat);
		}
		else
		{
			s = Relay.GetPortMode(Relay.Overheat);
		}
		s += _T(";\r\n");
		f.Write(s, s.GetLength());
		fAddExtraLineSpace = TRUE;
	}
	if ( Relay.GetPortModes(Relay.LightsOn) != DEFAULT_LIGHTSON )
	{
		s = sTab + _T("// Ports toggled when Lights On / Off menu entry selected\r\n") + 
			sTab + _T("ReefAngel.LightsOnPorts = ");
		f.Write(s, s.GetLength());
		if ( IsLatestDevVersion() )
		{
			s = Relay.GetPortModeText(Relay.LightsOn);
		}
		else
		{
			s = Relay.GetPortMode(Relay.LightsOn);
		}
		s += _T(";\r\n");
		f.Write(s, s.GetLength());
		fAddExtraLineSpace = TRUE;
	}

	BOOL fAddAlwaysOnComment = FALSE;
	// Ports that are always on
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		if ( Relay.IsPortAlwaysOn(i) )
		{
			if ( !fAddAlwaysOnComment )
			{
				// do we need an extra line to space the ports from above??
				if ( fAddExtraLineSpace )
				{
					s = _T("\r\n");
					f.Write(s, s.GetLength());
				}
				s = sTab + _T("// Ports that are always on\r\n");
				f.Write(s, s.GetLength());
				fAddAlwaysOnComment = TRUE;
			}
			s = LookupDeviceFunction(Relay.GetPortDevice(i+1));
			s1.Format(_T("%sReefAngel.%s(Port%d);\r\n"), sTab, s, i+1);
			f.Write(s1, s1.GetLength());
		}
	}

	// Custom code comment goes here
	s = _T("\
    ////// Place additional initialization code below here\r\n\
    \r\n\r\n\
    ////// Place additional initialization code above here\r\n");
	f.Write(s, s.GetLength());

	s = _T("\
}\
\r\n");
	f.Write(s, s.GetLength());
}

void CController::WriteLoop(CFile &f)
{
	CString s, s1;
	CString sTab = _T("    ");
	s = _T("\r\n\
void loop()\r\n\
{\r\n\
    // Specific functions that use Internal Memory values\r\n\
");
	f.Write(s, s.GetLength());

	// Specific functions
	for ( int i = 0; i < MAX_PORTS; i++ )
	{
		if ( Relay.IsPortAlwaysOn(i) ||
			 Relay.IsPortNotUsed(i) )
		{
			// skip the ports that are always on because they were handled above
			// also skip the ports that are not in use
			continue;
		}
		// Now we have a good port to use, so let's use it
		s = LookupDeviceFunction(Relay.GetPortDevice(i+1));
		if ( Relay.IsPortDelayedOn(i) )
		{
			s1.Format(_T("%sReefAngel.%s(Port%d, %d);\r\n"), sTab, s, i+1, Relay.GetPortDelay(i+1));
		}
		else
		{
			s1.Format(_T("%sReefAngel.%s(Port%d);\r\n"), sTab, s, i+1);
		}
		f.Write(s1, s1.GetLength());
	}

	// add in pwmslope code here
	if ( m_fAddPWMSlope )
	{
		if ( IsLatestDevVersion() )
		{
			s = _T("\r\n\
    // PWMSlope based on Internal Memory values for Standard Lights\r\n\
    ReefAngel.PWM.ActinicPWMSlope();\r\n\
    ReefAngel.PWM.DaylightPWMSlope();\r\n");
		}
		else
		{
			s = _T("\r\n\
    ReefAngel.PWM.SetActinic(PWMSlope(\r\n\
        InternalMemory.StdLightsOnHour_read(),\r\n\
        InternalMemory.StdLightsOnMinute_read(),\r\n\
        InternalMemory.StdLightsOffHour_read(),\r\n\
        InternalMemory.StdLightsOffMinute_read(),\r\n\
        InternalMemory.PWMSlopeStartA_read(),\r\n\
        InternalMemory.PWMSlopeEndA_read(),\r\n\
        InternalMemory.PWMSlopeDurationA_read(),\r\n\
        ReefAngel.PWM.GetActinicValue()\r\n\
        ));\r\n\
    ReefAngel.PWM.SetDaylight(PWMSlope(\r\n\
        InternalMemory.StdLightsOnHour_read(),\r\n\
        InternalMemory.StdLightsOnMinute_read(),\r\n\
        InternalMemory.StdLightsOffHour_read(),\r\n\
        InternalMemory.StdLightsOffMinute_read(),\r\n\
        InternalMemory.PWMSlopeStartD_read(),\r\n\
        InternalMemory.PWMSlopeEndD_read(),\r\n\
        InternalMemory.PWMSlopeDurationD_read(),\r\n\
        ReefAngel.PWM.GetDaylightValue()\r\n\
        ));\r\n");
		}
		f.Write(s, s.GetLength());
	}

	// Custom code comment goes here
	s = _T("\
    ////// Place your custom code below here\r\n\
    \r\n\r\n\
    ////// Place your custom code above here\r\n");
	f.Write(s, s.GetLength());

	if ( m_fPortal )
	{
		// 0.9.X has a built-in timer with the function
		CString sUser, sKey;
		// TODO improve storing and retrieving portal info
		LoadPortalInfo(sUser, sKey);
		if ( !sUser.IsEmpty() )
		{
			s = sTab + _T("// This sends all the data to the portal\r\n") +
				sTab + _T("// Do not add any custom code that changes any relay status after this line\r\n") +
				sTab + _T("// The only code after this line should be the ShowInterface function\r\n");
			f.Write(s, s.GetLength());
			if ( sKey.IsEmpty() )
			{
				s.Format(_T("%sReefAngel.Portal(\"%s\");\r\n"), sTab, sUser);
			}
			else
			{
				s.Format(_T("%sReefAngel.Portal(\"%s\", \"%s\");\r\n"), sTab, sUser, sKey);
			}
			f.Write(s, s.GetLength());
		}
	}
	// add showinterface to the end
	s = _T("\r\n\
    // This should always be the last line\r\n\
    ReefAngel.ShowInterface();\r\n\
}\r\n\r\n");
	f.Write(s, s.GetLength());
}
