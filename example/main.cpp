#include"router/router.h"


int main() {
	muyi::muyiController r;

	InitRouter(r);

	r.Init();
	r.Run();
}