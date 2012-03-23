// TestComPortsDlg.cpp : implementation file
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "RAGen.h"
#include "TestComPortsDlg.h"
#include "ComPortFunctions.h"


DWORD WINAPI UpdateThread(LPVOID lpParam)
{
	TestComPortsDlg* pWnd = (TestComPortsDlg*)lpParam;
	DWORD dwRet = 0;
	if ( ! pWnd->UpdateStatus() )
	{
		dwRet = 1;
	}
	if ( dwRet == 0 )
	{
		// completed successfully, close the window
		::PostMessage(pWnd->GetSafeHwnd(), WM_COMMAND, IDOK, 0);
	}
	return dwRet;
}


// TestComPortsDlg dialog

IMPLEMENT_DYNAMIC(TestComPortsDlg, CDialog)

TestComPortsDlg::TestComPortsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TestComPortsDlg::IDD, pParent)
{
	m_Ports = NULL;
	m_iCount = 0;
}

TestComPortsDlg::~TestComPortsDlg()
{
	if ( m_Thread )
	{
		CloseHandle(m_Thread);
	}
}

void TestComPortsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestComPortsDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// TestComPortsDlg message handlers
BOOL TestComPortsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_TESTING_STATUS, "");

	m_Thread = CreateThread(
		0,
		0,
		UpdateThread,
		this,
		0,
		NULL
		);

	return TRUE;
}

BOOL TestComPortsDlg::UpdateStatus()
{
	CString text = _T("");
	m_bCancel = FALSE;
	BOOL bRet = TRUE;
	BOOL f;
	BOOL fOpti;
	/*
	loop through the ports
	*/
	for ( int i = 0; i < m_iCount; i++ )
	{
		text.Format(_T("Testing COM%d ..."), m_Ports[i].iPort);
		SetDlgItemText(IDC_TESTING_STATUS, text);
		if ( m_bCancel )
		{
			bRet = FALSE;
			break;
		}
		// Check for Optiboot controller
		if ( TestPort(m_Ports[i].iPort) )
		{
			f = TRUE;
			fOpti = TRUE;
		}
		else
		{
			//f = FALSE;
			fOpti = FALSE;
			// Check for standard controller
			if ( TestPort(m_Ports[i].iPort, CBR_57600) )
			{
				f = TRUE;
			}
			else
			{
				f = FALSE;
			}
		}
		m_Ports[i].fHasRA = f;
		m_Ports[i].fOptiboot = fOpti;
	}  // for i

	if ( ! m_bCancel )
	{
		SetDlgItemText(IDC_TESTING_STATUS, _T("Done"));
	}
	return bRet;
}

void TestComPortsDlg::OnBnClickedCancel()
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	m_bCancel = TRUE;
	WaitForSingleObject(m_Thread, 5000);
	TerminateThread(m_Thread, 1);
	OnCancel();
}
