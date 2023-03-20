#pragma once
#include<map>
#include"network.h"
#include<iostream>

namespace muyi {
	class muyiController {
	public:
		muyiController(int port);
		muyiController();
		void Init();
		void GET(mstring, void(*handlerFunc)(context*));
		void POST(mstring, void(*handlerFunc)(context*));
		error* DoRouter(mstring method, mstring url, context* data);
		void SetHTMLGlob(mstring url);
		void Static(mstring url);
		mstring GetHTMLGlob();
		void Run();
	private:
		mstring htmlGlob;
		mstring staticGlob;
		networkLink networker;
		std::map<mstring, void(*)(context*)>getFuncMap;
		std::map<mstring, void(*)(context*)>postFuncMap;
	};

	class context {
	public:
		context(std::map<mstring, mstring>* reqHeader, mstring data, mstring version, muyiController* controller);
		~context();

		mstring GetCookie();

		template<class TYPE>
		void HTML(int httpState, mstring fileUrl, TYPE data) {

		}
		template<class TYPE>
		void JSON(int httpState, TYPE data) {

		}

		mstring GetHeader(mstring name);
		void SetHeader(mstring name, mstring value);
		mstring GetVsersion();
		mstring GetResData();
		int GetStateCode();
		std::map<mstring, mstring>* GetResHeader();
		std::map<mstring, mstring>* GetReqHeader();

	private:
		std::map<mstring, mstring>* reqHeader;
		std::map<mstring, mstring>* resHeader;
		mstring version;
		mstring url;
		int stateCode;
		mstring resData;
		mstring reqData;
		muyiController* controller;
	};

}