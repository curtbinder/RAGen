// SettingsDlg.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

#include "Resource.h"

// SettingsDlg dialog

class SettingsDlg : public CDialog
{
	DECLARE_DYNAMIC(SettingsDlg)

public:
	SettingsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~SettingsDlg();

// Dialog Data
	enum { IDD = IDD_SETTINGS };

protected:
	HICON m_hIcon;
	void UpdateArduinoStatus();
	void UpdateDevVersionMenu();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	// 0 - Always Save; 1 - Prompt to Save; 2 - Never Save
	int m_iSaveRegistry;
	// 0 - Always Launch; 1 - Prompt to Launch; 2 - Never Launch
	int m_iLaunchArduino;
	// 0 - normal, 1 - development libraries
	int m_iAppMode;
	// 0 - autodetect, 1 - force 0.8.x, 2 - force 0.9.x or later
	int m_iDevVersion;
	// Is the arduino.exe file in the arduino directory?
	BOOL m_fHasArduinoExe;
	// Folder for Arduino
	CString m_sArduinoFolder;
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnCbnSelchangeSettingsCbAppMode();
};
