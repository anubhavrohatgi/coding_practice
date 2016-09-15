#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool canFindMonster2(int numOfCaves, const vector<int> &strategy) {
	vector<bool> remaining(numOfCaves, true);

	for(int pos : strategy) {
		remaining[pos] = false;

		vector<bool> next(numOfCaves, false);
		for(int i=0; i<numOfCaves; i++) {
			bool b = false;
			if(i>0)
				b |= remaining[i-1];
			if(i<numOfCaves-1)
				b |= remaining[i+1];

			next[i] = b;
		}
		remaining = next;
	}
	
	for(bool b : remaining) {
		if(b == true)
			return false;
	}
	return true;
}

bool canFindMonster(int numOfCaves, const vector<int> &strategy) {
	queue<int> q;
	for(int i=0; i<numOfCaves; i++) {
		q.push(i);
	}

	int days = 0;
	while(!q.empty() && days < strategy.size()) {
		bool added[numOfCaves];
		memset(added, false, numOfCaves);

		int qSize = q.size();
		for(int i=0; i<qSize; i++) {
			int curr = q.front();
			q.pop();
			// the monster intelligently not to step on the strategy position
			if(curr == strategy[days])
				continue;
			// monster tries to move left
			if(curr-1 >= 0 && added[curr-1] == false) {
				added[curr-1] = true;
				q.push(curr-1);
			}
			// monster tries to move right
			if(curr+1 < numOfCaves && added[curr+1] == false) {
				added[curr+1] = true;
				q.push(curr+1);
			}
		}

		++days;
	}
	
	return q.empty();
}

int main() {
	vector<int> strategy = {1, 2, 3, 1, 2, 3};
	cout << canFindMonster(5, strategy) << endl;
	cout << canFindMonster2(5, strategy) << endl;
}
