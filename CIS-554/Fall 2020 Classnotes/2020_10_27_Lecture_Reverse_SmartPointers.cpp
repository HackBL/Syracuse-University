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
	shared_ptr<Node> next;
	weak_ptr<Node> previous;
	Node(int i) { value = i; }
	Node() {}
};

class DoublyLinkedList {
public:
	shared_ptr<Node> head;
	shared_ptr<Node> tail;
	DoublyLinkedList() { }
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();
	void reverse();
	void sort();
};
void DoublyLinkedList::reverse() {
	if (!head || !head->next) return;
	shared_ptr<Node> p1 = head, p2, p3;
	while (p1) {
		p2 = p1->next;
		p1->next = p1->previous.lock();
		p1->previous = p2;
		p3 = p1;//this statement is tricky.
		p1 = p2;
	}
	p2 = head;
	head = tail;
	tail = p2;
}


void DoublyLinkedList::sort() {
	if (!head || !head->next) return;
	
	shared_ptr<Node> p1 = head; 
	while(p1) {
		shared_ptr<Node> p2 = p1->next; 
		int min = p1->value; 
		shared_ptr<Node> p_min = p1; 
		while (p2) {
			if (p2->value < min) {
				min = p2->value;
				p_min = p2; 
			}
			p2 = p2->next; 
		}
		p_min->value = p1->value; 
		p1->value = min; 
		p1 = p1->next; 
	}
}




void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		shared_ptr<Node> p1 = make_shared<Node>(rand() % n);
		p1->previous = tail;
		if (tail) tail->next = p1;
		tail = p1;
		if (!head) head = p1;
	}
}

void DoublyLinkedList::printForward() {
	cout << endl;
	shared_ptr<Node> p1 = head;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	shared_ptr<Node> p1 = tail;
	while (p1) {
		cout << p1->value << " ";
		p1 = p1->previous.lock();
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