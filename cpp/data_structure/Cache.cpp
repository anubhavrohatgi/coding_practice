#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>

using namespace std;

class Strategy {
protected:
	int m_size;

public:
	Strategy(int size) : m_size(size) {}
	virtual int handleGet(int key) = 0;
	virtual void handlePut(int key, int value) = 0;
	virtual void printCache() = 0;
};

class LRUStrategy : public Strategy {
// inherit constructor
using Strategy::Strategy;

private:
	list<pair<int, int>> m_list;
	unordered_map<int, list<pair<int, int>>::iterator> m_map;

public:
	int handleGet(int key) {
		auto found_iter = m_map.find(key);
		if(found_iter == m_map.end())
			return -1;
		
		m_list.splice(m_list.begin(), m_list, found_iter->second);
		return found_iter->second->second;
	}

	void handlePut(int key, int value) {
		auto found_iter = m_map.find(key);
		if(found_iter != m_map.end()) {
			found_iter->second->second = value;
			m_list.splice(m_list.begin(), m_list, found_iter->second);
		}
		else {
			if(m_map.size() == m_size) {
				int key_to_delete = m_list.back().first;
				m_map.erase(key_to_delete);
				m_list.pop_back();
			}
			m_list.emplace_front(make_pair(key, value));
			m_map[key] = m_list.begin();	
		}
	}

	void printCache() {
		for(auto a = m_list.begin(); a != m_list.end(); a++)
			cout << "(" << a->first << " , " << a->second << ") ";
		cout << endl;
	}
};

class Cache {
private:
	int m_size;
	Strategy *strategy;

public:
	Cache(int size = 3) : m_size(size), strategy(new LRUStrategy(m_size)) {}
	
	Cache(int size, Strategy *stra) : m_size(size), strategy(stra) {}

	int get(int key) {
		return strategy->handleGet(key);
	}

	void put(int key, int value) {
		strategy->handlePut(key, value);
	}

	void printCache() {
		strategy->printCache();
	}
};

int main() {
	Cache *cache = new Cache();
	cache->put(1, 11);
	cache->put(3, 33);
	cache->put(2, 22);
	cache->printCache();
	cache->put(4, 44);
	cache->printCache();
	cache->get(3);
	cache->printCache();
}
