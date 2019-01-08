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
// CUserDlg ���

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


// CUserDlg ��Ϣ�������



void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	if (user_flag == 1)
	{
		m_user = TEXT("���");
	}
	else if (user_flag == 2)
	{
		m_user = TEXT("����Ա");
	}
	else if (user_flag == 3)
	{
		m_user = TEXT("����Ա");
	}
	m_name = user_name;
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	MYSQL_RES *res;
	if (m_newpwd.IsEmpty())
	{
		MessageBox("�������벻��Ϊ�գ�");
		return;
	}
	if (m_newpwd != m_surepwd)
	{
		MessageBox("�����������벻һ�£�");
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
	if (ress == 0) //����ѯ�ɹ�
	{
		MessageBox("�޸ĳɹ�!");
	}
	else
	{
		MessageBox("�޸�ʧ��!");
	}
	
	

}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_newpwd = "";
	m_surepwd = "";
	UpdateData(FALSE);
}

