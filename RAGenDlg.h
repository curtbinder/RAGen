#pragma once
#include "afxcmn.h"
#include "RATabSheet.h"
#include "DlgStatusBar.h"

// RAGenDlg dialog

class RAGenDlg : public CDialog
{
	DECLARE_DYNAMIC(RAGenDlg)

public:
	RAGenDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAGenDlg();

// Dialog Data
	enum { IDD = IDD_RAGEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void SetStatus(LPCTSTR s);
	void ClearStatus();
	void SetStatusComPort(int port);
	void ClearStatusComPort();
	void ChangeMenu(UINT menuID);
	int FindMenuItem(CMenu* pMenu, LPCTSTR sMenu);
	void GetFolders();
	void UpdateSettings();
	void UpdateLaunchButtonVisibility(int nCmdShow);
	void CreateStatusBar();

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
	BOOL fRestartRequired;
	RATabSheet m_Tabs;
	DlgStatusBar m_StatusBar;
	int m_iStatusBarSize;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditSettings();
	afx_msg void OnFileExit();
	afx_msg void OnFileRestart();
	afx_msg void OnControllerFind();
	afx_msg void OnControllerWebBanner();
	afx_msg void OnControllerPasswordProtectWifi();
	afx_msg void OnControllerImportFeatures();
	afx_msg void OnControllerShowUnknownFeatures();
	afx_msg void OnControllerInternalMemory();
	afx_msg void OnHelpAbout();
	afx_msg void OnBnClickedBtnGenerate();
	afx_msg void OnBnClickedBtnLaunch();
	afx_msg void OnResetAll();
	afx_msg void OnResetSaved();
	afx_msg void OnResetPorts();
	afx_msg void OnResetTemp();
	afx_msg void OnResetLogging();
	afx_msg void OnResetFeedingMode();
	afx_msg void OnResetWaterChangeMode();
	afx_msg void OnResetOverheat();
	afx_msg void OnResetLightsOn();
	afx_msg void OnClose();
	afx_msg void OnBnClickedClose();
};
