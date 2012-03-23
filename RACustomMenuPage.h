// RACustomMenuPage.h
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once


// RACustomMenuPage dialog

class RACustomMenuPage : public CDialog
{
	DECLARE_DYNAMIC(RACustomMenuPage)

public:
	RACustomMenuPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RACustomMenuPage();

// Dialog Data
	enum { IDD = IDD_RACUSTOMMENU };

	void UpdateValues();
	void UpdateDisplay();
	void SelectMenuQuantity(int qty);
	void LoadMenuEntrySelections(int qty);
	void EnableWindows(BOOL fEnable);
	void LoadCurrentFunction();
	void SaveCurrentFunction();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	BOOL m_fEnable;
	int m_iMenuQty;
	int m_iCurrent;
	CMenu m_mFunctions;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMenuBtnReset();
	afx_msg void OnBnClickedMenuBtnLoad();
	afx_msg void OnBnClickedMenuBtnClear();
	afx_msg void OnCbnSelchangeMenuCboMenu();
	afx_msg void OnCbnSelchangeMenuCboEntries();
	afx_msg void OnBnClickedMenuCkEnable();
	// TODO add in buttons to insert a function/action for the current menu item
	afx_msg void OnBnClickedMenuBtnPredefined();
	afx_msg void OnMenuFunctionSelected(UINT nID);
};
