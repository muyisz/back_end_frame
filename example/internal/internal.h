#pragma once
#include"../data/data.h"
#include"body.h"
#include<vector>
#include<fstream>
#include<Windows.h>

muyi::error* Login(string name, string password, int type);
muyi::error* Regester(string id,string name, string password, int type);
muyi::error* AddSubject(string name,string content,string answer,int knowledgePoint,int type, vector<string> test, vector<vector<string>> data);
muyi::returnTable<vector<InternalSubjectListCell>> GetAllSubject();
muyi::returnTable<InternalSubjectDetail> GetSubjectDetailInternal(int id);
muyi::error* CreateTestPaper(vector<int> subjectList, string creater, int facilityValue);
muyi::returnTable<InternalTestPaperDetail> TestPaperDetail(int id);
muyi::returnTable<vector<InternalTestPaper>> GetAllTestPaper();
bool creatFile(muyi::mstring name,muyi::mstring content);
muyi::error* compileCppFile(muyi::mstring name);
muyi::error* runCode(muyi::mstring exeName,muyi::mstring inName,muyi::mstring outName);
muyi::returnTable<muyi::mstring>GetFileContent(muyi::mstring name);