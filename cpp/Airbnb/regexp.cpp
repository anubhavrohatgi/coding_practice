#include <iostream>
#include <vector>

using namespace std;

bool isMatch(string s, string p) {
	/*
	string new_p;
	for(int i=0; i<p.size(); i++) {
		if(p[i] == '+' && i>0) {
			new_p.append(1, p[i-1]);
			new_p.append(1, '*');
		}
		else
			new_p.append(1, p[i]);
	}
	p = new_p;
	cout << p << endl;
*/
	int s_len = s.size(), p_len = p.size();
	if(s_len == 0 && p_len == 0)
		return false;
	else if(p_len == 0)
		return false;

	bool **dp = new bool*[s_len+1];
	for(int i=0; i<s_len+1; i++)
		dp[i] = new bool[p_len+1];

	dp[s_len][p_len] = true;
	for(int i=s_len-1; i>=0; i--)
		dp[i][p_len] = false;
	for(int j=p_len-1; j>=0; j--) {
		if(p[j] == '*') {
			j--;
			dp[s_len][j] = dp[s_len][j+2];
		}
		else
			dp[s_len][j] = false;
	}

	for(int i=s_len-1; i>=0; i--) {
		for(int j=p_len-1; j>=0; j--) {
			if(s[i] == p[j] || p[j] == '.') {
				dp[i][j] = dp[i+1][j+1];
			}
			else if(p[j] == '*') {
				j--;
				if(s[i] == p[j] || p[j] == '.')
					dp[i][j] = dp[i][j+2] || dp[i+1][j];
				else
					dp[i][j] = dp[i][j+2];
			}
			else if(p[j] == '+') {
				j--;
				if(s[i] == p[j] || p[j] == '.')
					dp[i][j] = dp[i+1][j] || dp[i+1][j+2];
				else
					dp[i][j] = false;
			}
			else {
				dp[i][j] = false;
			}
		}
	}

	return dp[0][0];
}

int main() {
	string s = "aaaaab";
	string p = ".+ab*";

	cout << isMatch(s, p) << endl;
}
