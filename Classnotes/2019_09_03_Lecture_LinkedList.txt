//LInked List
#include <iostream>
using namespace std;


class Node {
public:
	Node* next;
	int value;
	//The following two functions are constructors -- for initializing object values
	Node() { next = nullptr; }
	Node(int i) { value = i; next = nullptr; }
};

class LinkedList {
public:
	Node* head;
	LinkedList() { head = nullptr; }
	void makeList(int m, int n);
	void printList();
	void reverse();
	void sort();
	void removeOne(int k);
};

void LinkedList::makeList(int m, int n) {//Create a link list of m nodes with
	//values being randomly distributed in 0 .. n-1
	Node* p1;
	for (int i = 0; i < m; i++) {
		p1 = new Node(rand() % n);
		p1->next = head;
		head = p1;
	}
}

void LinkedList::printList() {
	cout << endl;
	Node* p1 = head;
	while (p1) { //  this statement can also be written as while (p1 != nullptr)
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void LinkedList::reverse() {

	if (!head || !(head->next)) return;//return if the linked list contains
	//0 node or 1 node
	Node* p1 = head, * p2, * p3;
	p2 = p1->next;
	while (p2) {//this is the same as while (p2 != nullptr)
		p3 = p2->next;
		p2->next = p1;
		if (p1 == head) p1->next = nullptr;
		p1 = p2;
		p2 = p3;
	}
	head = p1;
}

void LinkedList::sort() {
	//Selection sort
	if (!head || !(head->next)) return;
	//Note "if (!(head->next || !head)"  might lead to errors when head==nullptr
	Node *p1 = head, *p2;
	int min;
	Node* p_min;
	while (p1) {
		min = p1->value;
		p_min = p1;
		p2 = p1->next;
		while (p2)  {//This loop will find the minimum value node from
			//the node pointed by p1 until the end of the linked list
			if (p2->value < min) {
				min = p2->value;
				p_min = p2;
			}
			p2 = p2->next;
		}
		//Swap the values at nodes pointed by p1 and p_min
		p_min->value = p1->value;
		p1->value = min;
		p1 = p1->next;
	}
}

void LinkedList::removeOne(int k) { //Remove a node (the first of such nodes) with value k
	if (!head) return;
	Node* p1 = head, *p2;
	if (head->value == k) {//if the first node contain value k
		head = head->next;
		delete p1;
		return;
	}
	p2 = p1->next;
	while (p2) {
		if (p2->value == k) {
			p1->next = p2->next;
			delete p2;
			return;
		}
		p1 = p2;
		p2 = p2->next;
	}
}

int main() {
	LinkedList L1;
	L1.makeList(20, 30);
	L1.printList();
	L1.reverse();
	L1.printList();
	L1.sort();
	L1.printList();
	L1.removeOne(29);
	L1.removeOne(1);
	L1.removeOne(14);
	L1.printList();

	getchar();
	getchar();
	return 0;


}
