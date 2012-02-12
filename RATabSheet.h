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
	void CheckLaunch(BOOL fSkipPrompt);
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
	void UpdateControllerTab();
	inline BOOL IsStandardTab() { return m_iCurrentTab == Standard; }
	inline void SetDeveloperMode(BOOL fEnable = TRUE) { m_fDevMode = fEnable; }
	
protected:
	DECLARE_MESSAGE_MAP()
	int m_iNumTabs;
	int m_iCurrentTab;
	CDialog* m_pTabs[5];
	BOOL m_fDevMode;

	enum Tabs {
		Controller,
		Features,
		MainRelay,
		CustomMenu,
		//Colors,
		Standard,
	};

public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


