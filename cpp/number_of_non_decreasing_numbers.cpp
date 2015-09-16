#include <iostream>
#include <vector>

using namespace std;

int countNonDecreasing(int digit) {
	if(digit <= 0)
		return 0;
	
	// the array that represents how many numbers there are with the last digit equals i
	// Ex: Given digit equals 5, endsWith[3] = how may combination there are for xxxx3
	vector<int> endsWith(10, 1);

	for(int i=1; i<digit; i++) {
		for(int j=1; j<endsWith.size(); j++) {
			endsWith[j] += endsWith[j-1];
		}
	}

	int count = 0;
	for(int i=0; i<endsWith.size(); i++) {
		count += endsWith[i];
	}

	return count;
}

int main() {
	cout << countNonDecreasing(3) << endl;
}
