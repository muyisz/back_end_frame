#include<queue>
#include<iostream>
#include<vector>
#include"../back_end_frame/header/muyi.h"
#include"../back_end_frame/header/json.h"
#include"../back_end_frame/header/mstring.h"
using namespace std;


void GetHome(muyi::context* c) {
	c->HTML(200, "home.html");
}

int main() {
	muyi::muyiController r;
	r.Init();
	r.SetHTMLGlob("example/");
	r.Static("example/");
	r.GET("/home", GetHome);
	r.GET("/", GetHome);

	r.Run();
	return 0;
}