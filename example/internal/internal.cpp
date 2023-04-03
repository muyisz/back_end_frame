#include"internal.h"
#include"const.h"

muyi::error* Login(string id, string password, int type) {
	auto userData = dataBase::instence()->GetUserByIDAndType(id,type);
	if (userData.Err != nullptr) {
		//todo 打印日志
		return userData.Err;
	}
	if (userData.Data.password != password) {
		return muyi::error::NewError(WrongPassword);
	}
	return nullptr;
}

muyi::error* Regester(string id,string name, string password, int type) {
	auto err = dataBase::instence()->CreateUser(id, name, password, type);
	if (err != nullptr) {
		//todo 打印日志
		return err;
	}
	return nullptr;
}

muyi::error* AddSubject(string name, string content, string answer, int knowledgePoint, int type, vector<string> test, vector<vector<string>> data) {
	auto err = dataBase::instence()->CreateSubject(name, content, answer, knowledgePoint, type);
	if (err != nullptr) {
		//todo 打印日志
		return err;
	}
	if (type == SubjectProgram) {
		auto subjectIDData = dataBase::instence()->GetSubjectIdByNameAndContent(name, content);
		if (subjectIDData.Err != nullptr) {
			return subjectIDData.Err;
		}
		auto err = dataBase::instence()->CreateProgramTest(subjectIDData.Data, test[0], test[1]);
		if (err != nullptr) {
			return err;
		}
		for (int i = 0; i < data.size(); i++) {
			auto err = dataBase::instence()->CreateProgramTest(subjectIDData.Data, data[i][0], data[i][1]);
			if (err != nullptr) {
				return err;
			}
		}
	}

	return nullptr;
}