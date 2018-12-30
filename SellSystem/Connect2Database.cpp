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
	const char pswd[] = "Gj1312159064.";
	const char host[] = "120.77.203.15";
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
