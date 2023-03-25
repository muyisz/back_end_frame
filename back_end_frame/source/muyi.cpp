#include"../header/muyi.h"
#include"../header/const.h"

namespace muyi {

	context::context(std::map<mstring, mstring>* reqHeader, mstring url, mstring data, mstring version, muyiController* controller) :reqHeader(reqHeader), url(url), reqData(data), version(version), controller(controller) {
		resHeader = new std::map<mstring, mstring>;
	}

	context::~context() {
		delete resHeader;
	}

	void context::HTML(int httpState, mstring fileUrl) {
		stateCode = httpState;
		(*resHeader)[HTTPContentType] = ContentTypeHTML;
		returnTable<mstring> httpFileData = GetFile(controller->GetHTMLGlob() + fileUrl);
		if (httpFileData.Err != nullptr) {
			//todo打印日志
			delete httpFileData.Err;
		}

		(*resHeader)[HTTPContentLength] = mstring::FromInt(httpFileData.Data.size());
		resData = httpFileData.Data;
	}

	mstring context::GetCookie() {
		return "";
	}

	void context::SetStateCode(int code) {
		stateCode = code;
	}

	void context::SetData(mstring data) {
		resData = data;
	}

	mstring context::GetHeader(mstring name) {
		//todo
		return (*reqHeader)[name];
	}

	void context::SetHeader(mstring name, mstring value) {
		(*resHeader)[name] = value;
	}

	mstring context::GetVsersion() {
		return version;
	}

	mstring context::GetResData() {
		return resData;
	}

	int context::GetStateCode() {
		return stateCode;
	}

	std::map<mstring, mstring>* context::GetResHeader() {
		return resHeader;
	}

	std::map<mstring, mstring>* context::GetReqHeader() {
		return reqHeader;
	}

	muyiController::muyiController(int port) : networker(port, this) {
		ContentType["js"] = ContentTypeJS;
		ContentType["html"] = ContentTypeHTML;
		ContentType["xml"] = ContentTypeXML;
		ContentType["gif"] = ContentTypeGIF;
		ContentType["jpg"] = ContentTypeJPEG;
		ContentType["png"] = ContentTypePNG;
		ContentType["jfif"] = ContentTypeJPEG;
	}

	muyiController::muyiController() : networker(DefaultPort, this) {
		ContentType["js"] = ContentTypeJS;
		ContentType["html"] = ContentTypeHTML;
		ContentType["xml"] = ContentTypeXML;
		ContentType["gif"] = ContentTypeGIF;
		ContentType["jpg"] = ContentTypeJPEG;
		ContentType["png"] = ContentTypePNG;
		ContentType["jfif"] = ContentTypeJPEG;
	}

	error* muyiController::GetResource(context* c, mstring url) {

		url = staticGlob + url;
		auto FileData = GetFile(url);
		if (FileData.Err != nullptr) {
			//todo 打印日志
			c->SetStateCode(HTTPStateNotFind);
			return FileData.Err;
		}
		c->SetData(FileData.Data);
		c->SetStateCode(HTTPStateOK);
		mstring ExtendedName = GetFileExtended(url);
		c->SetHeader(HTTPContentType, ContentType[ExtendedName]);
		c->SetHeader(HTTPContentLength, mstring::FromInt(FileData.Data.size()));
		return nullptr;
	}

	void muyiController::GET(mstring url, void(*handlerFunc)(context*)) {
		getFuncMap[url] = handlerFunc;
	}

	void muyiController::POST(mstring url, void(*handlerFunc)(context*)) {
		postFuncMap[url] = handlerFunc;
	}

	mstring muyiController::GetHTMLGlob() {
		return htmlGlob;
	}

	void muyiController::Init() {
		networker.Init();
	}

	void muyiController::SetHTMLGlob(mstring url) {
		htmlGlob = htmlGlob + url;
	}

	void muyiController::Static(mstring url) {
		staticGlob = staticGlob + url;
	}

	error* muyiController::DoRouter(mstring method, mstring url, context* data) {
		if (!method.compare(HTTPMethodGet)) {
			if (url.find(FileExtendedFix) != mstring::maxSize())
				return GetResource(data, url);

			if (getFuncMap.count(url)) {
				getFuncMap[url](data);
				return nullptr;
			}
			return error::NewError(RouterNotFind);
		}
		else if (!method.compare(HTTPMethodPost)) {
			if (postFuncMap.count(url)) {
				postFuncMap[url](data);
				return nullptr;
			}
			return error::NewError(RouterNotFind);
		}
		else {
			return error::NewError(UnsupportedMethod);
		}
	}

	void muyiController::Run() {
		networker.Listen();
	}
}