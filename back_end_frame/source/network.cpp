#include"../header/network.h"
#include"../header/const.h"
#include"../header/http.h"
#include"../header/muyi.h"
#include"../header/thread_pool.h"


namespace muyi {
	threadPool threadpool;

	networkLink::networkLink(int port, muyiController* controller) :port(port), controller(controller) {}

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
		SOCKADDR_IN client;
		int iaddrSize = sizeof(SOCKADDR_IN);
		listen(listenSOCKET, 1);
		while (true) {
			SOCKET* acceptSOCKET = new SOCKET(accept(listenSOCKET, (struct sockaddr*)&client, &iaddrSize));
			threadpool.Commit(conversation, acceptSOCKET, controller);
		}
	}

	void conversation(SOCKET* conversionSock, muyiController* controller) {
		if (conversionSock == nullptr) {
			//todo 打印日志
			return;
		}
		HANDLE disconnectHANDLE = CreateEvent(NULL, TRUE, FALSE, TEXT("disconnectHANDLE"));
		HANDLE noticeMessage = CreateEvent(NULL, TRUE, FALSE, TEXT("noticeMessage"));
		mutexQueue<mstring> messageQueue;
		threadpool.Commit(getHTTPMessage, conversionSock, &messageQueue, &disconnectHANDLE, &noticeMessage);
		int sendSize;
		int tryNumber;
		while (true) {
			mstring message;
			error* err = messageQueue.GetFront(message);
			if (err != nullptr) {
				delete err;
				WaitForSingleObject(noticeMessage, INFINITE);
				continue;
			}

			returnTable<mstring> resData = HandleHTTP(message, controller);
			if (resData.Err != nullptr) {
				//todo 打印日志
				continue;
				delete resData.Err;
			}

			//Multiple attempts
			for (sendSize = 0, tryNumber = 0; tryNumber < 3 && (sendSize == 0 || sendSize == -1); tryNumber++) {
				//todo 打印日志
				sendSize = send(*conversionSock, resData.Data.c_str(), resData.Data.size(), 0);
			}

			if (disconnectHANDLE) {
				//todo 打印日志
				break;
			}
		}

		delete conversionSock;
	}

	void getHTTPMessage(SOCKET* conversionSOCK, mutexQueue<mstring>* messageQueue, HANDLE* disconnectHANDLE, HANDLE* noticeMessage) {
		char* recvBuffer = new char[MaxBufferSize];
		int gotMessageSize = 0;
		mstring HTTPMessage = "";
		mstring messageBuffer = "";

		while (true) {
			gotMessageSize = recv(*conversionSOCK, recvBuffer, MaxBufferSize, 0);
			if (gotMessageSize == 0 || gotMessageSize == -1) {
				//todo 打印日志
				SetEvent(*disconnectHANDLE);
				break;
			}
			
			if (DrawHTTPMessage(HTTPMessage, messageBuffer, recvBuffer,gotMessageSize)) {
				messageQueue->Push(HTTPMessage);
				PulseEvent(*noticeMessage);
			}
		}

		delete[]recvBuffer;
	}
}