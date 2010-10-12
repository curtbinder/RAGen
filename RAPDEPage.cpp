// RAPDEPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAPDEPage.h"


// RAPDEPage dialog

IMPLEMENT_DYNAMIC(RAPDEPage, CPropertyPage)

RAPDEPage::RAPDEPage()
	: CPropertyPage(RAPDEPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
}

RAPDEPage::~RAPDEPage()
{
}

void RAPDEPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RAPDEPage, CPropertyPage)
END_MESSAGE_MAP()


// RAPDEPage message handlers
