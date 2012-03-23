// WebBannerDlg.h
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

typedef struct _WebBannerInfo {
	int nInterval;	// Update interval
	CString sID;	// ID to use
	CString sT1n;	// Temperature 1 name
	CString sT2n;	// Temperature 2 name
	CString sT3n;	// Temperature 3 name
	CString sR1n;	// Relay 1 name
	CString sR2n;	// Relay 2 name
	CString sR3n;	// Relay 3 name
	CString sR4n;	// Relay 4 name
	CString sR5n;	// Relay 5 name
	CString sR6n;	// Relay 6 name
	CString sR7n;	// Relay 7 name
	CString sR8n;	// Relay 8 name
} WebBannerInfo;

// Interval range defines, value is in seconds
#define WEB_INTERVAL_MIN	1
#define WEB_INTERVAL_MAX	300

// WebBannerDlg dialog

class WebBannerDlg : public CDialog
{
	DECLARE_DYNAMIC(WebBannerDlg)

public:
	WebBannerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~WebBannerDlg();

// Dialog Data
	enum { IDD = IDD_WEB_BANNER };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void UpdateInfo();

	DECLARE_MESSAGE_MAP()

	WebBannerInfo m_wi;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedQuestion();
};

void LoadWebBannerInfoDefaults(WebBannerInfo& wi);
void SaveWebBannerInfo(WebBannerInfo& wi);
void UpdateWebBannerInfoStrings(WebBannerInfo& wi);
CString GetWebBannerInfoString(WebBannerInfo& wi, BOOL bProgMem = TRUE);
