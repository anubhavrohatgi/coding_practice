#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <thread>
// #include <shared_mutex>
#include <mutex>
#include <condition_variable>

using namespace std;

// http://codereview.stackexchange.com/questions/84109/a-multi-threaded-producer-consumer-with-c11
class Buffer {
private:
	int m_size;
	queue<int> m_q;
	
	condition_variable cv;
	mutex mtx;
public:
	Buffer(int size = 3) : m_size(size), m_q(), cv(), mtx() {}

	void push(int val) {
		while(true) {
			unique_lock<mutex> lk(mtx);
			cv.wait(lk, [this]{ return m_q.size() < m_size; });

			m_q.push(val);
			
			lk.unlock();
			cv.notify_all();
			return;
		}
	}

	int pop() {
		while(true) {
			unique_lock<mutex> lk(mtx);
			cv.wait(lk, [this]{ return m_q.size() > 0; } );

			int ret = m_q.front();
			m_q.pop();

			lk.unlock();
			cv.notify_all();
			return ret;
		}
	}

};


mutex print_mtx;

class Producer {
private:
	Buffer &m_buffer;

public:
	Producer(Buffer &buffer) : m_buffer(buffer) {}

	void run() {
		while(true) {
			int num = std::rand() % 100;
			m_buffer.push(num);

			unique_lock<mutex> lk(print_mtx);
			cout << "producer push : " << num << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
};

class Consumer {
private:
	Buffer &m_buffer;

public:
	Consumer(Buffer &buffer) : m_buffer(buffer) {}

	void run() {
		while(true) {
			int num = m_buffer.pop();

			unique_lock<mutex> lk(print_mtx);
			cout << "consumer pop : " << num << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
};

int main() {
	Buffer b;
	Producer p(b);
	Consumer c(b);

	thread producer_thread(&Producer::run, &p);
	thread consumer_thread(&Consumer::run, &c);

	producer_thread.join();
	consumer_thread.join();
}
