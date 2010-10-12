#pragma once


// RASettingsPage dialog

class RASettingsPage : public CPropertyPage
{
	DECLARE_DYNAMIC(RASettingsPage)

public:
	RASettingsPage();
	virtual ~RASettingsPage();

// Dialog Data
	enum { IDD = IDD_RASETTINGSPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
