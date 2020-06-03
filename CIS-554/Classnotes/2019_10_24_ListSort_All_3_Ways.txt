#include <iostream>
#include <list>
using namespace std;
bool comp1(int* p1, int* p2) { return *p1 < *p2; }
class my_comp_class {
public:
	bool operator()(int* p1, int* p2) { return *p1 < *p2; }

} comp2;
int main() {
	list<int*> L1{ new int{22}, new int{11}, new int{6}, new int{4}, new int{2} };
	L1.sort(comp1);
	for (auto i : L1) { cout << *i << " "; }
	cout << endl;
	list<int*> L2{ new int{22}, new int{11}, new int{6}, new int{4}, new int{2} };
	L2.sort([](int* p1, int* p2) {return *p1 < *p2; });
	for (auto i : L2) { cout << *i << " "; }
	cout << endl;
	list<int*> L3{ new int{22}, new int{11}, new int{6}, new int{4}, new int{2} };
	L1.sort(comp2);
	for (auto i : L1) { cout << *i << " "; }

	cin.get();
	return 0;
}