#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
	int start;
	int end;
	int value;

	Job(int s, int e, int v) : start(s), end(e), value(v) {}
};

bool myfunction(Job j1, Job j2) {
	return j1.end < j2.end;
}

// This search method has O(n) time complexity, making findMaxProfit() to be O(n^2)
int findLatestNonConflict(const vector<Job> &v, int i) {
	for(int j = i-1; j>=0; j--) {
		if(v[j].end <= v[i].start) {
			return j;
		}
	}
	// return -1 when Job not found
	return -1;
}

// O(n^2) algorithm
int findMaxProfit(const vector<Job> &v) {
	int n = v.size();
	if(n == 1) {
		return v[0].value;
	}

	vector<int> maxProfit(n, 0);
	maxProfit[0] = v[0].value;

	for(int i=0; i<n; i++) {
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
	Job j1(3, 10, 20);
	Job j2(1, 2 , 50);
	Job j3(6, 19, 100);
	Job j4(2, 100,200);

	v.push_back(j1);
	v.push_back(j2);
	v.push_back(j3);
	v.push_back(j4);

	sort(v.begin(), v.end(), myfunction);
	printJobs(v);

	cout << "Max profit that we can get from above jobs withiout overlapping is " << findMaxProfit(v) << endl;
}
