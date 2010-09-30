#pragma once


// RAColorsPage dialog

class RAColorsPage : public CPropertyPage
{
	DECLARE_DYNAMIC(RAColorsPage)

public:
	RAColorsPage();
	virtual ~RAColorsPage();

// Dialog Data
	enum { IDD = IDD_RACOLORSPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
