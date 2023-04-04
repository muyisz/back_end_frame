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