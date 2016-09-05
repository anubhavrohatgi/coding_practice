#include <iostream>
#include <vector>

using namespace std;

class myIterator {
private:
	vector<vector<int>>::iterator it, end;
	int ptr, removePtr;

	const vector<vector<int>>::iterator head;
	vector<vector<int>>::iterator print;
public:
	myIterator(vector<vector<int>> &data) : it(data.begin()), end(data.end()), ptr(0), removePtr(-1), head(data.begin()) {
	}

	int next() {
		removePtr = ptr;
		return (*it)[ptr++];
	}

	bool hasNext() {
		while(it != end && ptr == (*it).size()) {
			it++;
			ptr = 0;
		}

		return it != end;
	}

	void remove() {
		// TODO if removePtr == -1, throw exception 

		// 2 cases: 	1. removePtr is pointing to the last element of current vector.
		// 		2. removePtr is pointing to the middle element of current vector.
		//
		if(removePtr == (*it).size()-1) {
			(*it).erase( (*it).begin() + removePtr );
			removePtr = -1;
		}
		else {
			(*it).erase( (*it).begin() + removePtr );
			// vector has shrinked, move the pointer backward
			ptr--;	
		}

		if((*it).size() == 0)
			ptr = 0;
	}

	void printRawData() {
		print = head;
		int p = 0;
		cout << "-----------" << endl;
		while(print != end) {
			while(p < (*print).size()) {
				cout << (*print)[p++] << " ";
			}
			cout << endl;
			print++;
			p = 0;
		}
	}
};

int main() {
	vector<vector<int>> data = {
		{1, 4, 2, 5},
		{7, 2, 4},
		{},
		{9}
	};

	myIterator it = myIterator(data);
	while(it.hasNext()) {
//		cout << it.next() << endl;
		it.next();
		it.remove();
		it.printRawData();
	}

}
