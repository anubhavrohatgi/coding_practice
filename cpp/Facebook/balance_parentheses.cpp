#include <iostream>
#include <stack>

using namespace std;

// https://instant.1point3acres.com/thread/180240
string balance_parentheses(string &s) {
	int left = 0, right = 0;
	string ret, tmp;

	for(char c : s) {
		if(c == '(') {
			left++;
			tmp.push_back('(');
		}
		else if(c == ')') {
			if(left > 0) {
				left--;
				tmp.push_back(')');
			}
		}
		else {
			tmp.push_back(c);
		}
	}

	for(int i=tmp.size()-1; i>=0; i--) {
		char c = tmp[i];
		if(c == ')') {
			right++;
			ret.push_back(')');
		}
		else if(c == '(') {
			if(right > 0) {
				right--;
				ret.push_back('(');
			}
		}
		else {
			ret.push_back(c);
		}
	}

	reverse(ret.begin(), ret.end());
	
	return ret;

}

int main() {
	string s1 = "(a)()";
	string s2 = "((bc)";
	string s3 = "))a((";
	string s4 = "(a(b)";
	string s5 = "((a))()";

	cout << balance_parentheses(s1) << endl;
	cout << balance_parentheses(s2) << endl;
	cout << balance_parentheses(s3) << endl;
	cout << balance_parentheses(s4) << endl;
	cout << balance_parentheses(s5) << endl;
}
