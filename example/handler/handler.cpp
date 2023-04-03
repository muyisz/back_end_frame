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
	LoginRegesterRes res;
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
	LoginRegesterRes res;
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