#include<queue>
#include<iostream>
#include<vector>
#include"../back_end_frame/header/muyi.h"
#include"../back_end_frame/header/json.h"
#include"../back_end_frame/header/mstring.h"
using namespace std;

struct yz {
	int a;
	string c;
	bool b;
};
REGESTER(yz,a,c,b)

struct wrk {
	yz a1;
	std::vector<std::vector<int>> xyy;
	yz a2;
};

REGESTER(wrk, a1, xyy, a2);

int main() {
	yz  q1;
	q1.a = 1;
	q1.b = true;
	q1.c = "";

	yz  q2;
	q2.a = 2;
	q2.b = true;
	q2.c = "123123";

	wrk sb;
	vector<int> a1;
	a1.push_back(1);
	a1.push_back(2);
	a1.push_back(3);

	vector<int> a2;
	a2.push_back(4);
	a2.push_back(5);
	a2.push_back(6);

	vector<int> a3;
	a3.push_back(7);
	a3.push_back(8);
	a3.push_back(9);

	sb.xyy.push_back(a1);
	sb.xyy.push_back(a2);
	sb.xyy.push_back(a3);

	sb.a1 = q1;
	sb.a2 = q2;

	std::cout << toJson(sb).GetSourceString() << std::endl;

	wrk w;
	toStruct(w, toJson(sb));


	return 0;
}