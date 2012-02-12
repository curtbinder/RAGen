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
	fun.Format(_T("void MenuEntry%d()\r\n{"), index+1);
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

void CCustomMenu::WriteMenuCode(CFile &f)
{
	// TODO write out the custom menu
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
	LoadInitialMenu();
	m_Labels.SetAt(0, _T("Feeding"));
	m_Functions.SetAt(0, _T("ReefAngel.FeedingModeStart();"));
	m_Labels.SetAt(1, _T("Water Change"));
	m_Functions.SetAt(1, _T("ReefAngel.WaterChangeModeStart();"));
	m_Labels.SetAt(2, _T("ATO Clear"));
	m_Functions.SetAt(2, _T("ReefAngel.ATOClear();\r\nReefAngel.DisplayMenuEntry(\"Clear ATO Timeout\");"));
	m_Labels.SetAt(3, _T("Overheat Clear"));
	m_Functions.SetAt(3, _T("ReefAngel.OverheatClear();\r\nReefAngel.DisplayMenuEntry(\"Clear Overheat\");"));
	m_Labels.SetAt(4, _T("PH Calibration"));
	m_Functions.SetAt(4, _T("ReefAngel.SetupCalibratePH();"));
	// next 3 are optional based on enabled features
	m_Labels.SetAt(5, _T("Sal Calibration"));
	m_Functions.SetAt(5, _T("ReefAngel.SetupCalibrateSalinity();"));
	m_Labels.SetAt(6, _T("Date / Time"));
	m_Functions.SetAt(6, _T("ReefAngel.SetupDateTime();"));
	m_Labels.SetAt(7, _T("Version"));
	m_Functions.SetAt(7, _T("ReefAngel.DisplayVersion();"));
}
