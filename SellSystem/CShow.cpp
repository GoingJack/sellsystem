// CShow.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "CShow.h"
#include "afxdialogex.h"


// CShow 对话框

IMPLEMENT_DYNAMIC(CShow, CDialogEx)

CShow::CShow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_INFO, pParent)
{

}

CShow::~CShow()
{
}

void CShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShow, CDialogEx)
END_MESSAGE_MAP()


// CShow 消息处理程序
