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

struct SubjectListCell {
	int id;
	string name;
	string content;
	string answer;
	int knowledgePoint;
	int type;
	ProgramData test;
};
REGESTER(SubjectListCell, id, name, content, answer, knowledgePoint, type, test);

struct GetSubjectListRes {
	int code;
	string message;
	vector<SubjectListCell> subjectList;
};
REGESTER(GetSubjectListRes, code, message, subjectList);

struct GetDetailReq {
	int id;
};
REGESTER(GetDetailReq,id)

struct SubjectDetail {
	int id;
	string name;
	string content;
	string answer;
	int knowledgePoint;
	int type;
	ProgramData test;
	vector<ProgramData>data;
};
REGESTER(SubjectDetail, id, name, content, answer, knowledgePoint, type, test, data);

struct GetSubjectDetailRes {
	int code;
	string message;
	SubjectDetail subject;
};
REGESTER(GetSubjectDetailRes,code,message,subject)