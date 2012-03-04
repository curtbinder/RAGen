#include "StdAfx.h"
#include "Resource.h"
#include "GlobalVars.h"
#include "CustomMenu.h"
#include "InternalMemoryDefaults.h"

// TODO Consider moving Resource.h out of here and handle the local functions elsewhere or some other way
// TODO Added in Default Menu (which is just the SIMPLE_MENU)

CCustomMenu::CCustomMenu(void)
{
	m_Labels.SetSize(MENU_MAX);
	m_Functions.SetSize(MENU_MAX);
	LoadInitialMenu();
	FillFunctionCodes();
	TRACE("INIT\n");
}

CCustomMenu::~CCustomMenu(void)
{
}

void CCustomMenu::FillFunctionCodes()
{
	m_Codes[DISPLAY_VERSION].id = ID_CODE_DISPLAY_VERSION;
	m_Codes[DISPLAY_VERSION].sRAFunction = _T("ReefAngel.DisplayVersion();\r\n");
	m_Codes[FEEDING_MODE].id = ID_CODE_FEEDING_MODE;
	m_Codes[FEEDING_MODE].sRAFunction = _T("ReefAngel.FeedingModeStart();\r\n");
	m_Codes[WATER_CHANGE_MODE].id = ID_CODE_WATER_CHANGE_MODE;
	m_Codes[WATER_CHANGE_MODE].sRAFunction = _T("ReefAngel.WaterChangeModeStart();\r\n");
	m_Codes[ATO_CLEAR].id = ID_CODE_ATO_CLEAR;
	m_Codes[ATO_CLEAR].sRAFunction = _T("ReefAngel.ATOClear();\r\n");
	m_Codes[OVERHEAT_CLEAR].id = ID_CODE_OVERHEAT_CLEAR;
	m_Codes[OVERHEAT_CLEAR].sRAFunction = _T("ReefAngel.OverheatClear();\r\n");
	m_Codes[DISPLAY_ENTRY].id = ID_CODE_DISPLAY_ENTRY;
	m_Codes[DISPLAY_ENTRY].sRAFunction = _T("ReefAngel.DisplayMenuEntry(\"TEXT\");\r\n");
	m_Codes[CALIBRATE_PH].id = ID_CODE_CALIBRATE_PH;
	m_Codes[CALIBRATE_PH].sRAFunction = _T("ReefAngel.SetupCalibratePH();\r\nReefAngel.DisplayedMenu = ALT_SCREEN_MODE;\r\n");
	m_Codes[CALIBRATE_SALINITY].id = ID_CODE_CALIBRATE_SALINITY;
	m_Codes[CALIBRATE_SALINITY].sRAFunction = _T("ReefAngel.SetupCalibrateSalinity();\r\nReefAngel.DisplayedMenu = ALT_SCREEN_MODE;\r\n");
	m_Codes[DATE_TIME].id = ID_CODE_DATE_TIME;
	m_Codes[DATE_TIME].sRAFunction = _T("ReefAngel.SetupDateTime();\r\nReefAngel.DisplayedMenu = ALT_SCREEN_MODE;\r\n");
	m_Codes[LIGHTS_ON].id = ID_CODE_LIGHTS_ON;
	m_Codes[LIGHTS_ON].sRAFunction = _T("\
ReefAngel.Relay.RelayMaskOn = ReefAngel.LightsOnPorts;\r\n\
#ifdef RelayExp\r\n\
for ( byte i = 0; i < MAX_RELAY_EXPANSION_MODULES; i++ )\r\n\
{\r\n\
    ReefAngel.Relay.RelayMaskOnE[i] = ReefAngel.LightsOnPortsE[i];\r\n\
}\r\n\
#endif  // RelayExp\r\n\
ReefAngel.Relay.Write();\r\n\
");
	m_Codes[LIGHTS_OFF].id = ID_CODE_LIGHTS_OFF;
	m_Codes[LIGHTS_OFF].sRAFunction = _T("\
ReefAngel.Relay.RelayMaskOn = 0;\r\n\
#ifdef RelayExp\r\n\
for ( byte i = 0; i < MAX_RELAY_EXPANSION_MODULES; i++ )\r\n\
{\r\n\
    ReefAngel.Relay.RelayMaskOnE[i] = 0;\r\n\
}\r\n\
#endif  // RelayExp\r\n\
ReefAngel.Relay.Write();\r\n\
");
	m_Codes[WATCHDOG].id = ID_CODE_WATCHDOG;
	m_Codes[WATCHDOG].sRAFunction = _T("wdt_reset();\r\n");
}

void CCustomMenu::GetMenuFunction(int index, CString &fun)
{
	if ( (index < 0) || (index >= MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return;
	}

	// Add in the function prototype and closing parenthesis
	fun.Format(_T("void MenuEntry%d()\r\n{\r\n"), index+1);
	fun += m_Functions.GetAt(index);
	fun += _T("\r\n}\r\n");
}

void CCustomMenu::GetMenuFunctionCode(int index, CString &fun)
{
	if ( (index < 0) || (index >= MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return;
	}
	fun = m_Functions.GetAt(index);
}

void CCustomMenu::SetMenuFunction(int index, CString fun)
{
	if ( (index < 0) || (index >= MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return;
	}

	m_Functions.SetAt(index, fun);
}

void CCustomMenu::GetMenuLabel(int index, CString &label)
{
	if ( (index < 0) || (index >= MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return;
	}
	label = m_Labels.GetAt(index);
}

void CCustomMenu::SetMenuLabel(int index, CString label)
{
	if ( (index < 0) || (index >= MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return;
	}
	m_Labels.SetAt(index, label);
}

void CCustomMenu::WriteMenuCode(CFile &f, int qty)
{
	CString s;
	// Create the custom menu here
	// Custom Menu requires avr/pgmspace.h
	s = _T("#include <avr/pgmspace.h>\r\n");
	f.Write(s, s.GetLength());
	int i;
	CString labels = _T("");
	CString menu = _T("PROGMEM const char *menu_items[] = {\r\n");
	CString functions = _T("");
	CString label;
	for ( i = 0; i < qty; i++ )
	{
		GetMenuLabel(i, label);
		s.Format(_T("prog_char menu%d_label[] PROGMEM = \"%s\";\r\n"), i, label);
		labels += s;
		s.Format(_T("menu%d_label%c "), i, (i+1==qty)?' ':',');
		menu += s;
		GetMenuFunction(i, s);
		functions += s;
	}
	menu += _T("};\r\n\r\n");
	functions += _T("\r\n");
	f.Write(labels, labels.GetLength());
	f.Write(menu, menu.GetLength());
	f.Write(functions, functions.GetLength());
}

void CCustomMenu::LoadInitialMenu()
{
	TRACE("Load Initial Menu\n");
	CString s;
	for ( int i = 0; i < MENU_MAX; i++ )
	{
		s.Format(_T("ReefAngel.DisplayMenuEntry(\"Item %d\");\r\n"), i+1);
		m_Functions.SetAt(i, s);
		s.Format(_T("Item %d"), i+1);
		m_Labels.SetAt(i, s);
	}
}

void CCustomMenu::LoadSimpleMenu()
{
	TRACE("Load Simple Menu\n");
	// Clear out the menus first
	LoadInitialMenu();
	// Load in the simple menu default values that are always there
	AddFeedingModeItem(0);
	AddWaterChangeModeItem(1);
	AddATOClearItem(2);
	AddOverheatClearItem(3);
	AddPHCalibrationItem(4);
}

void CCustomMenu::AddSalinityItem(int i)
{
	m_Labels.SetAt(i, _T("Sal Calibration"));
	m_Functions.SetAt(i, m_Codes[CALIBRATE_SALINITY].sRAFunction);
}

void CCustomMenu::AddDateTimeItem(int i)
{
	m_Labels.SetAt(i, _T("Date / Time"));
	m_Functions.SetAt(i, m_Codes[DATE_TIME].sRAFunction);
}

void CCustomMenu::AddVersionItem(int i)
{
	m_Labels.SetAt(i, _T("Version"));
	m_Functions.SetAt(i, m_Codes[DISPLAY_VERSION].sRAFunction);
}

void CCustomMenu::AddPHCalibrationItem(int i)
{
	m_Labels.SetAt(i, _T("PH Calibration"));
	m_Functions.SetAt(i, m_Codes[CALIBRATE_PH].sRAFunction);
}

void CCustomMenu::AddFeedingModeItem(int i)
{
	m_Labels.SetAt(i, _T("Feeding"));
	m_Functions.SetAt(i, m_Codes[FEEDING_MODE].sRAFunction);
}

void CCustomMenu::AddWaterChangeModeItem(int i)
{
	m_Labels.SetAt(i, _T("Water Change"));
	m_Functions.SetAt(i, m_Codes[WATER_CHANGE_MODE].sRAFunction);
}

void CCustomMenu::AddATOClearItem(int i)
{
	m_Labels.SetAt(i, _T("ATO Clear"));
	m_Functions.SetAt(i, m_Codes[ATO_CLEAR].sRAFunction + _T("ReefAngel.DisplayMenuEntry(\"Clear ATO Timeout\");"));
}

void CCustomMenu::AddOverheatClearItem(int i)
{
	m_Labels.SetAt(i, _T("Overheat Clear"));
	m_Functions.SetAt(i, m_Codes[OVERHEAT_CLEAR].sRAFunction + _T("ReefAngel.DisplayMenuEntry(\"Clear Overheat\");"));
}

void CCustomMenu::GetPresetFunctionCode(int id, CString &fun)
{
	fun = _T("// Not found\r\n");
	for ( int i = 0; i < MAX_FUNCTIONS; i++ )
	{
		if ( m_Codes[i].id == id )
		{
			fun = m_Codes[i].sRAFunction;
			break;
		}
	}
}
