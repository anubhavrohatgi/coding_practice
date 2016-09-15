#include <iostream>

using namespace std;

class TreeNode {
public:
	TreeNode *left, *right;
	int val;

	TreeNode(int v) : left(NULL), right(NULL), val(v) {}
};

TreeNode *bst_to_dll(TreeNode *root) {
	if(root == NULL)
		return NULL;

	if(root->left != NULL) {
		TreeNode *left_ret = bst_to_dll(root->left); 
		while(left_ret->right)
			left_ret = left_ret->right;
		left_ret->right = root;
		root->left = left_ret;
	}
	if(root->right != NULL) {
		TreeNode *right_ret = bst_to_dll(root->right);
		while(right_ret->left)
			right_ret = right_ret->left;
		root->right = right_ret;
		right_ret->left = root;
	}

	return root;
}

void print_list(TreeNode *n) {
	TreeNode *ptr = n, *pre = NULL;

	while(ptr) {
		cout << ptr->val << " ";
		pre = ptr;
		ptr = ptr->right;
	}
	cout << endl;
	while(pre) {
		cout << pre->val << " ";
		pre = pre->left;
	}
	cout << endl;
}

void inorder_print(TreeNode *n) {
	if(n == NULL)
		return;
	inorder_print(n->left);
	cout << n->val << " ";
	inorder_print(n->right);
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

	cout << "Original Tree inorder : " << endl;
	inorder_print(n1);
	cout << endl;

	n1 = bst_to_dll(n1);
	TreeNode *ptr = n1;
	while(ptr->left)
		ptr = ptr->left;
	print_list(ptr);
}
