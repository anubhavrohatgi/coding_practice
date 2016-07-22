/**
 * Question:
 * Given a binary tree, convert it to doubly linked list with inorder sequence
 */ 

#include <iostream>

using namespace std;

class TreeNode {
public:
	TreeNode *left, *right;
	int val;

	TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

TreeNode *convertToDllUtil(TreeNode *n) {
	if(n == NULL)
		return NULL;
	if(n->left) {
		TreeNode *left_ret = convertToDllUtil(n->left);
		while(left_ret->right)
			left_ret = left_ret->right;
		left_ret->right = n;
		n->left = left_ret;
	}
	if(n->right) {
		TreeNode *right_ret = convertToDllUtil(n->right);
		while(right_ret->left)
			right_ret = right_ret->left;
		right_ret->left = n;
		n->right = right_ret;
	}

	return n;
}

TreeNode *convertToDll(TreeNode *root) {
	if(root == NULL)
		return NULL;

	root = convertToDllUtil(root);
	while(root->left)
		root = root->left;
	return root;
}

int main() {

	TreeNode *root		= new TreeNode(10);
	root->left		= new TreeNode(12);
	root->right		= new TreeNode(15);
	root->left->left	= new TreeNode(25);
	root->left->right	= new TreeNode(30);
	root->right->left	= new TreeNode(36);

	TreeNode *newHead = convertToDll(root);
	TreeNode *ptr = newHead;

	while(ptr) {
		cout << ptr->val << endl;
		ptr = ptr->right;
	}
}
