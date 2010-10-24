#pragma once


// RAStdPage dialog

class RAStdPage : public CDialog
{
	DECLARE_DYNAMIC(RAStdPage)

public:
	RAStdPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAStdPage();

// Dialog Data
	enum { IDD = IDD_RASTDPAGE };

	TCHAR m_sSketchDirectory[MAX_PATH];  //!< Sketch directory
	int iSaveReg;  //!< Variable for saving to registry, 0 - always, 1 - prompt, 2 - never

	inline void Use12Hour(BOOL f = TRUE) { fUse12Hour = f; }

protected:
	BOOL fUse12Hour;
	BOOL fTemp;  //!< Temperature flag, 0 - Farenheit, 1 - Celcuis
	BOOL fLogging;  //!< Logging mode flag, 0 - no logging, 1 - Logging enabled

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	int m_iMHDelay;
	int m_iWM1Interval;
	int m_iWM1IntervalTemp;
	int m_iWM2Interval;
	int m_iWM2IntervalTemp;
	int m_iFeeding;
	int m_iLCD;
	int m_iATOTimeout;

	void InitSpinners();
	void InitTimeBoxes();
	void InitTempBoxes();
	void LoadDefaults();
	BOOL WritePDE();
	void SaveSettings();
	void LoadSettings();
	void UpdateTemperatureSelections(int hOn, int hOff, int cOn, int cOff, int o);
	int ConvertTemp(int nTempOffset, BOOL fToF = TRUE);

public:
	void OnBnClickedBtnGenerate();
	void OnResetAll();
	void OnResetSaved();
	afx_msg void OnBnClickedCkWm1AlwaysOn();
	afx_msg void OnBnClickedCkWm2AlwaysOn();
	afx_msg void OnBnClickedStdCkAto();
	afx_msg void OnBnClickedStdCkStdLights();
	afx_msg void OnBnClickedStdCkMhLights();
	afx_msg void OnBnClickedStdCkWm2();
	afx_msg void OnBnClickedStdCkWm1();
	afx_msg void OnBnClickedStdCkChiller();
	afx_msg void OnBnClickedStdCkHeater();
	afx_msg void OnBnClickedStdTemp0();
	afx_msg void OnBnClickedStdTemp1();
};
