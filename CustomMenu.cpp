#include "StdAfx.h"
#include "CustomMenu.h"
#include "InternalMemoryDefaults.h"

// TODO Added in Default Menu (which is just the SIMPLE_MENU)

CCustomMenu::CCustomMenu(void)
{
	m_Labels.SetSize(MENU_MAX);
	m_Functions.SetSize(MENU_MAX);
	LoadInitialMenu();
	TRACE("INIT\n");
}

CCustomMenu::~CCustomMenu(void)
{
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
	m_Functions.SetAt(i, _T("ReefAngel.SetupCalibrateSalinity();"));
}

void CCustomMenu::AddDateTimeItem(int i)
{
	m_Labels.SetAt(i, _T("Date / Time"));
	m_Functions.SetAt(i, _T("ReefAngel.SetupDateTime();"));
}

void CCustomMenu::AddVersionItem(int i)
{
	m_Labels.SetAt(i, _T("Version"));
	m_Functions.SetAt(i, _T("ReefAngel.DisplayVersion();"));
}

void CCustomMenu::AddPHCalibrationItem(int i)
{
	m_Labels.SetAt(i, _T("PH Calibration"));
	m_Functions.SetAt(i, _T("ReefAngel.SetupCalibratePH();"));
}

void CCustomMenu::AddFeedingModeItem(int i)
{
	m_Labels.SetAt(i, _T("Feeding"));
	m_Functions.SetAt(i, _T("ReefAngel.FeedingModeStart();"));
}

void CCustomMenu::AddWaterChangeModeItem(int i)
{
	m_Labels.SetAt(i, _T("Water Change"));
	m_Functions.SetAt(i, _T("ReefAngel.WaterChangeModeStart();"));
}

void CCustomMenu::AddATOClearItem(int i)
{
	m_Labels.SetAt(i, _T("ATO Clear"));
	m_Functions.SetAt(i, _T("ReefAngel.ATOClear();\r\nReefAngel.DisplayMenuEntry(\"Clear ATO Timeout\");"));
}

void CCustomMenu::AddOverheatClearItem(int i)
{
	m_Labels.SetAt(i, _T("Overheat Clear"));
	m_Functions.SetAt(i, _T("ReefAngel.OverheatClear();\r\nReefAngel.DisplayMenuEntry(\"Clear Overheat\");"));
}
