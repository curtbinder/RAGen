#pragma once


// RAController dialog

class RAController : public CDialog
{
	DECLARE_DYNAMIC(RAController)

public:
	RAController(CWnd* pParent = NULL);   // standard constructor
	virtual ~RAController();

// Dialog Data
	enum { IDD = IDD_RACONTROLLER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	int m_fWifi;
	int m_iExpRelayQty;
	int m_fAddPWM;
	int m_fPortal;
	BOOL m_fTemp;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPortal();
	afx_msg void OnCbnSelchangeCboWifi();
	afx_msg void OnCbnSelchangeCboExpRelayQty();
	afx_msg void OnCbnSelchangeCboPwmslope();
	afx_msg void OnCbnSelchangeCboPortal();
	afx_msg void OnBnClickedControllerTemp0();
	afx_msg void OnBnClickedControllerTemp1();
	void UpdateValues();
	void UpdateControllerTemperature();
};
