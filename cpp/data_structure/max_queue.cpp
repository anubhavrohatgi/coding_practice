// Similar to https://leetcode.com/problems/min-stack/, but to maintain a queue that support frontMax() (or pollMax())

#include <iostream>
#include <queue>
#include <deque>

using namespace std;

class MaxQueue {
private:
	queue<int> q;
	// pair<int, int> = (element, count), count is for compression
	deque< pair<int, int> > dq;
public:
	void pop() {
		q.pop();
		// pop_front() if the count is 0
		if(--dq.front().second == 0)
			dq.pop_front();
	}

	int front() {
		return q.front();
	}

	int frontMax() {
		return dq.front().first;
	}

	void push(int val) {
		q.push(val);

		int count = 1;
		// pop_back() until the tail elem is greater than current elem
		while(!dq.empty() && dq.back().first < val) {
			count += dq.back().second;
			dq.pop_back();
		}
		
		dq.push_back({val, count});
	}
};

int main() {
	MaxQueue mq;
	mq.push(1);
	mq.push(2);
	mq.push(3);
	mq.push(4);
	mq.push(5);
	mq.push(4);
	mq.push(3);
	mq.push(2);
	mq.push(1);

	cout << mq.frontMax() << endl;
	mq.pop();
	mq.pop();
	mq.pop();
	mq.pop();
	cout << mq.frontMax() << endl;
	mq.pop();
	cout << mq.frontMax() << endl;
}
