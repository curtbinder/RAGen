#pragma once


// RAStdPage dialog

class RAStdPage : public CDialog
{
	DECLARE_DYNAMIC(RAStdPage)

public:
	RAStdPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAStdPage();

// Dialog Data
	enum { IDD = IDD_RASTDPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
