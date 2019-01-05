#include "stdafx.h"
#include "Connect2Database.h"
#include "mysql.h"

Connect2Database::Connect2Database()
{
}


Connect2Database::~Connect2Database()
{
}

MYSQL Connect2Database::getconnect()
{
	const char user[] = "root";
	const char pswd[] = "1";
	const char host[] = "127.0.0.1";
	const char table[] = "sellSystem";
	unsigned int port = 3306;
	
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, host, user, pswd, table, port, NULL, 0))
	{
		AfxMessageBox(_T("∑√Œ  ˝æ›ø‚ ß∞‹!"));

	}
	return mysqlCon;
}
void Connect2Database::closeconnect(MYSQL *mysqlCon)
{
	mysql_close(mysqlCon);
}
