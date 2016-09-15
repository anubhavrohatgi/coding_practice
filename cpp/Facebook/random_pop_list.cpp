#include <iostream>
#include <list>
#include <time.h>
#include <climits>

using namespace std;

class RandomPopList {
private:
	list<int> lst;
public:
	RandomPopList(list<int> l) : lst(l) {
		unsigned seed;
		seed = (unsigned)time(NULL);
		srand(seed);
	}

	int pop() {
		
		int ret;
		if(rand()%2) {
			ret = lst.back();
			lst.pop_back();
		}
		else {
			ret = lst.front();
			lst.pop_front();
		}

		return ret;
	}

	bool empty() {
		return lst.empty();
	}
};

// This only handles rList with no duplicated element
list<int> popAndReconstruct(RandomPopList &rList) {
	list<int> small, large;

	int prev = INT_MAX;
	while(!rList.empty()) {
		int curr = rList.pop();

		if(prev == INT_MAX) {
			prev = curr;
			continue;
		}

		if(curr > prev) {
			small.push_back(prev);
		}
		else {
			large.push_front(prev);
		}
		prev = curr;
	}

	// in the last, prev will be the midist element, we can either push back to small list or push front to large list
	small.push_back(prev);
	small.insert(small.end(), large.begin(), large.end());
	return small;
}

void print_list(const list<int> lst) {
	for(int num : lst) {
		cout << num << " ";	
	}
	cout << endl;
}

int main() {
	list<int> lst = {1, 2, 3, 4, 6, 8, 9, 14, 16, 20};
	RandomPopList rList(lst);

	cout << "Original list : " << endl;
	print_list(lst);
	
	list<int> new_lst = popAndReconstruct(rList);
	cout << "popAndReconstruct()" << endl;
	print_list(new_lst);
}
