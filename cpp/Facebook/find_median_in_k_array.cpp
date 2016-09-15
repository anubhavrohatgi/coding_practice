#include <vector>
#include <iostream>
#include <queue>
#include <climits>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <time.h> 
#include <stdlib.h>
#include <iterator>
#include <iterator>

using namespace std;

vector<int> starts, lens;

// Approach 1. Binary search
double findMedian(vector<vector<int>> &arrs) {
	int N = 0;
	for(auto arr : arrs)
		N += arr.size();

	int L = INT_MAX, U = INT_MIN;
	for(auto arr : arrs) {
		if(arr.size() > 0) {
			L = min(L, arr[0]);
			U = max(U, arr[arr.size()-1]);
		}
	}

	while(true) {
		int mid = L + (U - L)/2;
		// find lower bound and upper bound for each array
		int smaller = 0, larger = 0;

		int max_smaller = L, min_larger = U;
		for(vector<int> arr : arrs) {
			if(arr.size() == 0)
				continue;

			auto it = lower_bound(arr.begin(), arr.end(), mid);
			if(mid >= *arr.begin()) {
				smaller += distance(arr.begin(), it);
			}
			// keep track of the largest number which is a little bit smaller than mid
			if(int(distance(arr.begin(), it) - 1) >= 0)
				max_smaller = max(max_smaller, (it==arr.end()) ? arr.back() : *(it-1) );

			it = upper_bound(arr.begin(), arr.end(), mid);
			larger += (arr.size() - distance(arr.begin(), it));

			// keep track of the smallest number which is a little bit larger than mid
			if(it != arr.end())
				min_larger = min(min_larger, *it);
		}
		
		// found median and there are duplicates in the middle
		if(smaller <= N/2 && larger <= N/2) {
			if(N%2) {
				return mid; 
			}
			else {
				if(smaller + larger == N) {
					// if mid appears in the arrays, it means at least one of smaller or larger is < N/2
					// so if smaller + larger == N, it means mid is not in the arrays
					return (max_smaller + min_larger) / 2.0;
				}
				else if(smaller < N/2 && larger < N/2) {
					// mid is in the arrays, and smaller < N/2 && larger < N/2, meaning that there are all duplicates in the middle
					return mid;
				}
				else if(smaller == N/2) {
					// x, x, x, 7, 7, x
					return (max_smaller + mid) / 2.0;
				}
				else if(larger == N/2) {
					// x, 7, 7, x, x, x
					return (min_larger + mid) / 2.0;
				}
			}
		}
		else if(smaller > N/2) {
			U = mid;
		}
		else {
			L = mid;
		}
	}

	return 0.0;
}

// Approach 2. http://stackoverflow.com/questions/6182488/median-of-5-sorted-arrays
int findMedian2(vector<vector<int>> &arrs) {
	starts.clear();	
	lens.clear();	
	int n = arrs.size();
	for(auto a : arrs) {
		starts.push_back(0);
		lens.push_back(a.size());
	}

	// use to record the remaining arrays
	bool remain[n];
	memset(remain, true, sizeof(remain));

	while(n > 2) {
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> low_meds;
		priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> high_meds;

		for(int i=0; i<starts.size(); i++) {
			if(lens[i] != 0) {
				int high_med_pos = starts[i] + lens[i]/2;
				int high_med = arrs[i][high_med_pos];
				int low_med = (high_med_pos == starts[i]) ? INT_MAX : arrs[i][high_med_pos-1];


				cout << "low_med for arrs[" << i << "] = " << low_med << endl;
				cout << "high_med for arrs[" << i << "] = " << high_med << endl;

				low_meds.push({low_med, i});
				high_meds.push({high_med, i});
			}
			else {
				if(remain[i]) {
					remain[i] = false;
					--n;
				}
			}
		}

		if(n <= 2)
			break;

		int lowest_med = low_meds.top().first;
		int lowest_med_from = low_meds.top().second;
		// avoid picking up same array for lowest median and highest median
		if(high_meds.top().second == lowest_med_from) {
			high_meds.pop();
		}
		int highest_med = high_meds.top().first;
		int highest_med_from = high_meds.top().second;
		cout << "lowest  low_med  = " << low_meds.top().first << " comes from arrs[" << low_meds.top().second << "]" << endl;
		cout << "highese high_med = " << high_meds.top().first << " comes from arrs[" << high_meds.top().second << "]" << endl;
	
		int i = starts[lowest_med_from], i_lower = i;
		int j = starts[highest_med_from] + lens[highest_med_from] - 1, j_upper = j;

		// number of elements to be removed from the array which hosting the lowest median. Inclusive.
		int num_of_elements_to_remove1 = lens[lowest_med_from]/2;
		// number of elements to be removed from the array which hosting the highest median. Inclusive.
		int num_of_elements_to_remove2 = lens[highest_med_from]/2 + (lens[highest_med_from] % 2 ? 1 : 0);
		// min between these two values
		int num_to_remove = min(num_of_elements_to_remove1, num_of_elements_to_remove2);
		// remove elementa from both sides by shrinking the array range
		starts[lowest_med_from] += num_to_remove;
		lens[lowest_med_from] -= num_to_remove;

		lens[highest_med_from] -= num_to_remove;
		
		cout << "-------------" << endl;
		cout << "Now valid array : " << endl;
		for(int i=0; i<arrs.size(); i++) {
			vector<int> curr = arrs[i];
			
			cout << "{";
			for(int j=0; j<lens[i]; j++)
				cout << curr[ starts[i]+j ] << ",";
			cout << "}";
		}
		cout << endl;
		cout << "-------------" << endl;
		cout << endl;
	}
	return 0;
}

double findMedianBruteForce(vector<vector<int>> &arrs) {
	vector<int> nums;
	for(auto arr : arrs) {
		for(auto n : arr)
			nums.push_back(n);
	}
	
	sort(nums.begin(), nums.end());
		
	return (nums.size() % 2 == 0) ? nums[nums.size()/2] : (double(nums[nums.size()/2]) + double(nums[nums.size()/2+1]))/2;
}

int main() {
	vector<vector<int>> arrs = {
		{1, 3, 5, 6, 7, 8},
		{4, 8, 10, 15, 21},
		{1, 4, 6, 7},
		{2, 100, 1001, 1002},
		{7, 9}
	};

	vector<vector<int>> arrs2 = {
		{7},
//		{8},
//		{7},
//		{2},
//		{2},
//		{1}
	};

	cout << "find median with binary search : " << findMedian(arrs2) << endl;
//	cout << "find median with brute force : " << findMedianBruteForce(arrs2) << endl;

//	vector<int> nums = {1, 2, 3, 4, 4, 4, 6, 7, 8};
//	auto it = lower_bound(nums.begin(), nums.end(), 5);
//	cout << *it << endl;

//	cout << distance(nums.begin(), nums.end()) << endl;
	//cout << (nums.size() - distance(nums.begin(), upper_bound(nums.begin(), nums.end(), 4))) << endl;
}
