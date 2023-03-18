#pragma once
#include<string>

namespace muyi {
	class error {
	public:
		error(std::string msg);
		error(char msg[]);
		template<class TYPE>
		static error* NewError(TYPE message) {
			return new error(message);
		}
		std::string GetMsg();
	private:
		std::string message;
	};
}