// PortalDlg.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once


// CPortalDlg dialog

class CPortalDlg : public CDialog
{
	DECLARE_DYNAMIC(CPortalDlg)

public:
	CPortalDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPortalDlg();
	inline void SetUsername(CString sUser) { m_sUsername = sUser; }
	inline void SetKey(CString sKey) { m_sKey = sKey; }
	inline CString GetUsername() { return m_sUsername; }
	inline CString GetKey() { return m_sKey; }

// Dialog Data
	enum { IDD = IDD_PORTAL };

protected:
	HICON m_hIcon;
	BOOL m_fShowKey;
	CString m_sUsername;
	CString m_sKey;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPortalShow();
	afx_msg void OnBnClickedPortalClear();
	afx_msg void OnBnClickedPortalClearAll();
	afx_msg void OnBnClickedOk();
};

void LoadPortalInfo(CString &sUser, CString &sKey);
void SavePortalInfo(CString &sUser, CString &sKey);
