#pragma once


// RAFeaturesPage dialog

class RAFeaturesPage : public CPropertyPage
{
	DECLARE_DYNAMIC(RAFeaturesPage)

public:
	RAFeaturesPage();
	virtual ~RAFeaturesPage();

// Dialog Data
	enum { IDD = IDD_RAFEATURESPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
