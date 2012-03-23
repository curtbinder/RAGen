// PortalDlg.cpp : implementation file
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "RAGen.h"
#include "PortalDlg.h"


void LoadPortalInfo(CString &sUser, CString &sKey)
{
	CString s;
	s.LoadString(IDS_PORTAL);
	sUser = AfxGetApp()->GetProfileString(s, _T("username"), _T(""));
	sKey = AfxGetApp()->GetProfileString(s, _T("key"), _T(""));
}

void SavePortalInfo(CString &sUser, CString &sKey)
{
	CString s;
	s.LoadString(IDS_PORTAL);
	AfxGetApp()->WriteProfileString(s, _T("username"), sUser);
	AfxGetApp()->WriteProfileString(s, _T("key"), sKey);
}

// CPortalDlg dialog

IMPLEMENT_DYNAMIC(CPortalDlg, CDialog)

CPortalDlg::CPortalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPortalDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_fShowKey = FALSE;
	m_sUsername = _T("");
	m_sKey = _T("");
}

CPortalDlg::~CPortalDlg()
{
}

void CPortalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortalDlg, CDialog)
	ON_BN_CLICKED(IDC_PORTAL_SHOW, &CPortalDlg::OnBnClickedPortalShow)
	ON_BN_CLICKED(IDC_PORTAL_CLEAR, &CPortalDlg::OnBnClickedPortalClear)
	ON_BN_CLICKED(IDC_PORTAL_CLEAR_ALL, &CPortalDlg::OnBnClickedPortalClearAll)
	ON_BN_CLICKED(IDOK, &CPortalDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPortalDlg message handlers

void CPortalDlg::OnBnClickedPortalShow()
{
	// show / hide the key and change the label of the text
	// flip the show key flag
	m_fShowKey = !m_fShowKey;
	CEdit* e = (CEdit*)GetDlgItem(IDC_PORTAL_KEY);
	CButton* b = (CButton*)GetDlgItem(IDC_PORTAL_SHOW);
	if ( m_fShowKey )
	{
		e->SetPasswordChar(0);
		b->SetWindowText(_T("Hide"));
	}
	else
	{
		e->SetPasswordChar('*');
		b->SetWindowText(_T("Show"));
	}
	e->Invalidate();	
}

void CPortalDlg::OnBnClickedPortalClear()
{
	SetDlgItemText(IDC_PORTAL_KEY, _T(""));
}

void CPortalDlg::OnBnClickedPortalClearAll()
{
	SetDlgItemText(IDC_PORTAL_USERNAME, _T(""));
	OnBnClickedPortalClear();
}

void CPortalDlg::OnBnClickedOk()
{
	UpdateData();
	GetDlgItemText(IDC_PORTAL_USERNAME, m_sUsername);
	GetDlgItemText(IDC_PORTAL_KEY, m_sKey);
	OnOK();
}

BOOL CPortalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CEdit* e = (CEdit*)GetDlgItem(IDC_PORTAL_KEY);
	e->SetPasswordChar('*');
	SetDlgItemText(IDC_PORTAL_USERNAME, m_sUsername);
	SetDlgItemText(IDC_PORTAL_KEY, m_sKey);

	return TRUE;
}

