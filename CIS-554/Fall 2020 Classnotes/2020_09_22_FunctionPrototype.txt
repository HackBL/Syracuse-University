//function structure, iomanip, reference
#include <iostream>
#include <iomanip>
#include <list>

using namespace std;



int f2(int &i); //function prototype
int f1(int &i); 
//int f1(int i) { return i * i; }
//With function prototypes, the sequence of functions is no longer important.

int main() {
	int k{ 10 };
	cout << f2(k)<<endl;

	float f1{ 234.129456 };
	cout << setprecision(2)<<fixed<< f1 << endl;

	//reference

	int a{ 25 };

	int &b {a};//an alternative name b for the same object
	b = 200;
	cout << a << endl;


	const int& c{ k };
	//const int * p1 = &k;
	//*p1 = 400; //error
	//k = 400; ok

	//c = 1000;
	k = 999;


	list<int> L1{ 1,2,3,4,5 };
	auto it{ ++L1.begin() };//it points to 2
	L1.insert(it, 20); //insert a new element 20 right before it  1 20 2 3 4 5
	//L1.insert(L1.begin(), 100); add to the front
	//L1.insert(L1.end(), 2000); add to the end



	return 0;
}

int f2(int& i) {

	return f1(i) * 3;
}

int f1(int &i) { return i * i; }