#include"data.h"
#include"../../back_end_frame/header/mstring.h"
#include"../config/config.h"
#include"const.h"
#include<iostream>

dataBase* dataBase::instenceDataBase = nullptr;

dataBase* dataBase::instence() {
	if (!instenceDataBase) {
		instenceDataBase = new dataBase;
	}
	return instenceDataBase;
}

dataBase::dataBase() {
	DB = new MYSQL;
	if (!mysql_init(DB)) {
		//todo 打印日志
		exit(1);
	}
	if (!mysql_real_connect(DB, DBhost, DBuser, DBpassword, DBname, DBport, 0, 0)) {
		//todo 打印日志
		cout << mysql_error(DB) << "---------" << endl;
		exit(1);
	}
	mysql_query(DB, DBEncoded);
}

muyi::returnTable<user> dataBase::GetUserByIDAndType(string id, int type) {

	char* sql = new char[1000];
	sprintf(sql, GetUserByNameAndTypeFomat, id.c_str(), type);

	muyi::returnTable<user> returnData;
	auto resData = query(sql);
	if (resData.Err != nullptr) {
		//打印日志
		returnData.Err = resData.Err;
		return returnData;
	}
	MYSQL_ROW column = mysql_fetch_row(resData.Data);
	if (column == nullptr) {
		returnData.Err = muyi::error::NewError(CanNotFind);
		return returnData;
	}

	returnData.Data.id = column[0];
	returnData.Data.name = column[1];
	returnData.Data.type = muyi::mstring(column[2]).ToInt().Data;
	returnData.Data.password = column[3];
	returnData.Data.photo_url = column[4];
	return returnData;
}

muyi::error* dataBase::CreateUser(string id,string name, string password, int type) {
	char* sql = new char[1000];
	sprintf(sql, CreateUserFomat,id.c_str(), name.c_str(), type, password.c_str());

	auto err = insert(sql);
	if (err != nullptr) {
		return err;
	}
	return nullptr;
}

muyi::returnTable<MYSQL_RES*>dataBase::query(const char* fomat) {
	muyi::returnTable<MYSQL_RES*> returnData;

	MYSQL_RES* res;
	if (!mysql_query(DB, fomat)) {
		res = mysql_store_result(DB);
		if (res!=nullptr) {
			returnData.Data = res;
		}
		else {
			cout << mysql_error(DB) << endl;
			returnData.Err = muyi::error::NewError(mysql_error(DB));
		}
	}
	else {
		cout << mysql_error(DB) << endl;
		returnData.Err = muyi::error::NewError(mysql_error(DB));
	}
	return returnData;
}

muyi::error* dataBase::insert(const char* fomat) {
	if (mysql_query(DB, fomat)) {
		cout << mysql_error(DB) << endl;
		return muyi::error::NewError(mysql_error(DB));
	}
	return nullptr;
}