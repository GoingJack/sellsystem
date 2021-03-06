// COrderInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "COrderInfo.h"
#include "afxdialogex.h"
#include "CInfoDatabase.h"

// COrderInfo 对话框

IMPLEMENT_DYNCREATE(COrderInfo, CFormView)


COrderInfo::COrderInfo()
	:CFormView(COrderInfo::IDD)
	, m_user(_T(""))
	, m_seller(_T(""))
	, m_date(_T(""))
{
}

COrderInfo::~COrderInfo()
{
}

void COrderInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_seller);
	DDX_Text(pDX, IDC_EDIT5, m_date);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
}


BEGIN_MESSAGE_MAP(COrderInfo, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &COrderInfo::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &COrderInfo::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

#ifdef _DEBUG
void COrderInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
// COrderInfo 消息处理程序

void COrderInfo::Data2Mouth(char *date,char **out)//分割字符串
{
	if (date == NULL)
	{
		MessageBox("error传入的字符串为空");
		return;
	}
	char *tmp = strstr(date, "-");
	tmp += 1;
	char *tmp1 = strstr(tmp, "-");
	char realdate[20];
	int i = 0;
	for (date; date != tmp1; date++)
	{
		realdate[i] = *date;
		i++;
	}

	realdate[i] = '\0';
	strcpy(*out, realdate);


}
void COrderInfo::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//日期字符串分割
	/*char *date = "2018-09-01";
	char *out=(char *)malloc(200);
	Data2Mouth(date, &out);
	MessageBox(out);*/
	// TODO: 在此添加专用代码和/或调用基类
	m_combo.ResetContent();
	((CEdit*)m_combo.GetWindow(GW_CHILD))->SetReadOnly();
	//初始化下拉框
	CInfoDatabase data;
	data.ReadInfo_Order(1);

	
	int times = 0;//是否第一次添加查看销售额的容器
	for (list<ordersystem>::iterator it = data.order.begin(); it != data.order.end(); it++)
	{
		m_combo.AddString(CString(it->Order_Id));
	}
	
	//设置初始化的商品
	if (m_combo.GetCount() != 0)//如果不为空
	{
		m_combo.SetCurSel(0);
		OnCbnSelchangeCombo2();

	}
	else
	{
		m_button1.EnableWindow(0);
		//m_button2.EnableWindow(0);
	}
	//初始化list信息
	m_list.DeleteAllItems();
	LONG styles;
	styles = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, styles | LVS_REPORT);
	CString str[] = { _T("序号"),_T("商品名字"),_T("购买个数"),_T("总价格") };
	for (int i = 0; i < 4; i++)
	{
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 90, -1);
	}

}


void COrderInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	m_list.DeleteAllItems();
	CInfoDatabase datagetCommodity;//用于商品映射的对象
	CInfoDatabase ordertoCommodity;//用于存取订单具体商品各种信息
	datagetCommodity.ReadDocline();

	msg tmp;
	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	msg showdata;//显示的具体商品
	int index = m_combo.GetCurSel();
	CString name;//当前选中的订单编号
	m_combo.GetLBText(index, name);
	CStringA tmp_name = name;
	char *pp = tmp_name.GetBuffer();
	CString sql_to_getallcommodity;
	sql_to_getallcommodity.Format("SELECT C_Id,Out_Count,Out_Total FROM outsystem WHERE Order_Id=\'%s\'", pp);
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)sql_to_getallcommodity);
	if (ress == 0)
	{
		res = mysql_store_result(&mysqlCon);
		if (mysql_num_rows(res) == 0)
		{
			MessageBox("此订单号暂时无产品!\n");
		}
		else
		{
			//MessageBox("here");
			char szBuffer[1024];
			while (row = mysql_fetch_row(res))
			{
				sprintf(szBuffer, "%s", row[0]);
				tmp.id = atoi(szBuffer);//商品id赋值给临时结构体
				sprintf(szBuffer, "%s", row[1]);
				tmp.pnum = atoi(szBuffer);//商品购买的个数赋值给结构体
				sprintf(szBuffer, "%s", row[2]);
				datagetCommodity.charToDouble(szBuffer, tmp.totalprice);
				for (list<msg>::iterator j = datagetCommodity.ls.begin(); j != datagetCommodity.ls.end(); j++)
				{
					if (tmp.id == j->id)
					{
						sprintf(tmp.name, "%s", j->name);
					}
				}
				ordertoCommodity.ls.push_back(tmp);
			}
		}
		int seller_index_listctrl = 0;
		for (list<msg>::iterator it = ordertoCommodity.ls.begin(); it != ordertoCommodity.ls.end(); it++)
		{
			//MessageBox("here");
			CString str;
			str.Format("%d", seller_index_listctrl);
			m_list.InsertItem(seller_index_listctrl, str);
			m_list.SetItemText(seller_index_listctrl, 1, it->name);
			CString tmp;
			tmp.Format("%d", it->pnum);
			m_list.SetItemText(seller_index_listctrl, 2, tmp);
			tmp.Format("%lf", it->totalprice);
			m_list.SetItemText(seller_index_listctrl++, 3, tmp);
		}
	}
	else
	{
		MessageBox("你点击的太快了请稍后再试试！");
	}
}


void COrderInfo::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoDatabase data;
	data.ReadInfo_Order(1);
	for (list<ordersystem>::iterator it = data.order.begin(); it != data.order.end(); it++)
	{
		if ((CString)it->Order_Id == name)
		{
			m_user = it->Username;
			m_seller = it->Order_dealer;
			m_date = it->Order_Date;
			UpdateData(FALSE);
		}
	}
}
