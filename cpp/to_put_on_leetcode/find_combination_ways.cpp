/** 
 * Question:
 * Given a positive int target and an int array with all positives numbers and no duplicates.
 * Find out the number of ways that can make up the target by using the elements in the array.
 * 
 * For example, target = 4, nums = [1, 2, 3]
 * Combination ways would be:
 * (1, 1, 1, 1)
 * (1, 1, 2)
 * (1, 2, 1)
 * (1, 3)
 * (2, 1, 1)
 * (2, 2)
 * (3, 1)
 *
 * So the answer is 7
 *
 * Follow up : what if negative numbers are allowed in the given array, how does it change the question
 */ 

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int findCombinationWays(vector<int> &nums, int target) {
	// key   : sum
	// value : number of ways that can make up the sum
	unordered_map<int, int> prev;
	prev[0] = 1;

	int ret = 0;
	// each layer we pick up one more element from nums[] it the sum is still less than target
	while(true) {
		unordered_map<int, int> curr;
		ret += prev[target];

		for(int i=0; i<nums.size(); i++) {
			for(auto a : prev) {
				if(nums[i] + a.first <= target)
					curr[nums[i] + a.first] += a.second;
			}
		}

		if(curr.size() > 0)
			prev = curr;
		else
			break;
	}

	return ret;
}

int main()
{
	cout << "Hello World" << endl; 
	vector<int> nums = {1, 2, 3};
	int target = 32;

	cout << findCombinationWays(nums, target) << endl;

	return 0;
}
