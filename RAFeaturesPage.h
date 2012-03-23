// RAFeaturesPage.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

#include "GlobalVars.h"
#include "afxcmn.h"

// RAFeaturesPage dialog

class RAFeaturesPage : public CDialog
{
	DECLARE_DYNAMIC(RAFeaturesPage)

public:
	RAFeaturesPage(CWnd* pParent = NULL);
	virtual ~RAFeaturesPage();

// Dialog Data
	enum { IDD = IDD_RAFEATURESPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CTreeCtrl m_tree;
	int m_iExpRelayQty;

	void ClearDescription();
	void SetDescription(UINT id);
	// loads features from registry
	void LoadFeatures();
	// clears the features class
	void ClearFeatures();
	// initialize the feature tree list
	void InitTree();
	void EnableExpRelayControls(BOOL fEnable);
	void CheckEnableExpansionRelay();

public:
	void LoadDefaults();
	// updates the tree list with the features
	void UpdateDisplay();
	void UpdateListNode(HTREEITEM p, BOOL fStoreFeatures = FALSE);
	// updates the features from the tree list
	void UpdateFeatures(BOOL fResetPDEFeatures = TRUE);
	// writes the features.h file
	BOOL WriteFeatures();
	// saves features to registry
	void SaveFeatures();
	// reads the features.h file
	BOOL ReadFeatures(CString sFeaturesFile);
	// displays popup window of unknown features
	void ShowUnknownFeatures();

	afx_msg void OnTvnSelchangedFeaturesTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCboExpRelayQty();
	void OnResetAll();
	void OnResetSaved();
	virtual BOOL OnInitDialog();
};
