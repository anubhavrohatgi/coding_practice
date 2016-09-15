#include <iostream>
#include <climits>

using namespace std;

class TreeNode {
public:
	TreeNode *left, *right;
	int val;

	TreeNode(int v) : val(v) {}
};


int p_depth = INT_MIN, q_depth = INT_MIN, lca_depth = INT_MIN;

TreeNode *lca(TreeNode *root, TreeNode *p, TreeNode *q, int depth) {
	if(root == NULL) {
		return NULL;
	}
	if(root == p || root == q) {
		if(p_depth != INT_MIN)
			swap(p_depth, q_depth);
		p_depth = depth;

		return root;
	}

	TreeNode *l = lca(root->left,  p, q, depth+1);
	TreeNode *r = lca(root->right, p, q, depth+1);

	if(!l && !r) {
		if(lca_depth == INT_MIN)
			lca_depth = depth;
		return root;
	}
	else if(!l)
		return l;
	else if(!r)
		return r;
	else
		return NULL;
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

	TreeNode *r = lca(n1, n4, n5, 0);
	cout << r->val << endl;
	cout << "lca_depth = " << lca_depth <<  " p_depth = " << p_depth << " q_depth = " << q_depth << endl;
}
