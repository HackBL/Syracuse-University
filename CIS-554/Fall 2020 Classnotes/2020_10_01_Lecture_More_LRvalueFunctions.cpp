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

	LinkedList & operator=(const LinkedList& L);//Lvalue operator=
	~LinkedList();//destructor  -- the defualt one will only do shallow delete
	/*
	Only in 2 cases will destructor be called:
	1. when an object is going out of scope
	2. When when delete function is called
	*/
	LinkedList ThreeTimes();
	LinkedList(LinkedList&& L);//move constructor
	LinkedList & operator=(LinkedList&& L);//Rvalue operator=
};

LinkedList & LinkedList::operator=(LinkedList&& L) {
	while (head) {
		Node* p3{ head->next };
		delete head;
		head = p3;
	}
	head = L.head;
	L.head = nullptr;
	cout << "move assignment" << endl;//Rvalue operator=
	return *this;
}

LinkedList::LinkedList(LinkedList&& L) :LinkedList() {
	head = L.head;
	L.head = nullptr;
	cout << "move constructor" << endl;
}

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
LinkedList & LinkedList::operator=(const LinkedList& L) {
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
	cout << "copy assignment" << endl;//Lvalue operator=
	return *this;
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

int f1(int& i) {//return value of i; if i= 25, then it return value 25

	return i;
}
int & f2(int& i) { //return object i itself
	return i;
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
	//LinkedList L2 = L1;//copy constructor
	L2.head->value = 100;
	cout << L1 << endl;
	LinkedList L3;
	L3 = L1;//  L3.operator=(L1); operator assignment
	//L1 is Lvalue
	L3.head->value = 500;
	cout << L1 << endl;
	LinkedList L4;
	//LinkedList L4 = L1.ThreeTimes();//copy, not assignment
	L4 = L1.ThreeTimes();//assignment
	//compiler will change it to
	//L4.opertor=(L1.ThreeTimes());
	cout << L4 << endl;
	cout << " ********************" << endl;
	//L2 = L1;
	L4 = L3 = L2 = move(L1);

	//L3.operator=(L2.operator=(L1));//L1: Lvalue; return *this -- return value of L2
	//L4.operator=(L3.operator=(L2.operator=(L1)));

	/*L1.head->value = 222;
	L2.head->value = 333;
	L3.head->value = 444;
	L4.head->value = 555;*/

	cout << L4 << endl;
	cout << L3 << endl;
	cout << L2 << endl;
	cout << L1 << endl;



	return 0;
}