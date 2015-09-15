#include <iostream>
#include <vector>

using namespace std;

int count_ways(int score, const vector<int> score_type) {
	int n = score;
	vector<int> ways(n+1, 0);
	// base case for score=0
	ways[0] = 1;

	for(int i=0; i<score_type.size(); i++) {
		for(int j=score_type[i]; j<=n; j++) {
			ways[j] += ways[ j-score_type[i] ];
		}
	}

	return ways[n];
}

int main() {
	int arr[] = {3, 5, 10};
	vector<int> type(arr, arr + sizeof(arr)/sizeof(arr[0]));

	cout << count_ways(13, type) << endl;
}
