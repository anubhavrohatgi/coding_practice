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

// This will handles rList with no duplicated element
list<int> popAndReconstructWithDup(RandomPopList &rList) {
	list<int> small, large, dup;

	int prev = INT_MAX;
	while(!rList.empty()) {
		int curr = rList.pop();

		if(prev == INT_MAX) {
			prev = curr;
			continue;
		}

		if(curr > prev) {
			if(dup.empty())
				small.push_back(prev);
			else {
				dup.push_back(prev);
				small.insert(small.end(), dup.begin(), dup.end());
				dup.clear();
			}
		}
		else if(curr < prev) {
			if(dup.empty())
				large.push_front(prev);
			else {
				dup.push_back(prev);
				large.insert(large.begin(), dup.begin(), dup.end());
				dup.clear();
			}
		}
		else {	// curr == prev
			dup.push_back(prev);
		}

		prev = curr;
	}

	if(!dup.empty()) {
		small.insert(small.end(), dup.begin(), dup.end());
	}
	small.push_back(prev);

	small.insert(small.end(), large.begin(), large.end());
	return small;
}

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

	// ---------

	list<int> lst2 = {1, 2, 3, 4, 6, 6, 6, 6, 6, 6, 8, 9, 9, 9, 9, 14, 16, 20};
	RandomPopList rList2(lst2);

	cout << "Original list : " << endl;
	print_list(lst2);

	list<int> new_lst2 = popAndReconstructWithDup(rList2);
	cout << "popAndReconstructWithDup()" << endl;
	print_list(new_lst2);
}
