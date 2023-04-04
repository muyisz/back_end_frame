#include"tool.h"
#include"../../back_end_frame/header/mstring.h"

vector<string>Spilt(string source, string interval) {
	string cell;
	vector<string>returnData;
	int firstSeat = source.find(interval);
	while (firstSeat != string::npos) {
		cell = muyi::mstring(source).Cut(0, firstSeat).Data.GetSourceString();
		source = muyi::mstring(source).Cut(firstSeat + interval.length(), source.length()).Data.GetSourceString();
		firstSeat = source.find(interval);
		returnData.push_back(cell);
	}
	return returnData;
}