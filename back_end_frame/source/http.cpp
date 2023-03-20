#include"../header/http.h"
#include"../header/muyi.h"

namespace muyi {
	http HTTP;

	http::http() {
		CodeToSentence[200] = HTTPSentence2xx;
		CodeToSentence[404] = HTTPSentence4xx;
	}

	returnTable<http::headerStruct> http::getFirstHeader(mstring& HTTPMessage) {
		returnTable<http::headerStruct> returnData;
		unsigned int firstSeat = 0;
		unsigned int tailSeat = HTTPMessage.find(HeaderInterval);

		returnTable<mstring> cutData = HTTPMessage.Cut(firstSeat, tailSeat);
		if (cutData.Err != nullptr) {
			//todo 打印日志
			returnData.Err = cutData.Err;
			return returnData;
		}
		returnData.Data.name = cutData.Data;

		firstSeat = tailSeat + HeaderIntervalSize;
		tailSeat = HTTPMessage.find(crlf);

		cutData = HTTPMessage.Cut(firstSeat, tailSeat);
		if (cutData.Err != nullptr) {
			//todo 打印日志
			returnData.Err = cutData.Err;
			return returnData;
		}
		returnData.Data.value = cutData.Data;
		firstSeat = tailSeat + HTTPCrlfSize;


		HTTPMessage = HTTPMessage.Cut(firstSeat, HTTPMessage.size()).Data;

		return returnData;
	}

	returnTable<mstring> http::GetSentenceByCode(int stateCode) {
		returnTable<mstring> returnData;
		if (CodeToSentence.count(stateCode)) {
			returnData.Data = CodeToSentence[stateCode];
			return returnData;
		}
		returnData.Err = error::NewError(WrongHTTPCode);
		return returnData;
	}

	returnTable<analysisHTTPData> http::AnalysisHTTP(mstring sourceHTTP) {
		std::cout << sourceHTTP.GetSourceString() << std::endl;

		returnTable<analysisHTTPData> analysisData;
		analysisData.Data.Header = new std::map<mstring, mstring>;
		returnTable<mstring> cutData;
		std::map<mstring, mstring> header;

		unsigned int firstSeat = 0;
		unsigned int tailSeat = sourceHTTP.find(HTTPFieldInterval);
		cutData = sourceHTTP.Cut(firstSeat, tailSeat);
		if (cutData.Err != nullptr) {
			//todo 打印日志
			analysisData.Err = cutData.Err;
			return analysisData;
		}
		analysisData.Data.Method = cutData.Data;

		firstSeat = tailSeat + HTTPFieldIntervalSize;
		sourceHTTP = sourceHTTP.Cut(firstSeat, sourceHTTP.size()).Data;
		firstSeat = 0;

		tailSeat = sourceHTTP.find(HTTPFieldInterval);
		cutData = sourceHTTP.Cut(firstSeat, tailSeat);
		if (cutData.Err != nullptr) {
			//todo 打印日志
			analysisData.Err = cutData.Err;
			return analysisData;
		}
		analysisData.Data.Url = cutData.Data;

		firstSeat = tailSeat + HTTPFieldIntervalSize;
		sourceHTTP = sourceHTTP.Cut(firstSeat, sourceHTTP.size()).Data;
		firstSeat = 0;

		tailSeat = sourceHTTP.find(crlf);
		cutData = sourceHTTP.Cut(firstSeat, tailSeat);
		if (cutData.Err != nullptr) {
			//todo 打印日志
			analysisData.Err = cutData.Err;
			return analysisData;
		}
		analysisData.Data.Version = cutData.Data;

		firstSeat = tailSeat + HTTPCrlfSize;
		sourceHTTP = sourceHTTP.Cut(firstSeat, sourceHTTP.size()).Data;
		firstSeat = 0;

		while (sourceHTTP[0] != crlf) {
			returnTable<http::headerStruct> headerData = getFirstHeader(sourceHTTP);
			if (headerData.Err != nullptr) {
				//todo 打印日志
				analysisData.Err = cutData.Err;
				return analysisData;
			}
			(*analysisData.Data.Header)[headerData.Data.name] = headerData.Data.value;
		}

		firstSeat = HTTPCrlfSize;

		analysisData.Data.Data = sourceHTTP.Cut(firstSeat, sourceHTTP.size()).Data;

		return analysisData;
	}

	returnTable<mstring> http::CreateHTTP(mstring version, int stateCode, mstring sentence, std::map<mstring, mstring>* header, mstring data) {
		returnTable<mstring> HTTPdata;

		return HTTPdata;
	}

	returnTable<mstring> HandleHTTP(mstring HTTPMessage, muyiController* controller) {
		returnTable<mstring> returnData;

		returnTable<analysisHTTPData> HTTPData = HTTP.AnalysisHTTP(HTTPMessage);
		if (HTTPData.Err != nullptr) {
			//todo 打印日志
			returnData.Err = HTTPData.Err;
			return returnData;
		}
		
		context sourceContext(HTTPData.Data.Header, HTTPData.Data.Data, HTTPData.Data.Version);

		controller->DoRouter(HTTPData.Data.Method, HTTPData.Data.Url, &sourceContext);

		returnTable<mstring> sentenceData = HTTP.GetSentenceByCode(sourceContext.GetStateCode());
		if (sentenceData.Err != nullptr) {
			//todo 打印日志
			returnData.Err = sentenceData.Err;
			return returnData;
		}

		returnTable<mstring> creatHTTPData = HTTP.CreateHTTP(sourceContext.GetVsersion(), sourceContext.GetStateCode(), sentenceData.Data, sourceContext.GetResHeader(), sourceContext.GetResData());
		if (creatHTTPData.Err != nullptr) {
			//todo 打印日志
			returnData.Err = creatHTTPData.Err;
			return returnData;
		}

		returnData.Data = creatHTTPData.Data;

		delete HTTPData.Data.Header;
		return returnData;
	}

}