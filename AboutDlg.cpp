//
// AboutDlg.cpp
//

#include "stdafx.h"
#include "AboutDlg.h"
#include "cb_FileVersion.h"

AboutDlg::AboutDlg() : CDialog(AboutDlg::IDD)
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABOUT_REEFANGEL_LOGO, m_RALogo);
	DDX_Control(pDX, IDC_ABOUT_CURTBINDER_LOGO, m_CBLogo);
}

BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
END_MESSAGE_MAP()

BOOL AboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString fmt;
	GetDlgItemText(IDC_ABOUT_TEXT_VERSION, fmt);

	CString buffer;
	buffer.Format(fmt, cb_GetFileVersionString(AfxGetInstanceHandle()));
	SetDlgItemText(IDC_ABOUT_TEXT_VERSION, buffer);

	m_bmpRALogo.LoadBitmapA(IDB_REEFANGEL_LOGO);
	m_bmpCBLogo.LoadBitmapA(IDB_CURTBINDER_LOGO);
	m_RALogo.SetBitmap(m_bmpRALogo);
	m_CBLogo.SetBitmap(m_bmpCBLogo);
	return TRUE;
}