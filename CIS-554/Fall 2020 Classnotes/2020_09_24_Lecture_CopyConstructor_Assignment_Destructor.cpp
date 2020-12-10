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
	Node(int i): value(i), next(nullptr){}//avoid using NULL; will be penalized in HW
	Node(): next(nullptr){}
};

class LinkedList {
public:
	Node* head;
	LinkedList(): head(nullptr){}
	LinkedList(const initializer_list<int>& I);//initializer_list
	LinkedList(const LinkedList& L);//copy constructor
	/*
	Only in three cases will copy constructor be invoked:
	call/pass by value;
	return by value;
	declared and initialized in the same statement; such as LinkedList L2 {L1};
	*/

	void operator=(const LinkedList & L);//Lvalue operator=
	~LinkedList();//destructor  -- the defualt one will only do shallow delete
	/*
	Only in 2 cases will destructor be called:
	1. when an object is going out of scope
	2. When when delete function is called
	*/
	LinkedList ThreeTimes();
};

LinkedList LinkedList::ThreeTimes() {
	LinkedList temp{ *this };//copy constructor
	Node* p1{ temp.head };
	while (p1) {
		p1->value *= 3;
		p1 = p1->next;
	}
	cout << "ThreeTimes" << endl;
	return temp;
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

LinkedList::LinkedList(const LinkedList& L): LinkedList() {
	
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



LinkedList::LinkedList(const initializer_list<int>& I): LinkedList() {
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

int main() {
	/*
	string s1{ "MAT397" }, s2{ "CIS554" };
	if (s1 < s2) cout << "Yes"<<endl;
	else cout << "No" << endl;
	*/

	LinkedList L1{ 10,20,30,40,50 };
	cout << L1 << endl;
	LinkedList L2{ L1 };//will run copy constructor
	//The above statement can be equivalently written as   LinkedList L2 = L1;//copy constructor

	L2.head->value = 100;
	cout << L1 << endl;

	LinkedList L3;
	L3 = L1;//  L3.operator=(L1); operator assignment
	L3.head->value = 500;
	cout << L1 << endl;
	

	LinkedList L4;
	L4 = L1.ThreeTimes();
	//compiler will change it to
	//L4.opertor=(L1.ThreeTimes());
	cout << L4 << endl;

	return 0;
}