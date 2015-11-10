// http://www.geeksforgeeks.org/dynamic-programming-set-13-cutting-a-rod/

#include <iostream>
#include <vector>

using namespace std;

int max_profit(const vector<int> &v) {
	int n = v.size();
	vector<int> profit(n, 0);

	for(int i=1; i<n; i++) {
		for(int j=i; j<n; j++) {
			if(profit[j-i]+v[i] > profit[j])
				profit[j] = profit[j-i] + v[i];
		}
	}
	return profit[n-1];
}

int main() {
	vector<int> price = {0, 3, 5, 8, 9, 10, 17, 17, 20};

	cout << "max profit = " << max_profit(price) << endl;
}
