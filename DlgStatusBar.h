
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
