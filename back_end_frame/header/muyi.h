#pragma once
#include<map>
#include<iostream>
#include"network.h"
#include"json.h"

namespace muyi {
	class context;

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
		error* GetResource(context* c, mstring url);
		mstring GetHTMLGlob();
		void Run();
	private:
		std::map<mstring, mstring> ContentType;
		mstring htmlGlob;
		mstring staticGlob;
		networkLink networker;
		std::map<mstring, void(*)(context*)>getFuncMap;
		std::map<mstring, void(*)(context*)>postFuncMap;
	};

	class context {
	public:
		context(std::map<mstring, mstring>* reqHeader, mstring url, mstring data, mstring version, muyiController* controller);
		~context();

		mstring GetCookie();

		void HTML(int httpState, mstring fileUrl);
		template<class TYPE>
		void JSON(int httpState, TYPE& data) {
			stateCode = httpState;

			(*resHeader)[HTTPContentType] = ContentTypeJSON;
			mstring jsonData = toJson(data);
			(*resHeader)[HTTPContentLength] = mstring::FromInt(jsonData.size());

			resData = jsonData;
		}

		mstring GetHeader(mstring name);
		void SetHeader(mstring name, mstring value);
		void SetStateCode(int code);
		void SetData(mstring data);
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