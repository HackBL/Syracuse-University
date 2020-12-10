//template
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

using namespace std;
/*
class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	int getVol() { return ht * wid * dep; }
};
*/

template <class T> class ThreeD {  //template allow us to view
//data type as argument passed to a stucture, such as a class, a funciton, etc.
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = (T) 0; }
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


int main() {

	ThreeD<int> t1(3, 4, 5), t2(3, 9, 2), t3(1, 5, 6);
	cout << t1 << endl;
	ThreeD<float> t6(3.1, 3.5, 8.8);
	cout << t6 << endl;

	list<ThreeD<int>> L = { t1, t2, t3 };
	cout << L << endl;


	char c1;
	c1 = getchar();
	c1 = getchar();
	return 0;
}
