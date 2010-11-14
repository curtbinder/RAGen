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
	BOOL m_bDosingPumpSetup;
	BOOL m_bWavemakerSetup;
	BOOL m_bOverheatSetup;
	BOOL m_bDateTimeSetup;
	BOOL m_bVersionMenu;
	BOOL m_bATOSetup;
	BOOL m_bMetalHalideSetup;
	BOOL m_bDirectTempSensor;
	BOOL m_bDisplayLEDPWM;
	BOOL m_bWifi;
	BOOL m_bAlternateFont;
	BOOL m_bSingleATO;
	BOOL m_bStandardLightSetup;
	BOOL m_bRemoveAllLights;
	BOOL m_bSaveRelayState;

	void ClearDescription();
	void SetDescription(UINT id);
	void LoadFeatures();
	void LoadDefaults();

public:
	void UpdateFeaturesStruct(Features& fs);
	BOOL WriteFeatures(Features fs, LPCTSTR sLibraryFolder);
	void SaveFeatures(Features fs);
	afx_msg void OnBnHotItemChangeCkDisplayImages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkSetupExtras(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDosingpumpSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkWavemakerSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkOverheatSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDateTimeSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkVersionMenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkAtoSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkMetalHalideSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDirectTempSensor(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkDisplayLedPwm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkWifi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkAlternateFont(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkSaveRelayState(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkStandardLightsSetup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkRemoveAllLights(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnHotItemChangeCkSingleAto(NMHDR *pNMHDR, LRESULT *pResult);
	void OnResetAll();
	void OnResetSaved();
	virtual BOOL OnInitDialog();
};
