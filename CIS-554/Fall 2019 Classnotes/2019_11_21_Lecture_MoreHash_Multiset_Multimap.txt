//map and unordered_map (for hash table)
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
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
	size_t operator() (const ThreeD<X>& t)   const {
		hash<X> h;
		return (h(t.ht) * h(t.wid) * h(t.dep) % 73);

	}
};
template <typename X> struct my_equal {
	bool operator()(const ThreeD<X>& t1, const ThreeD<X>& t2)  const {
		return (t1.getVol() == t2.getVol());
	}

};

int main() {
	set<int>S1{ 5,7,4,2,3,5,3,9,0 };
	S1.insert(8);
	for (auto i : S1) { cout << i << " "; } //will 0 2 3 4 5 7 8 9

	cout << endl;

	multiset<int> S2{ 5,7,4,2,3,5,3,9,0 };
	S2.insert(8);
	for (auto i : S2) { cout << i << " "; } //will 0 2 3 3  4 5 5 7 8 9 
	cout << endl;



	map<int, string> M1 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"} };
	M1.insert({ 8, "Mary" });
	M1.insert({ 5, "Bob" });
	for (auto i : M1) { cout << i.first << " " << i.second << " "; }
	cout << endl;

	multimap<int, string> M2 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"}, {6,"Bob"} };
	M2.insert({ 6,"John" });
	for (auto i : M2) { cout << i.first << " " << i.second << " "; }
	cout << endl;


	map<int, string, greater<int>> M3 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"} };
	for (auto i : M3) { cout << i.first << " " << i.second; }
	cout << endl;


	unordered_map<int, string> M4 = { {6, "Dave"}, {8, "Sanjay"}, {4, "Nancy"},{3, "Ling"} };
	for (auto i : M4) { cout << i.first << " " << i.second; }
	cout << endl;

	ThreeD<int> t1(3, 4, 5), t2(1, 7, 8), t3(2, 3, 9);
	map<ThreeD<int>, int, my_compare_1<int> > M5 = { {t1, 1}, {t3, 3}, {t2,2} };
	for (auto i : M5) { cout << i.first << " " << i.second; }
	cout << endl;


	unordered_map <ThreeD<int>, int, my_hash<int>, my_equal<int> > M6 = { {t1, 1}, {t3, 3}, {t2,2} };
	for (auto i : M6) { cout << i.first << " " << i.second; }
	cout << endl;
	cout << M6[t2] << endl;
	M5[t2] = 100;
	//The above statement is equivalent to
	//M5.insert({t2,100});
	cout << M6[t2] << endl;

	unordered_multimap<int, string> M7{ {3, "Dave"}, {2, "Steve"},{100, "John"}, {2, "Bob"} , {2, "Nancy"} };
	M7.insert({ 2, "John" });
	cout << (M7.find(2)->first) << M7.find(2)->second << endl;



	auto ret = M7.equal_range(2); //function equal_range can apply to multimap, multiset, and
					  //unordered_multimap
	/*
	ret is a pair of iterators. {iterator1, iterator2}
	The two iterators set the range of all elements whose key is 2.
	Remember that iterator1 is the begining of the range, and iterator2 is the one past the
	last of the range.
	*/
	for_each(ret.first, ret.second, [](auto i) {cout << i.first << " " << i.second << " "; });
	//This for_each cannot be replaced with for.

	cout << endl;
	for (auto i : M7) { cout << i.first << " " << i.second << " "; }


	//Use default hash<string> and equal_to<string>
	string str1{ "C++ programming is not object-oriented." }, str2{ "Pointer operation is easy." },
		str3{ "Smart pointers can avoid memory leak." };
	unordered_map<string, string>M8{ {str3, "Yes!"}, { str1, "No!" }, { str2, "No!" } };
	cout << endl;
	cout << M8[str2] << endl;
	cout << M8.find(str2)->first << " " << M8.find(str2)->second << " " << endl;

	cin.get();
	return 0;
}

/*
Output:
0 2 3 4 5 7 8 9
0 2 3 3 4 5 5 7 8 9
3 Ling 4 Nancy 5 Bob 6 Dave 8 Sanjay
3 Ling 4 Nancy 6 Dave 6 Bob 6 John 8 Sanjay
8 Sanjay6 Dave4 Nancy3 Ling
6 Dave8 Sanjay4 Nancy3 Ling
[2, 3, 9] 3[1, 7, 8] 2[3, 4, 5] 1
[3, 4, 5] 1[2, 3, 9] 3[1, 7, 8] 2
2
2
2Steve
2 Steve 2 Bob 2 Nancy 2 John
3 Dave 2 Steve 2 Bob 2 Nancy 2 John 100 John
No!
Pointer operation is easy. No!

*/

