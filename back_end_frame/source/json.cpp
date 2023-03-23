#include"../header/json.h"


dataTypeInfo::dataTypeInfo() {
	typeName = {
	{"class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >",1 },
	{"int",1},
	{"bool",1},
	{"class muyi::mstring",1},
	};
}

dataTypeInfo* dataTypeInfo::dataTypeInfoInstance = nullptr;

int dataTypeInfo::GetDataType(muyi::mstring typeIDName) {
	return typeName[typeIDName];
}

dataTypeInfo* dataTypeInfo::Instence() {
	if (dataTypeInfoInstance == nullptr) {
		dataTypeInfoInstance = new dataTypeInfo;
	}
	return dataTypeInfoInstance;
}

void toStruct(int& data, muyi::mstring json) {
	data = atoi(json.c_str());
}

void toStruct(std::string& data, muyi::mstring json) {
	muyi::mstring sourceData= "\"";
	sourceData = sourceData + json + "\"";
	data = sourceData.GetSourceString();
}

void toStruct(bool& data, muyi::mstring json) {
	if (json == "true")
		data = true;
	else {
		data = false;
	}
}

void toStruct(muyi::mstring& data, muyi::mstring json) {
	data = "\"";
	data = data + json + "\"";
}

muyi::mstring toJson(int data) {
	return muyi::mstring::FromInt(data);
}

muyi::mstring toJson(muyi::mstring data) {
	muyi::mstring returnDada = "\"";
	return returnDada + data + "\"";
}

muyi::mstring toJson(bool data) {
	return muyi::mstring::FromBool(data);
}

muyi::mstring toJson(std::string data) {
	return "\"" + data + "\"";
}

bool isVector(muyi::mstring typeName) {
	if (typeName.find(muyi::VectorTypePrefix) != muyi::mstring::maxSize()) {
		return true;
	}
	return false;
}

bool isStruct(muyi::mstring typeName) {
	if (typeName.find(muyi::StructTypePrefix) != muyi::mstring::maxSize()) {
		return true;
	}
	return false;
}

void removeLastCommon(muyi::mstring& data) {
	data.GetSourceString().pop_back();
}
