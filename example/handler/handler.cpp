#include"handler.h"
#include"../internal/internal.h"
#include"const.h"
#include"body.h"
#include<iostream>

void GetLogin(muyi::context* c) {
	c->HTML(HTTPStateOK, "login.html");
}

void PostLogin(muyi::context* c) {
	UserReq userInfo;
	Res res;
	toStruct(userInfo, c->GetReqData());

	auto err = Login(userInfo.id, userInfo.password, userInfo.type);
	if (err != nullptr) {
		//todo 打印日志
		res.code = -1;
		res.message = err->GetMsg();
		delete err;
	}
	else {
		res.code = 0;
		res.message = "";
	}
	c->JSON(HTTPStateOK, res);
}

void PostRegester(muyi::context* c) {
	UserReq userInfo;
	Res res;
	toStruct(userInfo, c->GetReqData());

	auto err = Regester(userInfo.id, userInfo.name, userInfo.password, userInfo.type);
	if (err != nullptr) {
		//todo 打印日志
		res.code = -1;
		res.message = err->GetMsg();
		delete err;
	}
	else {
		res.code = 0;
		res.message = "";
	}

	c->JSON(HTTPStateOK, res);
}

void PostAddSubject(muyi::context* c) {
	SubjectReq subjectInfo;
	Res res;
	toStruct(subjectInfo, c->GetReqData());

	vector<string>test;
	test.push_back(subjectInfo.test.in);
	test.push_back(subjectInfo.test.out);

	vector<vector<string>>data;
	for (int i = 0; i < subjectInfo.data.size(); i++) {
		vector<string>cell;
		cell.push_back(subjectInfo.data[i].in);
		cell.push_back(subjectInfo.data[i].out);
		data.push_back(cell);
	}

	auto err = AddSubject(subjectInfo.name, subjectInfo.content, subjectInfo.answer, subjectInfo.knowledgePoint, subjectInfo.type, test, data);
	if (err != nullptr) {
		//todo 打印日志
		res.code = -1;
		res.message = err->GetMsg();
		delete err;
	}
	else {
		res.code = 0;
		res.message = "";
	}

	c->JSON(HTTPStateOK, res);
}

void GetSubjectList(muyi::context* c) {
	GetSubjectListRes res;

	auto subjectListData = GetAllSubject();
	if (subjectListData.Err != nullptr) {
		res.code = -1;
		res.message = subjectListData.Err->GetMsg();
		delete subjectListData.Err;
	}
	else {
		res.code = 0;
		res.message = "";
		for (int i = 0; i < subjectListData.Data.size(); i++) {
			SubjectListCell cell;
			cell.id = subjectListData.Data[i].id;
			cell.answer = subjectListData.Data[i].answer;
			cell.content = subjectListData.Data[i].content;
			cell.name = subjectListData.Data[i].name;
			cell.knowledgePoint = subjectListData.Data[i].knowledgePoint;
			cell.type = subjectListData.Data[i].type;
			if (cell.type == SubjectProgram) {
				cell.test.in = subjectListData.Data[i].test[0];
				cell.test.out = subjectListData.Data[i].test[1];
			}
			res.subjectList.push_back(cell);
		}
	}

	c->JSON(HTTPStateOK, res);
}

void GetSubjectDetail(muyi::context* c) {
	GetDetailReq req;
	GetSubjectDetailRes res;

	toStruct(req, c->GetReqData());
	auto subjectData = GetSubjectDetailInternal(req.id);
	if (subjectData.Err != nullptr) {
		res.code = -1;
		res.message = subjectData.Err->GetMsg();
	}
	else {
		res.code = 0;
		res.message = "";
		res.subject.id = subjectData.Data.id;
		res.subject.answer = subjectData.Data.answer;
		res.subject.content = subjectData.Data.content;
		res.subject.knowledgePoint = subjectData.Data.knowledgePoint;
		res.subject.name = subjectData.Data.name;
		res.subject.type = subjectData.Data.type;
		if (res.subject.type == SubjectProgram) {
			res.subject.test.in = subjectData.Data.test[0];
			res.subject.test.out = subjectData.Data.test[1];
			for (int i = 0; i < subjectData.Data.data.size(); i++) {
				ProgramData cell;
				cell.in = subjectData.Data.data[i][0];
				cell.out = subjectData.Data.data[i][1];
				res.subject.data.push_back(cell);
			}
		}
	}
	c->JSON(HTTPStateOK, res);
}