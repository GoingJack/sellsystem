#pragma once
#include "mysql.h"
#include "Connect2Database.h"

#include <iostream>
#include <list>
#include <string>
using namespace std;
struct msg
{
	int id;//商品的编号
	char name[255];
	double price;
	int num;//库存
	int pnum;//购买的个数
	double totalprice;//单条信息总价格

};
struct msg_order//为了写入数据库
{
	char name[255];
};
struct ordersystem//订单信息表
{
	char Username[40];//订单发起者名字;
	char Order_Id[20];
	int Cu_Id;
	char Order_Date[20];
	int Order_Status;
	double Order_Totalprice;
};
class CInfoDatabase
{
public:
	CInfoDatabase();
	~CInfoDatabase();
	void charToDouble(const char* ch, double& res);

	void ReadDocline();

	list<msg> ls;//存储商品容器
	list<ordersystem> order;//订单信息
	void ReadInfo_Order();
};

