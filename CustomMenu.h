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

	void GetPresetFunctionCode(int id, CString &fun);

private:
	CStringArray m_Functions;
	CStringArray m_Labels;
	// TODO possibly not needed
	int m_iMenuQuantity;
	BOOL m_fEnabled;

	enum _PresetCodes {
		DISPLAY_VERSION,
		FEEDING_MODE,
		WATER_CHANGE_MODE,
		ATO_CLEAR,
		OVERHEAT_CLEAR,
		DISPLAY_ENTRY,
		CALIBRATE_PH,
		CALIBRATE_SALINITY,
		DATE_TIME,
		LIGHTS_ON,
		LIGHTS_OFF,
		WATCHDOG,
		// TODO add new preset codes above this line
		MAX_FUNCTIONS
	};
	device m_Codes[MAX_FUNCTIONS];
	void FillFunctionCodes();

	void GetMenuFunction(int index, CString &fun);
};
