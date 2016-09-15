#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class TreeNode {
public:
	TreeNode *left, *right;
	int val;

	TreeNode(int v) : val(v) {}
};

void dfs(TreeNode *n, vector<int> &path_sums, int curr_sum) {
	if(n == NULL)
		return;

	curr_sum += n->val;
	if(n->left == NULL && n->right == NULL) {
		path_sums.push_back(curr_sum);
		return;
	}
	dfs(n->left, path_sums, curr_sum);
	dfs(n->right, path_sums, curr_sum);
}

vector<int> binary_tree_path_sum_recursion(TreeNode *root) {
	vector<int> path_sums;
	dfs(root, path_sums, 0);

	return path_sums;
}

vector<int> binary_tree_path_sum_iteration(TreeNode *root) {
	vector<int> path_sums;
	if(root == NULL)
		return path_sums;

	// first: TreeNode, second: curr_sum
	queue<pair<TreeNode*, int>> q;
	q.push({root, root->val});
	while(!q.empty()) {
		auto it = q.front();
		q.pop();

		if(it.first->left == NULL && it.first->right == NULL)
			path_sums.push_back(it.second);

		if(it.first->left)
			q.push({ it.first->left, it.second + it.first->left->val });
		if(it.first->right)
			q.push({ it.first->right, it.second + it.first->right->val });
	}

	return path_sums;
}

void print_vector(const vector<int> &nums) {
	for(int num : nums) {
		cout << num << " ";
	}
	cout <<endl;
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

	vector<int> ret1 = binary_tree_path_sum_recursion(n1);
	print_vector(ret1);

	vector<int> ret2 = binary_tree_path_sum_iteration(n1);
	print_vector(ret2);
}
