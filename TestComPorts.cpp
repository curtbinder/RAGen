// TestComPorts.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "TestComPorts.h"
#include "ComPortFunctions.h"


DWORD WINAPI UpdateThread(LPVOID lpParam)
{
	TestComPorts* pWnd = (TestComPorts*)lpParam;
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


// TestComPorts dialog

IMPLEMENT_DYNAMIC(TestComPorts, CDialog)

TestComPorts::TestComPorts(CWnd* pParent /*=NULL*/)
	: CDialog(TestComPorts::IDD, pParent)
{
	m_Ports = NULL;
	m_iCount = 0;
}

TestComPorts::~TestComPorts()
{
	if ( m_Thread )
	{
		CloseHandle(m_Thread);
	}
}

void TestComPorts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TestComPorts, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// TestComPorts message handlers
BOOL TestComPorts::OnInitDialog()
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

BOOL TestComPorts::UpdateStatus()
{
	CString text = _T("");
	m_bCancel = FALSE;
	BOOL bRet = TRUE;
	BOOL f;
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
		if ( TestPort(m_Ports[i].iPort) )
		{
			f = TRUE;
		}
		else
		{
			f = FALSE;
		}
		m_Ports[i].fHasRA = f;
	}  // for i

	if ( ! m_bCancel )
	{
		SetDlgItemText(IDC_TESTING_STATUS, _T("Done"));
	}
	return bRet;
}

void TestComPorts::OnBnClickedCancel()
{
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
	m_bCancel = TRUE;
	WaitForSingleObject(m_Thread, 5000);
	TerminateThread(m_Thread, 1);
	OnCancel();
}
