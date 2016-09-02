#include <iostream>
#include <vector>

using namespace std;

int decode(string testEncStr) {
	string truth = "kljJJ324hijkS_";

	if (testEncStr == truth) {
		return 848662;
	} 
	else {
		return -1;
	}
}

void decodeFinder(int &ret, string badEncStr, int idx) {
	if(ret != -1)
		return;
	if(idx == badEncStr.size()) {
		int code = decode(badEncStr);
		if(code != -1)
			ret = code;
		return;
	}

	if(!isalpha(badEncStr[idx])) {
		decodeFinder(ret, badEncStr, idx+1);	
	}
	else {
		string tmp(badEncStr);
		// not to change current char
		decodeFinder(ret, badEncStr, idx+1);
		// change current char
		if(islower(badEncStr[idx])) {
			tmp[idx] = toupper(badEncStr[idx]);
			decodeFinder(ret, tmp, idx+1);
		}
		else {
			tmp[idx] = tolower(badEncStr[idx]);
			decodeFinder(ret, tmp, idx+1);
		}
	}
}

int main() {
	int ret = -1;
	string badEncStr = "kLjjj324hijks_";

	decodeFinder(ret, badEncStr, 0);

	cout << ret << endl;
}
