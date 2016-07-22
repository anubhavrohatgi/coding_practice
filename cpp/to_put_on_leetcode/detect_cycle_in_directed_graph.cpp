#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Node {
	public:
		int val;
		set<Node*> children;

		Node(int v) : val(v) {}
};

class Graph {
	public:
		vector<Node*> nodes;
};

bool hasCycle(Node *n, set<Node*> visited, set<Node*> inStack) {
	if(visited.find(n) == visited.end()) {
		visited.insert(n);
		inStack.insert(n);

		for(auto a : n->children) {
			if(inStack.find(a) != inStack.end())
				return true;
			if(visited.find(a) == visited.end() && hasCycle(a, visited, inStack))
				return true;
		}
		inStack.erase(n);
	}
	return false;
}

int main()
{
	cout << "Hello World" << endl; 

	Node *n1 = new Node(1);
	Node *n2 = new Node(2);
	Node *n3 = new Node(3);
	Node *n4 = new Node(4);
	Node *n5 = new Node(5);

	n1->children = {n2, n3};
	n3->children = {n4};
	n4->children = {n3};

	Graph *graph = new Graph();
	graph->nodes = {n1, n2, n3, n4, n5};

	set<Node*> visited, inStack;

	for(auto a : graph->nodes) {
		if(hasCycle(a, visited, inStack)) {
			cout << "Graph has cycle" << endl;
			return 0;
		}
	}
	cout << "Graph doesn't have cycle" << endl;

	//cout << hasCycle(n1, visited, inStack) << endl;

	return 0;
}
