#pragma once
#include"mstring.h"
#include"const.h"
#include<map>
#include<vector>


enum DataType {
	ObjectBase = 1,
	ObjectStruct,
	ObjectVector,
};

void removeLastCommon(muyi::mstring& data);

class dataTypeInfo {
public:
	static dataTypeInfo* Instence();
	int GetDataType(muyi::mstring typeIDName);
private:
	dataTypeInfo();
	std::map<muyi::mstring, int>typeName;
	static dataTypeInfo* dataTypeInfoInstance;
};


muyi::mstring toJson(int data);
muyi::mstring toJson(std::string data);
muyi::mstring toJson(muyi::mstring data);
muyi::mstring toJson(bool data);

template<class TYPE>
muyi::mstring toJson(std::vector<TYPE> data) {
	muyi::mstring json("[");
	for (int i = 0; i < data.size(); i++) {
		json = json + toJson(data[i]) + ",";
	}
	removeLastCommon(json);
	json = json + "]";
	return json;
}

bool isVector(muyi::mstring typeName);

#define COUNT(...)  __count__(0, ##__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define __count__(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define __func_1(func,member)     func(member);
#define __func_2(func,member,...) __func_1(func,member)  __func_1(func,__VA_ARGS__)
#define __func_3(func,member,...) __func_1(func,member)  __func_2(func,__VA_ARGS__)
#define __func_4(func,member,...) __func_1(func,member)  __func_3(func,__VA_ARGS__)
#define __func_5(func,member,...) __func_1(func,member)  __func_4(func,__VA_ARGS__)
#define __func_6(func,member,...) __func_1(func,member)  __func_5(func,__VA_ARGS__)
#define __func_7(func,member,...) __func_1(func,member)  __func_6(func,__VA_ARGS__)
#define __func_8(func,member,...) __func_1(func,member)  __func_7(func,__VA_ARGS__)
#define __func_9(func,member,...) __func_1(func,member)  __func_8(func,__VA_ARGS__)
#define __func_10(func,member,...) __func_1(func,member)  __func_9(func,__VA_ARGS__)

#define MASHAL_ELEMENT(dataName)\
	json = json + "\""+#dataName+"\":" + toJson(data.dataName) + "," \

#define MACRO_CAT(a,b) __macro_cat__(a,b)
#define __macro_cat__(a,b)  a##b

#define FOR_EACH(func,...)\
    MACRO_CAT(__func_,COUNT(__VA_ARGS__))(func,__VA_ARGS__)

#define REGESTER(type,...)\
	muyi::mstring toJson(type data) {\
		muyi::mstring json;\
		if (dataTypeInfo::Instence()->GetDataType(typeid(data).name()) != ObjectBase)\
			json = json + "{";\
		FOR_EACH(MASHAL_ELEMENT,__VA_ARGS__)\
		removeLastCommon(json);\
		if (dataTypeInfo::Instence()->GetDataType(typeid(data).name()) != ObjectBase)\
			json = json + "}";\
		return json;\
	}
