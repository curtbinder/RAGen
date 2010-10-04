#pragma once


// RATabSheet

class RATabSheet : public CTabCtrl
{
	DECLARE_DYNAMIC(RATabSheet)

public:
	RATabSheet();
	virtual ~RATabSheet();
	void Init();
	void SetRectangle();

protected:
	DECLARE_MESSAGE_MAP()
	int m_iNumTabs;
	int m_iCurrentTab;
	CDialog* m_pTabs[4];

public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
};


