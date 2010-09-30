#pragma once


// RAPDEPage dialog

class RAPDEPage : public CPropertyPage
{
	DECLARE_DYNAMIC(RAPDEPage)

public:
	RAPDEPage();
	virtual ~RAPDEPage();

// Dialog Data
	enum { IDD = IDD_RAPDEPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
