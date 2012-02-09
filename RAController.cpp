// RAController.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAController.h"
#include "Controller.h"


// RAController dialog

IMPLEMENT_DYNAMIC(RAController, CDialog)

RAController::RAController(CWnd* pParent /*=NULL*/)
	: CDialog(RAController::IDD, pParent)
	, m_fWifi(0)
	, m_iExpRelayQty(0)
	, m_fAddPWM(0)
	, m_fPortal(0)
{
	m_fTemp = FALSE;
}

RAController::~RAController()
{
}

void RAController::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_CONTROLLER_TEMP_0, m_fTemp);
	DDX_CBIndex(pDX, IDC_CBO_WIFI, m_fWifi);
	DDX_CBIndex(pDX, IDC_CBO_EXP_RELAY_QTY, m_iExpRelayQty);
	DDV_MinMaxInt(pDX, m_iExpRelayQty, 0, 8);
	DDX_CBIndex(pDX, IDC_CBO_PWMSLOPE, m_fAddPWM);
	DDX_CBIndex(pDX, IDC_CBO_PORTAL, m_fPortal);
}


BEGIN_MESSAGE_MAP(RAController, CDialog)
	ON_BN_CLICKED(IDC_BTN_PORTAL, &RAController::OnBnClickedBtnPortal)
	ON_CBN_SELCHANGE(IDC_CBO_WIFI, &RAController::OnCbnSelchangeCboWifi)
	ON_CBN_SELCHANGE(IDC_CBO_EXP_RELAY_QTY, &RAController::OnCbnSelchangeCboExpRelayQty)
	ON_CBN_SELCHANGE(IDC_CBO_PWMSLOPE, &RAController::OnCbnSelchangeCboPwmslope)
	ON_CBN_SELCHANGE(IDC_CBO_PORTAL, &RAController::OnCbnSelchangeCboPortal)
	ON_BN_CLICKED(IDC_CONTROLLER_TEMP_0, &RAController::OnBnClickedControllerTemp0)
	ON_BN_CLICKED(IDC_CONTROLLER_TEMP_1, &RAController::OnBnClickedControllerTemp1)
END_MESSAGE_MAP()


// RAController message handlers

BOOL RAController::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString s;
	s.LoadStringA(IDS_CONTROLLER_TIPS);
	SetDlgItemText(IDC_CONTROLLER_TITLE, s);

	UpdateValues();

	return TRUE;
}

void RAController::UpdateValues()
{
	//a_Controller.Features.GetFeatureValue(a_Controller.Features.
	m_fWifi = a_Controller.Features.GetFeatureValue(a_Controller.Features.WIFI);
	if ( a_Controller.Features.GetFeatureValue(a_Controller.Features.EXPANSION_MODULE) )
	{
		m_iExpRelayQty = a_Controller.Features.iInstalledExpansionModules;
	}
	else
	{
		m_iExpRelayQty = 0;
	}
	m_fPortal = a_Controller.IsPortalEnabled();
	if ( m_fPortal && !m_fWifi)
	{
		m_fPortal = FALSE;
		a_Controller.EnablePortal(m_fPortal);
	}

	// if pwm disabled, disable pwmslope function
	if ( ! a_Controller.Features.GetFeatureValue(a_Controller.Features.DISPLAY_LED_PWM) )
	{
		m_fAddPWM = FALSE;
	}
	a_Controller.AddPWMSlope(m_fAddPWM);

	UpdateData(FALSE);
}

void RAController::OnBnClickedBtnPortal()
{
	// pass the request on to the main window
	theApp.m_pMainWnd->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_CONTROLLER_WEBBANNER, 0), 0);
}

void RAController::OnCbnSelchangeCboWifi()
{
	UpdateData();
	TRACE("Wifi:  %d\n", m_fWifi);
	a_Controller.Features.SetFeatureValue(a_Controller.Features.WIFI, m_fWifi);
}

void RAController::OnCbnSelchangeCboExpRelayQty()
{
	UpdateData();
	TRACE("Exp Qty:  %d\n", m_iExpRelayQty);
	BOOL fEnable = FALSE;
	if ( m_iExpRelayQty > 0 ) 
	{
		fEnable = TRUE;
	}
	a_Controller.Features.SetFeatureValue(a_Controller.Features.EXPANSION_MODULE, fEnable);
	a_Controller.Features.iInstalledExpansionModules = m_iExpRelayQty;
}

void RAController::OnCbnSelchangeCboPwmslope()
{
	UpdateData();
	TRACE("PWM:  %d\n", m_fAddPWM);
	a_Controller.AddPWMSlope(m_fAddPWM);
	if ( m_fAddPWM )
	{
		// enable display led pwm if we add pwmslope
		a_Controller.Features.SetFeatureValue(a_Controller.Features.DISPLAY_LED_PWM, TRUE);
	}
	// do not disable led pwm if we remove pwmslope
}

void RAController::OnCbnSelchangeCboPortal()
{
	// TODO update the controller variable used for enabling the PORTAL
	UpdateData();
	TRACE("Portal:  %d\n", m_fPortal);
	a_Controller.EnablePortal(m_fPortal);
	if ( m_fPortal )
	{
		// Make sure wifi is enabled if we enable the portal
		a_Controller.Features.SetFeatureValue(a_Controller.Features.WIFI, TRUE);
		m_fWifi = 1;
		UpdateData(FALSE);
	}
}

void RAController::OnBnClickedControllerTemp0()
{
	UpdateData();
	UpdateControllerTemperature();
}

void RAController::OnBnClickedControllerTemp1()
{
	UpdateData();
	UpdateControllerTemperature();
}

void RAController::UpdateControllerTemperature()
{
	TRACE("Temp:  %s\n", m_fTemp?"Celsius":"Fahrenheit");
	a_Controller.SetTemperatureUnit(m_fTemp);
}
