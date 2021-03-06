#pragma once


// COrderInfo 窗体视图
class COrderInfo : public CFormView
{
	DECLARE_DYNCREATE(COrderInfo)

public:
	COrderInfo();
	virtual ~COrderInfo();
public:
	enum { IDD = DIALOG_ORDER_INFO };
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
	afx_msg void OnBnClickedButton1();
	CListCtrl m_list;
	CString m_user;
	CString m_seller;
	CString m_date;
	CComboBox m_combo;
	void Data2Mouth(char *date, char **out);
	CButton m_button1;
	afx_msg void OnCbnSelchangeCombo2();
};