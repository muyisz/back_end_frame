#pragma once
#include<string>
#include"error.h"
namespace muyi {
	template<class TYPE>
	struct returnTable {
		TYPE Data;
		muyi::error* Err;
	};

	class mstring {
	public:
		mstring();
		mstring(int data);
		mstring(double data);
		mstring(char data[]);
		mstring(const char* data);
		mstring(std::string data);
		returnTable<int> ToInt();
		returnTable<double> ToDouble();
		returnTable<std::string>ToStdString();
		void operator+(mstring& other);
	private:
		std::string sourceString;
	};
}