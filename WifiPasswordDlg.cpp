// WifiPasswordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "WifiPasswordDlg.h"

// Globals
void LoadPasswordProtection(CString &sUsername, CString &sPassword)
{
	CString s;
	s.LoadString(IDS_WIFI_PASSWORD);
	sUsername = AfxGetApp()->GetProfileString(s, _T("username"), _T(""));
	sPassword = AfxGetApp()->GetProfileString(s, _T("password"), _T(""));
}

void SavePasswordProtection(CString &sUsername, CString &sPassword)
{
	CString s;
	s.LoadString(IDS_WIFI_PASSWORD);
	AfxGetApp()->WriteProfileString(s, _T("username"), sUsername);
	AfxGetApp()->WriteProfileString(s, _T("password"), sPassword);
}

BOOL IsPasswordProtected()
{
	CString s1, s2;
	LoadPasswordProtection(s1, s2);
	if ( s1.IsEmpty() || s2.IsEmpty() )
	{
		// if either is empty, no password protection
		return FALSE;
	}
	// we are password protected
	return TRUE;
}

CString GetWifiAuthenticationString()
{
	CString s, u, p;
	LoadPasswordProtection(u, p);
	s.Format(_T("WifiAuthentication(\"%s:%s\");\r\n"), u, p);
	return s;
}


// WifiPasswordDlg dialog

IMPLEMENT_DYNAMIC(WifiPasswordDlg, CDialog)

WifiPasswordDlg::WifiPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WifiPasswordDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_fShowPassword = FALSE;
	LoadPasswordProtection(m_sUsername, m_sPassword);
}

WifiPasswordDlg::~WifiPasswordDlg()
{
}

void WifiPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WifiPasswordDlg, CDialog)
	ON_BN_CLICKED(IDC_PASSWORD_SHOW, &WifiPasswordDlg::OnBnClickedPasswordShow)
	ON_BN_CLICKED(IDOK, &WifiPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// WifiPasswordDlg message handlers

BOOL WifiPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CEdit* e = (CEdit*)GetDlgItem(IDC_PASSWORD_PASSWORD);
	e->SetPasswordChar('*');
	SetDlgItemText(IDC_PASSWORD_USERNAME, m_sUsername);
	SetDlgItemText(IDC_PASSWORD_PASSWORD, m_sPassword);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void WifiPasswordDlg::OnBnClickedPasswordShow()
{
	// show / hide the password and change the label of the text
	// flip the show password flag
	m_fShowPassword = !m_fShowPassword;
	CEdit* e = (CEdit*)GetDlgItem(IDC_PASSWORD_PASSWORD);
	CButton* b = (CButton*)GetDlgItem(IDC_PASSWORD_SHOW);
	if ( m_fShowPassword )
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

void WifiPasswordDlg::OnBnClickedOk()
{
	// if either of the fields is blank, clear out both fields
	CString su;
	GetDlgItemText(IDC_PASSWORD_USERNAME, su);
	CString sp;
	GetDlgItemText(IDC_PASSWORD_PASSWORD, sp);
	if ( su.IsEmpty() || sp.IsEmpty() )
	{
		m_sUsername = _T("");
		m_sPassword = _T("");
	}
	else
	{
		m_sUsername = su;
		m_sPassword = sp;
	}
	int ulen = m_sUsername.GetLength();
	int plen = m_sPassword.GetLength();
	if ( (ulen + plen + 1) > 20 )
	{
		su.Format(_T("Username & Password length cannot exceed 20 chars.\n\nYour length:  %d"), ulen+plen+1);
		AfxMessageBox(su);
		return;
	}
	SavePasswordProtection(m_sUsername, m_sPassword);
	OnOK();
}
