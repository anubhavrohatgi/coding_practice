#include <iostream>
#include <vector>

using namespace std;

int maxSumIS(const vector<int> &v) {
	int n = v.size();
	// sum[i] = max sum ends at v[i]
	vector<int> sum(v);

	for(int i=1; i<n; i++) {
		for(int j=0; j<i; j++) {
			if(v[i] > v[j] && sum[i] < sum[j] + v[i])
				sum[i] = sum[j] + v[i];
		}
	}

	int ret = 0;
	for(int i=0; i<n; i++) {
		ret = max(ret, sum[i]);
	}

	return ret;
}

void printArray(const vector<int> &v) {
	cout << "{";
	for(int i=0; i<v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "}" << endl;
}

int main() {
	int arr[] = {10, 5, 4, 3};
	vector<int> v(arr, arr+sizeof(arr)/sizeof(arr[0]));

	cout << "Input array : ";
	printArray(v);
	cout << "maximum sum increasing subsequence = " << maxSumIS(v) << endl;
}
