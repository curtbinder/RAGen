//
// AboutDlg.h
//

#pragma once
#include "resource.h"
#include "afxwin.h"

// AboutDlg dialog used for App About

class AboutDlg : public CDialog
{
public:
	AboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUT };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
	CStatic m_RALogo;
	CStatic m_CBLogo;
	CBitmap m_bmpRALogo;
	CBitmap m_bmpCBLogo;
};
