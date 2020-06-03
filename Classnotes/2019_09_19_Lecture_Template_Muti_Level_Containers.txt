//template and Multi_leve_Containers
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;

template <class T> class ThreeD {  //template allow us to view
//data type as argument passed to a stucture, such as a class, a funciton, etc.
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = (T)0; }
	ThreeD(T i, T j, T k) { ht = i; wid = j; dep = k; }
	T getVol() { return ht * wid * dep; }
	T getArea();
};
template <class T> T ThreeD<T>::getArea() { //Notice the syntax.
	return 2 * (ht * wid + wid * dep + dep * ht);
}


template <class X> ostream& operator<<(ostream& str, const ThreeD<X>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ") ";
	return str;
}


//Allows cout for list<any object>
template <class X> ostream& operator<<(ostream& str, const list<X>& L) {
	str << "<";
	for (auto i : L) { str << i << " "; }
	str << ">";
	return str;
}

template <class X> ostream& operator<<(ostream& str, const vector<X>& V) {
	str << "< ";
	for (X i : V) { str << i << " "; }
	str << ">";
	return str;
}

template <class X1, class X2> ostream& operator<<(ostream& str, map<X1, X2>& M) {
	str << "{";
	for (auto i : M) { str << i.first << " " << i.second; }
	str << "}";
	return str;
}




int main() {

	ThreeD<int> t1(3, 4, 5), t2(3, 9, 2), t3(1, 5, 6);
	cout << t1 << endl;
	ThreeD<double> t6(3.1, 3.5, 8.8);
	cout << t6 << endl;

	list<ThreeD<int>> L = { t1, t2, t3 };
	cout << L << endl;


	list<vector<int>> L1 = { {1,2,3}, {4,5}, {7,8,9,10} };
	cout << L1 << endl;


	map<int, list<int> > M1 = { {5, {7,8,9}},{11, {4,5,6}}, {4,{3,7,4}} };
	cout << L1 << endl;

	list<map<int, vector<int>>> L2 = { { {3, {7,8,9}}, {4, {5,6,7,8}} }, {{4, {1,2,3,4,5}}, {5, {11,12} }},
		{ {7, {100,200}},{8, {55,66,77,88}}} };

	cout << L2 << endl;




	char c;
	c = getchar();
	c = getchar();
	return 0;
}
