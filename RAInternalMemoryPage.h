
#pragma once

// RAInternalMemoryPage dialog
class RAInternalMemoryPage : public CDialog
{
	DECLARE_DYNAMIC(RAInternalMemoryPage)

// Construction
public:
	RAInternalMemoryPage(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MEMORY };

	CString sFilename;  //!< Filename of the file generated
	CString sFileExtension;

	inline void Use12Hour(BOOL f = TRUE) { fUse12Hour = f; }
	inline void UseDegreeF(BOOL f = TRUE) { fDegF = f; }

	// Implementation
protected:
	HICON m_hIcon;
	BOOL fUse12Hour;
	BOOL fDegF;

	enum _Locations{
		MHONHOUR,
		MHONMINUTE,
		MHOFFHOUR,
		MHOFFMINUTE,
		STDLIGHTSONHOUR,
		STDLIGHTSONMINUTE,
		STDLIGHTSOFFHOUR,
		STDLIGHTSOFFMINUTE,
		WM1TIMER,
		WM2TIMER,
		DP1TIMER,
		DP2TIMER,
		FEEDINGTIMER,
		LCDTIMER,
		OVERHEATTEMP,
		LEDPWMDAYLIGHT,
		LEDPWMACTINIC,
		HEATERTEMPON,
		HEATERTEMPOFF,
		CHILLERTEMPON,
		CHILLERTEMPOFF,
		ATOTIMEOUT,
		PHMAX,
		PHMIN,
		MHDELAY,
		DP1ONHOUR,
		DP1ONMINUTE,
		DP2ONHOUR,
		DP2ONMINUTE,
		ATOHOURINTERVAL,
		ATOHIGHHOURINTERVAL,
		ATOHIGHTIMEOUT,
		DP1REPEATINTERVAL,
		DP2REPEATINTERVAL,
		SALMAX,
		PWMSLOPESTARTD,
		PWMSLOPEENDD,
		PWMSLOPEDURATIOND,
		PWMSLOPESTARTA,
		PWMSLOPEENDA,
		PWMSLOPEDURATIONA,
		RFMODE,
		RFSPEED,
		RFDURATION,
		PWMSLOPESTART0,
		PWMSLOPEEND0,
		PWMSLOPEDURATION0,
		PWMSLOPESTART1,
		PWMSLOPEEND1,
		PWMSLOPEDURATION1,
		PWMSLOPESTART2,
		PWMSLOPEEND2,
		PWMSLOPEDURATION2,
		PWMSLOPESTART3,
		PWMSLOPEEND3,
		PWMSLOPEDURATION3,
		PWMSLOPESTART4,
		PWMSLOPEEND4,
		PWMSLOPEDURATION4,
		PWMSLOPESTART5,
		PWMSLOPEEND5,
		PWMSLOPEDURATION5,
		MAX_LOCATIONS
	};

	MemLocation m_Locations[MAX_LOCATIONS];

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	//void InitSpinners();
	//void InitTimeBoxes();
	//void InitTempBoxes();
	void InitLocationBox();
	void SetMemoryLocation(int iLocation, CString sLabel, int iValue, BOOL fCombo);
	void SetMemoryValue(int iLocation, int iValue);
	void LoadDefaults();
	BOOL WriteValues();
	void LoadValues();
	void SaveValues();
	//void EnableTimeoutsPH(BOOL bEnable);
	//void UpdateCheckBoxes();
	void SetStatus(UINT id);
	void SetStatus(LPCSTR s);
	
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
	//afx_msg void OnBnClickedCkAtoLowInterval();
	//afx_msg void OnBnClickedCkAtoHighInterval();
	//afx_msg void OnBnClickedCkWm1AlwaysOn();
	//afx_msg void OnBnClickedCkWm2AlwaysOn();
	//afx_msg void OnBnClickedBtnEnableAdvanced();
	//void OnEditTimeoutsPH();
	afx_msg void OnBnClickedBtnGenerate();
	afx_msg void OnBnClickedBtnLaunch();
	//void OnResetAll();
	//void OnResetSaved();
};
