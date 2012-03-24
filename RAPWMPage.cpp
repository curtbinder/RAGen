// RAPWMPage.cpp : implementation file
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
#include "RAPWMPage.h"


// RAPWMPage dialog

IMPLEMENT_DYNAMIC(RAPWMPage, CDialog)

RAPWMPage::RAPWMPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAPWMPage::IDD, pParent)
{

}

RAPWMPage::~RAPWMPage()
{
}

void RAPWMPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RAPWMPage, CDialog)
END_MESSAGE_MAP()


// RAPWMPage message handlers

BOOL RAPWMPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString s;
	s.LoadStringA(IDS_CONTROLLER_TIPS);
	SetDlgItemText(IDC_INFO_TITLE, s);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
