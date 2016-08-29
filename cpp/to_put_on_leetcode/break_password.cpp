#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string> 

using namespace std;

// n^d * n, where n is the numbers we allowed to use, d is the length of password
bool visited[1000][10] = {false};

void dfs(int from, string &ret) {
	for(int i=0; i<10; i++) {
		if(visited[from][i] == false) {
			visited[from][i] = true;
			//      4
			// 123 --> 234
			int to = (from%100)*10 + i;
			dfs(to, ret);
			ret += to_string(i);
		}
	}
}

string ToString(int value,int digitsCount) {
	ostringstream os;
	os<<setfill('0')<<setw(digitsCount)<<value;
	return os.str();
}

int main() {
	string ret;
	dfs(0, ret);

	reverse(ret.begin(), ret.end());
	// start point
	ret = "000" + ret;

	for(int i=0; i<10000; i++) {
		string toFind = ToString(i, 4);
		if(ret.find(toFind) == string::npos)
			cout << "missing : " + toFind << endl;
	}

	cout << ret << endl;
	cout << ret.size() << endl;
}
