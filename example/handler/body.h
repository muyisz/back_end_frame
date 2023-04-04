#pragma once
#include<string>
#include"../../back_end_frame/header/json.h"
using namespace std;

struct UserReq {
	string id;
	string name;
	int type;
	string password;
};
REGESTER(UserReq, id, name, type, password)

struct Res{
	int code;
	string message;
};
REGESTER(Res, code, message)

struct ProgramData {
	string in;
	string out;
};
REGESTER(ProgramData,in,out)

struct SubjectReq {
	string name;
	string content;
	string answer;
	int knowledgePoint;
	int type;
	ProgramData test;
	vector<ProgramData> data;
};
REGESTER(SubjectReq, name, content, answer, knowledgePoint, type, test, data)