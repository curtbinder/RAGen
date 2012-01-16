#pragma once

#include "GlobalVars.h"

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

	// features - if you change any features, make sure you update the _Features structure in GlobalVars.h
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

	// unknown features from features file
	CString m_sUnknownFeatures;

	void ClearDescription();
	void SetDescription(UINT id);
	void LoadFeatures();
	void ProcessFeature(CString sFeature, CString sValue = _T(""));
	void ClearFeatures();

public:
	void LoadDefaults();
	void UpdateFeaturesStruct(Features& fs, BOOL fResetPDEFeatures = TRUE);
	BOOL WriteFeatures(Features fs, LPCTSTR sLibraryFolder);
	void SaveFeatures(Features fs);
	BOOL ReadFeatures(CString sFeaturesFile);
	void ShowUnknownFeatures();
	afx_msg void OnBnHotItemChangeCkDisplayImages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkSetupExtras(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkOverheatSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDateTimeSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkVersionMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDirectTempSensor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDisplayLedPwm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkWifi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkAlternateFont(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkSaveRelayState(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkRemoveAllLights(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkExpansionModule(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDosingIntervalSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkAtoLogging(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkExceedFlag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkWdt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkCustomMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkSimpleMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkCustomMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkColorsPde(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkPwmExpansion(NMHDR *pNMHDR, LRESULT *pResult);
	void OnResetAll();
	void OnResetSaved();
	virtual BOOL OnInitDialog();
};
