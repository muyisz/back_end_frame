#include"router.h"
#include"../handler/handler.h"

void InitRouter(muyi::muyiController& r) {
	r.Static("example/view/");
	r.SetHTMLGlob("example/view/pages/");
	r.GET("/", GetLogin);
	r.GET("/regester", GetRegester);
	r.GET("/subject/list_pages",GetSubjestListPages);
	r.GET("/subject/detail_pages",GetSubjestDetailPages);
	r.GET("/subject/create_pages",CreateSubjestPages);
	r.GET("/test_paper/choose_example", GetChooseExample);
	r.GET("/test_paper/list_pages",GetTestPaperListPages);
	r.GET("/test_paper/detail_pages", GetTestPaperDetailPages);
	r.GET("/test_paper/create_pages",CreateTestPaperPages);
	r.GET("/test_paper/test_pages", GetTestPaperTestPages);
	/////////////////////////////////////////////////////////////////////////////////////////
	r.GET("/subject/list", GetSubjectList);
	r.GET("/subject/detail", GetSubjectDetail);
	r.GET("/test_paper/detail", GetTestPaperDetail);
	r.GET("/test_peper/list", GetTestPaperList);
	/////////////////////////////////////////////////////////////////////////////////////////
	r.POST("/login", PostLogin);
	r.POST("/regester", PostRegester);
	r.POST("/subject/create", PostAddSubject);
	r.POST("/test_paper/create", PostCreateTestPaper);
	r.POST("/test_paper/submit", SubmitTestPaper);
}