#pragma once
#include<map>
#include"mstring.h"

namespace muyi {
	class context {
	public:
		context(mstring httpMessage);
		template<class TYPE>
		void HTML(int httpState, mstring fileUrl, TYPE data) {

		}
		template<class TYPE>
		void JSON(int httpState, TYPE data) {

		}
		template<class TYPE>
		mstring GetHeader(TYPE* data) {

		}
	private:
		std::map<mstring, mstring>reqHeader;
		std::map<mstring, mstring>resHeader;
		mstring resText;
		mstring reqText;
	};


	class muyiController {
	public:
		muyiController();
		mstring GetCookie();
		void GET(mstring, void(*handlerFunc)(context*));
		void POST(mstring, void(*handlerFunc)(context*));
		mstring GetHTMLGlob();
		///////////////////////////////////////////////////////////////
	private:
		mstring htmlGlob;
		std::map<mstring, void(*)(context*)>getFuncMap;
		std::map<mstring, void(*)(context*)>postFuncMap;
	};

}