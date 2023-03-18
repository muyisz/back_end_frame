#include"../header/error.h"

namespace muyi {
	error::error(std::string msg) {
		message = msg;
	}
	error::error(char msg[]) {
		message = std::string(msg);
	}

	std::string error::GetMsg() {
		return message;
	}
}