// RATabSheet.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RATabSheet.h"
#include "RAFeaturesPage.h"
#include "RAPDEPage.h"
//#include "RAColorsPage.h"
#include "RAStdPage.h"  // Standard screen, not part of tabs


// RATabSheet

IMPLEMENT_DYNAMIC(RATabSheet, CTabCtrl)

RATabSheet::RATabSheet()
{
	m_fDevMode = FALSE;
	fHasArduinoExe = FALSE;
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
	m_pTabs[2] = new RAStdPage;
	m_iNumTabs = 3;

	CString s;
	if ( m_fDevMode )
	{
		s.LoadStringA(IDS_FEATURES_TAB);
		InsertItem(Features, s);
		s.LoadStringA(IDS_PDE_TAB);
		InsertItem(PDE, s);
		//s.LoadStringA(IDS_COLORS_TAB);
		//InsertItem(Colors, _T("Colors"));

		m_iCurrentTab = 0;
		m_pTabs[Features]->Create(IDD_RAFEATURESPAGE, this);
		m_pTabs[PDE]->Create(IDD_RAPDEPAGE, this);
		//m_pTabs[Colors]->Create(IDD_RACOLORSPAGE, this);

		m_pTabs[0]->ShowWindow(SW_SHOW);
		for ( int i = 1; i < m_iNumTabs-1; i++ )
		{
			m_pTabs[i]->ShowWindow(SW_HIDE);
		}
		// hide generate button
		//GetParent()->GetDlgItem(IDC_BTN_GENERATE)->ShowWindow(SW_HIDE);
		// Change to Save since the Features Tab is the first tab
		GetParent()->GetDlgItem(IDC_BTN_GENERATE)->SetWindowText(_T("Save"));
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
			pf->UpdateFeaturesStruct(FALSE);
			pf->WriteFeatures(g_Features, m_sLibraryDirectory);
			break;
		}
		case PDE:
			{
			/*
			Update PDE Features list
			Write ReefAngel_Features.h file
			Generate PDE file
			*/
			RAPDEPage* p = (RAPDEPage*)m_pTabs[m_iCurrentTab];
			p->UpdatePDEFeatures(g_Features);
			RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];
			pf->WriteFeatures(g_Features, m_sLibraryDirectory);
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

void RATabSheet::CheckLaunch(BOOL fSkipPrompt /*= FALSE*/)
{
	CString sFilename = _T("");
	GetFilename(sFilename);
	if ( sFilename.IsEmpty() )
	{
		return;
	}
	if ( ! fHasArduinoExe )
	{
		return;
	}
	
	if ( fSkipPrompt )
	{
		// only for when the Launch button is pressed
		LaunchArduino();
		return;
	}

	switch ( iLaunch )
	{
	case ALWAYS:
		LaunchArduino();
		break;
	case PROMPT:
		{
			int iRet = AfxMessageBox(_T("Do you want to launch arduino?"),
				MB_ICONINFORMATION | MB_YESNO);
			if ( iRet == IDYES )
			{
				LaunchArduino();
			}
		}
		break;
	default:
		break;
	}
}

void RATabSheet::LaunchArduino()
{
	// use CreateProcess function to launch arduino
	// use m_sArduinoFolder + arduino.exe for application
	// use m_sSketchFolder + sketchfilename for PDE file to open
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR sPDE[32768];
	CString sFilename;
	CString sFileExtension;
	BOOL f09xDev = FALSE;

	switch ( iDevVersion )
	{
	default:
	case AUTODETECT:
		f09xDev = AutodetectDevVersion(m_sLibraryDirectory);
		break;
	case FORCE_08X:
		f09xDev = FALSE;
		break;
	case FORCE_09X:
		f09xDev = TRUE;
		break;
	}
	if ( f09xDev )
	{
		sFileExtension.LoadString(IDS_INO_EXTENSION);
	}
	else
	{
		sFileExtension.LoadString(IDS_PDE_EXTENSION);
	}

	GetFilename(sFilename);
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	_stprintf_s(sPDE, 32768, _T("%s\\arduino.exe \"%s\\%s\\%s.%s\""), 
			m_sArduinoDirectory, m_sSketchDirectory, sFilename, sFilename, sFileExtension);

	if ( ! CreateProcess(NULL, sPDE, NULL, NULL, FALSE,
						0, NULL, m_sArduinoDirectory,
						&si, &pi) )
	{
		TRACE("Failed to launch arduino.exe\n");
		AfxMessageBox(_T("Failed to launch arduino.exe"), MB_ICONINFORMATION|MB_OK);
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
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
	RAPDEPage* pp = (RAPDEPage*)m_pTabs[PDE];
	RAStdPage* ps = (RAStdPage*)m_pTabs[Standard];
	RAFeaturesPage* pf = (RAFeaturesPage*)m_pTabs[Features];

	pp->iDevVersion = iDevVersion;
	pp->iSaveReg = iSaveReg;
	ps->iSaveReg = iSaveReg;
	_tcscpy_s(pp->m_sSketchDirectory, MAX_PATH, m_sSketchDirectory);
	_tcscpy_s(ps->m_sSketchDirectory, MAX_PATH, m_sSketchDirectory);
	_tcscpy_s(pp->m_sLibraryDirectory, MAX_PATH, m_sLibraryDirectory);

	if ( m_fDevMode )
	{
		CString sFile;
		sFile.Format(_T("%s\\ReefAngel_Features\\ReefAngel_Features.h"), m_sLibraryDirectory);
		if (  !pf->ReadFeatures(sFile) )
		{
			// we failed reading the file in, so let's restore the defaults
			pf->LoadDefaults();
		}
	}
}

void RATabSheet::GetFilename(CString &s)
{
	if ( m_iCurrentTab == PDE )
	{
		RAPDEPage* p = (RAPDEPage*)m_pTabs[PDE];
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

void RATabSheet::GetFileExtension(CString &s)
{
	if ( m_iCurrentTab == PDE )
	{
		RAPDEPage* p = (RAPDEPage*)m_pTabs[PDE];
		s = p->sFileExtension;
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
		pf->UpdateFeaturesStruct();
	}
	m_pTabs[m_iCurrentTab]->ShowWindow(SW_HIDE);
	m_pTabs[cur]->ShowWindow(SW_SHOW);
	m_iCurrentTab = cur;

	// change the menu
	//int nShow = SW_SHOW;
	UINT menuID = IDR_MENU_RESET;
	switch ( m_iCurrentTab )
	{
		case PDE:
			menuID = IDR_MENU_PDE_RESET;
			GetParent()->GetDlgItem(IDC_BTN_GENERATE)->SetWindowText(_T("Generate"));
			break;
		case Features:
			//nShow = SW_HIDE;
			GetParent()->GetDlgItem(IDC_BTN_GENERATE)->SetWindowText(_T("Save"));
			break;
		//default:
		//	break;
	}
	// show/hide generate button appropriately
	//GetParent()->GetDlgItem(IDC_BTN_GENERATE)->ShowWindow(nShow);

	GetParent()->PostMessageA(WM_COMMAND, MAKEWPARAM(ID_CHANGE_MENU, 0), LPARAM(menuID));

	// clear the status
	GetParent()->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_UPDATE_STATUS, 0), 0);
}
