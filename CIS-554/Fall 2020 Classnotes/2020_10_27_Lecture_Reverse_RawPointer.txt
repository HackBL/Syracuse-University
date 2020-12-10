//CIS554 HW1
//Due: 11:59PM, Wednesday ( September 9)
//Do not modify main funaiton.
//Do not introduce new functions.
//In-place implementation is required.  Exteranl stuctures are not allowed.
//For example, you are not allowed to copy linked list values to outside, and then process the data and copy them
//back to linked list.


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
	void reverse();
	//inplement the following member functions:

	//void group();
	/*
	Group all occurances of the same numbers together accourding to the order of appearance.

	For a list with values

	7 6 12 4 33 12 6 6 7 ,

	after grouping, it becomes

	7 7 6 6 6 12 12 4 33

	Note that in the original sequence, 7 appears before 6 before 12 before 4 before 33
	*/


};
void DoublyLinkedList::reverse() {
	if (!head || !head->next) return;
	Node* p1 = head, * p2;
	while (p1) {
		p2 = p1->next;
		p1->next = p1->previous;
		p1->previous = p2;
		p1 = p2;
	}
	p2 = head;
	head = tail;
	tail = p2;
}

void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail) tail->next = p1;
		tail = p1;
		if (!head) head = p1;
	}
}

void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

int main() {
	DoublyLinkedList d1;
	d1.makeRandomList(30, 20);
	d1.printForward();
	d1.printBackward();

		d1.reverse();
		d1.printForward();
		d1.printBackward();

	return 0;
}