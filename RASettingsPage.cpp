// RASettingsPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RASettingsPage.h"


// RASettingsPage dialog

IMPLEMENT_DYNAMIC(RASettingsPage, CPropertyPage)

RASettingsPage::RASettingsPage()
	: CPropertyPage(RASettingsPage::IDD)
{
	m_psp.dwFlags &= ~PSP_HASHELP;
}

RASettingsPage::~RASettingsPage()
{
}

void RASettingsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RASettingsPage, CPropertyPage)
END_MESSAGE_MAP()


// RASettingsPage message handlers
