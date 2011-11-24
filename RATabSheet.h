#pragma once

#include "GlobalVars.h"

// RATabSheet

class RATabSheet : public CTabCtrl
{
	DECLARE_DYNAMIC(RATabSheet)

public:
	RATabSheet();
	virtual ~RATabSheet();
	void Init();
	void SetRectangle();
	void SaveFeatures();
	void Generate();
	void CheckLaunch(BOOL fSkipPrompt = FALSE);
	void ResetAll();
	void ResetSaved();
	void ResetPorts();
	void ResetTemp();
	void ResetLogging();
	void ResetFeedingMode();
	void ResetWaterChangeMode();
	void ResetOverheat();
	void ResetLightsOn();
	void UpdateSettingsForTabs();
	void GetFilename(CString &s);
	void ImportFeatures(CString sFile);
	void ShowUnknownFeatures();
	inline BOOL IsStandardTab() { return m_iCurrentTab == Standard; }
	void SetDeveloperMode(BOOL fEnable = TRUE) { m_fDevMode = fEnable; }
	
	TCHAR m_sSketchDirectory[MAX_PATH];  //!< Sketch directory
	TCHAR m_sArduinoDirectory[MAX_PATH];  //!< Arduino directory
	TCHAR m_sLibraryDirectory[MAX_PATH];  //!< Libraries directory
	int iSaveReg;  //!< Variable for saving to registry, 0 - always, 1 - prompt, 2 - never
	int iLaunch;
	int iDevVersion;
	BOOL fHasArduinoExe;
	Features m_Features;

protected:
	void LaunchArduino();
	DECLARE_MESSAGE_MAP()
	int m_iNumTabs;
	int m_iCurrentTab;
	CDialog* m_pTabs[4];
	BOOL m_fDevMode;

	enum Tabs {
		Features,
		PDE,
		//Colors,
		Standard,
	};

public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


