#pragma once
#include<string>

namespace muyi {
	//http
	const int HttpStateOK = 200;

	//error
	const std::string MstringChangeFailed = "String conversion failed, original data is";

	//thread_pool
	const int TaskWaitMaxTime = 5 * 1000;
}