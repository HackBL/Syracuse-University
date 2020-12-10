
//functor, lambada , function pointer -- callables
#include <iostream>
#include <functional> //function
#include <algorithm> //find_if, count_if
#include <typeinfo>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <set>

using namespace std;


class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() :ht(0), wid(0), dep(0) {}
	ThreeD(int i, int j, int k) : ht(i), wid(j), dep(k) {}
	int getVol() const { return ht * wid * dep; }
	bool operator<(const ThreeD& t) const { return getVol() < t.getVol(); }


};



class myCompare {
public:
	string s2;
	myCompare(string s) : s2(s) {}
	myCompare() {}
	bool operator()(int a, int b) { return a < b; }
	bool operator()(string s1) { return s1 < s2; }
	bool operator()(const ThreeD& t1, const ThreeD& t2) const {
		return (t1.ht + t1.wid + t1.dep < t2.ht + t2.wid + t2.dep);
	}
	bool operator()(const vector<int*>& V1, const vector<int*>& V2) const {
		int sum1{ 0 }, sum2{ 0 };
		for (auto i : V1) { sum1 += *i; };
		for (auto i : V2) { sum2 += *i; };
		return sum1 < sum2;

	}

};


int min(int a, int b, function<bool(int, int)> func) {//any callable
	return func(a, b) ? a : b;
}

template <class T>  int Min(int a, int b, T func) {//any callable

	return func(a, b) ? a : b;
}


int MIN(int a, int b, bool (*func)(int a, int b)) { return a < b; }//good only for regular function and 
																   //lambdas that do not capture


bool f1(int a, int b) { return  a < b; }

ostream& operator<<(ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

template <class T1, class T2> ostream& operator<<(ostream& str, const map<T1, T2>& M) {
	str << "{ ";
	for (auto i : M) { str << i.first << " " << i.second << " "; }
	str << "}";
	return str;
}

template <class T1, class T2, class T3> ostream& operator<<(ostream& str, const map<T1, T2, T3>& M) {
	str << "{ ";
	for (auto i : M) { str << i.first << " " << i.second << " "; }
	str << "}";
	return str;
}

template <class T> ostream& operator<<(ostream& str, const set<T, myCompare>& S);
template <class T> ostream& operator<<(ostream& str, const vector<T*>& V);

int main() {

	cout << f1(3, 5) << " " << [](int a, int b) {return a < b; }(3, 5) << endl;
	auto f2 = [](int a, int b) {return a < b; };
	cout << f1(3, 5) << " " << f2(3, 5) << endl;
	myCompare f3;
	cout << f1(3, 5) << " " << [](int a, int b) {return a < b; }(3, 5) << " " << f3(3, 5) << endl;
	//function is stateless
	//lambda and functor are with state
	myCompare f4("bob");
	cout << f4("Dave") << endl;//functor can carry internal states by accessing data members of the class
	string s{ "Dan" };
	cout << [s](string s1) {return s1 > s; }("Steve") << endl;//lambda can states by captureing
	//lambda:   [capture clause](argument list) {function body}

	cout << min(3, 5, f1) << " " << min(3, 5, [](int a, int b) { return a < b; }) << " " << min(3, 5, f3) << endl;

	cout << Min(3, 5, f1) << " " << Min(3, 5, [](int a, int b) { return a < b; }) << endl;// " " << Min(3, 5, f3) << endl;


	cout << MIN(3, 5, f1) << " " << MIN(3, 5, [](int a, int b) { return a < b; }) << endl;
	//" " << MIN(3, 5, f3) << endl;
	//lambba cna be converted to function pointer only if it does not capture.


	ThreeD t1{ 3,4,5 }, t2{ 4,4, 4 }, t3{ 12, 1, 1 };

	map<ThreeD, int> M1{ {t1, 1}, {t2, 2}, {t3,3} };
	cout << M1 << endl;
	map<ThreeD, int, myCompare> M2{ {t1, 1}, {t2, 2}, {t3,3} };
	cout << M2 << endl;
	set<vector<int*>, myCompare> S1{ {new int {5}, new int {3}}, {new int {11}, new int {7}, new int {2}}, {new int {4}, new int {23}, new int {7}} };
	cout << S1 << endl;

	set<int, less<int>> M3{ 3,2,5,1,6,4 };
	for (auto i : M3) { cout << i << " "; };
	cout << endl;

	set<int, greater<int>> M4{ 3,2,5,1,6,4 };
	for (auto i : M4) { cout << i << " "; };
	cout << endl;

	return 0;
}
template <class T> ostream& operator<<(ostream& str, const set<T, myCompare>& S) {
	str << "< ";
	for (auto i : S) { str << i << " "; }
	str << ">";
	return str;
}
template <class T> ostream& operator<<(ostream& str, const vector<T*>& V) {
	str << "[ ";
	for (auto i : V) { str << *i << " "; }
	str << "]";
	return str;

}