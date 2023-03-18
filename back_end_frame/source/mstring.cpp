#include"../header/mstring.h"
#include"../header/const.h"

namespace muyi {
	mstring::mstring() {}

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

	void mstring::operator+(mstring& other) {
		sourceString += other.sourceString;
	}
}