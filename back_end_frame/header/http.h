#pragma once
#include<map>
#include"mstring.h"

namespace muyi {
	class muyiController;

	struct analysisHTTPData {
		std::map<mstring, mstring>* Header;
		mstring Method;
		mstring Url;
		mstring Data;
		mstring Version;
	};

	class http {
	public:
		http();
		returnTable<analysisHTTPData> AnalysisHTTP(mstring sourceHTTP);
		returnTable<mstring> GetSentenceByCode(int stateCode);
		returnTable<mstring> CreateHTTP(mstring version, int stateCode, mstring sentence, std::map<mstring, mstring>* header, mstring data);
	private:
		struct headerStruct{
			mstring name;
			mstring value;
		};

		returnTable<headerStruct> getFirstHeader(mstring& HTTPMessage);
		std::map<int, mstring>CodeToSentence;
	};

	returnTable<mstring> HandleHTTP(mstring HTTPMessage, muyiController* controller);
}