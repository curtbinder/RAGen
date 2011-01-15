// WebBannerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebBannerDlg.h"


// Global Functions
void LoadWebBannerInfoDefaults(WebBannerInfo &wi)
{
	CString s;
	s.LoadString(IDS_WEBBANNER);
	wi.sID = AfxGetApp()->GetProfileString(s, _T("id"), _T("rimai"));
	wi.sT1n = AfxGetApp()->GetProfileString(s, _T("t1n"), _T("Water"));
	wi.sT2n = AfxGetApp()->GetProfileString(s, _T("t2n"), _T("Room"));
	wi.sT3n = AfxGetApp()->GetProfileString(s, _T("t3n"), _T(""));
	wi.sR1n = AfxGetApp()->GetProfileString(s, _T("r1n"), _T("ATO"));
	wi.sR2n = AfxGetApp()->GetProfileString(s, _T("r2n"), _T("Actinic"));
	wi.sR3n = AfxGetApp()->GetProfileString(s, _T("r3n"), _T("Halide"));
	wi.sR4n = AfxGetApp()->GetProfileString(s, _T("r4n"), _T("Powerhead 2"));
	wi.sR5n = AfxGetApp()->GetProfileString(s, _T("r5n"), _T("Powerhead 1"));
	wi.sR6n = AfxGetApp()->GetProfileString(s, _T("r6n"), _T("Chiller"));
	wi.sR7n = AfxGetApp()->GetProfileString(s, _T("r7n"), _T("Heater"));
	wi.sR8n = AfxGetApp()->GetProfileString(s, _T("r8n"), _T("Sump"));
	wi.nInterval = AfxGetApp()->GetProfileInt(s, _T("interval"), 180);
}

void SaveWebBannerInfo(WebBannerInfo &wi)
{
	CString s;
	s.LoadString(IDS_WEBBANNER);
	AfxGetApp()->WriteProfileString(s, _T("id"), wi.sID);
	AfxGetApp()->WriteProfileString(s, _T("t1n"), wi.sT1n);
	AfxGetApp()->WriteProfileString(s, _T("t2n"), wi.sT2n);
	AfxGetApp()->WriteProfileString(s, _T("t3n"), wi.sT3n);
	AfxGetApp()->WriteProfileString(s, _T("r1n"), wi.sR1n);
	AfxGetApp()->WriteProfileString(s, _T("r2n"), wi.sR2n);
	AfxGetApp()->WriteProfileString(s, _T("r3n"), wi.sR3n);
	AfxGetApp()->WriteProfileString(s, _T("r4n"), wi.sR4n);
	AfxGetApp()->WriteProfileString(s, _T("r5n"), wi.sR5n);
	AfxGetApp()->WriteProfileString(s, _T("r6n"), wi.sR6n);
	AfxGetApp()->WriteProfileString(s, _T("r7n"), wi.sR7n);
	AfxGetApp()->WriteProfileString(s, _T("r8n"), wi.sR8n);
	AfxGetApp()->WriteProfileInt(s, _T("interval"), wi.nInterval);
}

void UpdateWebBannerInfoStrings(WebBannerInfo &wi)
{
	if ( wi.sT1n.IsEmpty() ) { wi.sT1n = _T("Not Used"); }
	if ( wi.sT2n.IsEmpty() ) { wi.sT2n = _T("Not Used"); }
	if ( wi.sT3n.IsEmpty() ) { wi.sT3n = _T("Not Used"); }
	if ( wi.sR1n.IsEmpty() ) { wi.sR1n = _T("Not Used"); }
	if ( wi.sR2n.IsEmpty() ) { wi.sR2n = _T("Not Used"); }
	if ( wi.sR3n.IsEmpty() ) { wi.sR3n = _T("Not Used"); }
	if ( wi.sR4n.IsEmpty() ) { wi.sR4n = _T("Not Used"); }
	if ( wi.sR5n.IsEmpty() ) { wi.sR5n = _T("Not Used"); }
	if ( wi.sR6n.IsEmpty() ) { wi.sR6n = _T("Not Used"); }
	if ( wi.sR7n.IsEmpty() ) { wi.sR7n = _T("Not Used"); }
	if ( wi.sR8n.IsEmpty() ) { wi.sR8n = _T("Not Used"); }
	wi.sT1n.Replace(_T(" "), _T("%20"));
	wi.sT2n.Replace(_T(" "), _T("%20"));
	wi.sT3n.Replace(_T(" "), _T("%20"));
	wi.sR1n.Replace(_T(" "), _T("%20"));
	wi.sR2n.Replace(_T(" "), _T("%20"));
	wi.sR3n.Replace(_T(" "), _T("%20"));
	wi.sR4n.Replace(_T(" "), _T("%20"));
	wi.sR5n.Replace(_T(" "), _T("%20"));
	wi.sR6n.Replace(_T(" "), _T("%20"));
	wi.sR7n.Replace(_T(" "), _T("%20"));
	wi.sR8n.Replace(_T(" "), _T("%20"));
}

CString GetWebBannerInfoString(WebBannerInfo &wi, BOOL bProgMem /*= TRUE*/)
{
	CString s = _T("");
	UpdateWebBannerInfoStrings(wi);
	if ( bProgMem )
	{
		s.Format(_T("\
prog_char id_label[] PROGMEM = \"%s\";\r\n\
prog_char probe1_label[] PROGMEM = \"%s\";\r\n\
prog_char probe2_label[] PROGMEM = \"%s\";\r\n\
prog_char probe3_label[] PROGMEM = \"%s\";\r\n\
prog_char relay1_label[] PROGMEM = \"%s\";\r\n\
prog_char relay2_label[] PROGMEM = \"%s\";\r\n\
prog_char relay3_label[] PROGMEM = \"%s\";\r\n\
prog_char relay4_label[] PROGMEM = \"%s\";\r\n\
prog_char relay5_label[] PROGMEM = \"%s\";\r\n\
prog_char relay6_label[] PROGMEM = \"%s\";\r\n\
prog_char relay7_label[] PROGMEM = \"%s\";\r\n\
prog_char relay8_label[] PROGMEM = \"%s\";\r\n\
PROGMEM const char *webbanner_items[] = {\r\n\
    id_label, probe1_label, probe2_label, probe3_label, relay1_label, relay2_label,\r\n\
	relay3_label, relay4_label, relay5_label, relay6_label, relay7_label, relay8_label};\r\n\
"), wi.sID, wi.sT1n, wi.sT2n, wi.sT3n, wi.sR1n, wi.sR2n, wi.sR3n, wi.sR4n,
		wi.sR5n, wi.sR6n, wi.sR7n, wi.sR8n);
	}
	else
	{
		s.Format(_T("&t1n=%s&t2n=%s&t3n=%s&r1n=%s&r2n=%s&r3n=%s&r4n=%s&r5n=%s&r6n=%s&r7n=%s&r8n=%s"),
			wi.sT1n, wi.sT2n, wi.sT3n, wi.sR1n, wi.sR2n, wi.sR3n, wi.sR4n,
			wi.sR5n, wi.sR6n, wi.sR7n, wi.sR8n);
	}
	return s;
}

// WebBannerDlg dialog

IMPLEMENT_DYNAMIC(WebBannerDlg, CDialog)

WebBannerDlg::WebBannerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(WebBannerDlg::IDD, pParent)
{
	LoadWebBannerInfoDefaults(m_wi);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
}

WebBannerDlg::~WebBannerDlg()
{
}

void WebBannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL WebBannerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CSpinButtonCtrl* pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_WEB_SPIN_INTERVAL);
	pSpin->SetBuddy(GetDlgItem(IDC_WEB_EDIT_INTERVAL));
	pSpin->SetRange32(WEB_INTERVAL_MIN, WEB_INTERVAL_MAX);

	SetDlgItemInt(IDC_WEB_EDIT_INTERVAL, m_wi.nInterval);
	SetDlgItemText(IDC_WEB_ID, m_wi.sID);
	SetDlgItemText(IDC_WEB_T1, m_wi.sT1n);
	SetDlgItemText(IDC_WEB_T2, m_wi.sT2n);
	SetDlgItemText(IDC_WEB_T3, m_wi.sT3n);
	SetDlgItemText(IDC_WEB_R1, m_wi.sR1n);
	SetDlgItemText(IDC_WEB_R2, m_wi.sR2n);
	SetDlgItemText(IDC_WEB_R3, m_wi.sR3n);
	SetDlgItemText(IDC_WEB_R4, m_wi.sR4n);
	SetDlgItemText(IDC_WEB_R5, m_wi.sR5n);
	SetDlgItemText(IDC_WEB_R6, m_wi.sR6n);
	SetDlgItemText(IDC_WEB_R7, m_wi.sR7n);
	SetDlgItemText(IDC_WEB_R8, m_wi.sR8n);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(WebBannerDlg, CDialog)
	ON_BN_CLICKED(IDOK, &WebBannerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_WEB_BTN_QUESTION, &WebBannerDlg::OnBnClickedQuestion)
END_MESSAGE_MAP()

void WebBannerDlg::UpdateInfo()
{
	// Get all the data from the window
	// Update the values in the structure
	CString s;
	GetDlgItemText(IDC_WEB_EDIT_INTERVAL, s);
	m_wi.nInterval = atoi(s);
	GetDlgItemText(IDC_WEB_ID, m_wi.sID);
	GetDlgItemText(IDC_WEB_T1, m_wi.sT1n);
	GetDlgItemText(IDC_WEB_T2, m_wi.sT2n);
	GetDlgItemText(IDC_WEB_T3, m_wi.sT3n);
	GetDlgItemText(IDC_WEB_R1, m_wi.sR1n);
	GetDlgItemText(IDC_WEB_R2, m_wi.sR2n);
	GetDlgItemText(IDC_WEB_R3, m_wi.sR3n);
	GetDlgItemText(IDC_WEB_R4, m_wi.sR4n);
	GetDlgItemText(IDC_WEB_R5, m_wi.sR5n);
	GetDlgItemText(IDC_WEB_R6, m_wi.sR6n);
	GetDlgItemText(IDC_WEB_R7, m_wi.sR7n);
	GetDlgItemText(IDC_WEB_R8, m_wi.sR8n);
}

// WebBannerDlg message handlers

void WebBannerDlg::OnBnClickedOk()
{
	UpdateData();
	UpdateInfo();
	SaveWebBannerInfo(m_wi);
	OnOK();
}

void WebBannerDlg::OnBnClickedQuestion()
{
	CString s;
	s = _T("In order to use the web banner, you need to configure your wifi module as follows:\n\n\
set u m 2 \n\
set d n www.reefangel.com \n\
set i h 198.171.134.6 \n\
set i r 80 \n\
save \n\
reboot \n\n\
If you have any questions, please goto http://www.reefangel.com/");
	AfxMessageBox(s);
}
