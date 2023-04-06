#pragma once
#include"../../back_end_frame/header/muyi.h"

void GetLogin(muyi::context* c);
void GetRegester(muyi::context* c);
void GetSubjestListPages(muyi::context* c);
void GetSubjestDetailPages(muyi::context* c);
void CreateSubjestPages(muyi::context* c);
void GetTestPaperListPages(muyi::context* c);
void GetTestPaperDetailPages(muyi::context* c);
void CreateTestPaperPages(muyi::context* c);
void GetChooseExample(muyi::context* c);

void GetSubjectList(muyi::context* c);
void GetSubjectDetail(muyi::context* c);
void GetTestPaperDetail(muyi::context* c);
void GetTestPaperList(muyi::context* c);

void PostLogin(muyi::context* c);
void PostRegester(muyi::context* c);
void PostAddSubject(muyi::context* c);
void PostCreateTestPaper(muyi::context* c);