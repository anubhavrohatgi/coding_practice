#include <iostream>
#include <vector>

using namespace std;

// Exponential time complexity
int findMaximumExponential(int n) {
	if(n <= 6)
		return n;

	int max = 0;
	for(int i=n-3; i>=1; i--) {
		int curr = (n-i-1)*findMaximumExponential(i);
		if(curr > max)
			max = curr;
	}

	return max;
}

// O(ni^2) time and O(n) space complexity
int findMaximumDP(int n) {
	if(n <= 6)
		return n;

	vector<int> optimal(n, 0);
	for(int i=1; i<=6; i++) {
		optimal[i-1] = i;
	}

	for(int i=7; i<=n; i++) {
		optimal[i-1] = 0;

		for(int j=i-3; j>=1; j--) {
			int curr = (i-j-1)*optimal[j-1];

			if(curr > optimal[i-1])
				optimal[i-1] = curr;
		}
	}
	return optimal[n-1];
}


int main() {
	for (int N=1; N<=20; N++) {
		printf("Maximum Number of A's with %d keystrokes is %d\n", N, findMaximumDP(N));
	}
}
