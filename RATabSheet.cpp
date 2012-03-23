// RATabSheet.cpp : implementation file
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "RAGen.h"
#include "RATabSheet.h"
#include "RAFeaturesPage.h"
#include "RARelayPage.h"
//#include "RAColorsPage.h"
#include "RAControllerPage.h"
#include "RAStdPage.h"  // Standard screen, not part of tabs
#include "Controller.h"
#include "RACustomMenuPage.h"
#include "RAInfoPage.h"


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
	m_pTabs[Info] = new RAInfoPage;
	m_pTabs[Controller] = new RAControllerPage;
	m_pTabs[Features] = new RAFeaturesPage;
	m_pTabs[MainRelay] = new RARelayPage;
	m_pTabs[CustomMenu] = new RACustomMenuPage;
	m_pTabs[Standard] = new RAStdPage;
	m_iNumTabs = 6;

	CString s;
	UINT menuID = IDR_MENU_RESET;
	if ( m_fDevMode )
	{
		s.LoadStringA(IDS_INFO_TAB);
		InsertItem(Info, s);
		s.LoadStringA(IDS_CONTROLLER_TAB);
		InsertItem(Controller, s);
		s.LoadStringA(IDS_FEATURES_TAB);
		InsertItem(Features, s);
		s.LoadStringA(IDS_MAIN_RELAY_TAB);
		InsertItem(MainRelay, s);
		s.LoadStringA(IDS_CUSTOM_MENU_TAB);
		InsertItem(CustomMenu, s);
		//s.LoadStringA(IDS_COLORS_TAB);
		//InsertItem(Colors, _T("Colors"));

		m_iCurrentTab = 0;
		m_pTabs[Info]->Create(IDD_RAINFOPAGE, this);
		m_pTabs[Controller]->Create(IDD_RACONTROLLER, this);
		m_pTabs[Features]->Create(IDD_RAFEATURESPAGE, this);
		m_pTabs[MainRelay]->Create(IDD_RARELAYPAGE, this);
		m_pTabs[CustomMenu]->Create(IDD_RACUSTOMMENU, this);
		//m_pTabs[Colors]->Create(IDD_RACOLORSPAGE, this);

		m_pTabs[0]->ShowWindow(SW_SHOW);
		for ( int i = 1; i < m_iNumTabs-1; i++ )
		{
			m_pTabs[i]->ShowWindow(SW_HIDE);
		}
		// hide generate button
		GetParent()->GetDlgItem(IDC_BTN_GENERATE)->ShowWindow(SW_HIDE);
		// set the controller menu
		menuID = IDR_MENU_CONTROLLER_RESET;
	}
	else
	{
		s.LoadStringA(IDS_STD_TAB);
		InsertItem(Standard, s);
		
		m_iCurrentTab = Standard;
		m_pTabs[Standard]->Create(IDD_RASTDPAGE, this);
		m_pTabs[Standard]->ShowWindow(SW_SHOW);
	}

	GetParent()->PostMessageA(WM_COMMAND, MAKEWPARAM(ID_CHANGE_MENU, 0), LPARAM(menuID));

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

void RATabSheet::SaveFeatures()
{
	RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[m_iCurrentTab];
	pf->SaveFeatures();
}

void RATabSheet::Generate()
{
	switch ( m_iCurrentTab )
	{
		case Features:
		{
			RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
			pf->UpdateFeatures(FALSE);
			pf->WriteFeatures();
			break;
		}
		case Controller:
			{
			/*
			Update PDE Features list
			Write ReefAngel_Features.h file
			Generate PDE file
			*/
			RARelayPage* p = (RARelayPage*)m_pTabs[MainRelay];
			p->UpdatePDEFeatures();
			RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
			pf->WriteFeatures();
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

void RATabSheet::CheckLaunch(BOOL fSkipPrompt)
{
	CString sFilename = _T("");
	GetFilename(sFilename);

	if ( sFilename.IsEmpty() )
	{
		return;
	}
	if ( ! theApp.fHasArduinoExe )
	{
		return;
	}
	
	if ( fSkipPrompt )
	{
		// only for when the Launch button is pressed
		LaunchArduino(sFilename);
		return;
	}

	switch ( theApp.iLaunch )
	{
	case ALWAYS:
		LaunchArduino(sFilename);
		break;
	case PROMPT:
		{
			int iRet = AfxMessageBox(_T("Do you want to launch arduino?"),
				MB_ICONINFORMATION | MB_YESNO);
			if ( iRet == IDYES )
			{
				LaunchArduino(sFilename);
			}
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
			p->OnResetAll();
			}
			break;
		case Controller:
			{
			RAControllerPage* p = (RAControllerPage*)m_pTabs[m_iCurrentTab];
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
			p->OnResetSaved();
			}
			break;
		case Controller:
			{
			RAControllerPage* p = (RAControllerPage*)m_pTabs[m_iCurrentTab];
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
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
		case Controller:
			{
			RAControllerPage* p = (RAControllerPage*)m_pTabs[m_iCurrentTab];
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
		case Controller:
			{
			RAControllerPage* p = (RAControllerPage*)m_pTabs[m_iCurrentTab];
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
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
		case MainRelay:
			{
			RARelayPage* p = (RARelayPage*)m_pTabs[m_iCurrentTab];
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

	if ( m_fDevMode )
	{
		CString sFile;
		sFile.Format(_T("%s\\ReefAngel_Features\\ReefAngel_Features.h"), theApp.m_sLibraryDirectory);
		if (  !pf->ReadFeatures(sFile) )
		{
			// we failed reading the file in, so let's restore the defaults
			pf->LoadDefaults();
		}
	}
}

void RATabSheet::GetFilename(CString &s)
{
	if ( m_iCurrentTab == Controller )
	{
		s = a_Controller.GetFilename();
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

void RATabSheet::GetFileExtension(CString &s)
{
	if ( m_iCurrentTab == Controller )
	{
		s = a_Controller.GetExtension();
	}
	else if ( m_iCurrentTab == Standard )
	{
		s.LoadString(IDS_PDE_EXTENSION);
	}
	else
	{
		s = _T("");
	}
}

void RATabSheet::ImportFeatures(CString sFile)
{
	RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
	CString buf;
	if (  pf->ReadFeatures(sFile) )
	{
		buf = _T("Successfully imported features");
	}
	else
	{
		buf = _T("Failed to import features");
	}
	AfxMessageBox(buf, MB_OK|MB_ICONINFORMATION);
}

void RATabSheet::ShowUnknownFeatures()
{
	RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
	pf->ShowUnknownFeatures();
}

void RATabSheet::UpdateControllerTab()
{
	RAControllerPage* pc = (RAControllerPage*)m_pTabs[Controller];
	pc->UpdateValues();
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
	if ( m_iCurrentTab == Features )
	{
		// update the features structure before we proceed
		RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
		pf->UpdateFeatures();
		RAControllerPage* pc = (RAControllerPage*)m_pTabs[Controller];
		pc->UpdateValues();
		RACustomMenuPage* pm = (RACustomMenuPage*)m_pTabs[CustomMenu];
		pm->UpdateValues();
	}
	
	if ( (m_iCurrentTab == Controller) ||
		 (m_iCurrentTab == CustomMenu) )
	{
		RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
		pf->UpdateDisplay();
	}

	m_pTabs[m_iCurrentTab]->ShowWindow(SW_HIDE);
	m_pTabs[cur]->ShowWindow(SW_SHOW);
	m_iCurrentTab = cur;

	// change the menu
	int nShow = SW_SHOW;
	UINT menuID = IDR_MENU_RESET;
	switch ( m_iCurrentTab )
	{
		case MainRelay:
			menuID = IDR_MENU_RELAY_RESET;
			nShow = SW_HIDE;
			break;
		case Features:
			//nShow = SW_HIDE;
			GetParent()->GetDlgItem(IDC_BTN_GENERATE)->SetWindowText(_T("Save"));
			break;
		case Controller:
			menuID = IDR_MENU_CONTROLLER_RESET;
			GetParent()->GetDlgItem(IDC_BTN_GENERATE)->SetWindowText(_T("Generate"));
			break;
		case Info:
		case CustomMenu:
			nShow = SW_HIDE;
			// TODO hide Reset menu for Custom Menu
			break;
		//default:
		//	break;
	}
	// show/hide generate button appropriately
	GetParent()->GetDlgItem(IDC_BTN_GENERATE)->ShowWindow(nShow);

	// update the reset menu appropriately
	GetParent()->PostMessageA(WM_COMMAND, MAKEWPARAM(ID_CHANGE_MENU, 0), LPARAM(menuID));

	// clear the status
	GetParent()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), 0);
}
