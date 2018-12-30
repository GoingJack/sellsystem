#pragma once
#include "mysql.h"
class Connect2Database
{
public:
	Connect2Database();
	~Connect2Database();
	MYSQL getconnect();
};

