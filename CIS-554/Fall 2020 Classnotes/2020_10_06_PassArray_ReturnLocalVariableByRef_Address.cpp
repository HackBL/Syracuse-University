#include <iostream>
#include <vector>

using namespace std;

int f1(int B[], int size ) {
	//compiler will change it to
	//int f1(int* B, int size) {;//this is more accurate
	int sum{ 0 };
	for (int i = 0; i < size; ++i) {
		sum += B[i];

		B[i] += 10;
	}
	
	return  sum;
}

void f2(int* p1) {

	*p1 = 25;
	int* p2 = new int{ 500 };
	//all dynamic objects created by function new are global objects with no scopes
}

int& f3() {
	int x{ 33 };
	cout << "&x= " << &x << " " << x << endl;
	return x;//void doing this.
	//We should avoid returning local variables by reference
}


int& f4(vector<int> &V) {
	return V[2];

}

int *  f5() {
	int q{ 300 };
	cout << "&q " << &q << q << endl;
	return &q;//Avoid this;
	//we should avoid return address of local variables
}

int main() {


	int A[] { 1,2,3,4,5 };


	int k{ 25 };
	cout << sizeof(k) << endl;//return #bytes
	cout << sizeof(A) / sizeof(int) << endl;
	cout << f1(A, sizeof(A) / sizeof(int))<< endl;//A is the address of the first element of array 

	for (int i = 0; i < (sizeof(A) / sizeof(int)); ++i) {
		cout << A[i] << " ";
	}

	int* p = new int{ 100 };

	f2(p);
	cout << endl;
	cout << *p << endl;

	int& y{ f3() };//ref is for alias

	cout << "&y= " << &y << " " << y << endl;

	y = 400;
	cout << &y << " " << y << endl;

	vector<int> vec{ 1,2,3,4,5 };
	int& w{ f4(vec) };//vec[2]

	f3() = 4;


	int* p3 = f5();
	cout << p3 << " " << *p3 << endl;
	*p3 = 600;
	return 0;
}