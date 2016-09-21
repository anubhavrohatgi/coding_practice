#include <iostream>
#include <vector>

using namespace std;

// https://instant.1point3acres.com/thread/185215
int strstr_permutation(const string &s, const string &p) {
	int s_len = s.size(), p_len = p.size();
	if(p_len == 0)
		return 0;
	if(s_len < p_len)
		return -1;

	int count[26] = {0};
	// how many alphabet we need to reset in the current sliding window
	int num_of_reset = 0
	for(char c : s) {
		if(count[c])
			num_of_reset += 1;
		count[c]++;
	}

	for(int i=0; i<s_len; i++) {
		int c_idx = s[i] - 'a';
		if(count[c_idx] == 0)
			num_of_reset++;
	

		if(num_of_reset == 0)
			return i - p_len + 1;
	}

	return -1;
}

int main() {

}
