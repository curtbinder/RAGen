// ComPortListDlg.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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
	CListBox m_ListBox;

public:
	Port* m_Ports;
	int m_iCount;
	virtual BOOL OnInitDialog();
};
