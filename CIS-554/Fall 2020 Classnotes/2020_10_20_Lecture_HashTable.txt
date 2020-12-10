#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;
template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD():ht(0), wid(0), dep(0){}
	ThreeD(T i, T j, T k): ht(i), wid(j), dep(k){}
	T getVol() const { return ht * wid * dep; }
	T getSurface() const { return 2 * (ht * wid + wid * dep + dep * ht); }


};

template <class T> class my_compare {
public:
	bool operator()(const ThreeD<T>& t1, const ThreeD<T>& t2) const {return t1.getSurface() < t2.getSurface(); }


};

template <class T> class my_equal_to {
public:
	bool operator()(const ThreeD<T>& t1, const ThreeD<T>& t2) const { return t1.getSurface() == t2.getSurface(); }


};

template <class T> class my_hash {
public:

	size_t operator() (const ThreeD<T>& t1) const {
	hash<int> h;
	return h(t1.getSurface() * t1.getVol());
	}
	
	

};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {

	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}


int main() {

	map<int, int> M1{ {5, 20}, {4, 100}, {3, 40}, {6, 100}, {5, 1000} };
	for (auto i : M1) { cout << i.first << " " << i.second << "   "; }
	cout << endl;
	unordered_map<int, int> M2{ {5, 20}, {4, 100}, {3, 40}, {6, 100}, {5, 1000} };
	for (auto i : M2) { cout << i.first << " " << i.second << "   "; }
	cout << endl;
	ThreeD<int> t1(6, 4, 3), t2(9, 8, 4), t3(1, 2, 3);
	map<ThreeD<int>, int, my_compare<int>> M3{ {t1, 11},{t2, 12},{t3, 13},{t1, 111} };
	for (auto i : M3) { cout << i.first << " " << i.second << "   "; }
	cout << endl;

	unordered_map<ThreeD<int>, int, my_hash<int>, my_equal_to<int>> M4{ {t1, 11},{t2, 12},{t3, 13},{t1, 111} };
	for (auto i : M4) { cout << i.first << " " << i.second << "   "; }
	cout << endl;

	unordered_multimap<ThreeD<int>, int, my_hash<int>, my_equal_to<int>> M5{ {t1, 11},{t2, 12},{t3, 13},{t1, 111} };
	for (auto i : M5) { cout << i.first << " " << i.second << "   "; }
	cout << endl;

	//auto ret = M5.equal_range(t1, my_equal_to<int>());


	return 0;
}