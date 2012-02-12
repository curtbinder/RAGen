#pragma once

class CCustomMenu
{
public:
	CCustomMenu(void);
	~CCustomMenu(void);

	// TODO possibly not needed
	inline BOOL IsCustomMenuEnabled() { return m_fEnabled; }
	inline void EnableCustomMenu(BOOL fEnable = TRUE) { m_fEnabled = fEnable; }
	inline int GetMenuQuantity() { return m_iMenuQuantity; }
	inline void SetMenuQuantity(int qty) { m_iMenuQuantity = qty; }

	void GetMenuFunction(int index, CString &fun);
	void GetMenuFunctionCode(int index, CString &fun);
	void SetMenuFunction(int index, CString fun);
	void GetMenuLabel(int index, CString &label);
	void SetMenuLabel(int index, CString label);

	void WriteMenuCode(CFile &f);

private:
	CStringArray m_Functions;
	CStringArray m_Labels;
	// TODO possibly not needed
	int m_iMenuQuantity;
	BOOL m_fEnabled;
};
