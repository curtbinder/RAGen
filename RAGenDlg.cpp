// RAGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "RAGenDlg.h"
#include "AboutDlg.h"


// RAGenDlg dialog

IMPLEMENT_DYNAMIC(RAGenDlg, CDialog)

RAGenDlg::RAGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RAGenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
}

RAGenDlg::~RAGenDlg()
{
}

void RAGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tabs);
}

void RAGenDlg::SetStatus(LPCTSTR s)
{
	SetDlgItemText(IDC_TEXT_STATUS, s);
}

void RAGenDlg::ClearStatus()
{
	SetStatus(_T(""));
}

BEGIN_MESSAGE_MAP(RAGenDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EDIT_SETTINGS, &RAGenDlg::OnEditSettings)
	ON_COMMAND(ID_FILE_EXIT, &RAGenDlg::OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT, &RAGenDlg::OnHelpAbout)
	ON_BN_CLICKED(IDC_BTN_GENERATE, &RAGenDlg::OnBnClickedBtnGenerate)
END_MESSAGE_MAP()


// RAGenDlg message handlers

BOOL RAGenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Tabs.Init();

	return TRUE;
}

void RAGenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR RAGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void RAGenDlg::OnEditSettings()
{
	// Load settings
	//SetStatus(_T("This is the status"));
}

void RAGenDlg::OnFileExit()
{
	PostMessage(WM_CLOSE);
}

void RAGenDlg::OnHelpAbout()
{
	AboutDlg dlg;
	dlg.DoModal();
}

void RAGenDlg::OnBnClickedBtnGenerate()
{
	// Process the Generate Button Press
}

BOOL RAGenDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::OnCommand(wParam, lParam);
}
