#pragma once
#include<string>
#include<vector>
using namespace std;

struct InternalSubjectListCell {
	int id;
	string name;
	string content;
	string answer;
	int knowledgePoint;
	int type;
	vector<string> test;
};

struct InternalSubjectDetail {
	int id;
	string name;
	string content;
	string answer;
	int knowledgePoint;
	int type;
	vector<string> test;
	vector<vector<string>>data;
};

struct InternalTestPaperDetail {
	int id;
	string creater;
	int facilityValue;
	vector<InternalSubjectListCell>subjectList;
};

struct InternalTestPaper {
	int id;
	string creater;
	int facilityValue;
};