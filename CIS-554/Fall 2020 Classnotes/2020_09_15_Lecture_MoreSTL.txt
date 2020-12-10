//more stl
#include <iostream>
#include <vector>
#include <list>
#include <map>//map and multimap
#include <stack>
#include <queue> //queue and priority queue
#include <set>  //set and multiset
#include <string>

using namespace std;

bool f1(int i, int j) { return (i+1) % 2 < (j+1) % 2; }
bool f2(int i, int j) { return i % 2 == j % 2; }

int main() {
	vector<int> V1{ 1,2,3,4,5 };
	auto it1{ V1.begin() + 2 };
	//cout << it1 << endl;
	//V1.erase(V1.begin(), V1.begin() + 2); //will delete 1 2  [...)  
	V1.erase(it1);//will erase 3
	//cout << *it1 << endl;  Error!  it1 is only associated with the deleted object.  It is now invalid.

	int* p1 = new int{ 5 };
	delete p1;
	cout << p1 << endl;//no error, but p1 is really invalid.  Should be avoided.
	p1 = new int{ 7 };

	int A[8][8];//values are undefined

	vector<vector<int>> V2(8, vector<int>(8));//values initialized to 0
	V2[3][5] = 11;

	for (auto i : V2) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	vector<int> V3{ 1,2,3,4,5,6 };
	V3.resize(4);
	cout << endl;
	for (int i : V3) { cout << i << " "; }
	cout << endl;
	V3.resize(6);
	for (int i : V3) { cout << i << " "; }
	cout << endl;

	V3.resize(10, 100);
	for (int i : V3) { cout << i << " "; }
	cout << endl;
	//resize is also suuported for list

	vector<int> V4;//size is 0
	V4.assign(5, 2);//assign applies to list as well
	for (int i : V4) { cout << i << " "; }
	cout << endl;

	int k{ 10 };
	//int AA[k]; compiler time error.  array size has to be const

	vector<int> V5(k);

	list<int> L1{ 11,11,2,33,33,14,11,25 };
	L1.unique();//remove all consecutive duplicates except the first one
	for (auto i : L1) { cout << i << " "; }
	cout << endl;

	int A2 [] { 1,2,3,4,5 };

	vector<int> V6{ A2, A2 + 3 };
	for (auto i : V6) { cout << i << " "; }
	cout << endl;
	vector<int> V7(V6.begin(), V6.begin() + 2);
	for (auto i : V7) { cout << i << " "; }
	cout << endl;

	list<int> L3{ 11,2,31, 4,1 };
	L3.sort();
	for (auto i : L3) { cout << i << " "; }
	cout << endl;

	list<int> L4{ 11,2,31, 4,1 };
	L4.sort(f1);
	for (auto i : L4) { cout << i << " "; }
	list<int> L5{ 11,11,21,33,33,14,11,25 };
	L5.unique(f2);//will print 11 14 11; 11 11 21 33 33 are equal according to f2; 11 and 25 are equal
	for (auto i : L5) { cout << i << " "; }


	cout << endl;

	vector<int> V8{ 1,2,3,4,5 };
	V8.clear();//reset size to 0.  It also works for list and map.


	stack<int> S1;//S{1,2,3,4,5} Error stack and queue do not support initializer_list
	S1.push(1);
	S1.push(2);
	S1.push(3);
	S1.push(4);
	while (!S1.empty()) {
		cout << S1.top() << " ";
		S1.pop();
	}
	cout << endl;
	for (auto i : { 1,2,3,4,5,6,7,8 }) { S1.push(i); }
	cout << S1.size() << endl;
	while (!S1.empty()) {//empty() and size() work for all containers
		cout << S1.top() << " ";
		S1.pop();
	}
	cout << endl;


	queue<int> Q1;
	for (int i : {1, 2, 3, 4, 5, 6, 7, 8}) { Q1.push(i); }
	while (!Q1.empty()) {//empty() and size() work for all containers
		cout << Q1.front() << " ";
		Q1.pop();
	}
	cout << endl;

	set<int> SS1{ 8,4,2,1,3, 2, 8 };//sorted and no duplicates

	SS1.insert(6);

	for (auto i : SS1) { cout << i << " "; }
	cout << endl;

	multimap<int, string> M1{ {8, "Bob"}, {5, "Nancy"},{8, "John"} };
	for (auto i : M1) { cout << i.first << " " << i.second << "  "; }
	cout << endl;

	//M1[7] = "Mary";  operator [] is not supported by multimap
	M1.insert({ 4, "Steve" });


	multiset<int> SS2{ 11,2,6,3,2,11,5 };
	for (auto i : SS2) { cout << i << " "; }
	cout << endl;

	priority_queue<int> PR1;//by default max heap
	for (auto i : { 33,4,55,6,89,5, 6,4 }) { PR1.push(i); }

	while (!PR1.empty()) {
		cout << PR1.top() << " ";
		PR1.pop();
	} 

	return 0;
}