#pragma once
#include<queue>
#include<mutex>
#include"mstring.h"

#ifdef _WIN32

#include<Winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#endif


namespace  muyi {

	class networkLink {
	public:
		networkLink(int port);
		void Init();
		void Listen();
	private:
		int port;
		SOCKET listenSOCKET;
	};

	void conversation(SOCKET* conversionSock);
}