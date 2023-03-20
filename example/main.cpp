#include<queue>
#include<iostream>
#include"../back_end_frame/header/muyi.h"
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

int main() {
	muyi::muyiController a;
	a.Init();
	a.Run();
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