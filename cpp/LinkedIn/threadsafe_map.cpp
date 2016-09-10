#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
// #include <shared_mutex>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadSafeMap {
private:
	vector<list<pair<int, int>>> m_map;
	int m_size;

	int hash(int n) {
		return n % m_size;
	}

	// Multi-threading
	// shared_mutex s_mtx;
	mutex mtx;
	condition_variable cv;
	int reader;
	bool is_writing;
public:
	ThreadSafeMap(int size) : m_size(size), reader(0), is_writing(false) {
		for(int i=0; i<m_size; i++)
			m_map.push_back(list<pair<int, int>>());
	}

	int get(int key) {
		// this will do
		// shared_lock<shared_mutex> lk(s_mtx);
		int hash_key = hash(key);

		unique_lock<mutex> lk(mtx);
		cv.wait(lk, [this] { return !is_writing; } );
		reader++;

		int ret = -1;
		for(auto it = m_map[hash_key].begin(); it != m_map[hash_key].end(); it++) {
			if((*it).first == key) {
				ret = (*it).second;
				break;
			}
		}

		reader--;
		cv.notify_all();

		return ret;
	}

	void put(int key, int val) {
		// this will do
		// unique_lock<shared_mutex> lk(s_mtx);
		int hash_key = hash(key);
		
		unique_lock<mutex> lk(mtx);
		cv.wait(lk, [this]{ return !(is_writing || reader > 0); } );
		is_writing = true;

		for(auto it = m_map[hash_key].begin(); it != m_map[hash_key].end(); it++) {
			if((*it).first == key) {
				(*it).first = key;
				(*it).second = val;
				
				is_writing = false;
				cv.notify_all();
				return;
			}
		}
		// new key, insert
		m_map[hash_key].push_front({key, val});

		is_writing = false;
		cv.notify_all();
	}

	void print_list(int key) {
		int hash_key = hash(key);
		for(auto it = m_map[hash_key].begin(); it != m_map[hash_key].end(); it++) {
			cout << "key = " << (*it).first << " value = " << (*it).second << endl;
		}
	}
};

int main() {
	ThreadSafeMap ts_map(3);

	ts_map.put(1, 1);
	ts_map.put(4, 4);
	ts_map.put(2, 2);
	ts_map.put(6, 6);
	ts_map.put(8, 8);
	ts_map.put(9, 9);

	cout << ts_map.get(8) << endl;
}
