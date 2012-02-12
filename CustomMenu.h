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

	void GetMenuFunctionCode(int index, CString &fun);
	void SetMenuFunction(int index, CString fun);
	void GetMenuLabel(int index, CString &label);
	void SetMenuLabel(int index, CString label);

	void WriteMenuCode(CFile &f, int qty);
	void LoadInitialMenu();
	void LoadSimpleMenu();
	// 0 based index of menu items
	void AddSalinityItem(int i);
	void AddDateTimeItem(int i);
	void AddVersionItem(int i);
	void AddPHCalibrationItem(int i);
	void AddFeedingModeItem(int i);
	void AddWaterChangeModeItem(int i);
	void AddATOClearItem(int i);
	void AddOverheatClearItem(int i);

private:
	CStringArray m_Functions;
	CStringArray m_Labels;
	// TODO possibly not needed
	int m_iMenuQuantity;
	BOOL m_fEnabled;

	void GetMenuFunction(int index, CString &fun);
};
