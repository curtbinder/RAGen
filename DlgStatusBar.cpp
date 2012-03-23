// DlgStatusBar.cpp
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

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
