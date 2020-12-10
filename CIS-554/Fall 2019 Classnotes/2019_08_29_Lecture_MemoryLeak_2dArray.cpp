#include <iostream>
using namespace std;


int main() {

	//Initialize values when using new

	int* p1 = new int{ 5 };//(5) will also work
	int j1 = 10;
	p1 = &j1;//will cause memory leak

	int* p2 = new int[5] { 1,2,3,4,5 };

	//delete p2;  will cause memory leak
	delete[] p2;
	p2 = &j1;

	int B[100];
	//you can't delete any part of B, which is not created
	//dynamically.

	int A[3][4] = { {0,1,2,3}, {4,5,6,7},{8,9,10,11} };

	cout << A[1][2] << endl;
	cout << *(*(A + 1) + 2) << endl;
	cout << *(A[1] + 2) << endl;
	cout << *(&A[0][0] + 4 * 1 + 2) << endl;

	//See the diagram uploaded to blackboard


	getchar();
	getchar();
	return 0;
}