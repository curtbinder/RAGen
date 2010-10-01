// RAGenPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenPropSheet.h"


// CRAGenPropSheet

IMPLEMENT_DYNAMIC(CRAGenPropSheet, CPropertySheet)

CRAGenPropSheet::CRAGenPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_NOCONTEXTHELP;
	m_psh.dwFlags &= ~PSH_HASHELP;
	AddPage(&m_FeaturesPage);
	//AddPage(&m_ColorsPage);
	//AddPage(&m_SettingsPage);
	//AddPage(&m_PDEPage);
}

CRAGenPropSheet::CRAGenPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_NOCONTEXTHELP;
	m_psh.dwFlags &= ~PSH_HASHELP;
	AddPage(&m_FeaturesPage);
	//AddPage(&m_ColorsPage);
	//AddPage(&m_SettingsPage);
	//AddPage(&m_PDEPage);
}

CRAGenPropSheet::~CRAGenPropSheet()
{
}


BEGIN_MESSAGE_MAP(CRAGenPropSheet, CPropertySheet)
	ON_COMMAND(ID_FILE_EXIT, &CRAGenPropSheet::OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, &CRAGenPropSheet::OnHelpAbout)
	ON_COMMAND(ID_EDIT_SETTINGS, &CRAGenPropSheet::OnEditSettings)
END_MESSAGE_MAP()


// CRAGenPropSheet message handlers

BOOL CRAGenPropSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Add a new menu.
	CMenu *pMenu = new CMenu;
	pMenu->LoadMenu(IDR_MENU_MAIN);
	SetMenu(pMenu); 
	pMenu->Detach(); 
	delete pMenu; 
	
	// Adjust property sheet size to account for the new menu. 
	CRect r; 
	GetWindowRect(&r); 
	r.bottom +=GetSystemMetrics(SM_CYMENU); 
	MoveWindow(r);
	
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->SetWindowText(_T("&Close"));

	return bResult;
}

void CRAGenPropSheet::OnFileExit()
{
	PostMessage(WM_CLOSE);
}

void CRAGenPropSheet::OnHelpAbout()
{
	// TODO: Add your command handler code here
}

void CRAGenPropSheet::OnEditSettings()
{
	// TODO: Add your command handler code here
}
