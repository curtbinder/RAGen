// RAInternalMemoryPage.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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

	// Implementation
protected:
	HICON m_hIcon;
	int m_iLocationIndex;

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
		ATOEXTENDEDTIMEOUT,
		ATOHIGHEXTENDEDTIMEOUT,
		MAX_LOCATIONS
	};

	MemLocation m_Locations[MAX_LOCATIONS];
	int m_Defaults[MAX_LOCATIONS];

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	int GetMaxLocations();
	void InitDefaultsArray();
	void InitLocationBox();
	void EnableValueControls(int iLocation);
	void UpdateValueControls(int iLocation);
	void ChangeControlRanges(int iLocation);
	void SetMemoryLocation(int iLocation, CString sLabel, CString sFunction, int iValue, BOOL fCombo);
	void SetMemoryValue(int iLocation, int iValue);
	void LoadDefaults();
	void SaveCurrentValue();
	BOOL WriteValues();
	void LoadValues();
	void SaveValues();
	void SetStatus(UINT id);
	void SetStatus(LPCSTR s);
	
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnGenerate();
	afx_msg void OnBnClickedBtnLaunch();
	afx_msg void OnCbnSelchangeMemoryCbLocations();
	//void OnResetAll();
	//void OnResetSaved();
};
