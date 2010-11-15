#pragma once

#include "ComPortFunctions.h"

// ComPortListDlg dialog

class ComPortListDlg : public CDialog
{
	DECLARE_DYNAMIC(ComPortListDlg)

public:
	ComPortListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ComPortListDlg();

// Dialog Data
	enum { IDD = IDD_COM_LIST };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CListCtrl m_ListBox;

public:
	Port* m_Ports;
	int m_iCount;
	virtual BOOL OnInitDialog();
};
