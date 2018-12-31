#pragma once
#include "mysql.h"
#include "Connect2Database.h"

#include <iostream>
#include <list>
#include <string>
using namespace std;
struct msg
{
	int id;
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
class CInfoDatabase
{
public:
	CInfoDatabase();
	~CInfoDatabase();
	void charToDouble(const char* ch, double& res);

	void ReadDocline();

	list<msg> ls;//存储商品容器
};

