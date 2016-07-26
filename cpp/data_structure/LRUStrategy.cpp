#include <iostream>
#include <utility>
#include <unordered_map>
#include <list>
#include "Strategy.h"

using namespace std;

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
