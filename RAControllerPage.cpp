// RAControllerPage.cpp : implementation file
//

/*
 * Copyright (c) 2011-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#include "stdafx.h"
#include "RAGen.h"
#include "RAControllerPage.h"
#include "Controller.h"


// RAControllerPage dialog

IMPLEMENT_DYNAMIC(RAControllerPage, CDialog)

RAControllerPage::RAControllerPage(CWnd* pParent /*=NULL*/)
	: CDialog(RAControllerPage::IDD, pParent)
	, m_fWifi(0)
	, m_fAddPWM(0)
	, m_fPortal(0)
{
	m_fTemp = FALSE;
}

RAControllerPage::~RAControllerPage()
{
}

void RAControllerPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_CONTROLLER_TEMP_0, m_fTemp);
	DDX_CBIndex(pDX, IDC_CBO_WIFI, m_fWifi);
	DDX_CBIndex(pDX, IDC_CBO_PWMSLOPE, m_fAddPWM);
	DDX_CBIndex(pDX, IDC_CBO_PORTAL, m_fPortal);
}


BEGIN_MESSAGE_MAP(RAControllerPage, CDialog)
	ON_BN_CLICKED(IDC_BTN_PORTAL, &RAControllerPage::OnBnClickedBtnPortal)
	ON_CBN_SELCHANGE(IDC_CBO_WIFI, &RAControllerPage::OnCbnSelchangeCboWifi)
	ON_CBN_SELCHANGE(IDC_CBO_PWMSLOPE, &RAControllerPage::OnCbnSelchangeCboPwmslope)
	ON_CBN_SELCHANGE(IDC_CBO_PORTAL, &RAControllerPage::OnCbnSelchangeCboPortal)
	ON_BN_CLICKED(IDC_CONTROLLER_TEMP_0, &RAControllerPage::OnBnClickedControllerTemp0)
	ON_BN_CLICKED(IDC_CONTROLLER_TEMP_1, &RAControllerPage::OnBnClickedControllerTemp1)
END_MESSAGE_MAP()


// RAControllerPage message handlers

BOOL RAControllerPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateValues();

	return TRUE;
}

void RAControllerPage::UpdateValues()
{
	m_fWifi = a_Controller.Features.GetFeatureValue(a_Controller.Features.WIFI);
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

void RAControllerPage::OnBnClickedBtnPortal()
{
	// pass the request on to the main window
	theApp.m_pMainWnd->SendMessageA(WM_COMMAND, MAKEWPARAM(ID_CONTROLLER_WEBBANNER, 0), 0);
}

void RAControllerPage::OnCbnSelchangeCboWifi()
{
	UpdateData();
	TRACE("Wifi:  %d\n", m_fWifi);
	a_Controller.Features.SetFeatureValue(a_Controller.Features.WIFI, m_fWifi);
}

void RAControllerPage::OnCbnSelchangeCboPwmslope()
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

void RAControllerPage::OnCbnSelchangeCboPortal()
{
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

void RAControllerPage::OnBnClickedControllerTemp0()
{
	UpdateData();
	UpdateControllerTemperature();
}

void RAControllerPage::OnBnClickedControllerTemp1()
{
	UpdateData();
	UpdateControllerTemperature();
}

void RAControllerPage::UpdateControllerTemperature()
{
	TRACE("Temp:  %s\n", m_fTemp?"Celsius":"Fahrenheit");
	a_Controller.SetTemperatureUnit(m_fTemp);
}

void RAControllerPage::OnResetTemperature()
{
	UpdateData();
	m_fTemp = FALSE;
	UpdateData(FALSE);
	UpdateControllerTemperature();
}

void RAControllerPage::OnResetLogging()
{
	UpdateData();
	m_fPortal = FALSE;
	UpdateData(FALSE);
	OnCbnSelchangeCboPortal();
}

void RAControllerPage::OnResetAll()
{
	OnResetLogging();
	OnResetTemperature();
	// TODO improve reset all
	UpdateData(FALSE);
}

void RAControllerPage::OnResetSaved()
{
	// TODO Code in ResetSaved - save values on generate
	UpdateData(FALSE);
}
