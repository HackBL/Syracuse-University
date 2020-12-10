
//Shallow and deep copy and assignment
//copy constructor, destructor, operator=
//Lvalue, Rvalue, move constructor, Rvalue operator=
#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node(int i) : value(i), next(nullptr) {}//avoid using NULL; will be penalized in HW
	Node() : next(nullptr) {}
};

class LinkedList {
public:
	Node* head;
	LinkedList() : head(nullptr) {}
	LinkedList(const initializer_list<int>& I);//initializer_list
	LinkedList(const LinkedList& L);//copy constructor
	/*
	Only in three cases will copy constructor be invoked:
	call/pass by value;
	return by value;
	declared and initialized in the same statement; such as LinkedList L2 {L1};
	*/

	void operator=(const LinkedList& L);//Lvalue operator=
	~LinkedList();//destructor  -- the defualt one will only do shallow delete
	/*
	Only in 2 cases will destructor be called:
	1. when an object is going out of scope
	2. When when delete function is called
	*/
	LinkedList ThreeTimes();
	//LinkedList(LinkedList&& L);//move constructor
	//void operator=(LinkedList&& L);//Rvalue operator=

};

//void LinkedList::operator=(LinkedList&& L) {
//	while (head) {
//		Node* p3{ head->next };
//		delete head;
//		head = p3;
//	}
//	head = L.head;
//	L.head = nullptr;
//	cout << "Rvalue operator=" << endl;
//}
//
//LinkedList::LinkedList(LinkedList&& L) :LinkedList() {
//	head = L.head;
//	L.head = nullptr;
//	cout << "move constructor" << endl;
//}

LinkedList LinkedList::ThreeTimes() {
	LinkedList temp{ *this };//copy constructor
	Node* p1{ temp.head };
	while (p1) {
		p1->value *= 3;
		p1 = p1->next;
	}
	cout << "ThreeTimes" << endl;
	return temp;
	//Now that you have provided move constructor, if you perform
	//return by value, the compiler will automatically change your code
	//into the following:
	//return move(temp); which will then invoke Rvalue referenced move constructor
}

LinkedList::~LinkedList() {
	while (head) {
		Node* p1{ head->next };
		delete head;
		head = p1;
	}
	cout << "destructor" << endl;

}
void LinkedList::operator=(const LinkedList& L) {
	while (head) {
		Node* p3{ head->next };
		delete head;
		head = p3;
	}

	Node* p1{ L.head }, * p2;
	while (p1) {
		p2 = new Node;
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}
	cout << "Lvalue operator=" << endl;
}

LinkedList::LinkedList(const LinkedList& L) : LinkedList() {

	Node* p1{ L.head }, * p2;
	while (p1) {
		p2 = new Node;
		p2->next = head;
		head = p2;
		p1 = p1->next;
	}
	p1 = L.head;
	p2 = head;
	while (p1) {
		p2->value = p1->value;
		p1 = p1->next;
		p2 = p2->next;
	}

	cout << "copy constructor" << endl;
}



LinkedList::LinkedList(const initializer_list<int>& I) : LinkedList() {
	auto p1{ I.end() - 1 };
	while (p1 != I.begin() - 1) {
		Node* p2 = new Node(*p1);
		p2->next = head;
		head = p2;
		--p1;
	}
	cout << "initializer_list" << endl;
}


ostream& operator<<(ostream& str, const LinkedList& L) {
	str << "< ";
	Node* p1{ L.head };
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	str << ">";
	return str;
}


void f2(int&& i) {

	i++;
}




int main() {
	
	LinkedList L1{ 10,20,30,40,50 };
	cout << L1 << endl;


	//return value optimiation (RVO) , named return value optimization(NRVO)
	LinkedList L2{ L1.ThreeTimes() };//NRVO -- saves one copy construcotr
	
	//We expected three copy constructors for the above statement.
	//However, we actually only see two copy constructors.
	//The copy constructor to create the "hidden copy" and the one to crate L2
	//are replaced with a single copy constructor.
	//This is called return value optimization or named return value optimization.

	
	
	
	



	int k{ 200 };
	f2(move(k));
	cout << k << endl;//201
	f2(100);
	return 0;
}