#include <vector>
#include <iostream>

using namespace std;

class SegmentTreeNode {
public:
	int start, end;
	SegmentTreeNode *left, *right;
	int sum;
	int max;

	SegmentTreeNode(int s, int e) : start(s), end(e) {
		this->left = NULL;
		this->right = NULL;
		sum = 0;
		max = 0;
	}
};

SegmentTreeNode *build(const vector<int> &nums, int start, int end) {
	if(start > end)
		return NULL;

	SegmentTreeNode *node = new SegmentTreeNode(start, end);
	if(start == end) {
		node->sum = nums[start];
		node->max = nums[start];
	}
	else {
		int mid = start + (end-start)/2;
		node->left = build(nums, start, mid);
		node->right = build(nums, mid+1, end);

		node->sum = node->left->sum + node->right->sum;
		node->max = max(node->left->max, node->right->max);
	}

	return node;
}

void update(SegmentTreeNode *root, int pos, int new_value) {
	if(root->start == root->end) {
		root->sum = new_value;
		root->max = new_value;
	}
	else {
		int mid = root->start + (root->end - root->start)/2;
		if(pos <= mid)
			update(root->left, pos, new_value);
		else
			update(root->right, pos, new_value);

		root->sum = root->left->sum + root->right->sum;
		root->max = max(root->left->max, root->right->max);
	}

	return;
}

int sum_range(SegmentTreeNode *root, int start, int end) {
	if(root->start==start && root->end==end)
		return root->sum;
	else {
		
		int mid = root->start + (root->end - root->start)/2;
		if(end<=mid)
			return sum_range(root->left, start, end);
		else if(start>mid)
			return sum_range(root->right, start, end);
		else
			return sum_range(root->left, start, mid) + sum_range(root->right, mid+1, end);
	}
}

int find_max(SegmentTreeNode *root, int start, int end) {
	if(root->start==start && root->end==end)
		return root->max;
	else{
		int mid = root->start + (root->end - root->start)/2;
		if(end<=mid)
			return find_max(root->left, start, end);
		else if(start>mid)
			return find_max(root->right, start, end);
		else
			return max(find_max(root->left, start, mid), find_max(root->right, mid+1, end));
	}
}

int main() {
	vector<int> nums = {1, 3, 5, 7, 9, 11};
	SegmentTreeNode *root = build(nums, 0, nums.size());

	cout << sum_range(root, 0, 5) << endl;
	cout << find_max(root, 0, 5) << endl;
	update(root, 3, 13);
	cout << sum_range(root, 0, 5) << endl;
	cout << find_max(root, 0, 5) << endl;
}
