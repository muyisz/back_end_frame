#pragma once
#include<queue>
#include<mutex>
#include"thread_pool.h"

#ifdef _WIN32

#include<Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#endif


namespace  muyi {
	class muyiController;

	class networkLink {
	public:
		networkLink(int port, muyiController* controller);
		void Init();
		void Listen();
	private:
		int port;
		SOCKET listenSOCKET;
		muyiController* controller;
	};

	void conversation(SOCKET* conversionSock, muyiController* controller);
	void getHTTPMessage(SOCKET* conversionSOCK, mutexQueue<mstring>* messageQueue, HANDLE* disconnectHANDLE, HANDLE* noticeMessage);
}