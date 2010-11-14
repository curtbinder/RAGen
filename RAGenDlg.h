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
	void ChangeMenu(UINT menuID);
	int FindMenuItem(CMenu* pMenu, LPCTSTR sMenu);
	BOOL GetSketchFolder();
	BOOL GetArduinoFolder(LPCTSTR sDir);
	void GetFolders();
	void UpdateSettings();
	void UpdateLaunchButtonVisibility(int nCmdShow);
	void CreateStatusBar();

	DECLARE_MESSAGE_MAP()

	TCHAR m_sSketchDirectory[MAX_PATH];  //!< Sketch directory
	TCHAR m_sArduinoDirectory[MAX_PATH];  //!< Arduino directory
	TCHAR m_sLibraryDirectory[MAX_PATH];  //!< Libraries directory
	TCHAR m_sCurrentDirectory[MAX_PATH];  //!< Current directory
	int iSaveReg;  //!< Variable for saving to registry, 0 - always, 1 - prompt, 2 - never
	int iLaunch;
	int iAppMode;  //!< Application mode, 0 - normal, 1 - development libraries
	BOOL fHasArduinoExe;
	HICON m_hIcon;
	BOOL fRestartRequired;
	RATabSheet m_Tabs;
	DlgStatusBar m_StatusBar;
	int m_iStatusBarSize;

public:
	void SetLaunchArduino(int iLaunchArduino) { iLaunch = iLaunchArduino; }
	void SetSaveRegistry(int iSave) { iSaveReg = iSave; }
	void SetAppMode(int iMode) { iAppMode = iMode; }
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditSettings();
	afx_msg void OnEditEnableAdvanced();
	afx_msg void OnFileExit();
	afx_msg void OnFileRestart();
	afx_msg void OnControllerFind();
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
