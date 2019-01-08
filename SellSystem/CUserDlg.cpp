#include "stdafx.h"
#include "SellSystem.h"
#include "CUserDlg.h"
#include "mysql.h"
#include "Connect2Database.h"
#include "CLogin.h"
#include "CDisplayView.h"
#include "MainFrm.h"
extern int user_flag;
extern CString user_name;
//CUserDlg
IMPLEMENT_DYNCREATE(CUserDlg, CFormView);
CUserDlg::CUserDlg()
	:CFormView(CUserDlg::IDD)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newpwd(_T(""))
	, m_surepwd(_T(""))
{
}


CUserDlg::~CUserDlg()
{
}
void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newpwd);
	DDX_Text(pDX, IDC_EDIT4, m_surepwd);
}
BEGIN_MESSAGE_MAP(CUserDlg, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()
// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序



void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	if (user_flag == 1)
	{
		m_user = TEXT("买家");
	}
	else if (user_flag == 2)
	{
		m_user = TEXT("销售员");
	}
	else if (user_flag == 3)
	{
		m_user = TEXT("管理员");
	}
	m_name = user_name;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	MYSQL_RES *res;
	if (m_newpwd.IsEmpty())
	{
		MessageBox("密码输入不能为空！");
		return;
	}
	if (m_newpwd != m_surepwd)
	{
		MessageBox("俩次密码输入不一致！");
		return;
	}
	CString sql_update_passwd;
	if (user_flag == 1)
	{
		sql_update_passwd.Format("UPDATE user_info SET Password=\'%s\' WHERE Username=\'%s\'",m_newpwd,m_name);
	}
	else if (user_flag == 2)
	{
		sql_update_passwd.Format("UPDATE user_seller SET Password=\'%s\' WHERE Username=\'%s\'", m_newpwd, m_name);
	}
	else if (user_flag == 3)
	{
		sql_update_passwd.Format("UPDATE user_admin SET Password=\'%s\' WHERE Username=\'%s\'", m_newpwd, m_name);
	}
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)sql_update_passwd);
	if (ress == 0) //检测查询成功
	{
		MessageBox("修改成功!");
	}
	else
	{
		MessageBox("修改失败!");
	}
	
	

}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newpwd = "";
	m_surepwd = "";
	UpdateData(FALSE);
}

