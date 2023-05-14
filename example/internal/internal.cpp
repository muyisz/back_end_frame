#include"internal.h"
#include"const.h"
#include"../tool/tool.h"

muyi::error* Login(string id, string password, int type) {
	auto userData = dataBase::instence()->GetUserByIDAndType(id, type);
	if (userData.Err != nullptr) {
		//todo ��ӡ��־
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
		//todo ��ӡ��־
		return err;
	}
	return nullptr;
}

muyi::error* AddSubject(string name, string content, string answer, int knowledgePoint, int type, vector<string> test, vector<vector<string>> data) {
	auto err = dataBase::instence()->CreateSubject(name, content, answer, knowledgePoint, type);
	if (err != nullptr) {
		//todo ��ӡ��־
		return err;
	}
	if (type == SubjectProgram) {
		auto subjectIDData = dataBase::instence()->GetSubjectIdByNameAndContent(name, content);
		if (subjectIDData.Err != nullptr) {
			return subjectIDData.Err;
		}
		auto err = dataBase::instence()->CreateProgramData(subjectIDData.Data, test[0], test[1]);
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
			//todu ��ӡ��־
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

muyi::error* CreateTestPaper(vector<int> subjectList, string creater, int facilityValue) {
	string subjectListString = Serialize(subjectList, ",");

	auto err = dataBase::instence()->CreateTestPaper(subjectListString, creater, facilityValue);
	if (err != nullptr) {
		return err;
	}
	return nullptr;
}

muyi::returnTable<InternalTestPaperDetail> TestPaperDetail(int id) {
	muyi::returnTable<InternalTestPaperDetail> returnData;

	auto testPaperData = dataBase::instence()->GetTestPaperByID(id);
	if (testPaperData.Err != nullptr) {
		returnData.Err = testPaperData.Err;
		return returnData;
	}
	returnData.Data.id = testPaperData.Data.id;
	returnData.Data.facilityValue = testPaperData.Data.facilityValue;
	returnData.Data.creater = testPaperData.Data.creater;

	auto subjectIDList = Spilt(testPaperData.Data.subjectList, ",");
	for (int i = 0; i < subjectIDList.size(); i++) {
		InternalSubjectListCell cell;
		auto subjectData = dataBase::instence()->GetSubjectByID(muyi::mstring(subjectIDList[i]).ToInt().Data);
		if (subjectData.Err != nullptr) {
			//todo ��ӡ��־
			delete subjectData.Err;
			continue;
		}
		cell.id = subjectData.Data.id;
		cell.answer = subjectData.Data.answer;
		cell.content = subjectData.Data.content;
		cell.knowledgePoint = subjectData.Data.knowledgePoint;
		cell.name = subjectData.Data.name;
		cell.type = subjectData.Data.type;
		if (cell.type == SubjectProgram) {
			auto programTestData = dataBase::instence()->GetProgramTest(cell.id);
			if (programTestData.Err != nullptr) {
				//todo��ӡ��־
				delete[]programTestData.Err;
				continue;
			}
			cell.test.push_back(programTestData.Data.exampleIn);
			cell.test.push_back(programTestData.Data.exampleOut);
		}
		returnData.Data.subjectList.push_back(cell);
	}
	return returnData;
}

muyi::returnTable<vector<InternalTestPaper>> GetAllTestPaper() {
	muyi::returnTable<vector<InternalTestPaper>> returnData;
	auto testPaperListData = dataBase::instence()->GetAllTestPaper();
	if (testPaperListData.Err != nullptr) {
		returnData.Err = testPaperListData.Err;
		return returnData;
	}

	for (int i = 0; i < testPaperListData.Data.size(); i++) {
		InternalTestPaper cell;
		cell.id = testPaperListData.Data[i].id;
		cell.creater = testPaperListData.Data[i].creater;
		cell.facilityValue = testPaperListData.Data[i].facilityValue;
		returnData.Data.push_back(cell);
	}
	return returnData;
}

bool creatFile(muyi::mstring name, muyi::mstring content) {
	fstream outputFstream;
	outputFstream.open(name.GetSourceString(), std::ios_base::out);
	if (!outputFstream) {
		return false;
	}

	outputFstream << content.GetSourceString();
	outputFstream.close();
	return true;
}

muyi::error* compileCppFile(muyi::mstring name) {
	char* order = new char[1024];
	sprintf(order, CompileCppFileOrder, name.c_str());
	system(order);

	return nullptr;
}

muyi::error* runCode(muyi::mstring exeName, muyi::mstring inName, muyi::mstring outName) {
	char* order = new char[1024];
	sprintf(order, StartRunOrder, exeName.c_str(), inName.c_str(), outName.c_str());
	system(order);

	return nullptr;
}

muyi::returnTable<muyi::mstring>GetFileContent(muyi::mstring name) {
	muyi::returnTable<muyi::mstring> returnData;
	fstream outputFstream;
	outputFstream.open(name.GetSourceString(), std::ios::in | std::ios::binary);
	if (!outputFstream) {
		returnData.Err = muyi::error::NewError(GetFileContentFailed);
		return returnData;
	}
	string result;
	outputFstream >> result;
	returnData.Data = result;
	return returnData;
}

bool EvaluationSubjectProgram(int id, string anwser) {
	auto dataData = dataBase::instence()->GetProgramData(id);
	if (dataData.Err != nullptr) {
		delete dataData.Err;
		return false;
	}
	if (dataData.Data.empty()) {
		return true;
	}

	muyi::mstring mAnwser = muyi::mstring(anwser);
	mAnwser.replace("\\n", "\n");
	if (!creatFile(CodeFileName, mAnwser.GetSourceString())) {
		return false;
	}
	if (!creatFile(InFileName, dataData.Data[0].dataIn)) {
		return false;
	}
	if (!creatFile(OutFileName, dataData.Data[0].dataOut)) {
		return false;
	}

	auto err = compileCppFile(CodeFileName);
	if (err != nullptr) {
		delete err;
		return false;
	}
	err = runCode(RunFileName, InFileName, OutFileName);
	if (err != nullptr) {
		delete err;
		return false;
	}
	auto result = GetFileContent(OutFileName);
	if (result.Err != nullptr) {
		delete result.Err;
		return false;
	}
	return result.Data.GetSourceString() == dataData.Data[0].dataOut;
}

bool EvaluationChoiceProgram(muyi::mstring anwser, muyi::mstring rightAnwser) {
	auto spiltData = Spilt(rightAnwser.GetSourceString(), SubjectChoiceInterval);
	if (!spiltData[0].compare(anwser.GetSourceString())) {
		return true;
	}
	return false;
}

muyi::returnTable<int> EvaluationTestPaper(vector<EvaluationTestPaperCell> subjectList) {
	muyi::returnTable<int> returnData;

	int score = 0;
	for (int i = 0; i < subjectList.size(); i++) {
		auto cellData = dataBase::instence()->GetSubjectByID(subjectList[i].id);
		if (cellData.Err != nullptr) {
			//todo ��ӡ��־
			delete cellData.Err;
			continue;
		}
		switch (cellData.Data.type) {
		case SubjectProgram:
			if (EvaluationSubjectProgram(subjectList[i].id, subjectList[i].anwser)) {
				score++;
			}
			break;
		case SubjectChoice:
			if (EvaluationChoiceProgram(subjectList[i].anwser, cellData.Data.answer)) {
				score++;
			}
			break;
		default:
			if (subjectList[i].anwser == cellData.Data.answer) {
				score++;
			}
		}
	}
	returnData.Data = double(score) / double(subjectList.size()) * FullMarks;
	return returnData;
}