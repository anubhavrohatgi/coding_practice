#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;
bool can_print = false;
int counter = 0;

void print_number_worker(int num) {
	while(counter < 50) {

		unique_lock<mutex> lk(m);
		cv.wait(lk, [] { return can_print; });

		cout << num << endl;
		counter++;
		cv.notify_one();
	}
}

int main() {
	thread worker1(print_number_worker, 1);
	thread worker2(print_number_worker, 2);

	{
		lock_guard<mutex> lk(m);
		can_print = true;
	}
	cv.notify_one();

	worker1.join();
	worker2.join();
}
