
#pragma once


// RAInternalMemoryPage dialog
class RAInternalMemoryPage : public CDialog
{
// Construction
public:
	RAInternalMemoryPage(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RAMEMORYPAGE };

	TCHAR m_sSketchDirectory[MAX_PATH];  //!< Sketch directory
	//TCHAR m_sCurrentDirectory[MAX_PATH];  //!< Current directory
	int iSaveReg;  //!< Variable for saving to registry, 0 - always, 1 - prompt, 2 - never
	CString sFilename;  //!< Filename of the PDE file generated

	inline void Use12Hour(BOOL f = TRUE) { fUse12Hour = f; }
	inline void UseDegreeF(BOOL f = TRUE) { fDegF = f; }

	// Implementation
protected:
	BOOL fUse12Hour;
	BOOL fDegF;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void InitSpinners();
	void InitTimeBoxes();
	void InitTempBoxes();
	void LoadDefaults();
	BOOL WriteValues();
	void LoadValues();
	void SaveValues();
	void EnableTimeoutsPH(BOOL bEnable);
	void UpdateCheckBoxes();
	
	DECLARE_MESSAGE_MAP()

	int m_iMHDelay;
	int m_iWM1Interval;
	int m_iWM1IntervalTemp;
	int m_iWM2Interval;
	int m_iWM2IntervalTemp;
	int m_iActinic;
	int m_iDaylight;
	int m_iDP1RunTime;
	int m_iDP2RunTime;
	int m_iFeeding;
	int m_iLCD;
	int m_iPH7;
	int m_iPH10;
	int m_iATOLowTimeout;
	int m_iATOHighTimeout;
	int m_iATOLowInterval;
	int m_iATOLowIntervalTemp;
	int m_iATOHighInterval;
	int m_iATOHighIntervalTemp;

public:
	afx_msg void OnBnClickedCkAtoLowInterval();
	afx_msg void OnBnClickedCkAtoHighInterval();
	afx_msg void OnBnClickedCkWm1AlwaysOn();
	afx_msg void OnBnClickedCkWm2AlwaysOn();
	void OnEditTimeoutsPH();
	void OnBnClickedBtnGenerate();
	void OnResetAll();
	void OnResetSaved();
};
