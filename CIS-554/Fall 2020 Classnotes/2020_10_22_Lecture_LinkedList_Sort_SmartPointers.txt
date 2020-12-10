#include <iostream>
#include <memory>
using namespace std;

class Node {
public:
	int value;
	//Node* next;
	shared_ptr<Node> next;
	//comes with default value nullptr
	//constructors to initialize object contents

	/*Node(int i) { value = i; next = nullptr; }
	Node() { next = nullptr; }*/
	Node(int i) { value = i; }
	Node() {}
};

class LinkedList {
public:
	//Node* head;
	shared_ptr<Node> head;
	//constructor
	//LinkedList() { head = nullptr; }
	LinkedList() { }
	void makeRandomList(int m, int n);//function prototype
	//Create a linked list of m nodes with random value in 0 .. n-1


	void print();

	//void reverse();


	void sort();
	LinkedList(const initializer_list<int>& I);



};

LinkedList::LinkedList(const initializer_list<int>& I) {
	auto p = I.end() - 1;
	while (p != I.begin() - 1) {
		shared_ptr<Node> sp1 = make_shared<Node>(*p);
		sp1->next = head;
		head = sp1;
		p--;
	}



}

void LinkedList::sort() { //selection sort
	if (!head || !head->next) return;//Return if the linked list contain 0 or 1 node
	//Node* p1 = head;
	shared_ptr<Node> p1 = head;
	while (p1) {
		//Node* p2 = p1->next;
		shared_ptr<Node> p2 = p1->next;
		int min = p1->value;
		//Node* p_min = p1;
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

//
//void LinkedList::reverse() {
//	if (!head || !head->next) return;//when the link list contains 0 or 1 node.
//	Node* p1{ head }, * p2 = p1->next;
//	while (p2) {
//		Node* p3 = p2->next;
//		p2->next = p1;
//		if (p1 == head) p1->next = nullptr;
//		p1 = p2;
//		p2 = p3;
//	}
//	head = p1;
//}
//



void LinkedList::print() {
	//Node* p = head;
	shared_ptr<Node> p = head;
	cout << endl;
	while (p) { //same as while (p!=nullptr)
		cout << p->value << " ";
		p = p->next;
	}
}

void LinkedList::makeRandomList(int m, int n) {
	for (int i = 0; i < m; i++) {
		//Node* p = new Node(rand() % n);//rand() return random int value; \
									   //rand()%n will return a random number in 0...n-1 
		//10%7 is 3 -- % returns remainder of a division
		shared_ptr<Node> p = make_shared<Node>(rand() % n);
		p->next = head;
		head = p;
	}
}

int main() {
	/*
	Node n1{ 10 };
	Node n2;
	int i{ 5 };
	int j;
	*/

	LinkedList L1;
	L1.makeRandomList(20, 10);
	L1.print();
	//L1.reverse();
	//L1.print();
	L1.sort();
	L1.print();

	LinkedList L5{ 1,2,3,4,5 };
	L5.print();



	return 0;
}