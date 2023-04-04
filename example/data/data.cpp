#include"data.h"
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
		exit(1);
	}
	mysql_query(DB, DBEncoded);
}

muyi::returnTable<user> dataBase::GetUserByIDAndType(string id, int type) {

	char* sql = new char[1024];
	sprintf(sql, GetUserByNameAndTypeFormat, id.c_str(), type);

	muyi::returnTable<user> returnData;
	auto resData = query(sql);
	delete[]sql;
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

muyi::error* dataBase::CreateUser(string id, string name, string password, int type) {
	char* sql = new char[1024];
	sprintf(sql, CreateUserFormat, id.c_str(), name.c_str(), type, password.c_str());

	return insert(sql);
}

muyi::error* dataBase::CreateSubject(string name, string content, string answer, int knowledgePoint, int type) {
	char* sql = new char[10240];
	sprintf(sql, CreateSubjectFormat, name.c_str(), content.c_str(), answer.c_str(), knowledgePoint, type);
	return insert(sql);
}

muyi::returnTable<int> dataBase::GetSubjectIdByNameAndContent(string name, string content) {
	char* sql = new char[10240];
	sprintf(sql, GetSubjectIdByNameAndContentFormat, name.c_str(), content.c_str());

	muyi::returnTable<int> returnData;
	auto resData = query(sql);
	delete[]sql;
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
	returnData.Data = muyi::mstring(column[0]).ToInt().Data;

	return returnData;
}

muyi::error* dataBase::CreateProgramTest(int subjectID, string exampleIn, string exampleOut) {
	char* sql = new char[10240];
	sprintf(sql, CreateProgramTestFormat, subjectID, exampleIn.c_str(), exampleOut);
	return insert(sql);
}

muyi::error* dataBase::CreateProgramData(int subjectID, string dataIn, string dataOut) {
	char* sql = new char[10240];
	sprintf(sql, CreateProgramDataFormat, subjectID, dataIn.c_str(), dataOut);
	return insert(sql);
}

muyi::returnTable<vector<subject>> dataBase::GetAllSubject() {
	muyi::returnTable<vector<subject>> returnData;
	auto resData = query(GetAllSubjectFormat);
	if (resData.Err != nullptr) {
		returnData.Err = resData.Err;
		return returnData;
	}
	MYSQL_ROW column;
	while (column = mysql_fetch_row(resData.Data)) {
		subject cell;
		cell.id = muyi::mstring(column[0]).ToInt().Data;
		cell.name = column[1];
		cell.content = column[2];
		cell.answer = column[3];
		cell.knowledgePoint = muyi::mstring(column[4]).ToInt().Data;
		cell.type = muyi::mstring(column[5]).ToInt().Data;
		returnData.Data.push_back(cell);
	}
	return returnData;
}

muyi::returnTable<programTest> dataBase::GetProgramTest(int id) {
	muyi::returnTable<programTest> returnData;
	char* sql = new char[1024];
	sprintf(sql, GetProgramTestFormat, id);
	auto resData = query(sql);
	delete[]sql;

	if (resData.Err != nullptr) {
		returnData.Err = resData.Err;
		return returnData;
	}
	MYSQL_ROW column = mysql_fetch_row(resData.Data);
	if (column == nullptr) {
		returnData.Err = muyi::error::NewError(CanNotFind);
		return returnData;
	}
	returnData.Data.id = muyi::mstring(column[0]).ToInt().Data;
	returnData.Data.subjectID = id;
	returnData.Data.exampleIn = column[2];
	returnData.Data.exampleOut = column[3];

	return returnData;
}

muyi::returnTable<vector<programData>> dataBase::GetProgramData(int id) {
	muyi::returnTable<vector<programData>> returnData;
	char* sql = new char[1024];
	sprintf(sql, GetProgramDataFormat, id);
	auto resData = query(sql);
	delete[]sql;

	if (resData.Err != nullptr) {
		returnData.Err = resData.Err;
		return returnData;
	}

	MYSQL_ROW column;
	while (column = mysql_fetch_row(resData.Data)) {
		programData cell;
		cell.id = muyi::mstring(column[0]).ToInt().Data;
		cell.subjectID = id;
		cell.dataIn = column[2];
		cell.dataOut = column[3];
		returnData.Data.push_back(cell);
	}
	return returnData;
}

muyi::returnTable<subject>dataBase::GetSubjectByID(int id) {
	muyi::returnTable<subject> returnData;
	char* sql = new char[1024];
	sprintf(sql, GetSubjectByIDFormat, id);
	auto resData = query(sql);
	delete[]sql;

	if (resData.Err != nullptr) {
		returnData.Err = resData.Err;
		return returnData;
	}
	MYSQL_ROW column = mysql_fetch_row(resData.Data);
	if (column == nullptr) {
		returnData.Err = muyi::error::NewError(CanNotFind);
		return returnData;
	}

	returnData.Data.id = muyi::mstring(column[0]).ToInt().Data;
	returnData.Data.name = column[1];
	returnData.Data.content = column[2];
	returnData.Data.answer = column[3];
	returnData.Data.knowledgePoint = muyi::mstring(column[4]).ToInt().Data;
	returnData.Data.type = muyi::mstring(column[5]).ToInt().Data;
	return returnData;
}

muyi::error* dataBase::CreateTestPaper(string subjectList, string creater, int facilityValue) {
	char* sql = new char[10240];
	sprintf(sql, CreateTestPaperFormat, subjectList, creater, facilityValue);
	return insert(sql);
}

muyi::returnTable<testPaper> dataBase::GetTestPaperByID(int id) {
	muyi::returnTable<testPaper> returnData;
	char* sql = new char[1024];
	sprintf(sql, GetTestPaperByIDFormat, id);
	auto resData = query(sql);
	delete[]sql;

	if (resData.Err != nullptr) {
		returnData.Err = resData.Err;
		return returnData;
	}
	MYSQL_ROW column = mysql_fetch_row(resData.Data);
	if (column == nullptr) {
		returnData.Err = muyi::error::NewError(CanNotFind);
		return returnData;
	}

	returnData.Data.id = muyi::mstring(column[0]).ToInt().Data;
	returnData.Data.subjectList = column[1];
	returnData.Data.creater = column[2];
	returnData.Data.facilityValue = muyi::mstring(column[3]).ToInt().Data;
	return returnData;
}

muyi::returnTable<MYSQL_RES*>dataBase::query(const char* format) {
	muyi::returnTable<MYSQL_RES*> returnData;

	MYSQL_RES* res;
	if (!mysql_query(DB, format)) {
		res = mysql_store_result(DB);
		if (res != nullptr) {
			returnData.Data = res;
		}
		else {
			returnData.Err = muyi::error::NewError(mysql_error(DB));
		}
	}
	else {
		returnData.Err = muyi::error::NewError(mysql_error(DB));
	}
	return returnData;
}

muyi::error* dataBase::insert(const char* format) {
	if (mysql_query(DB, format)) {
		return muyi::error::NewError(mysql_error(DB));
	}
	return nullptr;
}
