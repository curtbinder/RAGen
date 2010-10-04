#pragma once
#include "afxcmn.h"
#include "RATabSheet.h"

// RAGenDlg dialog

class RAGenDlg : public CDialog
{
	DECLARE_DYNAMIC(RAGenDlg)

public:
	RAGenDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAGenDlg();

// Dialog Data
	enum { IDD = IDD_RAGEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
	RATabSheet m_Tabs;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditSettings();
	afx_msg void OnFileExit();
	afx_msg void OnHelpAbout();
};
