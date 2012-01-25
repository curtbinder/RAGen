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

	void ClearDescription();
	void SetDescription(UINT id);
	// loads features from registry
	void LoadFeatures();
	// clears the features class
	void ClearFeatures();
	// initialize the feature tree list
	void InitTree();

public:
	void LoadDefaults();
	// updates the tree list with the features
	void UpdateDisplay();
	void UpdateListNode(HTREEITEM p, BOOL fStoreFeatures = FALSE);
	// updates the features from the tree list
	void UpdateFeatures(BOOL fResetPDEFeatures = TRUE);
	// writes the features.h file
	BOOL WriteFeatures(LPCTSTR sLibraryFolder);
	// saves features to registry
	void SaveFeatures();
	// reads the features.h file
	BOOL ReadFeatures(CString sFeaturesFile);
	// displays popup window of unknown features
	void ShowUnknownFeatures();

	afx_msg void OnTvnSelchangedFeaturesTree(NMHDR *pNMHDR, LRESULT *pResult);
	void OnResetAll();
	void OnResetSaved();
	virtual BOOL OnInitDialog();
};
