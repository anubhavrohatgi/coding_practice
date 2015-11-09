#include <iostream>
#include <vector>
#include <algorithm>
#include "job.cpp"

using namespace std;

bool myfunction(Job j1, Job j2) {
	return j1.end < j2.end;
}

// This search method has O(n) time complexity
int findLatestNonConflict(const vector<Job> &v, int i) {
	for(int j = i-1; j>=0; j--) {
		if(v[j].end <= v[i-1].start) {
			return j;
		}
	}
	// return -1 when Job not found
	return -1;
}

int findMaxProfitRecursiveUtil(const vector<Job> &v, int n) {
	if(n == 1) {
		return v[0].value;
	}

	int includeProfit = v[n-1].value;
	int i = findLatestNonConflict(v, n);
	if(i != -1) {
		includeProfit += findMaxProfitRecursiveUtil(v, i+1);
	}

	int excludeProfit = findMaxProfitRecursiveUtil(v, n-1);

	return max(excludeProfit, includeProfit);
}

// O(2^n) algorithm
int findMaxProfitRecursive(const vector<Job> &v) {
	return findMaxProfitRecursiveUtil(v, v.size());
}

// O(n^2) algorithm
int findMaxProfit(const vector<Job> &v) {
	int n = v.size();
	if(n == 1) {
		return v[0].value;
	}

	vector<int> maxProfit(n, 0);
	maxProfit[0] = v[0].value;

	for(int i=1; i<n; i++) {
		int includeProfit = v[i].value;
		int last = findLatestNonConflict(v, i);
		if(last != -1) {
			includeProfit += maxProfit[last];
		}

		maxProfit[i] = max(includeProfit, maxProfit[i-1]);
	}

	return maxProfit[n-1];
}

void printJobs(const vector<Job> &v) {
	for(Job j : v) {
		cout << "Job interval : [" << j.start << " , " << j.end << "]  \twith value " << j.value << endl;
	}
}

int main() {
	vector<Job> v;
	Job j1(2, 100,200);
	Job j2(1, 2 , 50);
	Job j3(6, 19, 100);
	Job j4(3, 10, 20);

	v.push_back(j1);
	v.push_back(j2);
	v.push_back(j3);
	v.push_back(j4);

	//sort(v.begin(), v.end(), myfunction);
	sort(v.begin(), v.end(), [](Job j1, Job j2) {
					return j1.end < j2.end;
					} );
	printJobs(v);

	cout << "Max profit that we can get from above jobs withiout overlapping is " << findMaxProfit(v) << endl;
}
