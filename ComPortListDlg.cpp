// ComPortListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RAGen.h"
#include "ComPortListDlg.h"


// ComPortListDlg dialog

IMPLEMENT_DYNAMIC(ComPortListDlg, CDialog)

ComPortListDlg::ComPortListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ComPortListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON_MAIN);
	m_iCount = 0;
}

ComPortListDlg::~ComPortListDlg()
{
}

void ComPortListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM_LIST_PORTS, m_ListBox);
}


BEGIN_MESSAGE_MAP(ComPortListDlg, CDialog)
END_MESSAGE_MAP()


// ComPortListDlg message handlers

BOOL ComPortListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CString s;
	CString s1;
	if ( m_iCount > 0 )
	{
		// fill in the list box
		for ( int i = 0; i < m_iCount; i++ )
		{
			if ( !m_Ports[i].fOptiboot && m_Ports[i].fHasRA )
			{
				s1 = _T(" (Legacy)");
			}
			else
			{
				s1 = _T("");
			}
			s.Format(_T("COM%d - %s%s"), m_Ports[i].iPort, 
				(m_Ports[i].fHasRA)?_T("ReefAngel Controller"):_T("None"), s1.GetBuffer());
				
			m_ListBox.AddString(s);
		}  // for i
	}
	else
	{
		m_ListBox.AddString(_T("No COM Ports"));
	}
	UpdateData(FALSE);

	return TRUE;
}
