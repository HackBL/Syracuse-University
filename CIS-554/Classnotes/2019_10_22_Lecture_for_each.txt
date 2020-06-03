#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
void add3(int& i) { i += 3; }
int main() {
	list<int> L1{ 6,2,7,9,4};
	for_each(L1.begin(), L1.end(), add3);
	for (auto i : L1) { cout << i << " "; }
	cout << endl;
	int A[]{ 4,5,6,7,8,9 };
	for_each(A, A + 6, add3);
	for (auto i : A) { cout << i << " "; }
	cin.get();
	return 0;
}