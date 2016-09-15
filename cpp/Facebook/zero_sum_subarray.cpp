// given an integer array, find out if there is a subarray that have sum = 0
// 
// Sol1. Simple Time O(n^2) go over all subarray
// 
// Sol2. Use set to store summation, if we saw the summation before, it means we got a zero sum subarray
// E.g. nums = [4, 2, 1, -5, 1, 4], sum = 4, 6, 7, 2, 3, 7, when we see the second '7', 
// we know the subarray between 1st and 2nd 7 is a zero sum subarray

#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool zeroSumSubarray(const vector<int> &nums) {
	int n = nums.size();
	set<int> found;

	int sum = 0;
	for(int i=0; i<n; i++) {
		sum += nums[i];
		// return true if
		// 1. sum is 0
		// 2. nums[i] is 0
		// 3. sum appears in the set
		if(sum == 0 || nums[i] == 0 || found.find(sum) != found.end())
			return true;
		
		found.insert(sum);
	}
	return false;
}

int main() {
	cout << zeroSumSubarray({4, 2, -3, 1, 6}) << endl;
	cout << zeroSumSubarray({4, 2, -3, 2, 6}) << endl;
}
