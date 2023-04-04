#pragma once
#include<mysql.h>
#include<vector>
#include"model.h"
#include"../../back_end_frame/header/error.h"

class dataBase {
public:
	static dataBase* instence();
	muyi::returnTable<user> GetUserByIDAndType(string id, int type);
	muyi::error* CreateUser(string id,string name, string password, int type);
	muyi::error* CreateSubject(string name,string content,string answer,int knowledgePoint,int type);
	muyi::returnTable<int> GetSubjectIdByNameAndContent(string name, string content);
	muyi::error* CreateProgramTest(int subjectID, string exampleIn, string exampleOut);
	muyi::error* CreateProgramData(int subjectID, string dataIn, string dataOut);
	muyi::returnTable<vector<subject>> GetAllSubject();
	muyi::returnTable<programTest>GetProgramTest(int id);
	muyi::returnTable<vector<programData>>GetProgramData(int id);
	muyi::returnTable<subject>GetSubjectByID(int id);

	muyi::returnTable<MYSQL_RES*>query(const char* format);
	muyi::error* insert(const char* format);

private:
	dataBase();
	static dataBase* instenceDataBase;
	MYSQL* DB;
};