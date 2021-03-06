// DlgStatusBar.h
//

/*
 * Copyright (c) 2010-12 by Curt Binder (http://curtbinder.info)
 *
 * This work is made available under the terms of the 
 * Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 */

#pragma once

class DlgStatusBar : public CStatusBar
{
// Construction
public:
	DlgStatusBar();

// Implementation
public:
	virtual ~DlgStatusBar();

protected:
	// Generated message map functions
	//{{AFX_MSG(DlgStatusBar)
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
