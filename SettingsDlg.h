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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	// 0 - Always Save; 1 - Prompt to Save; 2 - Never Save
	int m_iSaveRegistry;
	// 0 - Always Launch; 1 - Prompt to Launch; 2 - Never Launch
	int m_iLaunchArduino;
	// Is the arduino.exe file in the arduino directory?
	BOOL m_fHasArduinoExe;
	// Folder to save the sketch files
	CString m_sSketchFolder;
	// Folder for Arduino
	CString m_sArduinoFolder;
	afx_msg void OnBnClickedSketchBtnBrowse();
	afx_msg void OnBnClickedArduinoBtnBrowse();
	afx_msg void OnBnClickedBtnClear();
};
