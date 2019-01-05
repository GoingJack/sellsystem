#include "stdafx.h"
#include "CInfoDatabase.h"


CInfoDatabase::CInfoDatabase()
{
}


CInfoDatabase::~CInfoDatabase()
{
}
void CInfoDatabase::charToDouble(const char* ch, double& res)
{
	sscanf(ch, "%lf", &res);
}

void CInfoDatabase::ReadDocline()
{
	msg tmp;//存放商品信息结构体
	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	CString select_sql_by_product;
	select_sql_by_product.Format("SELECT C_Name,C_Price,ware_Count,commodity.C_Id,C_IPrice  from commodity,warehouse WHERE commodity.C_Id=warehouse.C_Id");
	mysql_query(&mysqlCon, "set names utf8");
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)select_sql_by_product);
	if (ress == 0)
	{
		//MessageBox("查找成功");
		res = mysql_store_result(&mysqlCon);
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			MessageBox(NULL,"提示消息","商家暂时无商品出售\n",0);
		}
		else
		{
			char szBuffer[1024];
			//CString wszString;
			while (row = mysql_fetch_row(res))
			{
				sprintf(szBuffer, "%s", row[0]);
				int wcsLen = MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), NULL, 0);
				wchar_t* wszString = new wchar_t[wcsLen + 1];
				MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), wszString, wcsLen);
				wszString[wcsLen] = '\0';
				WideCharToMultiByte(CP_ACP, 0, wszString, -1,tmp.name, sizeof(tmp.name), NULL, NULL);//将商品名字赋值给结构体
				//MessageBox(NULL, "sfs", (CString)tmp.name, 0);
				double tmp_price;
				charToDouble(row[1], tmp_price);
				tmp.price = tmp_price;//将商品的价格赋值给结构体
				//库存赋值
				char tmp_num[20];
				sprintf(tmp_num, "%s", row[2]);
				tmp.num=atoi(tmp_num);//将商品的库存赋值给结构体
				//商品id赋值
				sprintf(tmp_num, "%s", row[3]);
				tmp.id = atoi(tmp_num);//将商品的库存赋值给结构体
				sprintf(tmp_num, "%s", row[4]);
				charToDouble(row[4], tmp.IPrice);
				//添加进容器
				ls.push_back(tmp);
				//MessageBox((CString)wszString);
				delete wszString;
			}
		}
	}
	//mysql_close(&mysqlCon);
	
}
void CInfoDatabase::ReadInfo_Order()//查询订单
{
	ordersystem tmp;//存放订单信息结构体
	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	CString select_sql_by_order;
	select_sql_by_order.Format("SELECT Order_Id,Cu_Id,Order_Date,Order_Status,Order_Totalprice FROM ordersystem WHERE Order_Status=0");
	mysql_query(&mysqlCon, "set names utf8");
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)select_sql_by_order);
	if (ress == 0)
	{
		//MessageBox("查找成功");
		res = mysql_store_result(&mysqlCon);
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			MessageBox(NULL, "目前系统无未处理的订单\n", "提示消息",  0);
		}
		else
		{
			char szBuffer[1024];
			//CString wszString;
			while (row = mysql_fetch_row(res))
			{
				sprintf(szBuffer, "%s", row[0]);
				int wcsLen = MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), NULL, 0);
				wchar_t* wszString = new wchar_t[wcsLen + 1];
				MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), wszString, wcsLen);
				wszString[wcsLen] = '\0';
				WideCharToMultiByte(CP_ACP, 0, wszString, -1, tmp.Order_Id, sizeof(tmp.Order_Id), NULL, NULL);//将商品名字赋值给结构体
				
				tmp.Cu_Id = atoi(row[1]);

				sprintf(szBuffer, "%s", row[2]);
				int wcsLen1 = MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), NULL, 0);
				wchar_t* wszString1 = new wchar_t[wcsLen1 + 1];
				MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), wszString1, wcsLen1);
				wszString1[wcsLen1] = '\0';
				WideCharToMultiByte(CP_ACP, 0, wszString1, -1, tmp.Order_Date, sizeof(tmp.Order_Date), NULL, NULL);

				tmp.Order_Status = atoi(row[3]);
				
				charToDouble(row[4], tmp.Order_Totalprice);

				//添加到结构体名字
				CString sql_query_username;
				MYSQL_ROW row1;
				sql_query_username.Format("SELECT Username FROM user_info WHERE UserId=%d",atoi(row[1]));
				if (mysql_query(&mysqlCon, (char*)(LPCSTR)sql_query_username) == 0)
				{
					row1 = mysql_fetch_row(mysql_store_result(&mysqlCon));
					//MessageBox(NULL, "sfs", (CString)row1[0], 0);
					sprintf(szBuffer, "%s", row1[0]);
					int wcsLen2 = MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), NULL, 0);
					wchar_t* wszString2 = new wchar_t[wcsLen2 + 1];
					MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), wszString2, wcsLen2);
					wszString2[wcsLen2] = '\0';
					WideCharToMultiByte(CP_ACP, 0, wszString2, -1, tmp.Username, sizeof(tmp.Username), NULL, NULL);
				}
				//添加进容器
				order.push_back(tmp);
				//MessageBox((CString)wszString);
				delete wszString;
			}
		}
	}
	//mysql_close(&mysqlCon);
}
void CInfoDatabase::ReadInfo_Commodity()
{
	msg tmp;//存放订单信息结构体
	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	CString select_sql_by_view;
	select_sql_by_view.Format("SELECT * FROM commodity_show");
	mysql_query(&mysqlCon, "set names utf8");
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)select_sql_by_view);



	if (ress == 0)
	{
		//MessageBox("查找成功");
		res = mysql_store_result(&mysqlCon);
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			MessageBox(NULL, "目前无任何商品信息", "提示消息", 0);
		}
		else
		{
			char szBuffer[1024];
			//CString wszString;
			while (row = mysql_fetch_row(res))
			{
				sprintf(szBuffer, "%s", row[0]);
				int wcsLen = MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), NULL, 0);
				wchar_t* wszString = new wchar_t[wcsLen + 1];
				MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), wszString, wcsLen);
				wszString[wcsLen] = '\0';
				WideCharToMultiByte(CP_ACP, 0, wszString, -1, tmp.name, sizeof(tmp.name), NULL, NULL);//将商品名字赋值给结构体


				charToDouble(row[1], tmp.price);
				tmp.num = atoi(row[2]);
				charToDouble(row[3], tmp.IPrice);

				//添加进容器
				Info_commodity.push_back(tmp);
				//MessageBox((CString)wszString);
				delete wszString;
			}
		}
	}
	//mysql_close(&mysqlCon);

}
