#pragma once
#include "InternalMemoryDefaults.h"

class CCustomMenu
{
public:
	CCustomMenu(void);
	~CCustomMenu(void);

	inline BOOL IsCustomMenuEnabled() { return m_fEnabled; }
	inline void EnableCustomMenu(BOOL fEnable = TRUE) { m_fEnabled = fEnable; }
	inline int GetMenuQuantity() { return m_iMenuQuantity; }

	CString GetMenuFunction(int index);

private:
	CStringArray m_Functions[MENU_MAX];
	int m_iMenuQuantity;
	BOOL m_fEnabled;
};
