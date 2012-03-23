// RAInfoPage.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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
