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
		(*it).erase( (*it).begin() + removePtr );
		// vector has shrinked, move the pointer backward
		ptr--;	
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
		{1, 4, 2},
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
