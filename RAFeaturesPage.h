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

	// features - if you change any features, make sure you update the _Features structure in GlobalVars.h
	/*
	BOOL m_bDisplayImages;
	BOOL m_bSetupExtras;
	BOOL m_bOverheatSetup;
	BOOL m_bDateTimeSetup;
	BOOL m_bVersionMenu;
	BOOL m_bDirectTempSensor;
	BOOL m_bDisplayLEDPWM;
	BOOL m_bWifi;
	BOOL m_bAlternateFont;
	BOOL m_bRemoveAllLights;
	BOOL m_bSaveRelayState;
	BOOL m_bExpansionModule;
	BOOL m_bDosingIntervalSetup;
	BOOL m_bWDT;
	BOOL m_bCustomMenu;
	BOOL m_bSimpleMenu;
	BOOL m_bPWMExpansion;
	BOOL m_bCustomMain;
	BOOL m_bColorsPDE;
	BOOL m_bAtoLogging;
	BOOL m_bExceedFlags;
	int m_iCustomMenuEntries;
	int m_iInstalledExpansionModules;
	BOOL m_fSalinity;
	BOOL m_fRF;
	BOOL m_fORP;
	BOOL m_fIO;
	BOOL m_fAI;
	*/

	FeatureData m_efd[25];

	// unknown features from features file
	CString m_sUnknownFeatures;

	void ClearDescription();
	void SetDescription(UINT id);
	void LoadFeatures();
	void ProcessFeature(CString sFeature, CString sValue = _T(""));
	void ClearFeatures();
	void InitTree();

public:
	void LoadDefaults();
	void UpdateFeaturesStruct(BOOL fResetPDEFeatures = TRUE);
	BOOL WriteFeatures(Features fs, LPCTSTR sLibraryFolder);
	void SaveFeatures(/*Features fs*/);
	BOOL ReadFeatures(CString sFeaturesFile);
	void ShowUnknownFeatures();

	afx_msg void OnTvnSelchangedFeaturesTree(NMHDR *pNMHDR, LRESULT *pResult);
	void OnResetAll();
	void OnResetSaved();
	virtual BOOL OnInitDialog();
};
