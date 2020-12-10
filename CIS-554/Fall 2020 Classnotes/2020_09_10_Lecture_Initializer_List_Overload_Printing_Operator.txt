//Initializer_list, overload<<, operator overloading
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k):ht(i*10), wid(j*10), dep(k*10){}
	//ThreeD(){}//Once you define a constructor, make sure to also define a default constructor
	ThreeD(const initializer_list<int>& I);

	int getVol() const { return ht * wid * dep; }
	bool operator<(const ThreeD &t) const { return getVol() < t.getVol(); } //allows sort, map

	bool operator==(const ThreeD& t) const { return getVol() == t.getVol(); }//allows find, remove

};
ThreeD::ThreeD(const initializer_list<int>& I) {
	auto p1{ I.begin() };//const int * p1 {I.begin()};
	ht = *p1;
	wid = *(p1+1) ;
	dep = *(p1+2) ;
}
class Node {
public:
	int value;
	Node* next;
	Node(int i):value(i), next(nullptr){}
	Node():next(nullptr){}//value will be initialized to 0
};

class LinkedList {
public:
	Node* head;
	LinkedList() { head = nullptr; }
	LinkedList(const initializer_list<int>& I);

};
LinkedList::LinkedList(const initializer_list<int>& I) {
	head = nullptr;
	auto p1{ I.end()-1 };
	while (p1 != I.begin()-1) {
		Node* p2 = new Node(*p1);
		p2->next = head;
		head = p2;
		p1 = p1 - 1;
	}
}


ostream& operator<<(ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;

}

ostream& operator<<(ostream& str, const list<ThreeD>& L) {
	str << "[ ";
	for (auto i : L) { str << i << " "; }
	str << "]";
	return str;
}

ostream& operator<<(ostream& str, const map<ThreeD, string>& M) {
	str << "{ ";
	for (auto i : M) { str << i.first << " " << i.second << " "; }
	str << "}";
	return str;
}

ostream& operator<<(ostream& str, const LinkedList& L) {
	str << "<< ";
	Node* p = L.head;
	while (p) {
		str << p->value << " ";
		p = p->next;//a common error p++;
	}
	str << ">>";

	return str;
}



int main() {
	//Initializer_list > constructor > default aggregate initialization

	ThreeD t1{ 99,25,2000 };

	vector<int> V1 { 5,6,7,8,9 };


	ThreeD t2{ 2, 4, 6 };

	cout << t2 << endl;


	ThreeD t3(1, 2, 3);//will run constructor
	cout << t3 << endl;

	list<int> L1{ 22,3,44,5,6 };
	L1.sort();
	for (auto i : L1) { cout << i << " "; }
	cout << endl;


	list<ThreeD> L2{ t2, t1, t3 };
	cout << L2 << endl;
	L2.sort();

	cout << L2 << endl;

	L2.remove(t2);//Similarly, when running find ...

	map<ThreeD, string> M1{ {t1, "Dave"}, {t2, "Bob"}, {t3, "Mary"} };
	cout << M1 << endl;


	LinkedList L3{ 11,22,33,44,55 };

	cout << L3 << endl;

	return 0;
}






