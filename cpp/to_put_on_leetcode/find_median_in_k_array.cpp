#include <vector>
#include <iostream>
#include <queue>
#include <climits>
#include <stdio.h>
#include <algorithm>

using namespace std;

vector<int> starts, lens;

int findMedian() {

}

int findMedian(vector<vector<int>> &arrs) {
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
/*
		while(true) {
			if(i>i_lower && arrs[lowest_med_from][i-1] == lowest_med)
				break;
			if(j<j_upper && arrs[highest_med_from][j+1] == highest_med)
				break;
			// remove elementa from both sides by shrinking the array range
			starts[lowest_med_from]++;
			lens[lowest_med_from]--;

			lens[highest_med_from]--;

			++i;
			--j;
		}
*/
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
}

double findMedianBruteForce(vector<vector<int>> &arrs) {
	vector<int> nums;
	for(auto arr : arrs) {
		for(auto n : arr)
			nums.push_back(n);
	}
	
	sort(nums.begin(), nums.end());
	
	return (nums.size() % 2) ? nums[nums.size()/2] : (double(nums[nums.size()/2]) + double(nums[nums.size()/2+1]))/2;
}

int main() {
	vector<vector<int>> arrs = {
		{1, 3, 5, 6, 7, 8},
		{4, 8, 10, 15, 21},
		{1, 4, 6, 7},
		{2, 100, 1001, 1002},
		{9}
	};

	findMedian(arrs);

	cout << "find median with brute force : " << findMedianBruteForce(arrs) << endl;
}
