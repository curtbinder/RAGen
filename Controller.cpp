#include "StdAfx.h"
#include "Resource.h"
#include "Controller.h"
#include "RAGen.h"
#include "WebBannerDlg.h"
#include "cb_FileVersion.h"
#include "WifiPasswordDlg.h"

// The Controller
CController a_Controller;


CController::CController(void)
{
	m_sFilename = _T("");
	m_sExtension = _T("");
	m_fBanner = FALSE;
	m_fTemp = FALSE;
	LoadDeviceFunctions();
}

CController::~CController(void)
{
}

void CController::LookupDeviceFunction(int Device, CString &sFunction)
{
	sFunction = Devices[Device].sRAFunction;
}

void CController::LoadDeviceFunctions()
{
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

	if ( theApp.f09xDev )
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
	if ( theApp.f09xDev ) 
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
	if ( theApp.f09xDev )
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
#include <PWM.h>\r\n\
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
}

void CController::WriteCustomMenu(CFile &f)
{
	CString s;
	if ( theApp.f09xDev )
	{
		if ( Features.GetFeatureValue(Features.CUSTOM_MENU) )
		{
			// Custom Menu requires avr/pgmspace.h
			s = _T("#include <avr/pgmspace.h>\r\n");
			f.Write(s, s.GetLength());
		}
	}
	else
	{
		// web banner is only with 0.8.5.x code
		if ( m_fBanner || Features.GetFeatureValue(Features.CUSTOM_MENU) )
		{
			// Banner & Custom Menu require avr/pgmspace.h
			s = _T("#include <avr/pgmspace.h>\r\n");
			f.Write(s, s.GetLength());
		}
		if ( m_fBanner )
		{
			WebBannerInfo wi;
			LoadWebBannerInfoDefaults(wi);
			s.Format(_T("\
// Labels for the web banner\r\n\
%s\r\n\
"), GetWebBannerInfoString(wi));
			f.Write(s, s.GetLength());
		}
	}

	if ( Features.GetFeatureValue(Features.CUSTOM_MENU) )
	{
		// Create the custom menu here
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
    ReefAngel.Init();  //Initialize controller\r\n\
");
	f.Write(s, s.GetLength());
	// Add in Custom Menu if enabled
	if ( Features.GetFeatureValue(Features.CUSTOM_MENU) )
	{
		s = sTab + _T("ReefAngel.InitMenu(pgm_read_word(&(menu_items[0])),SIZE(menu_items));\r\n");
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
		s = sTab + GetWifiAuthenticationString();
		f.Write(s, s.GetLength());
	}

	// web banner timer
	if ( m_fBanner && !theApp.f09xDev )
	{
		WebBannerInfo wi;
		LoadWebBannerInfoDefaults(wi);
		s.Format(_T("\
    // Initialize and start the web banner timer\r\n\
    ReefAngel.LoadWebBanner(pgm_read_word(&(webbanner_items[0])), SIZE(webbanner_items));\r\n\
    ReefAngel.Timer[4].SetInterval(%d);  // set interval to %d seconds\r\n\
    ReefAngel.Timer[4].Start();\r\n"), wi.nInterval, wi.nInterval);
		f.Write(s, s.GetLength());
	}

	// add in an extra line to separate first part between the modes
	s = _T("\r\n");
	f.Write(s, s.GetLength());

	/*
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
	for ( int i = 0; i < MAX_PORTS; i++ )
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
	*/
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
    // Specific functions\r\n\
");
	f.Write(s, s.GetLength());
	/*
	// Specific functions
	for ( int i = 0; i < MAX_PORTS; i++ )
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
	*/

	if ( m_fBanner  )
	{
		// 0.9.X has a built-in timer with the function
		if ( theApp.f09xDev )
		{
			// TODO improve to include the scenario for passwords
			// Portal("user"); and Portal("user", "pass");
			s.Format(_T("\
	ReefAngel.Portal(\"%s\");\r\n"), _T("userid"));
		}
		else
		{
			// 0.8.5.X uses a timer for sending the data
			s = _T("\r\n\
    // Web Banner stuff\r\n\
    if(ReefAngel.Timer[4].IsTriggered())\r\n\
    {\r\n\
        ReefAngel.Timer[4].Start();\r\n\
        ReefAngel.WebBanner();\r\n\
    }\r\n\
");
		}
		f.Write(s, s.GetLength());
	}
	
	// add showinterface to the end
	s = _T("\r\n\
    ReefAngel.ShowInterface();\r\n\
}\r\n\r\n");
	f.Write(s, s.GetLength());
}
