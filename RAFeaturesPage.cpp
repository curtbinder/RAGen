// RAFeaturesPage.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAFeaturesPage.h"
#include "cb_FileVersion.h"
#include "GlobalVars.h"
#include "InternalMemoryDefaults.h"
#include "Features.h"


// RAFeaturesPage dialog

IMPLEMENT_DYNAMIC(RAFeaturesPage, CDialog)

RAFeaturesPage::RAFeaturesPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAFeaturesPage::IDD, pParent)
{
}

RAFeaturesPage::~RAFeaturesPage()
{
}

void RAFeaturesPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FEATURES_TREE, m_tree);
}


BEGIN_MESSAGE_MAP(RAFeaturesPage, CDialog)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, IDC_FEATURES_TREE, &RAFeaturesPage::OnTvnSelchangedFeaturesTree)
END_MESSAGE_MAP()


// RAFeaturesPage message handlers

BOOL RAFeaturesPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitTree();

	LoadFeatures();

	ClearDescription();

	return TRUE;
}

void RAFeaturesPage::InitTree()
{
	m_tree.ModifyStyle( 0, TVS_NOHSCROLL );
	// Strange hack, have to remove checkbox style and readd it otherwise checks won't display
	m_tree.ModifyStyle( TVS_CHECKBOXES, 0 );
	m_tree.ModifyStyle( 0, TVS_CHECKBOXES );

	// TODO add in missing feature strings
	HTREEITEM root;
	HTREEITEM setup;
	HTREEITEM menu;
	HTREEITEM exp;
	HTREEITEM screen;
	HTREEITEM fonts;
	HTREEITEM hi;
	root = m_tree.InsertItem(_T("Features"));
	m_tree.SetItemData(root, (DWORD)a_Features.NONE);
	hi = m_tree.InsertItem(_T("Wifi"), root);
	m_tree.SetItemData(hi, (DWORD)a_Features.WIFI);
	hi = m_tree.InsertItem(_T("Watchdog Timer"), root);
	m_tree.SetItemData(hi, (DWORD)a_Features.WDT);

	setup = m_tree.InsertItem(_T("Setup Menus"), root);
	m_tree.SetItemData(setup, (DWORD)a_Features.NONE);
	hi = m_tree.InsertItem(_T("Overheat Setup"), setup);
	m_tree.SetItemData(hi, (DWORD)a_Features.OVERHEAT_SETUP);
	hi = m_tree.InsertItem(_T("Date / Time Setup"), setup);
	m_tree.SetItemData(hi, (DWORD)a_Features.DATE_TIME_SETUP);
	hi = m_tree.InsertItem(_T("Dosing Repeat Setup"), setup);
	m_tree.SetItemData(hi, (DWORD)a_Features.DOSING_INTERVAL_SETUP);
	hi = m_tree.InsertItem(_T("Setup Extras"), setup);
	m_tree.SetItemData(hi, (DWORD)a_Features.SETUP_EXTRAS);

	menu = m_tree.InsertItem(_T("Menu System"), root);
	m_tree.SetItemData(menu, (DWORD)a_Features.NONE);
	hi = m_tree.InsertItem(_T("Simple Menu"), menu);
	m_tree.SetItemData(hi, (DWORD)a_Features.SIMPLE_MENU);
	hi = m_tree.InsertItem(_T("Custom Menu"), menu);
	m_tree.SetItemData(hi, (DWORD)a_Features.CUSTOM_MENU);

	exp = m_tree.InsertItem(_T("Expansion Modules"), root);
	m_tree.SetItemData(exp, (DWORD)a_Features.NONE);
	hi = m_tree.InsertItem(_T("Expansion Relays"), exp);
	m_tree.SetItemData(hi, (DWORD)a_Features.EXPANSION_MODULE);
	hi = m_tree.InsertItem(_T("PWM"), exp);
	m_tree.SetItemData(hi, (DWORD)a_Features.PWM_EXPANSION);
	hi = m_tree.InsertItem(_T("Salinity"), exp);
	m_tree.SetItemData(hi, (DWORD)a_Features.SALINITY);
	hi = m_tree.InsertItem(_T("ORP"), exp);
	m_tree.SetItemData(hi, (DWORD)a_Features.ORP);
	hi = m_tree.InsertItem(_T("AI LED"), exp);
	m_tree.SetItemData(hi, (DWORD)a_Features.AI);
	hi = m_tree.InsertItem(_T("RF"), exp);
	m_tree.SetItemData(hi, (DWORD)a_Features.RF);

	screen = m_tree.InsertItem(_T("Screen Options"), root);
	m_tree.SetItemData(screen, (DWORD)a_Features.NONE);
	hi = m_tree.InsertItem(_T("Custom Main Screen"), screen);
	m_tree.SetItemData(hi, (DWORD)a_Features.CUSTOM_MAIN);
	hi = m_tree.InsertItem(_T("Display Images"), screen);
	m_tree.SetItemData(hi, (DWORD)a_Features.DISPLAY_IMAGES);
	hi = m_tree.InsertItem(_T("Version Menu"), screen);
	m_tree.SetItemData(hi, (DWORD)a_Features.VERSION_MENU);
	hi = m_tree.InsertItem(_T("Display LED PWM"), screen);
	m_tree.SetItemData(hi, (DWORD)a_Features.DISPLAY_LED_PWM);
	hi = m_tree.InsertItem(_T("Remove All Lights"), screen);
	m_tree.SetItemData(hi, (DWORD)a_Features.REMOVE_ALL_LIGHTS);
	hi = m_tree.InsertItem(_T("Custom Colors"), screen);
	m_tree.SetItemData(hi, (DWORD)a_Features.CUSTOM_COLORS);

	fonts = m_tree.InsertItem(_T("Alternate Fonts"), root);
	m_tree.SetItemData(fonts, (DWORD)a_Features.NONE);
	hi = m_tree.InsertItem(_T("Font 8x8"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.FONT_8x8);
	hi = m_tree.InsertItem(_T("Font 8x16"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.FONT_8x16);
	hi = m_tree.InsertItem(_T("Font 12x16"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.FONT_12x16);
	hi = m_tree.InsertItem(_T("Numbers 8x8"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.NUMBERS_8x8);
	hi = m_tree.InsertItem(_T("Numbers 8x16"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.NUMBERS_8x16);
	hi = m_tree.InsertItem(_T("Numbers 12x16"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.NUMBERS_12x16);
	hi = m_tree.InsertItem(_T("Numbers 16x16"), fonts);
	m_tree.SetItemData(hi, (DWORD)a_Features.NUMBERS_16x16);

	hi = m_tree.InsertItem(_T("ATO Logging"), root);
	m_tree.SetItemData(hi, (DWORD)a_Features.ATO_LOGGING);
	hi = m_tree.InsertItem(_T("Exceed Flagging"), root);
	m_tree.SetItemData(hi, (DWORD)a_Features.EXCEED_FLAGS);
	hi = m_tree.InsertItem(_T("Direct Temp Sensor"), root);
	m_tree.SetItemData(hi, (DWORD)a_Features.DIRECT_TEMP_SENSOR);
	hi = m_tree.InsertItem(_T("Save Relay State"), root);
	m_tree.SetItemData(hi, (DWORD)a_Features.SAVE_RELAY_STATE);

	// expand all the levels
	m_tree.Expand(root, TVE_EXPAND);
	m_tree.Expand(setup, TVE_EXPAND);
	m_tree.Expand(menu, TVE_EXPAND);
	m_tree.Expand(screen, TVE_EXPAND);
	m_tree.Expand(fonts, TVE_EXPAND);
	m_tree.Expand(exp, TVE_EXPAND);

	m_tree.SelectItem(root);
}

void RAFeaturesPage::OnResetAll()
{
	LoadDefaults();
}

void RAFeaturesPage::OnResetSaved()
{
	LoadFeatures();
}

void RAFeaturesPage::ClearDescription()
{
	SetDlgItemText(IDC_FEATURES_TEXT_DESCRIPTION, _T("Click on features to get descriptions."));
}

void RAFeaturesPage::SetDescription(UINT id)
{
	CString s;
	s.LoadString(id);
	SetDlgItemText(IDC_FEATURES_TEXT_DESCRIPTION, s);
}

void RAFeaturesPage::LoadFeatures()
{
	// Restore values from registry after last generation
	// TODO add in conversion from old keys to new keys
	CString s;
	s.LoadStringA(IDS_FEATURES_TAB);
	BOOL fDefault = FALSE;
	for ( int i = 1; i < a_Features.MAX_FEATURES; i++ )
	{
		fDefault = a_Features.IsDefaultEnabledFeature(i);
		a_Features.SetFeatureValue(i, AfxGetApp()->GetProfileInt(s, a_Features.GetFeatureDefine(i), fDefault));
	}
	a_Features.iCustomMenuEntries = AfxGetApp()->GetProfileInt(s, _T("CustomMenuEntries"), MENU_DEFAULT);
	UpdateDisplay();
}

void RAFeaturesPage::SaveFeatures(/*Features fs*/)
{
	// Save values to registry after last generation
	CString s;
	s.LoadString(IDS_FEATURES_TAB);
	for ( int i = 1; i < a_Features.MAX_FEATURES; i++ )
	{
		AfxGetApp()->WriteProfileInt(s, a_Features.GetFeatureDefine(i), a_Features.GetFeatureValue(i));
	}
	AfxGetApp()->WriteProfileInt(s, _T("CustomMenuEntries"), a_Features.iCustomMenuEntries);
}

void RAFeaturesPage::LoadDefaults()
{
	// Load default values
	a_Features.LoadDefaults();
	UpdateDisplay();
}

void RAFeaturesPage::UpdateDisplay()
{
	HTREEITEM h;
	h = m_tree.GetNextItem(TVI_ROOT, TVGN_ROOT);
	UpdateListNode(h);
	m_tree.UpdateData();
}

void RAFeaturesPage::UpdateListNode(HTREEITEM h, BOOL fStoreFeatures /*= FALSE*/)
{
	DWORD index;
	BOOL fChecked;
	while ( h != NULL )
	{
		index = (DWORD)m_tree.GetItemData(h);
		if ( index == 0 )
		{
			// we hit a submenu, traverse it
			UpdateListNode(m_tree.GetNextItem(h, TVGN_CHILD), fStoreFeatures);
		}
		else
		{
			if ( fStoreFeatures )
			{
				// Store features from list in class
				fChecked = m_tree.GetCheck(h);
				TRACE("Store: %s, %s\n", a_Features.GetFeatureDefine(index), fChecked?"TRUE":"FALSE");
				a_Features.SetFeatureValue(index, fChecked);
			} 
			else
			{
				// Update feature list from features class
				fChecked = a_Features.GetFeatureValue(index);
				TRACE("Update: %s, %s\n", a_Features.GetFeatureDefine(index), fChecked?"TRUE":"FALSE");
				m_tree.SetCheck(h, fChecked);
			}
		}
		h = m_tree.GetNextItem(h, TVGN_NEXT);
	}
}

void RAFeaturesPage::UpdateFeatures(BOOL fResetPDEFeatures /*= TRUE*/)
{
	m_tree.UpdateData();
	HTREEITEM h;
	h = m_tree.GetNextItem(TVI_ROOT, TVGN_ROOT);
	UpdateListNode(h, TRUE);

	if ( fResetPDEFeatures || a_Features.IsCustomMenu() )
	{
		// features set on the PDE / INO page
		a_Features.ClearINOFeatures();
	}
}

BOOL RAFeaturesPage::WriteFeatures(LPCTSTR sLibraryFolder)
{
	return a_Features.Write(sLibraryFolder);
}

BOOL RAFeaturesPage::ReadFeatures(CString sFeaturesFile)
{
	BOOL fRet = a_Features.Read(sFeaturesFile);
	UpdateDisplay();
	return fRet;
}

void RAFeaturesPage::ShowUnknownFeatures()
{
	a_Features.ShowUnknownFeatures();
}

void RAFeaturesPage::ClearFeatures()
{
	a_Features.Clear();
}

void RAFeaturesPage::OnTvnSelchangedFeaturesTree(NMHDR * /*pNMHDR*/, LRESULT *pResult)
{
	HTREEITEM i = m_tree.GetSelectedItem();
	DWORD index = (DWORD)m_tree.GetItemData(i);
	TRACE("Desc:  %s, %d\n", a_Features.GetFeatureDefine(index), a_Features.GetFeatureStringID(index));
	if ( a_Features.GetFeatureStringID(index) == 0 )
	{
		ClearDescription();
	}
	else 
	{
		SetDescription(a_Features.GetFeatureStringID(index));
	}

	*pResult = 0;
}
