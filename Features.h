#pragma once


typedef struct _FeatureData {
	UINT uStringID;
	CString sDefine;
	BOOL fValue;
} FeatureData;

class CFeatures
{
public:
	CFeatures(void);
	~CFeatures(void);

	enum _FeaturesList {
		NONE = 0,
		DISPLAY_IMAGES,
		SETUP_EXTRAS,
		DOSING_PUMP_SETUP,
		WAVEMAKER_SETUP,
		OVERHEAT_SETUP,
		DATE_TIME_SETUP,
		VERSION_MENU,
		ATO_SETUP,
		METAL_HALIDE_SETUP,
		DIRECT_TEMP_SENSOR,
		DISPLAY_LED_PWM,
		WIFI,
		SINGLE_ATO,
		STANDARD_LIGHT_SETUP,
		REMOVE_ALL_LIGHTS,
		SAVE_RELAY_STATE,
		EXPANSION_MODULE,
		DOSING_INTERVAL_SETUP,
		WDT,
		CUSTOM_MENU,
		SIMPLE_MENU,
		PWM_EXPANSION,
		CUSTOM_MAIN,
		CUSTOM_COLORS, // ColorsPDE
		ATO_LOGGING,
		EXCEED_FLAGS,
		SALINITY,
		RF,
		ORP,
		IO,
		AI,
		FONT_8x8,
		FONT_8x16,
		FONT_12x16,
		NUMBERS_8x8,
		NUMBERS_8x16,
		NUMBERS_12x16,
		NUMBERS_16x16,
		CUSTOM_VARIABLES,
		// add other features here, above MAX_FEATURES
		MAX_FEATURES  // ALWAYS the last entry
	};

	int iCustomMenuEntries;
	int iInstalledExpansionModules;

	// File Actions
	BOOL Read(CString sFile);
	BOOL Write(CString sLibraryFolder);
	void ShowUnknownFeatures();

	// Initialize default values
	void LoadDefaults();
	BOOL IsDefaultEnabledFeature(int featureID);
	// Clears all the values
	void Clear();
	// Removes unnecessary features
	void CleanupFeatures();
	void ClearINOFeatures();
	BOOL IsCustomMenu();
	
	CString GetEnabledList();

	// Feature Data functions
	UINT GetFeatureStringID(int index);
	CString GetFeatureDefine(int index);
	BOOL GetFeatureValue(int index);
	void SetFeatureValue(int index, BOOL fValue);


private:
	FeatureData m_fd[MAX_FEATURES];
	CString m_sUnknown;

	void InitFeatureData();
	void SetFeatureData(int index, UINT stringID, CString sDefine, BOOL fValue = FALSE);
	void ProcessFeature(CString sFeature, CString sValue = _T(""));
};
