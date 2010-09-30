// RAFeaturesPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAFeaturesPage.h"


// RAFeaturesPage dialog

IMPLEMENT_DYNAMIC(RAFeaturesPage, CPropertyPage)

RAFeaturesPage::RAFeaturesPage()
	: CPropertyPage(RAFeaturesPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
}

RAFeaturesPage::~RAFeaturesPage()
{
}

void RAFeaturesPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RAFeaturesPage, CPropertyPage)
END_MESSAGE_MAP()


// RAFeaturesPage message handlers
