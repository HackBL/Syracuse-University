#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
void add3(int& i) { i += 3; }
class add3_class {
public:
	void operator()(int& i) { i += 3; }
} add3_1;
int main() {
	list<int> L1{ 6,2,7,9,4 };
	for_each(L1.begin(), L1.end(), add3);
	for (auto i : L1) { cout << i << " "; }
	cout << endl;
	list<int> L2{ 6,2,7,9,4 };
	for_each(L2.begin(), L2.end(), [](int& i) {i += 3; });
	for (auto i : L2) { cout << i << " "; }
	cout << endl;
	list<int> L3{ 6,2,7,9,4 };
	for_each(L3.begin(), L3.end(), add3_1);
	for (auto i : L3) { cout << i << " "; }
	cout << endl;

	list<int> L4{ 6,2,7,9,4 };
	for (auto& i : L4) { i += 3; }
	for (auto i : L4) { cout << i << " "; }
	cout << endl;
	
	int A[]{ 4,5,6,7,8,9 };
	for_each(A, A + 6, add3);
	for (auto i : A) { cout << i << " "; }
	cin.get();
	return 0;
}