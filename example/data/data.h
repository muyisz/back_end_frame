#pragma once
#include<mysql.h>
#include"model.h"
#include"../../back_end_frame/header/error.h"

class dataBase {
public:
	static dataBase* instence();
	muyi::returnTable<user> GetUserByIDAndType(string id, int type);
	muyi::error* CreateUser(string id,string name, string password, int type);

	muyi::returnTable<MYSQL_RES*>query(const char* fomat);

	muyi::error* insert(const char* fomat);

private:
	dataBase();
	static dataBase* instenceDataBase;
	MYSQL* DB;
};