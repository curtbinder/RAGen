// RAPWMPage.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once


// RAPWMPage dialog

class RAPWMPage : public CDialog
{
	DECLARE_DYNAMIC(RAPWMPage)

public:
	RAPWMPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAPWMPage();

// Dialog Data
	enum { IDD = IDD_RAPWMPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
