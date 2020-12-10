//template
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <set>
using namespace std;

template <class T> class ThreeD {//<typename T> is also OK
public:
	T ht;
	T wid;
	T dep;
	ThreeD(T i, T j, T k): ht(10*i), wid(10*j), dep (10*k){}
	ThreeD(){}
	T getVol ()  const;
};

template <class T> T ThreeD<T>::getVol() const {
	return ht * wid * dep;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto i : V) { str << i << " "; }
	str << "]";
	return str;
}

template <typename T> ostream& operator<<(ostream& str, const list<T>& L) {
	str << "< ";
	for (auto i : L) { str << i << " "; }
	str << ">";
	return str;
}

template <class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2>& M) {
	str << "{ ";
	for (auto i : M) { str << i.first << " " << i.second << " "; }
	str << "}";
	return str;
}


template <class T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "[ ";
	for (auto i : V) { str << *i << " "; }
	str << "]";
	return str;

}

template <class T> ostream& operator<<(ostream& str, const list<T*>& L) {
	str << "< ";
	for (auto i : L) { str << *i << " "; }
	str << ">";
	return str;

}




int main() {
	vector<int> V1{ 1,2,3,4,5 };//template is a type name parameter; rathn than an object

	ThreeD<int> t1{ 3,4,5 };
	ThreeD<float> t2{ 1.11,2.22,3.33 };

	cout << t1 << " " << t2 << endl;
	vector<int>  V2{ 1, 2, 3, 4, 5 };
	vector<ThreeD<int>> V3{ {1,2,3}, {4,5,6}, {7,8,9} };


	cout << V2 << "  " << V3 << endl;

	vector<list<ThreeD<int>>> V4{ { {1,2,3}, {2,2,2}, {4,3,2}   }, { {1,1,1}, {9,9,9}  } };
	cout << V4 << endl;

	map<int, string> M1{ {5, "Dave"}, {3, "Bob"}, {2, "Mary"} };
	map<int, vector<int>> M2{ { 6, {1,3, 5}    }, { 4, {  2,4,6,8  }    }, { 1, {   3,4,5,6,7  } } };

	cout << M1 << endl;
	cout << M2 << endl;

	vector<int*> V6{ new int{5}, new int{3}, new int{5} };

	cout << V6 << endl;

	ThreeD<int> t5;

	//vector<list< vector<int>*>* > V10;
	//cout << V10 << endl;




	set<int> SS1{ 4,2,7,3,9,4,2 };
	for (auto i : SS1) { cout << i << " "; }
	cout << endl;
	SS1.erase(2);//Erase the element with this value
	auto it1{ SS1.find(9) };//find ia a member function for set and map; it return the address of the matched one; or end() if no match found
	SS1.erase(it1); //Erase the elemnt at this address
	it1 = SS1.find(4); //
	SS1.erase(it1, SS1.end());//[...)  Erase all elements within the range
	for (auto i : SS1) { cout << i << " "; }
	cout << endl;
	//Same erase and find functions for map


	return 0;
}