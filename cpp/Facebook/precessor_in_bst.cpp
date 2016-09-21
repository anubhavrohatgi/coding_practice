#include <iostream>

using namespace std;

class TreeNode {
public:
	int val;
	TreeNode *left, *right;

	TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

TreeNode *inorderPrecessor(TreeNode *root, int val) {
	TreeNode *ret = NULL, *curr = root;
	while(curr) {
		if(curr->val < val) {
			ret = curr;
			curr = curr->right;
		}
		else {
			curr = curr->left;
		}
	}

	return ret;
}


int main() {
	TreeNode *n1 = new TreeNode(32);
	TreeNode *n2 = new TreeNode(24);
	TreeNode *n3 = new TreeNode(41);
	TreeNode *n4 = new TreeNode(21);
	TreeNode *n5 = new TreeNode(28);
	TreeNode *n6 = new TreeNode(36);
	TreeNode *n7 = new TreeNode(47);
	TreeNode *n8 = new TreeNode(14);
	TreeNode *n9 = new TreeNode(25);
	TreeNode *n10 = new TreeNode(31);
	TreeNode *n11 = new TreeNode(39);

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n3->left = n6;
	n3->right = n7;
	n4->left = n8;
	n5->left = n9;
	n5->right = n10;
	n6->right = n11;

	TreeNode *ret = inorderPrecessor(n1, 37);
	cout << ret->val << endl;
}
