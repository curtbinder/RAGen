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
