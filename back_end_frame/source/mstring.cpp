#include"../header/mstring.h"
#include"../header/const.h"

namespace muyi {
	mstring::mstring() {}

	mstring mstring::FromInt(int data) {
		return std::to_string(data);
	}
	mstring mstring::FromBool(bool data) {
		if (data) {
			return "true";
		}
		else {
			return "false";
		}
	}

	unsigned int mstring::maxSize() {
		return std::string::npos;
	}

	mstring::mstring(int data) {
		sourceString = std::to_string(data);
	}

	mstring::mstring(double data) {
		sourceString = std::to_string(data);
	}

	mstring::mstring(char data[]) {
		sourceString = data;
	}

	mstring::mstring(std::string data) {
		sourceString = data;
	}

	mstring::mstring(const char* data) {
		sourceString = data;
	}

	returnTable<int> mstring::ToInt() {
		returnTable<int> data;

		for (int i = 0; i < sourceString.size(); i++) {
			if (sourceString[i] > '9' || sourceString[i] < '0') {
				data.Err = error::NewError(MstringChangeFailed);
				return data;
			}
		}

		data.Err = nullptr;
		data.Data = atoi(sourceString.c_str());

		return data;
	}

	returnTable<double> mstring::ToDouble() {
		returnTable<double> data;
		int pointNumber = 0;
		for (int i = 0; i < sourceString.size(); i++) {
			if (sourceString[i] > '9' || sourceString[i] < '0') {
				if (sourceString[i] != '.' || pointNumber > 1) {
					data.Err = error::NewError(MstringChangeFailed + sourceString);
					return data;
				}
			}
		}

		data.Err = nullptr;
		data.Data = atof(sourceString.c_str());

		return data;
	}

	returnTable<std::string> mstring::ToStdString() {
		returnTable<std::string> data;
		data.Err = nullptr;
		data.Data = sourceString;
		return data;
	}

	mstring mstring::operator+(mstring other) {
		return mstring(sourceString + other.sourceString);
	}

	mstring mstring::operator+(char other) {
		return mstring(sourceString + other);
	}

	mstring mstring::operator+(char* other) {
		return mstring(sourceString + other);
	}

	mstring mstring::operator+(const char* other) {
		return mstring(sourceString + other);
	}

	bool mstring::operator>(const mstring& other) const {
		return sourceString > other.sourceString;
	}

	bool mstring::operator<(const mstring& other) const {
		return sourceString < other.sourceString;
	}

	bool mstring::operator>=(const mstring& other) const {
		return sourceString >= other.sourceString;
	}

	bool mstring::operator<=(const mstring& other) const {
		return sourceString <= other.sourceString;
	}

	bool mstring::operator==(const mstring& other) const {
		return sourceString == other.sourceString;
	}

	void mstring::swap(mstring& other) {
		sourceString.swap(other.sourceString);
	}

	int mstring::compare(mstring& other) {
		return sourceString.compare(other.sourceString);
	}

	int mstring::compare(std::string& other) {
		return sourceString.compare(other);
	}

	int mstring::compare(const std::string& other) {
		return sourceString.compare(other);
	}

	const char* mstring::c_str() {
		return sourceString.c_str();
	}

	int mstring::size() {
		return sourceString.size();
	}

	unsigned int mstring::find(mstring data) {
		return sourceString.find(data.sourceString);
	}

	unsigned int mstring::find(const char* data) {
		return sourceString.find(data);
	}

	unsigned int mstring::find(char data) {
		return sourceString.find(data);
	}

	unsigned int mstring::find(std::string data) {
		return sourceString.find(data);
	}

	char mstring::operator[](int seat) const {
		return sourceString[seat];
	}

	returnTable<mstring> mstring::Cut(long long left, long long right) {
		returnTable<mstring> returnData;
		returnData.Err = nullptr;

		if (left > right) {
			returnData.Err = error::NewError(LeftOverSize);
			return returnData;
		}
		if (right > sourceString.length()) {
			returnData.Err = error::NewError(CutOverSize);
			return returnData;
		}
		char* buffer = new char[right - left + 1];
		buffer[right - left] = StringTail;
		memcpy(buffer, sourceString.c_str() + left, (right - left));
		returnData.Data = buffer;
		delete[]buffer;

		return returnData;
	}

	std::string& mstring::GetSourceString() {
		return sourceString;
	}

}