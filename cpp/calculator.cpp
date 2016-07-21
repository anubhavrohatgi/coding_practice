#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

int priority(char op) {
	if(op == '*' || op == '/')
		return 2;
	if(op == '+' || op == '-')
		return 1;
	if(op == '(')
		return 0;
}

string getNumber(const string &s, int &idx) {
	int start = idx;
	while(idx < s.size() && isdigit(s[idx]))
		++idx;

	return s.substr(start, idx-start);
}

string infixToPostfix(const string &s) {
	int n = s.size();
	string postfix;
	stack<char> sta;

	int idx = 0;
	while(idx < n) {
		if(isdigit(s[idx])) {
			string num = getNumber(s, idx);
			postfix += num;
		}
		else if(s[idx] == '(') {
			sta.push('(');
			++idx;
		}
		else if(s[idx] == '+' || s[idx] == '-' || s[idx] == '*' || s[idx] == '/') {
			while(!sta.empty() && priority(sta.top()) >= priority(s[idx])) {
				postfix += sta.top();
				sta.pop();
			}
			sta.push(s[idx++]);
		}
		else if(s[idx] == ')') {
			while(sta.top() != '(') {
				postfix += sta.top();
				sta.pop();
			}
			// pop out '('
			sta.pop();
			idx++;
		}
	}
	while(!sta.empty()) {
		postfix += sta.top();
		sta.pop();
	}

	return postfix;
}

int calc(string postfix) {
	stack<int> s;
	for(int i=0; i<postfix.size(); i++) {
		if(isdigit(postfix[i])) { 
			s.push(postfix[i] - '0');
		}
		else {
			int n2 = s.top();
			s.pop();
			int n1 = s.top();
			s.pop();
			
			int tmp;
			if(postfix[i] == '+')
				tmp = n1 + n2;
			else if(postfix[i] == '-')
				tmp = n1 - n2;
			else if(postfix[i] == '*')
				tmp = n1 * n2;
			else if(postfix[i] == '/')
				tmp = n1 / n2;

			s.push(tmp);
		}
	}

	return s.top();
}

int main() {
	string expression = "(3-(4*5+2)*(3+1)*2)";
	string postfix = infixToPostfix(expression);
	cout << postfix << endl;
	cout << calc(postfix) << endl;
}
