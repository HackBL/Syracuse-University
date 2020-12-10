//functoin pointer and const version of call by reference

#include <iostream>
#include <list>
#include <vector>
#include <functional>

using namespace std;


bool f1(int a, int b) { return a > b; }
bool f2(int a, int b) { return a % 5 < b % 5; }

int max(int a, int b, bool (*func)(int x, int y)) {
	return func(a, b) ? a : b;
}


void f3(const int& i) {//call by reference and write proection inside the function
	cout << i * 5 << endl;
}

void f3(int&& i) {

	cout << i * 100 << endl;
}

int main() {

	bool (*F)(int a, int b);
	//F is an pointer to function which takes two int argument and returns bool
	F = f1;//function name is the starting address of the function in memory

	//F = &f1; also work
	//F = *f1; F = **f1;  F = *********f1; also works
	//F = &&f1; does not work



	cout << f1(5, 8) << " " << F(5, 8) << endl;

	cout << max(5, 8, f1) << endl;
	list<int> L1{ 6,12,8,4,5 };
	L1.sort(f2);
	for (auto i : L1) { cout << i << " "; }
	cout << endl;

	int k{ 10 };
	f3(k);
	//f3(10); will not compile

	f3(50);//const makes it possibe to pass constants to f3


	return 0;
}