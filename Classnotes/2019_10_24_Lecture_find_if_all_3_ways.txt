#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

bool comp1(int a, int b) { return a % 3 < b % 3; }
bool my_pred(int i) { return (i % 3 == 2) && (i % 2 == 0); }
class my_pred1_class {
public:
	bool operator()(int i){ return (i % 3 == 2) && (i % 2 == 0); }
}my_pred1;
int main() {
	list<int> L1{ 7, 4, 3, 8, 5 };
	auto it = find_if(L1.begin(), L1.end(), my_pred);
	if (it != L1.end()) cout << *it << endl;  //Will print 8
	it = find_if(L1.begin(), L1.end(), [](int i) {return (i % 3 == 2) && (i % 2 == 0); });
	if (it != L1.end()) cout << *it << endl;  //Will print 8
	it = find_if(L1.begin(), L1.end(), my_pred1);//functor
	if (it != L1.end()) cout << *it << endl;  //Will print 8
	vector<int> V1{ 7, 4, 3, 8, 5 };
	auto it1 = find_if(V1.begin(), V1.end(), my_pred);
	if (it1 != V1.end()) cout << *it1 << endl;  //Will print 8
	cin.get();
	return 0;
}