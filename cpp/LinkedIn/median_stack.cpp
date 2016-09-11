// http://www.geeksforgeeks.org/design-a-stack-with-find-middle-operation/

#include <iostream>
#include <list>

using namespace std;

class myStack {
private:
	list<int> m_list;
	list<int>::iterator it;

public:
	myStack() : it(m_list.begin()) {
	
	}

	void push(int val) {
		m_list.push_back(val);

		if(m_list.size()%2)
			++it;
	}

	int pop() {
		int ret = m_list.back();
		m_list.pop_back();

		if(m_list.size() == 0)
			it = m_list.begin();
		else if(m_list.size()%2 == 0)
			--it;

		return ret;
	}

	int findMedian() {
		return *it;
	}
};


int main() {
	myStack *sta = new myStack();

	sta->push(11);
	sta->push(22);
	sta->push(33);
	sta->push(44);
	cout << sta->findMedian() << endl;

	sta->push(55);
	cout << sta->findMedian() << endl;

	sta->pop();
	cout << sta->findMedian() << endl;
	sta->pop();
	cout << sta->findMedian() << endl;;
	sta->pop();
	cout << sta->findMedian() << endl;
	sta->pop();
	cout << sta->findMedian() << endl;
	sta->pop();
	cout << sta->findMedian() << endl;
}
