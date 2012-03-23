#pragma once


// RAControllerPage dialog

class RAControllerPage : public CDialog
{
	DECLARE_DYNAMIC(RAControllerPage)

public:
	RAControllerPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAControllerPage();

// Dialog Data
	enum { IDD = IDD_RACONTROLLER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	int m_fWifi;
	int m_fAddPWM;
	int m_fPortal;
	BOOL m_fTemp;

public:
	inline void EnablePortal(BOOL fEnable) { m_fPortal = fEnable; }
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPortal();
	afx_msg void OnCbnSelchangeCboWifi();
	afx_msg void OnCbnSelchangeCboPwmslope();
	afx_msg void OnCbnSelchangeCboPortal();
	afx_msg void OnBnClickedControllerTemp0();
	afx_msg void OnBnClickedControllerTemp1();
	void UpdateValues();
	void UpdateControllerTemperature();
	void OnResetTemperature();
	void OnResetLogging();
	void OnResetAll();
	void OnResetSaved();
};
