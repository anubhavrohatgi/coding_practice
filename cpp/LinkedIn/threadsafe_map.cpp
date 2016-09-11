#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <thread>
// #include <shared_mutex>
#include <mutex>
#include <condition_variable>

using namespace std;

// http://stackoverflow.com/questions/27860685/how-to-make-a-multiple-read-single-write-lock-from-more-basic-synchronization-pr
// Multiple readers and one writer, and starves writer
class RWLock {
private:
	int readers;
	bool is_writing;
	mutex mtx;
	condition_variable readerQ;
	condition_variable writerQ;
public:
	RWLock() : readers(0), is_writing(false), mtx(), readerQ(), writerQ() {}

	void ReadLock() {
		unique_lock<mutex> lk(mtx);
		readerQ.wait(lk, [this]{ return !is_writing; } );
		readers++;
		lk.unlock();
	}

	void ReadUnLock() {
		unique_lock<mutex> lk(mtx);
		readers--;
		if(readers == 0)
			writerQ.notify_all();
		
		lk.unlock();
	}

	void WriteLock() {
		unique_lock<mutex> lk(mtx);
		writerQ.wait(lk, [this]{ return !(is_writing || readers > 0); } );
		is_writing = true;

		lk.unlock();
	}

	void WriteUnLock() {
		unique_lock<mutex> lk(mtx);
		is_writing = false;
		readerQ.notify_all();

		lk.unlock();
	}
};

class ThreadSafeMap {
private:
	vector<list<pair<int, int>>> m_map;
	int m_size;

	int hash(int n) {
		return n % m_size;
	}

	// Multi-threading
	// shared_mutex s_mtx;
	RWLock rw_lock;

public:
	ThreadSafeMap(int size) : m_size(size), rw_lock() {
		for(int i=0; i<m_size; i++)
			m_map.push_back(list<pair<int, int>>());
	}

	int get(int key) {
		// this will do
		// shared_lock<shared_mutex> lk(s_mtx);
		rw_lock.ReadLock();
		
		int hash_key = hash(key);

		int ret = -1;
		for(auto it = m_map[hash_key].begin(); it != m_map[hash_key].end(); it++) {
			if((*it).first == key) {
				ret = (*it).second;
				break;
			}
		}

		rw_lock.ReadUnLock();
		return ret;
	}

	void put(int key, int val) {
		// this will do
		// unique_lock<shared_mutex> lk(s_mtx);
		int hash_key = hash(key);
		
		rw_lock.WriteLock();
		for(auto it = m_map[hash_key].begin(); it != m_map[hash_key].end(); it++) {
			if((*it).first == key) {
				(*it).first = key;
				(*it).second = val;
			
				rw_lock.WriteUnLock();
				return;
			}
		}
		// new key, insert
		m_map[hash_key].push_front({key, val});
		rw_lock.WriteUnLock();
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
