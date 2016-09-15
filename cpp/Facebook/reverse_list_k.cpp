#include <iostream>

using namespace std;

// http://www.1point3acres.com/bbs//forum.php?mod=viewthread&tid=141325
class ListNode {
public:
	ListNode *next;
	int val;

	ListNode(int v) : next(NULL), val(v) {}
}; 

ListNode *reverse_range(ListNode *before, ListNode *after) {
	ListNode *last = before->next, *curr = last->next;
	while(curr != after) {
		last->next = curr->next;
		curr->next = before->next;
		before->next = curr;
		curr = last->next;
	}
	return last;
}

ListNode *reverse_k(ListNode *head, int k) {
	if(head == NULL || k <= 1)
		return head;

	ListNode *dummy = new ListNode(-1);
	dummy->next = head;
	ListNode *ptr = dummy;
	
	bool reverse = true;
	int counter = 0;
	while(head != NULL) {
		counter++;
		if(counter % k == 0) {
			if(reverse) {
				ptr = reverse_range(ptr, head->next);
				head = ptr->next;
				reverse = false;
			}
			else {
				ptr = head;
				head = head->next;
				reverse = true;
			}
		}
		else {
			head = head->next;
		}
	}

	return dummy->next;
}

void print_list(ListNode *head) {
	while(head) {
		cout << head->val << " ";
		head = head->next;
	}
	cout << endl;
}

int main() {
	ListNode *n1 = new ListNode(1);
	ListNode *n2 = new ListNode(2);
	ListNode *n3 = new ListNode(3);
	ListNode *n4 = new ListNode(4);
	ListNode *n5 = new ListNode(5);
	ListNode *n6 = new ListNode(6);
	ListNode *n7 = new ListNode(7);
	ListNode *n8 = new ListNode(8);
	ListNode *n9 = new ListNode(9);

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n5->next = n6;
	n6->next = n7;
	n7->next = n8;
	n8->next = n9;

	ListNode *l = reverse_k(n1, 3);
	print_list(l);
}
