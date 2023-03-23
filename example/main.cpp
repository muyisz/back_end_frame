#include<queue>
#include<iostream>
#include<vector>
#include"../back_end_frame/header/muyi.h"
#include"../back_end_frame/header/json.h"
#include"../back_end_frame/header/mstring.h"
using namespace std;

/*
void a(SOCKET aa) {
	Sleep(200);
	cout << "1" << endl;
}

void b(int *bb) {
	Sleep(1000);
	cout << "2" << endl;

}


int main() {
	muyi::muyiController tp;
	SOCKET sb = 1;
	for (int i = 1; i <= 100; i++) {
		(&tp)->UpdateTask(a, sb);
	}

	Sleep(1000000000);
}
*/


struct yz {
	int a;
	bool zfy;
};

REGESTER(yz, a,zfy)

struct wrk {
	int a;
	std::vector<yz> xyy;
	bool c;
};

REGESTER(wrk, a, xyy, c);

int main() {
	wrk sb;
	sb.a = 1;
	sb.c = true;

	yz a1;
	a1.a = 1;
	a1.zfy = true;
	sb.xyy.push_back(a1);
	yz a2;
	a2.a = 2;
	a2.zfy = true;
	sb.xyy.push_back(a2);

	std::cout << toJson(sb).GetSourceString() << std::endl;

	wrk w;

	toStruct(w, toJson(sb));

	return 0;
}


/*
int main() {
	muyi::mstring a("123456789");
	cout << a.find("56");

	cout << endl;
	auto b = a.Cut(0, 9);
	b.Data.print();
	cout << endl;
	a.print();
}
*/