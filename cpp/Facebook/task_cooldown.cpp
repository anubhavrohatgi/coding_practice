#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// http://www.1point3acres.com/bbs/thread-188881-1-1.html
string print_with_cooldown(const vector<int> &nums, int cooldown) {
	int n = nums.size();
	string ret;
	// key : num
	// value : at which position we can print the num again
	unordered_map<int, int> m;

	int time = 0;
	for(int i=0; i<n; i++) {
		int num = nums[i];

		while(m.find(num) != m.end() && m[num] >= time) {
			ret += "_";
			time++;
		}

		ret += to_string(num);
		m[num] = time + cooldown;
		time++;
	}
	return ret;
}

int main() {
	vector<int> nums = {1, 2, 3 ,4, 5, 6, 2, 4, 6, 1, 2, 4};
	int cooldown = 6;

	cout << print_with_cooldown(nums, cooldown) << endl;
}
