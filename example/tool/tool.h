#pragma once
#include<string>
#include<vector>
using namespace std;

vector<string>Spilt(string source, string interval);

string ToString(int data);

template<class TYPE>
string Serialize(vector<TYPE> data, string interval) {
	string returnData = "";
	for (int i = 0; i < data.size(); i++) {
		returnData += ToString(data[i]);
		if (i != data.size() - 1) {
			returnData += interval;
		}
	}
	return returnData;
}