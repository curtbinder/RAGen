// RATabSheet.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RATabSheet.h"
#include "RAFeaturesPage.h"
#include "RAPDEPage.h"
#include "RAInternalMemoryPage.h"
//#include "RAColorsPage.h"
#include "RAStdPage.h"  // Standard screen, not part of tabs

// RATabSheet

IMPLEMENT_DYNAMIC(RATabSheet, CTabCtrl)

RATabSheet::RATabSheet()
{
	m_fDevMode = FALSE;
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
	m_pTabs[0] = new RAFeaturesPage;
	m_pTabs[1] = new RAPDEPage;
	m_pTabs[2] = new RAInternalMemoryPage;
	m_pTabs[3] = new RAStdPage;
	m_iNumTabs = 4;

	CString s;
	if ( m_fDevMode )
	{
		s.LoadStringA(IDS_FEATURES_TAB);
		InsertItem(Features, s);
		s.LoadStringA(IDS_PDE_TAB);
		InsertItem(PDE, s);
		s.LoadStringA(IDS_MEMORY_TAB);
		InsertItem(Memory, s);
		//s.LoadStringA(IDS_COLORS_TAB);
		//InsertItem(Colors, _T("Colors"));

		m_iCurrentTab = 0;
		m_pTabs[Features]->Create(IDD_RAFEATURESPAGE, this);
		m_pTabs[PDE]->Create(IDD_RAPDEPAGE, this);
		m_pTabs[Memory]->Create(IDD_RAMEMORYPAGE, this);
		//m_pTabs[Colors]->Create(IDD_RACOLORSPAGE, this);

		m_pTabs[0]->ShowWindow(SW_SHOW);
		for ( int i = 1; i < m_iNumTabs-1; i++ )
		{
			m_pTabs[i]->ShowWindow(SW_HIDE);
		}
	}
	else
	{
		s.LoadStringA(IDS_STD_TAB);
		InsertItem(Standard, s);
		
		m_iCurrentTab = Standard;
		m_pTabs[Standard]->Create(IDD_RASTDPAGE, this);
		m_pTabs[Standard]->ShowWindow(SW_SHOW);
	}

	GetParent()->PostMessageA(WM_COMMAND, MAKEWPARAM(ID_CHANGE_MENU, 0), LPARAM(IDR_MENU_RESET));

	SetRectangle();
}

void RATabSheet::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left - 1;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - nX - 3;
	nYc = tabRect.bottom - nY - 3;

	if ( m_fDevMode )
	{
		m_pTabs[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
		for(int i = 1; i < m_iNumTabs-1; i++)
		{
			m_pTabs[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
		}
	}
	else
	{
		m_pTabs[Standard]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	}
}

void RATabSheet::Generate()
{
	switch ( m_iCurrentTab )
	{
		case Features:
			{
			RAFeaturesPage* p = (RAFeaturesPage*)m_pTabs[m_iCurrentTab];
			p->OnBnClickedBtnGenerate();
			}
			break;
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnBnClickedBtnGenerate();
			}
			break;
		case Memory:
			{
			RAInternalMemoryPage* p = (RAInternalMemoryPage*)m_pTabs[m_iCurrentTab];
			p->OnBnClickedBtnGenerate();
			}
			break;
		case Standard:
			{
			RAStdPage* p = (RAStdPage*)m_pTabs[m_iCurrentTab];
			p->OnBnClickedBtnGenerate();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetAll()
{
	switch ( m_iCurrentTab )
	{
		case Features:
			{
			RAFeaturesPage* p = (RAFeaturesPage*)m_pTabs[m_iCurrentTab];
			p->OnResetAll();
			}
			break;
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetAll();
			}
			break;
		case Memory:
			{
			RAInternalMemoryPage* p = (RAInternalMemoryPage*)m_pTabs[m_iCurrentTab];
			p->OnResetAll();
			}
			break;
		case Standard:
			{
			RAStdPage* p = (RAStdPage*)m_pTabs[m_iCurrentTab];
			p->OnResetAll();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetSaved()
{
	switch ( m_iCurrentTab )
	{
		case Features:
			{
			RAFeaturesPage* p = (RAFeaturesPage*)m_pTabs[m_iCurrentTab];
			p->OnResetSaved();
			}
			break;
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetSaved();
			}
			break;
		case Memory:
			{
			RAInternalMemoryPage* p = (RAInternalMemoryPage*)m_pTabs[m_iCurrentTab];
			p->OnResetSaved();
			}
			break;
		case Standard:
			{
			RAStdPage* p = (RAStdPage*)m_pTabs[m_iCurrentTab];
			p->OnResetSaved();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetPorts()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetPorts();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetTemp()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetTemperature();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetLogging()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetLogging();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetFeedingMode()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetFeedingMode();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetWaterChangeMode()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetWaterChangeMode();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetOverheat()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetOverheat();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::ResetLightsOn()
{
	switch ( m_iCurrentTab )
	{
		case PDE:
			{
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->OnResetLightsOn();
			}
			break;
		default:
			break;
	}
}

void RATabSheet::UpdateSettingsForTabs()
{
	// set the settings for the tabs
	RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
	RAPDEPage* pp = (RAPDEPage*)m_pTabs[PDE];
	RAInternalMemoryPage* pm = (RAInternalMemoryPage*)m_pTabs[Memory];
	RAStdPage* ps = (RAStdPage*)m_pTabs[Standard];

	pf->iSaveReg = iSaveReg;
	pp->iSaveReg = iSaveReg;
	pm->iSaveReg = iSaveReg;
	ps->iSaveReg = iSaveReg;
	//_tcscpy_s(pf->m_sOutputDirectory, MAX_PATH, m_sOutputDirectory);
	//_tcscpy_s(pp->m_sOutputDirectory, MAX_PATH, m_sOutputDirectory);
	_tcscpy_s(pf->m_sCurrentDirectory, MAX_PATH, m_sCurrentDirectory);
	//_tcscpy_s(pp->m_sCurrentDirectory, MAX_PATH, m_sCurrentDirectory);
	_tcscpy_s(pm->m_sSketchDirectory, MAX_PATH, m_sSketchDirectory);
	_tcscpy_s(pp->m_sSketchDirectory, MAX_PATH, m_sSketchDirectory);
	_tcscpy_s(ps->m_sSketchDirectory, MAX_PATH, m_sSketchDirectory);
	_tcscpy_s(pf->m_sArduinoDirectory, MAX_PATH, m_sArduinoDirectory);
	//_tcscpy_s(pp->m_sArduinoDirectory, MAX_PATH, m_sArduinoDirectory);
}

void RATabSheet::GetFilename(CString &s)
{
	if ( m_iCurrentTab == PDE )
	{
		RAPDEPage* p = (RAPDEPage*)m_pTabs[PDE];
		s = p->sFilename;
	}
	else if ( m_iCurrentTab == Memory )
	{
		RAInternalMemoryPage* p = (RAInternalMemoryPage*)m_pTabs[Memory];
		s = p->sFilename;
	}
	else if ( m_iCurrentTab == Standard )
	{
		RAStdPage* p = (RAStdPage*)m_pTabs[Standard];
		s = p->sFilename;
	}
	else
	{
		s = _T("");
	}
}

void RATabSheet::EnableAdvanced()
{
	switch ( m_iCurrentTab )
	{
		case Memory:
			{
			RAInternalMemoryPage* p = (RAInternalMemoryPage*)m_pTabs[m_iCurrentTab];
			p->OnEditTimeoutsPH();
			}
			break;
		default:
			break;
	}
}

BEGIN_MESSAGE_MAP(RATabSheet, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &RATabSheet::OnTcnSelchange)
END_MESSAGE_MAP()



// RATabSheet message handlers

void RATabSheet::OnTcnSelchange(NMHDR *, LRESULT *pResult)
{
	*pResult = 0;
	// change the tabs
	int cur = GetCurSel();
	if ( m_iCurrentTab == cur )
	{
		return;
	}
	m_pTabs[m_iCurrentTab]->ShowWindow(SW_HIDE);
	m_pTabs[cur]->ShowWindow(SW_SHOW);
	m_iCurrentTab = cur;

	// change the menu
	UINT menuID;
	switch ( m_iCurrentTab )
	{
		case PDE:
			menuID = IDR_MENU_PDE_RESET;
			break;
		case Memory:
			{
			RAInternalMemoryPage* p = (RAInternalMemoryPage*)m_pTabs[m_iCurrentTab];
			p->OnEditTimeoutsPH();
			}
		default:
			menuID = IDR_MENU_RESET;
			break;
	}
	GetParent()->PostMessageA(WM_COMMAND, MAKEWPARAM(ID_CHANGE_MENU, 0), LPARAM(menuID));

	// clear the status
	GetParent()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), 0);
}
