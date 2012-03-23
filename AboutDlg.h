// AboutDlg.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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
