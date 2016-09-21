#include <iostream>
#include <vector>

using namespace std;

int decode_way(string code) {
	if(code.size() == 0 || code[0] == '0')
		return 0;

	int r1 = 1, r2 = 1;
	for(int i=1; i<code.size(); i++) {
		// 1220 , r1 = f(122), r2 = f(12)
		if(code[i] == '0')
			r1 = 0;

		if(code[i-1] == '1' || (code[i-1] == '2' && code[i] <= '6')) {
			int tmp = r1;
			r1 = r1 + r2;
			r2 = tmp;
		}
		else {
			r2 = r1;
		}
	}

	return r1;
}

bool isValid(const string &s) {
	if(s.size() == 0 || s[0] == '0')
		return false;
	int code = stoi(s);

	return code >= 1 && code <= 26;
}

void dfs(vector<string> &ret, string &tmp, const string &code, int idx) {
	if(idx == code.size()) {
		ret.push_back(tmp);
		return;
	}

	for(int len=1; len<=2 && idx+len<=code.size(); len++) {
		string curr = code.substr(idx, len);
		if(isValid(curr)) {
			tmp += 'A' + stoi(curr) - 1;
			dfs(ret, tmp, code, idx+len);
			tmp.pop_back();
		}
	}
}

int main() {
	string code = "1223";

	cout << decode_way(code) << endl;
	
	vector<string> ret;
	string tmp;
	dfs(ret, tmp, code, 0);

	for(string s : ret)
		cout << s << endl;
}
