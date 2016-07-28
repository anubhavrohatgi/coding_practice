#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class FixedSizeQueue {
private:
	int m_size;
	int n_element;
	vector<int> q;
	int push_ptr, pop_ptr;
public:
	FixedSizeQueue(int size) : m_size(size), n_element(0), q(vector<int>(m_size, INT_MAX)), push_ptr(0), pop_ptr(0) {}

	void push(int value) {
		if(n_element == m_size) {
			cout << "Invalid Opeartion : Queue is full" << endl;
			return;
		}

		++n_element;
		q[push_ptr] = value;
		push_ptr = (push_ptr+1) % m_size;
		return;
	}

	void pop() {
		if(n_element == 0) {
			cout << "Invalid Opeartion : Queue is empty" << endl;
			return;
		}
		
		--n_element;
		pop_ptr = (pop_ptr+1) % m_size;
	}

	int front() {
		if(n_element == 0) {
			cout << "Invalid Opeartion : Queue is empty" << endl;
			return INT_MAX;
		}

		return q[pop_ptr];
	}
};

int main() {
	FixedSizeQueue q(3);
	q.push(1);
	q.push(2);
	q.push(3);
	cout << q.front() << endl;
	q.pop();
	q.push(4);
	cout << q.front() << endl;
	q.pop();
	cout << q.front() << endl;
	q.pop();
	cout << q.front() << endl;
	q.pop();
	
	q.push(5);
	q.push(6);
	q.push(7);
	q.push(8);
}
