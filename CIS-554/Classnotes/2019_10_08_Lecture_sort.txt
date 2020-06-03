\begin{lstlisting}
#include <iostream>
#include <list>
using namespace std;

bool comp1(int a, int b) { return a % 3 < b % 3; }
int main() {
	list<int> L1{ 7,4,3,9,5 };
	L1.sort();
	for (int i : L1) { cout << i << " "; }//will print 3 4 5 7 9
	cout << endl;
	L1.sort(comp1); 
	for (int i : L1) {cout << i << " ";}//will print 3 9 4 7 5
	cin.get();
	return 0;
}