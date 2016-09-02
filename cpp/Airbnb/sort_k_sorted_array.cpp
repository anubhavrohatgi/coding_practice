// http://www.geeksforgeeks.org/nearly-sorted-algorithm/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void sortK(vector<int> &nums, int k) {
	int n = nums.size();
	priority_queue<int, vector<int>, greater<int>> pq;

	for(int i=0; i<k && i<n; i++) {
		pq.push(nums[i]);
	}

	int idx = 0;
	int next_idx = min(k, n);
	while(!pq.empty()) {
		nums[idx++] = pq.top();
		pq.pop();

		if(next_idx < n) {
			pq.push(nums[next_idx++]);
		}
	}
}

int main() {
	vector<int> nums = {2, 6, 3, 12, 56, 8};
	sortK(nums, 3);

	for(int i=0; i<nums.size(); i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
}
