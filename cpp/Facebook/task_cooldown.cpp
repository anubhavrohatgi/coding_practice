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

		if(m.find(num) != m.end() && m[num] > time) {
			ret.append(m[num] - time, '_');
			time = m[num];
		}
		
		ret += to_string(num);
		m[num] = time + cooldown + 1;
		time++;
	}
	return ret;
}

int main() {
	vector<int> nums1 = {1, 1, 2, 1};
	int cooldown1 = 2;

	cout << print_with_cooldown(nums1, cooldown1) << endl;

	vector<int> nums2 = {1, 2, 3, 1, 2, 3};
	int cooldown2 = 3;

	cout << print_with_cooldown(nums2, cooldown2) << endl;


	vector<int> nums3 = {1, 2, 3 ,4, 5, 6, 2, 4, 6, 1, 2, 4};
	int cooldown3 = 6;

	cout << print_with_cooldown(nums3, cooldown3) << endl;
}
