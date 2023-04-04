#include"internal.h"
#include"const.h"

muyi::error* Login(string id, string password, int type) {
	auto userData = dataBase::instence()->GetUserByIDAndType(id, type);
	if (userData.Err != nullptr) {
		//todo 打印日志
		return userData.Err;
	}
	if (userData.Data.password != password) {
		return muyi::error::NewError(WrongPassword);
	}
	return nullptr;
}

muyi::error* Regester(string id, string name, string password, int type) {
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

muyi::error* padProgramSubject(InternalSubjectListCell& data) {
	if (data.type != SubjectProgram)
		return nullptr;
	auto programTestData = dataBase::instence()->GetProgramTest(data.id);
	if (programTestData.Err != nullptr) {
		return programTestData.Err;
	}
	data.test.push_back(programTestData.Data.exampleIn);
	data.test.push_back(programTestData.Data.exampleOut);
	return nullptr;
}

muyi::returnTable<vector<InternalSubjectListCell>> GetAllSubject() {
	muyi::returnTable<vector<InternalSubjectListCell>> returnData;
	auto subjectData = dataBase::instence()->GetAllSubject();
	if (subjectData.Err != nullptr) {
		returnData.Err = subjectData.Err;
		return returnData;
	}

	for (int i = 0; i < subjectData.Data.size(); i++) {
		InternalSubjectListCell cell;
		cell.id = subjectData.Data[i].id;
		cell.name = subjectData.Data[i].name;
		cell.content = subjectData.Data[i].content;
		cell.answer = subjectData.Data[i].answer;
		cell.knowledgePoint = subjectData.Data[i].knowledgePoint;
		cell.type = subjectData.Data[i].type;
		auto err = padProgramSubject(cell);
		if (err != nullptr) {
			//todu 打印日志
			delete err;
			continue;
		}
		returnData.Data.push_back(cell);
	}
	return returnData;
}

muyi::returnTable<InternalSubjectDetail> GetSubjectDetailInternal(int id) {
	muyi::returnTable<InternalSubjectDetail> returnData;

	auto subjectData = dataBase::instence()->GetSubjectByID(id);
	if (subjectData.Err != nullptr) {
		returnData.Err = subjectData.Err;
		return returnData;
	}
	returnData.Data.id = subjectData.Data.id;
	returnData.Data.answer = subjectData.Data.answer;
	returnData.Data.content = subjectData.Data.content;
	returnData.Data.knowledgePoint = subjectData.Data.knowledgePoint;
	returnData.Data.name = subjectData.Data.name;
	returnData.Data.type = subjectData.Data.type;
	if (returnData.Data.type != SubjectProgram) {
		return returnData;
	}

	auto subjectTestData = dataBase::instence()->GetProgramTest(id);
	if (subjectTestData.Err != nullptr) {
		returnData.Err = subjectTestData.Err;
		return returnData;
	}
	returnData.Data.test.push_back(subjectTestData.Data.exampleIn);
	returnData.Data.test.push_back(subjectTestData.Data.exampleOut);

	auto subjectDataData = dataBase::instence()->GetProgramData(id);
	if (subjectDataData.Err != nullptr) {
		returnData.Err = subjectDataData.Err;
		return returnData;
	}
	for (int i = 0; i < subjectDataData.Data.size(); i++) {
		vector<string>cell;
		cell.push_back(subjectDataData.Data[i].dataIn);
		cell.push_back(subjectDataData.Data[i].dataOut);
		returnData.Data.data.push_back(cell);
	}
	return returnData;
}