#pragma once
#include<string>
using namespace std;

struct user {
	string id;
	string name;
	int type;
	string password;
	string photo_url;
};

struct subject {
	int id;
	string name;
	string content;
	string answer;
	int knowledgePoint;
	int type;
};

struct programTest {
	int id;
	int subjectID;
	string exampleIn;
	string exampleOut;
};

struct programData {
	int id;
	int subjectID;
	string dataIn;
	string dataOut;
};

struct testPaper {
	int id;
	string subjectList;
	string creater;
	int facilityValue;
};