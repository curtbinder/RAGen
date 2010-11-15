#pragma once

#include "ComPortFunctions.h"

// TestComPorts dialog

class TestComPorts : public CDialog
{
	DECLARE_DYNAMIC(TestComPorts)

public:
	TestComPorts(CWnd* pParent = NULL);   // standard constructor
	virtual ~TestComPorts();

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
