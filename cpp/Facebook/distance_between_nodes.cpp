#include <iostream>
#include <climits>

using namespace std;

// http://www.geeksforgeeks.org/find-distance-two-given-nodes/
class TreeNode {
public:
	TreeNode *left, *right;
	int val;

	TreeNode(int v) : val(v) {}
};

int findLevel(TreeNode *n, TreeNode *p, int level) {
	if(n == NULL)
		return -1;
	if(n == p) {
		return level;
	}
	
	int lv1 = findLevel(n->left, p, level+1);
	int lv2 = findLevel(n->right, p, level+1);

	return max(lv1, lv2);
}

TreeNode *lca(TreeNode *root, TreeNode *p, TreeNode *q, int &d1, int &d2, int &dist, int depth) {
	if(root == NULL) {
		return NULL;
	}
	if(root == p) {
		d1 = depth;
		return root;
	}
	if(root == q) {
		d2 = depth;
		return root;
	}

	TreeNode *l = lca(root->left,  p, q, d1, d2, dist, depth+1);
	TreeNode *r = lca(root->right, p, q, d1, d2, dist, depth+1);

	if(l && r) {
		dist = d1 + d2 - 2*depth;
		return root;
	}
	else if(l)
		return l;
	else if(r)
		return r;
	else
		return NULL;
}

int findDistance(TreeNode *root, TreeNode *p, TreeNode *q) {
	int d1 = -1, d2 = -1, dist = 0;
	TreeNode *r = lca(root, p, q, d1, d2, dist, 0);

	if(d1 != -1 && d2 != -1) {
		return dist;
	}
	else if(d1 != -1) {
		return findLevel(p, q, 0);
	}
	else if(d2 != -1) {
		return findLevel(q, p, 0);
	}

	return -1;
}

int main() {
	TreeNode *n1 = new TreeNode(1);
	TreeNode *n2 = new TreeNode(2);
	TreeNode *n3 = new TreeNode(3);
	TreeNode *n4 = new TreeNode(4);
	TreeNode *n5 = new TreeNode(5);
	TreeNode *n6 = new TreeNode(6);
	TreeNode *n7 = new TreeNode(7);
	TreeNode *n8 = new TreeNode(8);

	n1->left = n2;
	n2->left = n4;
	n2->right = n5;
	n1->right = n3;
	n3->left = n6;
	n3->right = n7;
	n6->right = n8;

	cout << findDistance(n1, n4, n5) << endl;
	cout << findDistance(n1, n4, n6) << endl;
	cout << findDistance(n1, n3, n4) << endl;
	cout << findDistance(n1, n2, n4) << endl;
	cout << findDistance(n1, n8, n5) << endl;
}
