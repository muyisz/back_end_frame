#pragma once
#include"../data/data.h"

muyi::error* Login(string name, string password, int type);
muyi::error* Regester(string id,string name, string password, int type);