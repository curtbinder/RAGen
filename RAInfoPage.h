#pragma once


// RAInfoPage dialog

class RAInfoPage : public CDialog
{
	DECLARE_DYNAMIC(RAInfoPage)

public:
	RAInfoPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAInfoPage();

// Dialog Data
	enum { IDD = IDD_RAINFOPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
