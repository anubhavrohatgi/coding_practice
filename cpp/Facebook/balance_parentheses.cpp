#include <iostream>
#include <stack>

using namespace std;

string balance_parentheses(string &s) {
	string ret, curr;
	int counter = 0;
	for(int i=0; i<s.size(); i++) {
		if(s[i] == '(')
			counter++;
		else if(s[i] == ')') {
			if(counter > 0) {
				counter--;
				ret += "(" + curr + ")";
				curr.clear();
			}
			else {
				ret += curr;
				curr.clear();
			}
		}
		else
			curr += s[i];
	}

	if(!curr.empty())
		ret += curr;

	return ret;
}

int main() {
	string s1 = "(a)()";
	string s2 = "((bc)";
	string s3 = "))a((";
	string s4 = "(a(b)";

	cout << balance_parentheses(s1) << endl;
	cout << balance_parentheses(s2) << endl;
	cout << balance_parentheses(s3) << endl;
	cout << balance_parentheses(s4) << endl;
}
