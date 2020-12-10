//CIS554 HW1
//Due: 11:59PM, Friday ( September 13)
//Do not modify main funaiton.
//Do not introduce new functions
//In-place implementation is required.

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

int main() {
	DoublyLinkedList d1;
	d1.makeRandomList(5, 20);
	d1.printForward();
	d1.printBackward();

	Node* p1 = d1.head->next;
	Node* p2 = d1.tail->previous;

	//Swap the two nodes pointed by p1 and p2
	//by modifying pointers
	Node* p3 = p1->next, * p4 = p1->previous;
	p1->next->previous = p2;
	p2->next->previous = p1;
	p1->previous->next = p2;
	p2->previous->next = p1;
	p1->next = p2->next;
	p2->next = p3;
	p1->previous = p2->previous;
	p2->previous = p4;
	d1.printForward();
	d1.printBackward();


	//Swap two consecutive nodes
	//by modifying pointers

	p1 = d1.head->next;
	p2 = d1.head->next->next;

	p4 = p1->previous;

	p2->next->previous = p1;
	p1->previous->next = p2;
	p1->next = p2->next;
	p1->previous = p2;
	p2->next = p1;
	p2->previous = p4;

	d1.printForward();
	d1.printBackward();



	getchar();
	getchar();
	return 0;
}