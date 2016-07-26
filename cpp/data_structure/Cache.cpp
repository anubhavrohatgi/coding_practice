// General Cache with plugable strategy, use LRU strategy by default

#include <iostream>
#include <utility>
#include <unordered_map>
#include <list>
#include "LRUStrategy.cpp"

using namespace std;

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
