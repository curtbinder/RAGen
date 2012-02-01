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
	void GetFileExtension(CString &s);
	void ImportFeatures(CString sFile);
	void ShowUnknownFeatures();
	inline BOOL IsStandardTab() { return m_iCurrentTab == Standard; }
	void SetDeveloperMode(BOOL fEnable = TRUE) { m_fDevMode = fEnable; }
	
protected:
	void LaunchArduino();
	DECLARE_MESSAGE_MAP()
	int m_iNumTabs;
	int m_iCurrentTab;
	CDialog* m_pTabs[4];
	BOOL m_fDevMode;

	enum Tabs {
		Features,
		MainRelay,
		//Colors,
		Standard,
	};

public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


