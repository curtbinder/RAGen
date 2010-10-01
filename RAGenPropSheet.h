#pragma once

#include "RAFeaturesPage.h"
#include "RAPDEPage.h"
#include "RAColorsPage.h"
#include "RASettingsPage.h"


// CRAGenPropSheet

class CRAGenPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CRAGenPropSheet)

public:
	CRAGenPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CRAGenPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CRAGenPropSheet();

protected:
	HICON m_hIcon;
	RAFeaturesPage m_FeaturesPage;
	//RASettingsPage m_SettingsPage;
	//RAColorsPage m_ColorsPage;
	//RAPDEPage m_PDEPage;


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
	afx_msg void OnEditSettings();
};


