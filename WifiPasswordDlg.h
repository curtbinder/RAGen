// WifiPasswordDlg.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once


// WifiPasswordDlg dialog

class WifiPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(WifiPasswordDlg)

public:
	WifiPasswordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~WifiPasswordDlg();

// Dialog Data
	enum { IDD = IDD_WIFI_PASSWORD };

	// Username / Password
	CString m_sUsername;
	CString m_sPassword;

protected:
	HICON m_hIcon;
	BOOL m_fShowPassword;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPasswordShow();
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedPasswordClear();
};


// Global Functions
void LoadPasswordProtection(CString &sUsername, CString &sPassword);
void SavePasswordProtection(CString &sUsername, CString &sPassword);
BOOL IsPasswordProtected();
CString GetWifiAuthenticationString();