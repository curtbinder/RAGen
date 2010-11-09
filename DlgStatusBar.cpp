
#include "stdafx.h"
#include <afxpriv.h>
#include "DlgStatusBar.h"


BEGIN_MESSAGE_MAP(DlgStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(DlgStatusBar)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


DlgStatusBar::DlgStatusBar()
{
}

DlgStatusBar::~DlgStatusBar()
{
}

LRESULT DlgStatusBar::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	if (IsWindowVisible())
	{
		CFrameWnd *pParent = (CFrameWnd *)GetParent();
		if (pParent)
			OnUpdateCmdUI(pParent, (BOOL)wParam);
	}
	return 0;
}
