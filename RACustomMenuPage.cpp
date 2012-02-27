// RACustomMenuPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RACustomMenuPage.h"
#include "InternalMemoryDefaults.h"
#include "Controller.h"


// RACustomMenuPage dialog

IMPLEMENT_DYNAMIC(RACustomMenuPage, CDialog)

RACustomMenuPage::RACustomMenuPage(CWnd* pParent /*=NULL*/)
	: CDialog(RACustomMenuPage::IDD, pParent)
{
	// MENU_MIN, MENU_MAX
	m_fEnable = FALSE;
	m_iMenuQty = MENU_DEFAULT;
	m_iCurrent = 0;
}

RACustomMenuPage::~RACustomMenuPage()
{
}

void RACustomMenuPage::UpdateValues()
{
	TRACE("Menu UpdateValues\n");
	m_fEnable = a_Controller.Features.GetFeatureValue(a_Controller.Features.CUSTOM_MENU);
	m_iMenuQty = a_Controller.Features.iCustomMenuEntries;
	SelectMenuQuantity(m_iMenuQty);
	EnableWindows(m_fEnable);
	CButton* p = (CButton*)GetDlgItem(IDC_MENU_CK_ENABLE);
	int ck = (m_fEnable)?BST_CHECKED:BST_UNCHECKED;
	p->SetCheck(ck);
}

void RACustomMenuPage::UpdateDisplay()
{
	SelectMenuQuantity(m_iMenuQty);
	LoadMenuEntrySelections(m_iMenuQty);
	LoadCurrentFunction();
}

void RACustomMenuPage::SelectMenuQuantity(int qty)
{
	CComboBox *p = (CComboBox *)GetDlgItem(IDC_MENU_CBO_ENTRIES);
	p->SetCurSel(qty-1);
}

void RACustomMenuPage::LoadMenuEntrySelections(int qty)
{
	CComboBox *p = (CComboBox *)GetDlgItem(IDC_MENU_CBO_MENU);
	CString s;
	p->ResetContent();
	for ( int i = 0; i < qty; i++ )
	{
		s.Format(_T("Menu Entry %d"), i+1);
		p->AddString(s);
	}
	m_iCurrent = 0;
	p->SetCurSel(m_iCurrent);
	LoadCurrentFunction();

	UpdateData(FALSE);
}

void RACustomMenuPage::EnableWindows(BOOL fEnable)
{
	GetDlgItem(IDC_MENU_FUNCTION_TEXT)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_CBO_ENTRIES)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_CBO_MENU)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_BTN_LOAD)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_BTN_RESET)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_FUNCTION_LABEL)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_BTN_CLEAR)->EnableWindow(fEnable);
	GetDlgItem(IDC_MENU_BTN_PREDEFINED)->EnableWindow(fEnable);
}

void RACustomMenuPage::LoadCurrentFunction()
{
	CString s;
	// Load the new function and label
	a_Controller.Menu.GetMenuFunctionCode(m_iCurrent, s);
	SetDlgItemText(IDC_MENU_FUNCTION_TEXT, s);
	a_Controller.Menu.GetMenuLabel(m_iCurrent, s);
	SetDlgItemText(IDC_MENU_FUNCTION_LABEL, s);
}

void RACustomMenuPage::SaveCurrentFunction()
{
	CString s;
	// Save the current function and label
	GetDlgItemText(IDC_MENU_FUNCTION_TEXT, s);
	a_Controller.Menu.SetMenuFunction(m_iCurrent, s);
	GetDlgItemText(IDC_MENU_FUNCTION_LABEL, s);
	a_Controller.Menu.SetMenuLabel(m_iCurrent, s);
}

void RACustomMenuPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_MENU_CBO_MENU, m_iCurrent);
}


BEGIN_MESSAGE_MAP(RACustomMenuPage, CDialog)
	ON_BN_CLICKED(IDC_MENU_BTN_RESET, &RACustomMenuPage::OnBnClickedMenuBtnReset)
	ON_BN_CLICKED(IDC_MENU_BTN_LOAD, &RACustomMenuPage::OnBnClickedMenuBtnLoad)
	ON_BN_CLICKED(IDC_MENU_BTN_CLEAR, &RACustomMenuPage::OnBnClickedMenuBtnClear)
	ON_CBN_SELCHANGE(IDC_MENU_CBO_MENU, &RACustomMenuPage::OnCbnSelchangeMenuCboMenu)
	ON_CBN_SELCHANGE(IDC_MENU_CBO_ENTRIES, &RACustomMenuPage::OnCbnSelchangeMenuCboEntries)
	ON_BN_CLICKED(IDC_MENU_CK_ENABLE, &RACustomMenuPage::OnBnClickedMenuCkEnable)
	ON_BN_CLICKED(IDC_MENU_BTN_PREDEFINED, &RACustomMenuPage::OnBnClickedMenuBtnPredefined)
	ON_COMMAND_RANGE(ID_CODE_DISPLAY_VERSION, ID_CODE_WATCHDOG, &RACustomMenuPage::OnMenuFunctionSelected)
END_MESSAGE_MAP()


// RACustomMenuPage message handlers
BOOL RACustomMenuPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_mFunctions.LoadMenu(IDR_MENU_CODE);
	UpdateDisplay();
	EnableWindows(m_fEnable);

	return TRUE;
}

void RACustomMenuPage::OnBnClickedMenuBtnReset()
{
	int iRet = AfxMessageBox(_T("This will reset your menu completely.\n\nAre you sure?"),
		MB_ICONQUESTION|MB_YESNO);
	if ( iRet == IDNO )
	{
		TRACE("Reset cancelled\n");
		return;
	}
	TRACE("Reset menu\n");
	m_iMenuQty = MENU_DEFAULT;
	a_Controller.LoadInitialMenu();
	UpdateDisplay();
	UpdateData(FALSE);
}

void RACustomMenuPage::OnBnClickedMenuBtnLoad()
{
	int iRet = AfxMessageBox(_T("This will replace your menu with the simple menu.\n\nAre you sure?"),
		MB_ICONQUESTION|MB_YESNO);
	if ( iRet == IDNO )
	{
		TRACE("Load cancelled\n");
		return;
	}
	// Load the menu
	a_Controller.LoadSimpleMenu();
	// Set the menu quantity based on menu entries
	m_iMenuQty = a_Controller.Features.iCustomMenuEntries;
	UpdateDisplay();
	UpdateData(FALSE);
}

void RACustomMenuPage::OnBnClickedMenuBtnClear()
{
	SetDlgItemText(IDC_MENU_FUNCTION_TEXT, _T(""));
}

void RACustomMenuPage::OnCbnSelchangeMenuCboMenu()
{
	// Menu entry:  Listed item is 1 more than indexed item
	//TRACE("Pre Item:  %d\n", m_iCurrent);
	SaveCurrentFunction();
	UpdateData();
	// m_iCurrent is the new value changing to
	//TRACE("Post Item:  %d\n", m_iCurrent);
	LoadCurrentFunction();
}

void RACustomMenuPage::OnCbnSelchangeMenuCboEntries()
{
	UpdateData();
	CComboBox *p = (CComboBox *)GetDlgItem(IDC_MENU_CBO_ENTRIES);
	m_iMenuQty = p->GetCurSel() + 1;
	TRACE("Changed to %d entries\n", m_iMenuQty);
	SaveCurrentFunction();
	a_Controller.Features.iCustomMenuEntries = m_iMenuQty;
	LoadMenuEntrySelections(m_iMenuQty);
}

void RACustomMenuPage::OnBnClickedMenuCkEnable()
{
	UpdateData();
	m_fEnable = !m_fEnable;
	TRACE("Enable:  %s\n", m_fEnable?"True":"False");
	EnableWindows(m_fEnable);
	// Update CustomMenu feature to match enabled
	// Update SimpleMenu feature to be opposite of enabled
	a_Controller.Features.SetFeatureValue(a_Controller.Features.CUSTOM_MENU, m_fEnable);
	a_Controller.Features.SetFeatureValue(a_Controller.Features.SIMPLE_MENU, !m_fEnable);
}

void RACustomMenuPage::OnBnClickedMenuBtnPredefined()
{
	CMenu *p = m_mFunctions.GetSubMenu(0);
	CRect r;
	GetDlgItem(IDC_MENU_BTN_PREDEFINED)->GetWindowRect(&r);
	//TRACE("Pre Button click:  %d %d\n", r.left, r.bottom);
	p->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, r.left, r.bottom, this);
}

void RACustomMenuPage::OnMenuFunctionSelected(UINT nID)
{
	UpdateData();
	TRACE("ID Clicked:  %d\n", nID);
	CString s;
	a_Controller.Menu.GetPresetFunctionCode(nID, s);
	CString code;
	GetDlgItemText(IDC_MENU_FUNCTION_TEXT, code);
	code += s;
	SetDlgItemText(IDC_MENU_FUNCTION_TEXT, code);
}
