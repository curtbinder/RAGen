#pragma once


// RATabSheet

class RATabSheet : public CTabCtrl
{
	DECLARE_DYNAMIC(RATabSheet)

public:
	RATabSheet();
	virtual ~RATabSheet();
	void Init();
	void SetRectangle();
	void Generate();
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
	void EnableAdvanced();
	inline BOOL IsMemoryTab() { return (m_iCurrentTab == Memory); }
	void SetDeveloperMode(BOOL fEnable = TRUE) { m_fDevMode = fEnable; }
	
	TCHAR m_sOutputDirectory[MAX_PATH];  //!< Output directory
	TCHAR m_sSketchDirectory[MAX_PATH];  //!< Sketch directory
	TCHAR m_sArduinoDirectory[MAX_PATH];  //!< Arduino directory
	TCHAR m_sCurrentDirectory[MAX_PATH];  //!< Current directory
	int iSaveReg;  //!< Variable for saving to registry, 0 - always, 1 - prompt, 2 - never

protected:
	DECLARE_MESSAGE_MAP()
	int m_iNumTabs;
	int m_iCurrentTab;
	CDialog* m_pTabs[4];
	BOOL m_fDevMode;

	enum Tabs {
		Features,
		PDE,
		Memory,
		//Colors,
		Standard,
	};

public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


