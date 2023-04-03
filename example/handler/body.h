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

struct LoginRegesterRes{
	int code;
	string message;
};
REGESTER(LoginRegesterRes, code, message)
