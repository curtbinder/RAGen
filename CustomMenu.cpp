#include "StdAfx.h"
#include "CustomMenu.h"
#include "InternalMemoryDefaults.h"

// TODO Added in Default Menu (which is just the SIMPLE_MENU)

CCustomMenu::CCustomMenu(void)
{
	m_Functions.SetSize(MENU_MAX);
	CString s;
	for ( int i = 0; i < MENU_MAX; i++ )
	{
		s.Format(_T("    ReefAngel.DisplayMenuEntry(\"Item %d\");\r\n"), i+1);
		//m_Functions.SetAt(i, s);
		m_Functions.Add(s);
	}
}

CCustomMenu::~CCustomMenu(void)
{
}

CString CCustomMenu::GetMenuFunction(int index)
{
	if ( (index < 0) || (index > MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return _T("");
	}

	// Add in the function prototype and closing parenthesis
	CString s;
	s.Format(_T("void MenuEntry%d()\r\n{"), index+1);
	s += m_Functions.GetAt(index);
	s += _T("\r\n}\r\n");
	return s;
}

void CCustomMenu::SetMenuFunction(int index, CString fun)
{
	if ( (index < 0) || (index > MENU_MAX) )
	{
		ASSERT("INVALID MENU INDEX");
		return;
	}

	m_Functions.SetAt(index, fun);
}
