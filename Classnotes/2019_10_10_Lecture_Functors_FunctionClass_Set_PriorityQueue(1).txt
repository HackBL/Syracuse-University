//Functor, class of function, map, multimap, set, multiset, priority queue, dequeue
#include <iostream>
#include <queue> //for prioirity
#include <vector>
#include <map>
#include <set>
#include <list>
using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i, T j, T k) { ht = i; wid = j; dep = k; }
	T getVol() const { return ht * wid * dep; }
	bool operator<(const ThreeD& t) const { return getVol() < t.getVol(); }
	T operator() (int i, int j, int k) { return i * ht + j * wid + k * dep; }
};

//Class of functions -- each object of this class is a functor (just like a function)
template <class X> class my_comparator {
public:
	bool operator()(const ThreeD<X>& t1, const ThreeD<X>& t2) const { //this const is optional
		return (t1.getVol() > t2.getVol()); //Note the ">" operator.

	}
};

template<class X> class my_comparator1 {
public:

	bool operator()(X value1, X value2) {
		return value1 > value2;
	}

};

template <class X> ostream& operator<<(ostream& str, const ThreeD<X>& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}



int main() {
	//***********************
	//Functors
	ThreeD<int> fn(4, 5, 6);
	int k = 0;
	k = fn(1, 2, 3);//fn looks just like a funciton -- it is a functor
	//an overloaded operator()
	my_comparator1<int> f1;
	if (f1(7, 5)) cout << "True" << endl;
	list<int> L4 = { 11,7,42,6, 3, 12 };
	L4.sort(f1);
	for (int i : L4) { cout << i << " "; }
	cout << endl;


	my_comparator1<int>* p = new my_comparator1<int>;
	if ((*p)(7, 5)) cout << "True" << endl;
	else cout << "false" << endl;
	my_comparator1<int>* p2;
	p2 = &f1;
	my_comparator1<int> comp2;
	list<int> L1{ 7,2,5,1 };
	L1.sort(*p2);//L1.sort(f1);
	for (int i : L1) {
		cout << i << " ";
	}
	cout << endl;


	//**********************
	//maps and multimaps
	//Two ways to sort map elements based on keys
	//first: overload operator< in the class of key
	//second: provide a class of comparator
	ThreeD<int> t1(3, 4, 5), t2(1, 7, 8), t3(2, 3, 9), t4(10, 10, 10), t5(1, 2, 1);
	map<ThreeD<int>, string> M1{ {t4, "Mary"}, {t2, "Steve"}, {t3, "Bob"} };
	M1[t1] = "Nancy";//Add {t1, "Nancy"} to M1.
	M1[t2] = "Dan"; //Overwrite {t2, "Steve"} with {t2, "Dan"}
	for (auto i : M1) { cout << i.first << " " << i.second << " "; }
	cout << endl;
	M1.insert({ t5,"Jennifer" }); //Add {t5, "Jennifer"} to M1
	M1.insert({ t1, "Ben" }); //Will be ignored because the key t1 has existed
	for (auto i : M1) { cout << i.first << " " << i.second << " "; }
	cout << endl;
	map<ThreeD<int>, string, my_comparator<int>> M2{ {t4, "Mary"}, {t2, "Steve"}, { t1,"Nancy" }, {t3, "Bob"} };
	for (auto i : M2) { cout << i.first << " " << i.second << " "; }
	cout << endl;

	//multimaps allow duplicates.
	multimap<ThreeD<int>, string> M3{ {t4, "Mary"}, {t2, "Steve"}, { t1,"Nancy" }, {t3, "Bob"}, {t2,"Jennifer" } };
	//M3[t5] = "Dan"; Error! 
	M3.insert({ t5, "Dan" });
	M3.insert({ t1, "Ben" });
	for (auto i : M3) { cout << i.first << " " << i.second << " "; }
	cout << endl;


	//**********************
	//sets and multisets
	//Sets behave like map, but only single-value elements, rather than pairs
	//Elements will automaticlly sort, just like map
	set<ThreeD<int>> S1{ t1,t2,t3 };
	S1.insert(t4);
	S1.insert(t2);//Will be ignored.
	for (auto i : S1) { cout << i << " "; }
	cout << endl;
	set<ThreeD<int>, my_comparator<int>> S2{ t1,t2,t3,t4 };
	for (auto i : S2) { cout << i << " "; }
	cout << endl;

	//multisets allow duplicates
	multiset<ThreeD<int>> S3{ t1,t2,t3, t3 };
	S3.insert(t1);
	for (auto i : S3) { cout << i << " "; }
	cout << endl;


	//**************************
	//priority_queue
	//heap -- top() returns the max or min, with default being max
	priority_queue<int> pq1;
	pq1.push(11);
	pq1.push(4);
	pq1.push(3);
	pq1.push(8);
	pq1.push(5);
	while (!pq1.empty()) {
		cout << pq1.top() << " ";
		pq1.pop();
	}
	cout << endl;

	priority_queue<int, vector<int>, greater<int>> pq2;
	pq2.push(11);
	pq2.push(4);
	pq2.push(3);
	pq2.push(8);
	pq2.push(5);
	while (!pq2.empty()) {
		cout << pq2.top() << " ";
		pq2.pop();
	}
	cout << endl;

	priority_queue<ThreeD<int>> pq3;
	pq3.push(t1);
	pq3.push(t2);
	pq3.push(t3);
	pq3.push(t4);
	while (!pq3.empty())
	{
		cout << pq3.top();
		pq3.pop();
	}
	cout << endl;

	priority_queue<ThreeD<int>, vector<ThreeD<int>>, my_comparator<int>> pq4;
	//If using user-defined comparator class, you need to specify either vector or deque
	//deque is a "vector" that allows push and pop at both front and back.

	pq4.push(t1);
	pq4.push(t2);
	pq4.push(t3);
	pq4.push(t4);
	while (!pq4.empty())
	{
		cout << pq4.top();
		pq4.pop();
	}


	cin.get();
	return 0;
}