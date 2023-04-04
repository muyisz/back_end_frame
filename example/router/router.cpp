#include"router.h"
#include"../handler/handler.h"

void InitRouter(muyi::muyiController& r) {
	r.Static("../view/");
	r.SetHTMLGlob("../view/pages/");
	r.GET("/", GetLogin);
	r.GET("/subject/list", GetSubjectList);
	r.GET("/subject/detail", GetSubjectDetail);
	r.GET("/test_paper/detail", GetTestPaperDetail);
	/////////////////////////////////////////////////////////////////////////////////////////
	r.POST("/login", PostLogin);
	r.POST("/regester", PostRegester);
	r.POST("/subject/create", PostAddSubject);
	r.POST("/test_paper/create", PostCreateTestPaper);
}