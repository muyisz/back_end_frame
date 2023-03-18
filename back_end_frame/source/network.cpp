#include"../header/network.h"

namespace muyi {
	networkLink::networkLink(int port) :port(port) {}

	void networkLink::Init() {
#if _WIN32
		WSADATA wsaData;
		SOCKADDR_IN local;
		int iaddrSize = sizeof(SOCKADDR_IN);
		int wsa = WSAStartup(0x0202, &wsaData);
		listenSOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(listenSOCKET, (struct sockaddr*)&local, sizeof(SOCKADDR_IN));
#endif // _WIN32

	}

	void networkLink::Listen() {

	}

}