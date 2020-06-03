#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i) { ht = wid = dep = i; }
	ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }
	T vol() const { return ht * wid*dep; }
	bool operator==(const ThreeD<T> &t) const { return (vol() == t.vol()); }
	template <class T> friend	ostream & operator<<(ostream &s, const ThreeD<T> &t);
};

template <class T> class node {
public:
	T value;
	//node<T> * next;
	shared_ptr<node<T>> next;
	//node<T> * previous;
	weak_ptr<node<T>> previous;
	//node<T>() { next = nullptr; previous = nullptr; }
	node<T>(){}
	//node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
	node<T>(T v) { value = v; }
	bool operator==(const node<T> &t) const { return value == t.value; }
};
template <class T> class linked_list {
public:
	//node<T> * first;
	//node<T> * last;
	shared_ptr<node<T>> first, last;
	//linked_list() { first = last = nullptr; }
	linked_list() {}
	linked_list(const initializer_list<T> &V);
	void push_front(T t);
	void push_back(T t);
	bool operator==(const linked_list<T> &L) const;
	linked_list(const linked_list<T> &L); //copy constructor
	//~linked_list();//destructor
	void operator=(const linked_list<T> &L);//L-value operator=
	template <class T> friend ostream & operator<<(ostream &s, const linked_list<T> &L);
};
template <class T> linked_list<T>::linked_list(const initializer_list<T> &V) : linked_list() {
	auto it1 = V.begin();
	while (it1 != V.end()) {
		push_back(*it1);
		it1++;
	}
}
/*
template <class T> linked_list<T>::~linked_list() {  //destructor										
	node<T> * p;
	while (first != nullptr) {
		p = first->next;
		delete first;
		first = p;
	}
}
*/
template <class T> linked_list<T>::linked_list(const linked_list<T> &L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
	//node<T> * p1 = L.first;
	shared_ptr<node<T>> p1 = L.first;
	//while (p1 != nullptr) {
	while (p1) {
		push_back(p1->value);
		p1 = p1->next;
	}
}

template <class T> void linked_list<T>::operator=(const linked_list<T> &L) { //operator= left ref
	//node<T> * p;
	shared_ptr<node<T>> p;
	first.reset();
	last.reset();
	/*
	while (first != nullptr) {
		p = first->next;
		delete first;
		first = p;
	}
	*/
	p = L.first;
	//while (p != nullptr) {
	while (p) {
		push_back(p->value);
		p = p->next;
	}
}

template <class T> void linked_list<T>::push_front(T t) {
	//node<T> * p = new node<T>(t);
	//shared_ptr<node<T>> p(new node<T>(t)); this is OK
	//shared_ptr<node<T>> p = new node<T>(t); Error!
	shared_ptr<node<T>> p = make_shared<node<T>>(t);
	//if (first == nullptr) { first = last = p; }
	if (!first) { first = last = p; }
	else {
		p->next = first;
		first->previous = p;
		first = p;
	}
}

template <class T> void linked_list<T>::push_back(T t)
{
	//node<T> * p = new node<T>(t);
	shared_ptr<node<T>> p = make_shared<node<T>>(t);
	//if (first == nullptr) { first = last = p; }
	if (!first) { first = last = p; }

	else {
		p->previous = last;
		last->next = p;
		last = p;
	}
}

template <class T> bool linked_list<T>::operator==(const linked_list<T> &L) const {
	int n1 = 0, n2 = 0;
	//node<T> * p;
	shared_ptr<node<T>> p;
	p = first;
	//while (p != nullptr) {
	while (p) {
		p = p->next;
		n1++;
	}
	p = L.first;
	//while (p != nullptr) {
	while (p) {
		p = p->next;
		n2++;
	}
	if (n1 != n2) return false;
	//node<T> * p1 = first, *p2 = L.first;
	shared_ptr<node<T>> p1 = first, p2 = L.first;

	//while (p1 != nullptr) {
	while (p1) {
		if (!(p1->value == p2->value)) { return false; }
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}

template <class T> ostream & operator<<(ostream &s, const ThreeD<T> &t) {//ostream & operator<<(ostream &s, ThreeD t) will also work.
	s << "( " << t.ht << ", " << t.wid << ", " << t.dep << " )";
	return s;
}



template <class T> ostream & operator<<(ostream &s, const linked_list<T> &L) {
	//node<T> * p = L.first;
	shared_ptr<node<T>> p = L.first;
	//while (p != nullptr) {
	while (p) {
		s << p->value << " ";
		p = p->next;
	}
	return s;
}

template <class T> ostream & operator<< (ostream &s, const vector<T> & V) {
	s << "[";
	for (size_t i = 0; i < V.size() - 1; i++) {
		s << V[i] << ", ";
	}
	s << V[V.size() - 1] << "]";
	return s;
}


int main() {



	ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);


	linked_list<string>ls_1;
	ls_1.push_front("David");
	ls_1.push_front("John");
	ls_1.push_front("Pat");
	ls_1.push_front("Ben");
	ls_1.push_front("Jeff");
	cout << ls_1 << endl;

	linked_list<string>ls_2;
	ls_2.push_front("Wendy");
	ls_2.push_front("Mary");
	ls_2.push_front("Nancy");
	ls_2.push_front("Jennifer");
	cout << ls_2 << endl;

	ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
	linked_list<ThreeD<double>> LTD1;
	LTD1.push_front(t10);

	LTD1.push_front(t11);
	linked_list<ThreeD<double>> LTD2;
	LTD2.push_front(t13);
	LTD2.push_front(t12);
	LTD2.push_front(t10);
	LTD2.push_front(t11);
	cout << LTD2;

	vector<linked_list<ThreeD<int>>>  V1 = {
		{ { 1,2,3 },{ 4,5,6 } },{ { 11,12,13 },{ 14,15,16 },{ 3,4,5 } },
		{ { 7,8,9 },{ 2,2,3 },{ 4,4,4 } }
	};
	cout << V1 << endl;



	getchar();
	getchar();
	return 0;

}