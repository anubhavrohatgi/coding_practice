#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// O(n^2)
int LIS(const vector<int> &v) {
	int n = v.size();
	// len[i] = the length of LIS that ends at v[i]
	vector<int> len(n, 1);

	for(int i=1; i<n; i++) {
		for(int j=0; j<i; j++) {
			if(v[j] < v[i] && len[j]+1>len[i]) {
				len[i] = len[j]+1;
			}
		}
	}

	int ret = 0;
	for(int l : len) {
		ret = (l > ret) ? l : ret;
	}
	return ret;
}

// O(nlogN)
int LIS2(const vector<int> &in) {
	vector<int> len;
	
	for(int v : in) {
		if(len.empty() || len.back() < v) {
			len.push_back(v);
		}	
		else {
			*lower_bound(len.begin(), len.end(), v) = v;		
		}
	}

	return len.size();
}

int main() {
	int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
	vector<int> input(arr, arr+sizeof(arr)/sizeof(arr[0]));

	for(int v : input) {
		cout << v << " ";
	}
	cout << endl;
	cout << "Using O(n^2) algorithm, the length of LIS of above array is " <<  LIS(input) << endl;	
	cout << "Using O(nlogN) algorithm, the length of LIS of above array is " <<  LIS2(input) << endl;	
}
