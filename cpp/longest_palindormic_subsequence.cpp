#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// X[0...n-1] be the original string, let L[0 ... n-1] be the longest palindormic subsequence of X[0 ... n-1]
// 
// L(0, 0) = 0
// L(i, i) = 1
// if(X[i] == X[j]), L(i, j) = L(i+1, j-1) + 2
// if(X[i] != X[j]), L(i, j) = max(L(i, j-1), L(i+1, j))
// L(0, 5) -> L(1, 5) & L(0, 4) -> L(2, 5) & L(1, 4) & L(1, 4) & L0, 3)

int lpsRecursiveUtil(const string &s, int i, int j) {
	if(i == j)
		return 1;
	if(s[i] == s[j] && j == i+1)
		return 2;

	if(s[i] == s[j])
		return (lpsRecursiveUtil(s, i+1, j-1)) + 2;
	else
		return max(lpsRecursiveUtil(s, i+1, j), lpsRecursiveUtil(s, i, j-1));
}

int lpsRecursive(const string &s) {
	return lpsRecursiveUtil(s, 0, s.size()-1);
}

int lpsDP(const string &s) {
	int n = s.size();
	int **dp = new int*[n];
	for(int i=0; i<n; i++) {
		dp[i] = new int[n];
	}

	for(int i=0; i<n; i++) {
		dp[i][i] = 1;
	}

	// ex, n = 5
	for(int len=2; len<=n; len++) {
		for(int i=0; i < n - len + 1; i++) {
			int j = i + len - 1;
			/*
			if(s[i] == s[j] && len == 2)
				dp[i][j] = 2;
			else if(s[i] == s[j])
				dp[i][j] = dp[i+1][j-1]+2;
			else
				dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
				*/
			cout << "i = " << i << " , j = " << j << endl;
			if(s[i] != s[j])
				dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
			else if(s[i] == s[j] && len == 2)
				dp[i][j] = 2;
			else
				dp[i][j] = dp[i+1][j-1];
		}
	}


	return dp[0][n-1];
}

int main() {
	string seq = "GEEKSFORGEEKS";
	cout << "Input = " << seq << " , the length of the LPS is " << lpsDP(seq) << endl;
}
