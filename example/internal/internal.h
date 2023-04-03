#pragma once
#include"../data/data.h"
#include<vector>

muyi::error* Login(string name, string password, int type);
muyi::error* Regester(string id,string name, string password, int type);
muyi::error* AddSubject(string name,string content,string answer,int knowledgePoint,int type, vector<string> test, vector<vector<string>> data);