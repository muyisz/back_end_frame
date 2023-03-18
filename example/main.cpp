#include<queue>
#include<iostream>
#include"../back_end_frame/header/thread_pool.h"
using namespace std;

void a() {
	Sleep(200);
	cout << "1" << endl;
}

void b() {
	Sleep(1000);
	cout << "2" << endl;

}


int main() {
	muyi::threadPool tp(3);

	for (int i = 1; i <= 100; i++) {
		tp.Commit(a);
	}
	Sleep(2000);
	for (int i = 1; i <= 100; i++) {
		tp.Commit(b);
	}


	Sleep(100000000);
}

