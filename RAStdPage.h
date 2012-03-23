// RAStdPage.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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

	CString sFilename;  //!< Filename of the PDE file generated

	inline void Use12Hour(BOOL f = TRUE) { fUse12Hour = f; }
	inline void LoadSavedSettings(BOOL f = FALSE) { fLoadSaved = f; }

protected:
	BOOL fLoadSaved;
	BOOL fUse12Hour;
	BOOL fTemp;  //!< Temperature flag, 0 - Fahrenheit, 1 - Celcuis
	BOOL fBanner;  //!< Web banner mode flag, 0 - no banner / logging, 1 - web banner enabled
	
	BOOL fDisableATO;
	BOOL fDisableStdLights;
	BOOL fDisableMHLights;
	BOOL fDisableWM1;
	BOOL fDisableWM2;
	BOOL fDisableChiller;
	BOOL fDisableHeater;
	BOOL fDisableSump;

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
	void RestorePorts();
	void UpdateDisablePortsVariables();
	void UpdateWMControls(int nWM);

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
