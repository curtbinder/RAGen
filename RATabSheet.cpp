// RATabSheet.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RATabSheet.h"
#include "RAFeaturesPage.h"
//#include "RAPDEPage.h"
//#include "RAColorsPage.h"
//#include "RASettingsPage.h"


// RATabSheet

IMPLEMENT_DYNAMIC(RATabSheet, CTabCtrl)

RATabSheet::RATabSheet()
{
	m_pTabs[0] = new RAFeaturesPage;
	m_iNumTabs = 1;
}

RATabSheet::~RATabSheet()
{
	for ( int i = 0; i < m_iNumTabs; i++ )
	{
		delete m_pTabs[i];
	}
}

void RATabSheet::Init()
{
	// TODO LoadString for tab names
	InsertItem(0, _T("Features"));
	//InsertItem(1, _T("Colors"));
	//InsertItem(2, _T("Values"));
	//InsertItem(3, _T("PDE"));

	m_iCurrentTab = 0;
	m_pTabs[0]->Create(IDD_RAFEATURESPAGE, this);	

	m_pTabs[0]->ShowWindow(SW_SHOW);
	for ( int i = 1; i < m_iNumTabs; i++ )
	{
		m_pTabs[i]->ShowWindow(SW_HIDE);
	}

	SetRectangle();
}

void RATabSheet::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 2;
	nXc = tabRect.right - itemRect.left - 2;
	nYc = tabRect.bottom - (itemRect.bottom + 2) - 2;

	m_pTabs[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for(int i = 1; i < m_iNumTabs; i++)
	{
		m_pTabs[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}

BEGIN_MESSAGE_MAP(RATabSheet, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &RATabSheet::OnTcnSelchange)
END_MESSAGE_MAP()



// RATabSheet message handlers

void RATabSheet::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int cur = GetCurSel();
	if ( m_iCurrentTab == cur )
	{
		return;
	}
	m_pTabs[m_iCurrentTab]->ShowWindow(SW_HIDE);
	m_pTabs[cur]->ShowWindow(SW_SHOW);
	m_iCurrentTab = cur;
}
