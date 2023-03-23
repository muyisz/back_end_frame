#pragma once
#include<string>

namespace muyi {
	//http
	const int HttpStateOK = 200;
	const int DefaultPort = 8080;
	const std::string HTTPContentLength = "Content-Length";
	const int ContentLengthLength = 16;
	const int CharSize = 1;
	const std::string HTTPMethodGet = "GET";
	const std::string HTTPMethodDelete = "DELETE";
	const std::string HTTPMethodPost = "POST";
	const std::string HTTPSentence2xx = "Success";
	const std::string HTTPSentence4xx = "Client error";
	const char HTTPFieldInterval = ' ';
	const int HTTPFieldIntervalSize = 1;
	const std::string HeaderInterval = ": ";
	const int HeaderIntervalSize = 2;

#if _WIN32
	const char crlf = '\r\n';
	const std::string HTTPBeginBody = "\r\n\r\n";
	const char StringTail = '\0';
	const int HTTPCrlfSize = 2;
#endif // _WIN32

	//network
	const int MaxBufferSize = 10240;

	//error
	const std::string MstringChangeFailed = "String conversion failed, original data is";
	const std::string GetNullQueue = "Queue is null";
	const std::string CutOverSize = "Cutting interval exceeds string size";
	const std::string LeftOverSize = "Left interval exceeds right interval";
	const std::string RouterNotFind = "No corresponding route found";
	const std::string UnsupportedMethod = "This method is not currently supported";
	const std::string WrongHTTPCode = "Invalid HTTP status code";

	//thread_pool
	const int TaskWaitMaxTime = 5 * 1000;
	const int DefaultMaxThread = 20;

	//json
	const std::string VectorTypePrefix = "class std::vector<";
	const std::string StructTypePrefix = "struct";
}