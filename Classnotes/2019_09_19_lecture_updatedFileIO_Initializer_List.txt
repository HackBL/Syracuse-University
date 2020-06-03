//CIS554 HW1
//Due: 11:59PM, Friday ( September 13)
//Do not modify main funaiton.
//Do not introduce new functions
//In-place implementation is required.

#include <iostream>
#include <fstream>
#include <vector>
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
	DoublyLinkedList(const initializer_list<int>& I);

};
DoublyLinkedList::DoublyLinkedList(const initializer_list<int>& I): DoublyLinkedList() {//Invoking Constructor to 
																	//initialize head = tail = nullptr;
	auto it = I.begin();
	while (it != I.end()) {
		Node* p1 = new Node(*it);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
		it++;
	}
}



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
	//The following is an exmaple of creating 
	//a DoublyLinkedList with your own selected numbers.
	//You can use this create a sorted DoublyLinkedList

	DoublyLinkedList d11 = { 1,2,3,4,5,6,7,8,9,10,11,12,12,13,14,15 };
	d11.printForward();
	d11.printBackward();

	//Alternatively, you can read the sorted list from an external file
	//as shown below.

	DoublyLinkedList d0;
	ifstream in1("data1.txt");//The file data1.txt need to be in the
	//same directory for source code.
	int i;
	vector<int> V;
	while (in1>>i) { //If we can successfully read in an int, (in1>>i) will return true
					 //else, it will return false.
					 //Thus, it will work even if there is spece at the end of file
		V.push_back(i);
	}
	for (int i : V) { cout << i << " "; }

	for (size_t i = 0; i < V.size(); i++) {
		Node* p1 = new Node(V[i]);
		p1->previous = d0.tail;
		if (d0.tail != nullptr) d0.tail->next = p1;
		d0.tail = p1;
		if (d0.head == nullptr) d0.head = p1;
	}
	d0.printForward();
	d0.printBackward();
	in1.close(); //When done with reading, rembmer to close it to avoid problems

	ofstream out1("data1.txt"); //if the file does not exist, it will be created.
	//If the file exists, it will be emptied first.  Be careful.

	for (int i : V) { out1 << i * 10 << " "; }


	out1.close(); //When done with writing, remember to close it to avoid problems



	/*
	DoublyLinkedList d1;
	d1.makeRandomList(50, 20);
	d1.printForward();
	d1.printBackward();

	d1.sort();
	d1.printForward();
	d1.printBackward();
	*/
	char c1;
	c1 = getchar();
	c1 = getchar();
	return 0;
}