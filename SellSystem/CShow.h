#pragma once


// CShow 窗体视图

class CShow : public CFormView
{
	DECLARE_DYNCREATE(CShow)
protected:
	CShow();
	virtual ~CShow();
public:
	enum { IDD = DIALOG_INFO };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CListCtrl m_list;
	afx_msg void OnChange32772();
	afx_msg void OnNMRClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawList4(NMHDR *pNMHDR, LRESULT *pResult);
};
