//priority queue and hash table
#include <iostream>
#include <queue> //allow you to use prioiry_queue
#include <map>
#include <set>//alos support multiset
#include <unordered_map> //Hahs Table
#include <algorithm> //for_each find_if, count_if
#include <string>
#include <iomanip>
#include <tuple>
using namespace std;
int k;//initialized to 0 for global int

template <class T> class my_compare {
public:
	bool operator()(T a, T b) { return a % 3 < b % 3; }
};

int main() {


	//queue<int> q1;// does not support initializer_list { 1, 2, 3, 4, 5 };
	//q1.push(1);
	//q1.push(2);
	//q1.push(3);
	//q1.push(4);
	//q1.push(5);

	//for (auto i : { 6,7,8,9,10 }) { q1.push(i); }
	//while (!q1.empty()) {
	//	cout << q1.front() << " ";
	//	q1.pop();
	//}
	//list<int> l1{ 1,2,3,4,5 };
	//for (auto i : { 6,7,8,9,10 }) { l1.push_back(i); }
	//cout << endl;
	//for (auto i : l1) { cout << i << " "; }
	//// auto &p1=    get<2>((*get<2>(*DB[id]))[semester]);
	////p1->push_back(new course(c));

	//int i = 10;
	//int& j = i;
	////int w;
	////cout << w << endl;//Error! value undefined.
	//cout << endl;
	//vector<int> v1(10);
	//cout << v1[2] << endl;


	map<int, string> M10;
	//is equivalent to 
	//map<int, string, less<int>> M10;  less is default for ascending
	map<int, string, greater<int>> M11;//keys will be sorted in descending order


	priority_queue<int> q1; //max heap; default comparator is less<int>
	for (auto i : { 1,2,3,4,5 }) { q1.push(i); }
	while (!q1.empty()) {
		cout << q1.top() << " ";
		q1.pop();
	}//5 4 3 2 1
	cout << endl;
	priority_queue<int, vector<int>, greater<int >> q2; //min heap    deque
	for (auto i : { 1,2,3,4,5 }) { q2.push(i); }
	while (!q2.empty()) {
		cout << q2.top() << " ";
		q2.pop();
	}//1 2 3 4 5
	cout << endl;
	priority_queue<int, vector<int>, my_compare<int>> q3; //min heap
	for (auto i : { 11,12,13,14,15 }) { q3.push(i); }
	while (!q3.empty()) {
		cout << q3.top() << " ";
		q3.pop();
	} //11 14 13 12 15
	cout << endl;
	multiset<int> s{ 6,2,8,4,7,2,9,2,1, 3,5,2,7,2 };
	for (auto i : s) { cout << i << " "; }
	cout << endl;
	auto it = s.find(2);
	it--;
	cout << *it << endl;
	auto ret = s.equal_range(2);//equal_range also applies to multimap
	//it return a pair of iterators [it1, it2)
	//for all elements that match
	cout << endl;
	for_each(ret.first, ret.second, [](auto i) {cout << i << " "; });



	return 0;
}
