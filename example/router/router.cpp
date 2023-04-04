#include"router.h"
#include"../handler/handler.h"

void InitRouter(muyi::muyiController& r) {
	r.GET("/", GetLogin);
	r.GET("/subject/list", GetSubjectList);
	r.GET("/subject/detail", GetSubjectDetail);
	/////////////////////////////////////////////////////////////////////////////////////////
	r.POST("/login", PostLogin);
	r.POST("/regester", PostRegester);
	r.POST("/subject/add", PostAddSubject);
}