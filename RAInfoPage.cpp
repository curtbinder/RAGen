// RAInfoPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAInfoPage.h"


// RAInfoPage dialog

IMPLEMENT_DYNAMIC(RAInfoPage, CDialog)

RAInfoPage::RAInfoPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAInfoPage::IDD, pParent)
{

}

RAInfoPage::~RAInfoPage()
{
}

void RAInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RAInfoPage, CDialog)
END_MESSAGE_MAP()


// RAInfoPage message handlers

BOOL RAInfoPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString s;
	s.LoadStringA(IDS_CONTROLLER_TIPS);
	SetDlgItemText(IDC_INFO_TITLE, s);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
