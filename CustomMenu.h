#pragma once

class CCustomMenu
{
public:
	CCustomMenu(void);
	~CCustomMenu(void);

	inline BOOL IsCustomMenuEnabled() { return m_fEnabled; }
	inline void EnableCustomMenu(BOOL fEnable = TRUE) { m_fEnabled = fEnable; }
	inline int GetMenuQuantity() { return m_iMenuQuantity; }
	inline void SetMenuQuantity(int qty) { m_iMenuQuantity = qty; }

	CString GetMenuFunction(int index);
	void SetMenuFunction(int index, CString fun);

private:
	CStringArray m_Functions;
	int m_iMenuQuantity;
	BOOL m_fEnabled;
};
