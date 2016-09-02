#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
	unordered_map<char, TrieNode*> m;
	bool isFinished;

	TrieNode() : isFinished(false) {}
};

class Trie {
public:
	TrieNode *root = new TrieNode();
	
	void insert(const string &str) {
		TrieNode *ptr = root;
		for(char c : str) {
			if(ptr->m.find(c) == ptr->m.end()) {
				ptr->m[c] = new TrieNode();
			}
			ptr = ptr->m[c];
		}
		ptr->isFinished = true;
	}
};

void dfs(vector<string> &ret, string word, string target, int k, vector<int> prev, TrieNode *n) {
	if(n->isFinished) {
		if(prev.back() <= k)
			ret.push_back(word);
		else
			return;
	}

	for(auto a : n->m) {
		vector<int> curr(target.size()+1, 0);
		curr[0] = word.size() + 1;	// +1 => + curr char

		for(int j=1; j<prev.size(); j++) {
			if(target[j-1] == a.first)
				curr[j] = prev[j-1];
			else
				curr[j] = min(prev[j-1], min(prev[j], curr[j-1])) + 1;
		}

		dfs(ret, word + a.first, target, k, curr, a.second);
	}
}

vector<string> getKEditDistance(const vector<string> &strs, const string &target, int k) {
	vector<string> ret;
	if(strs.size() == 0 || target == "" || k < 0)
		return ret;
	// build the Trie
	Trie *trie = new Trie();
	for(string str : strs) {
		trie->insert(str);
	}
	TrieNode *root = trie->root;

	// dp table for calculating edit distance
	int n = target.size();
	vector<int> prev(n+1, 0);
	for(int i=1; i<n+1; i++) {
		prev[i] = i;
	}

	dfs(ret, "", target, k, prev, root);

	return ret;
}


int main() {
	vector<string> strs = {"abc", "abcd", "abd", "adc"};
	string target = "ac";
	int k = 1;

	vector<string> ret = getKEditDistance(strs, target, k);

	for(string s : ret)
		cout << s << endl;
}
