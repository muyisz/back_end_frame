#include"../header/util.h"
#include<iostream>

namespace muyi {
	bool DrawHTTPMessage(mstring& HTTPMessage, mstring& messageBuffer, char* recvBuffer, int recvSize) {
		HTTPMessage = "";
		if (recvSize < MaxBufferSize) {
			recvBuffer[recvSize] = StringTail;
		}
		messageBuffer = messageBuffer + recvBuffer;

		unsigned int lengthSeat = messageBuffer.find(HTTPContentLength);
		unsigned int HTTPBodySeat = messageBuffer.find(HTTPBeginBody);

		if (HTTPBodySeat != messageBuffer.maxSize()) {
			auto HTTPMessageData = messageBuffer.Cut(0, HTTPBodySeat + 5 * CharSize);
			if (HTTPMessageData.Err != nullptr) {
				//todo 打印日志
				delete HTTPMessageData.Err;
				return false;
			}
			HTTPMessage = HTTPMessage + HTTPMessageData.Data;
		}

		if (lengthSeat != messageBuffer.maxSize() && lengthSeat < HTTPBodySeat) {
			int dataLength = 0;
			lengthSeat += ContentLengthLength;

			for (int i = lengthSeat; i < messageBuffer.size(); i++) {
				
				if (messageBuffer[i] == crlf) {
					auto sizeData = messageBuffer.Cut(lengthSeat, i);
					if (sizeData.Err != nullptr) {
						//todo 打印日志
						delete sizeData.Err;
						return false;
					}

					auto toIntData = sizeData.Data.ToInt();
					if (sizeData.Err != nullptr) {
						//todo 打印日志
						delete toIntData.Err;
						return false;
					}
					dataLength = toIntData.Data;
					break;
				}
			}

			if (HTTPBodySeat + 4 * CharSize + dataLength > messageBuffer.size()) {
				return false;
			}

			char* HTTPBody = new char[dataLength + 1];
			HTTPBody[dataLength] = StringTail;
			memcpy(HTTPBody, messageBuffer.c_str() + HTTPBodySeat + 5 * CharSize, dataLength);
			HTTPMessage = HTTPMessage + HTTPBody;
			delete[]HTTPBody;
		}

		auto messageBufferData = messageBuffer.Cut(HTTPMessage.size(), messageBuffer.size());
		if (messageBufferData.Err != nullptr) {
			//todo 打印日志
			delete messageBufferData.Err;
			return false;
		}

		return true;
	}


}