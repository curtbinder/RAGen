// RAColorsPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAColorsPage.h"


// RAColorsPage dialog

IMPLEMENT_DYNAMIC(RAColorsPage, CPropertyPage)

RAColorsPage::RAColorsPage()
	: CPropertyPage(RAColorsPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
}

RAColorsPage::~RAColorsPage()
{
}

void RAColorsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RAColorsPage, CPropertyPage)
END_MESSAGE_MAP()


// RAColorsPage message handlers
