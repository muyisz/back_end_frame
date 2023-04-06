#pragma once
#include<string>
#include<stack>
#include"error.h"
namespace muyi {
	class mstring {
	public:
		static mstring FromInt(int data);
		static mstring FromBool(bool data);
		static unsigned int maxSize();
		mstring();
		mstring(int data);
		mstring(double data);
		mstring(char data[]);
		mstring(const char* data);
		mstring(std::string data);
		returnTable<int> ToInt();
		returnTable<double> ToDouble();
		returnTable<std::string>ToStdString();
		mstring operator+(mstring other);
		mstring operator+(char* other);
		mstring operator+(char other);
		mstring operator+(const char* other);
		unsigned int MatchParentheses(char leftBracket, char rightBrackets, int seat);
		//The left side is a closed interval, and the right side is an open interval
		returnTable<mstring> Cut(long long left, long long right);

		bool operator<(const mstring& other) const;
		bool operator>(const mstring& other) const;
		bool operator<=(const mstring& other) const;
		bool operator>=(const mstring& other) const;
		bool operator==(const mstring& other) const;
		char operator[](int seat) const;

		int compare(mstring& other);
		int compare(std::string& other);
		int compare(const std::string& other);

		void swap(mstring& other);
		const char* c_str();
		int size();
		unsigned int findFrom(int seat, mstring data);
		unsigned int findFrom(int seat, const char* data);
		unsigned int findFrom(int seat, std::string data);
		unsigned int findFrom(int seat, char data);
		unsigned int find(mstring data);
		unsigned int find(const char* data);
		unsigned int find(std::string data);
		unsigned int find(char data);
		std::string& GetSourceString();

	private:
		std::string sourceString;
	};
}