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


struct a1 {
	int a;
	string b;
};

REGESTER(a1,a,b)

struct a2 {
	std::vector<a1>a;
	a1 xyy;
};

REGESTER(a2,a,xyy)



int main() {
	a1 qq;
	qq.a = 1;
	qq.b = "123123";

	a1 ww;
	ww.a = 2;
	ww.b = "qweqwe";

	a2 sb;
	sb.a.push_back(qq);
	sb.a.push_back(ww);
	sb.xyy.a = 3;
	sb.xyy.b = "asdasd";
	
	std::cout << toJson(sb).GetSourceString() << std::endl;

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