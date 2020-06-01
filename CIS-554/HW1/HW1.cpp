//HW1 by Bo Li
//SU Net ID: bli158  SUID: 218717316

#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();

	//inplement the following member functions:

	void sort();//sort all values based on frequency in ascending order.
	//In case of ties, the smaller values will appear earlier
	//Example:  for list with values  7 6 12 4 33 12 6 6 7
	//sorted results: 4 33 7 7 12 12 6 6 6


	//If your algorithm is inefficient, you might lose points.
	//You will not modify L.

};

void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
}

void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

void DoublyLinkedList::sort() {
	Node* p1, * p2;
	Node* p_origin;
	Node* p_temp;
	Node* p_occurred;
	Node* p_traverse = head;
	int list_length = 0;
	int cur_value;
	int distinct_node_num = 0;

	while (p_traverse) {  // get length of doubly linked list
		list_length++;
		p_traverse = p_traverse->next;
	}

	if (!head || !head->next) return; // return if the linked list contains 0 node or 1 node

	for (int i = list_length; i > 0; i--) {  // find out frequency of nodes in ascending order
		p1 = head;
		int count = 0;

		while (p1) {  // p1 traverses the entire doubly linked list
			p_occurred = p1->previous;
			int freq = 1;

			while (p_occurred) {   // if p1->value is occurred in its all previous nodes, move p1 to next
				if (p1->value == p_occurred->value && p1 != tail) {
					p1 = p1->next;
					p_occurred = p1;
				}
				else if (p1->value == p_occurred->value && p1 == tail) {  // if last node is occurred previously, do not count, and exit the loop
					freq = -1; // do not count
					break;
				}
				p_occurred = p_occurred->previous;
			}

			p2 = p1->next;  // p2 always indicates the next node of p1
			while (p2) {    // count frequency of each distinctive node
				if (p2->value == p1->value) {
					freq++;
				}
				p2 = p2->next;
			}

			if (freq == i) { // find out nodes by current frequency in ascending order, move them in the front of list
				distinct_node_num++;    // find out number of distinct nodes

				if (p1 == head)
					p_origin = p1;  //  the position of the node pointed by p1 has to be recorded in order to continue to track the entire list
				else
					p_origin = p1->previous;

				cur_value = p1->value;  // record current value pointed by p1

				while (p1) {  // based on current node pointed by p1, track all remnant nodes to find out nodes with current frequency, and move them to the front of list
					if (p1->value == cur_value) {
						if (p1 == head);  // do not move
						else if (p1 == tail) {  // move tail to the front
							tail = p1->previous;
							tail->next = nullptr;

							// put p1 node into head
							p1->next = head;
							head->previous = p1;
							head = p1;
							head->previous = nullptr;

							p1 = tail;
						}
						else {  // move middle nodes to the front
							p_temp = p1->previous;
							p1->previous->next = p1->next;
							p1->next->previous = p1->previous;

							// put p1 node into head
							p1->next = head;
							head->previous = p1;
							head = p1;
							head->previous = nullptr;

							p1 = p_temp;
						}
						count++;    // calculate how many nodes totally in current frequency
					}
					p1 = p1->next;
				}
				p1 = p_origin;
			}
			p1 = p1->next;
		}

		if (count != 0 && count != 1) {     // sort nodes by current frequency
			p1 = head;
			int tracker = 0;    // track nodes based on current frequency
			int temp;
			Node* p_current;

			while (p1) {
				if (tracker < count) {    // number of nodes on current frequency
					p2 = p1->previous;
					p_current = p1;

					while (p2) {  // use p2 to track all previous nodes of current node
						if (p1->value < p2->value) {    // swap if previous node value is larger than current node value
							temp = p1->value;
							p1->value = p2->value;
							p2->value = temp;

							p1 = p2;
						}
						p2 = p2->previous;
					}
				}
				else    // break to avoid tracking useless nodes
					break;

				p1 = p_current;
				tracker++;
				p1 = p1->next;
			}
		}
	}
}

int main() {
	DoublyLinkedList d1;
	d1.makeRandomList(50, 20);
	d1.printForward();
	d1.printBackward();

	d1.sort();
	d1.printForward();
	d1.printBackward();

	getchar();
	getchar();
	return 0;
}