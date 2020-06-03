#include <iostream>
#include <list>
using namespace std;
bool comp1(int * p1, int * p2) { return *p1 < *p2; }
int main() {
	list<int*> L1 { new int{22}, new int{11}, new int{6}, new int{4}, new int{2} };
	L1.sort(comp1);
	for (auto i : L1) { cout << *i << " "; }
	cin.get();
	return 0;
}