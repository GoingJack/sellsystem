// CShow.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "CShow.h"
#include "afxdialogex.h"
#include "CInfoDatabase.h"
#include "MainFrm.h"
#include "CSelectView.h"

CString changeInfo;
int Select_hang=-1;

// CShow 对话框

IMPLEMENT_DYNCREATE(CShow, CFormView)

CShow::CShow()
	:CFormView(CShow::IDD)
{
}

CShow::~CShow()
{
}

void CShow::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST4, m_list);
}


BEGIN_MESSAGE_MAP(CShow, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CShow::OnBnClickedButton1)
	ON_COMMAND(ID_CHANGE_32772, &CShow::OnChange32772)
	ON_NOTIFY(NM_RCLICK, IDC_LIST4, &CShow::OnNMRClickList4)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CShow::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShow::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShow 消息处理程序


void CShow::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化list信息
	m_list.DeleteAllItems();
	LONG styles;
	styles = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, styles | LVS_REPORT);
	CString str[] = { _T("序号"),_T("商品名字"),_T("商品单价"),_T("商品库存"),_T("商品进价")};
	for (int i = 0; i < 5; i++)
	{
		m_list.InsertColumn(i,str[i],LVCFMT_LEFT,90,-1);
	}
	//
	CInfoDatabase data;
	data.ReadInfo_Commodity();
	int info_index_listctrl = 0;
	for (list<msg>::iterator it = data.Info_commodity.begin(); it != data.Info_commodity.end(); it++)
	{
		
		CString tmp;
		tmp.Format("%d", info_index_listctrl);
		m_list.InsertItem(info_index_listctrl, tmp);
		
		m_list.SetItemText(info_index_listctrl, 1, it->name);
		tmp.Format("%lf", it->price);
		m_list.SetItemText(info_index_listctrl, 2, tmp);
		tmp.Format("%d", it->num);
		m_list.SetItemText(info_index_listctrl, 3, tmp);
		tmp.Format("%lf", it->IPrice);
		m_list.SetItemText(info_index_listctrl++, 4, tmp);
		
	}

}


void CShow::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	changeInfo.Format("可乐");
	CPoint point;
	GetCursorPos(&point);

	CMenu menu;
	menu.LoadMenuA(IDR_MENU1);
	CMenu *popup = menu.GetSubMenu(0);
	//弹出显示
	popup->TrackPopupMenu(TPM_RIGHTALIGN | TPM_LEFTALIGN, point.x, point.y, this);
	//::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}


void CShow::OnChange32772()
{
	// TODO: 在此添加命令处理程序代码
	

	//int num = m_list.GetSelectionMark();
	if (Select_hang >= 0)
	{
		changeInfo = m_list.GetItemText(Select_hang, 1);
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else
	{
		return;
	}
}


void CShow::OnNMRClickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//MessageBox("没有选中的项");
	//如果没有选中的行，右键菜单不显示
	//POSITION pos = m_list.GetFirstSelectedItemPosition();
	//int CurSel = m_list.GetNextSelectedItem(pos);//取得当前的行号
	//if (CurSel = -1)return;//没有选中的项目，返回
	//显示弹出的菜单
	//int num = m_list.GetSelectionMark();
	//CString tmp;
	//tmp.Format("%d", num);
	//MessageBox(tmp);
	////changeInfo = m_list.GetItemText(num, 1);
	////::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	m_list.ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_list.SubItemHitTest(&lvinfo);
	if (nItem != -1)
	{
		CString strtemp;
		strtemp.Format("单击的是第%d行第%d列", lvinfo.iItem, lvinfo.iSubItem);
		//AfxMessageBox(strtemp);
		Select_hang = lvinfo.iItem;
		CPoint point;
		GetCursorPos(&point);

		CMenu menu;
		menu.LoadMenuA(IDR_MENU1);
		CMenu *popup = menu.GetSubMenu(0);
		////弹出显示
		popup->TrackPopupMenu(TPM_RIGHTALIGN | TPM_LEFTALIGN, point.x, point.y, this);
	}
	else
	{
		return;
	}
	


	
}
