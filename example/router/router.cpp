#include"router.h"
#include"../handler/handler.h"

void InitRouter(muyi::muyiController& r) {
	r.GET("/", GetLogin);
	/////////////////////////////////////////////////////////////////////////////////////////
	r.POST("/login", PostLogin);
	r.POST("/regester", PostRegester);
	r.POST("/subject/add", PostAddSubject);
}