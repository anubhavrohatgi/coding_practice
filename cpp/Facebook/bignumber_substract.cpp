#include <iostream>
#include <vector>

using namespace std;

string bignumber_sub(vector<int> nums1, vector<int> nums2) {
	reverse(nums1.begin(), nums1.end());
	reverse(nums2.begin(), nums2.end());

	string ret;
	int borrow = 0;
	for(int i=0; i<max(nums1.size(), nums2.size()); i++) {
		int v1 = (i >= nums1.size()) ? 0 : nums1[i];
		int v2 = (i >= nums2.size()) ? 0 : nums2[i];

		cout << "v1 = " << v1 << " v2 = " << v2 << endl; 

		int curr = v1 - v2 - borrow;
		if(curr < 0) {
			borrow = 1;
			curr += 10;
		}
		else {
			borrow = 0;
		}

		ret = to_string(curr) + ret;
	}

	if(borrow)
		ret = "-" + ret;
	return ret;
}

int main() {
	vector<int> nums2 = {4, 2, 8, 1, 3, 7};
	vector<int> nums1 = {7, 2, 1, 1, 8, 4, 8, 0};

	cout << bignumber_sub(nums1, nums2) << endl;
}
