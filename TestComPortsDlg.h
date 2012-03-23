// TestComPortsDlg.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

#include "ComPortFunctions.h"

// TestComPortsDlg dialog

class TestComPortsDlg : public CDialog
{
	DECLARE_DYNAMIC(TestComPortsDlg)

public:
	TestComPortsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestComPortsDlg();

// Dialog Data
	enum { IDD = IDD_TESTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	BOOL UpdateStatus();
	HANDLE m_Thread;
	BOOL m_bCancel;
	Port* m_Ports;
	int m_iCount;
	afx_msg void OnBnClickedCancel();
};
