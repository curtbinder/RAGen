#include "StdAfx.h"
#include "CustomMenu.h"
#include "InternalMemoryDefaults.h"

// TODO Added in Default Menu (which is just the SIMPLE_MENU)

CCustomMenu::CCustomMenu(void)
{
	m_Labels.SetSize(MENU_MAX);
	m_Functions.SetSize(MENU_MAX);
	CString s;
	for ( int i = 0; i < MENU_MAX; i++ )
	{
		s.Format(_T("ReefAngel.DisplayMenuEntry(\"Item %d\");\r\n"), i+1);
		m_Functions.SetAt(i, s);
		s.Format(_T("Item %d"), i+1);
		m_Labels.SetAt(i, s);
	}
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
