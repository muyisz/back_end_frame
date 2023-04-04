#pragma once
#include"../../back_end_frame/header/muyi.h"

void GetLogin(muyi::context* c);
void GetSubjectList(muyi::context* c);
void GetSubjectDetail(muyi::context* c);
void GetTestPaperDetail(muyi::context* c);

void PostLogin(muyi::context* c);
void PostRegester(muyi::context* c);
void PostAddSubject(muyi::context* c);
void PostCreateTestPaper(muyi::context* c);