//map and unordered_map (for hash table)
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;
template <typename T> struct ThreeD {
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i, T j, T k) { ht = i; wid = j; dep = k; }
	T getVol() const { return (ht * wid * dep); }
};

template <typename X> ostream& operator<<(ostream& str, const ThreeD<X>& t) {
	str << "[";
	str << t.ht << ", " << t.wid << ", " << t.dep << "]";
	return str;
}
template <typename X> class my_compare_1 { //all "const"'s are needed
public:
	bool operator() (const ThreeD<X>& x1, const ThreeD<X>& x2) const {
		return (x1.getVol() < x2.getVol());
	}
};
template <typename X> class my_hash { //all "const"s are needed
public:
	size_t operator() (const ThreeD<X> &t)   const {
		hash<X> h;
		return (h(t.ht) * h(t.wid) * h(t.dep) % 73); 

	}
};
template <typename X> struct my_equal {
	bool operator()(const ThreeD<X> &t1, const ThreeD<X> &t2    )  const {
		
		
		return (t1.getVol() == t2.getVol());

	}

};

int main() {
	
	map<int, string> M1 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"} };
	for (auto i : M1) { cout << i.first << " " << i.second; }
	cout << endl;
	map<int, string, greater<int>> M2 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"} };
	for (auto i : M2) { cout << i.first << " " << i.second; }
	cout << endl;
	unordered_map<int, string> M3 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"} };
	for (auto i : M3) { cout << i.first << " " << i.second; }
	cout << endl;
	
	ThreeD<int> t1(3, 4, 5), t2(1, 7, 8), t3(2, 3, 9);
	map<ThreeD<int>, int, my_compare_1<int> > M4 = { {t1, 1}, {t3, 3}, {t2,2} };
	for (auto i : M4) { cout << i.first << " " << i.second; }
	cout << endl;
	
	//ThreeD<int> t1(3, 4, 5), t2(1, 7, 8), t3(2, 3, 9);
	unordered_map <ThreeD<int>, int, my_hash<int>, my_equal<int> > M5 = { {t1, 1}, {t3, 3}, {t2,2} };
	for (auto i : M5) { cout << i.first << " " << i.second; }
	cout << endl;
	cin.get();
	return 0;
}

