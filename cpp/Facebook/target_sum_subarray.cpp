#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Need to ask if negative numbers are allowed in the array. If not, greedy approach can solve it in O(n) time and O(1) space
// If negative numbers are allowed, need to use hash map
// http://www.geeksforgeeks.org/find-subarray-with-given-sum/
// http://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/

int target_sum_subarray_no_negative(const vector<int> &nums, int target) {
	int n = nums.size();
	int curr_sum = 0;

	for(int start=0, i=0; i<n; i++) {
		curr_sum += nums[i];

		while(curr_sum > target) {
			curr_sum -= nums[start++];
		}

		if(curr_sum == target) {
			cout << "Target sum found in subarray" << endl;
			return true;
		}
	}
	cout << "Target sum NOT found in subarray" << endl;
	return false;
}

void target_sum_subarray_has_negative(const vector<int> &nums, int target) {
	int n = nums.size();
	unordered_map<int, int> subsum;
	int curr_sum = 0;

	for(int i=0; i<nums.size(); i++) {
		curr_sum += nums[i];

		if(curr_sum == target) {
			cout << "Sum found between indexes 0 to " << i << endl;
			return;
		}

		if(subsum.find(curr_sum - target) != subsum.end()) {
			cout << "Sum found between indexes " << subsum[curr_sum - target] + 1 << " to " << i << endl;
			return;
		}

		subsum[curr_sum] = i;
	}

	cout << "No subarray with given sum exists" << endl;
}

int main() {
	vector<int> nums1 = {1, 4, 20, 3, 10, 5};
	vector<int> nums2 = {15, 2, 4, 8, 9, 5, 10, 23};

	target_sum_subarray_no_negative(nums1, 33);
	target_sum_subarray_no_negative(nums2, 23);
	target_sum_subarray_no_negative(nums2, 0);

	vector<int> nums3 = {10, 2, -2, -20, 10};

	target_sum_subarray_has_negative(nums3, -10);
	target_sum_subarray_has_negative(nums3, -20);
	target_sum_subarray_has_negative(nums3, 1);
}
