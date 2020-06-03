#include <iostream>
using namespace std;
int max(int a, int b, bool(*F)(int a, int b)) {
	cout << "Enter Max" << endl;
	if (F(a, b) == true) return a;
	else return b;
}
bool comp1(int a, int b) { return a > b; }
int main() {

	int a = 99, b = 44;
	cout << max(a, b, comp1) << endl; 

	bool(*p)(int a, int b); //p is a pointer to function.
	p = comp1;//Q points to the function for comp1.
	cout << max(a, b, comp1) << endl;
	cout << max(a, b, p) << endl;


	getchar();
	getchar();
	return 0;
}