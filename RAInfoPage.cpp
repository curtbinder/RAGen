// RAInfoPage.cpp : implementation file
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
