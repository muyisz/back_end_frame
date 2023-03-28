#pragma once
#include"mstring.h"
#include"const.h"
#include<map>
#include<vector>

#include<iostream>

enum DataType {
	ObjectBase = 1,
	ObjectStruct,
	ObjectVector,
};

void RemoveSpace(muyi::mstring& json);

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

void toStruct(std::string& data, muyi::mstring json);
void toStruct(int& data, muyi::mstring json);
void toStruct(bool& data, muyi::mstring json);
void toStruct(muyi::mstring& data, muyi::mstring json);
muyi::mstring toJson(int data);
muyi::mstring toJson(std::string data);
muyi::mstring toJson(muyi::mstring data);
muyi::mstring toJson(bool data);
bool isVector(muyi::mstring typeName);
bool isStruct(muyi::mstring typeName);

template<class TYPE>
muyi::mstring toJson(std::vector<TYPE> data) {
	muyi::mstring json("[");
	bool hasData = 0;
	for (int i = 0; i < data.size(); i++) {
		hasData = 1;
		json = json + toJson(data[i]) + ",";
	}
	if(hasData)
		removeLastCommon(json);
	json = json + "]";
	return json;
}

template<class TYPE>
void toStruct(std::vector<TYPE>& data, muyi::mstring json) {
	int lastSeat;
	muyi::mstring childJson;
	int intervalSize = 0;
	char leftBracket = ' ';
	char rightBracket;
	if (isStruct(typeid(TYPE).name())) {
		leftBracket = StructLeftBracket;
		rightBracket = StructRightBracket;
		intervalSize = 1;
	}
	else if (isVector(typeid(TYPE).name())) {
		leftBracket = VectorLeftBracket;
		rightBracket = VectorRightBracket;
		intervalSize = 1;
	}
	else {
		rightBracket = BaseRightBracket;
	}
	while (json.MatchParentheses(leftBracket,rightBracket,1) != muyi::mstring::maxSize()) {
		lastSeat = json.MatchParentheses(leftBracket, rightBracket, 1);
		lastSeat += intervalSize;
		TYPE element;
		childJson = json.Cut(1, lastSeat).Data;
		json = json.Cut(0, 1).Data + json.Cut(lastSeat + 1, json.size()).Data;
		toStruct(element, childJson);
		data.push_back(element);
	}
	if (rightBracket == ',') {
		lastSeat = json.find("]");
		TYPE element;
		childJson = json.Cut(1, lastSeat).Data;
		toStruct(element, childJson);
		data.push_back(element);
	}
}

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

#define UNMASHAL_ELEMENT(dataName)\
	firstSeat = json.find(muyi::mstring("\"") + #dataName + "\":");\
	nameLength= (muyi::mstring("\"") + #dataName + "\":").size();\
	if(dataTypeInfo::Instence()->GetDataType(typeid(object.dataName).name()) == ObjectBase){\
		lastSeat=json.find(muyi::mstring(","));\
		if(lastSeat==muyi::mstring::maxSize()){\
			lastSeat=json.find(muyi::mstring("}"));}}\
	else if(isVector(typeid(object.dataName).name())){\
		lastSeat=json.MatchParentheses('[',']',firstSeat+nameLength);lastSeat++;}\
	else if (isStruct(typeid(object.dataName).name())){\
		lastSeat=json.MatchParentheses('{','}',firstSeat+nameLength);lastSeat++;}\
	childJson = json.Cut(firstSeat+nameLength, lastSeat).Data;\
	json=json.Cut(0,firstSeat).Data+json.Cut(lastSeat+1,json.size()).Data;\
	toStruct(object.dataName, childJson);

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
	}\
	void toStruct(type& object, muyi::mstring json) {\
		int firstSeat;\
		int lastSeat;\
		int nameLength;\
		muyi::mstring childJson;\
		FOR_EACH(UNMASHAL_ELEMENT,__VA_ARGS__)\
	}
