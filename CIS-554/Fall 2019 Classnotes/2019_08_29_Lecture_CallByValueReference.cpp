//call by value, call by reference
#include <iostream>
using namespace std;

void F1(int i) { i++; }//call by value
//a new copy is created and used inside the function.
//Modifying the copy inside the function will not
//affect the original object ourside the function

void F2(int &i) { i++; } /// call by reference
//The original object is used inside the function
//No new copy creaed.
//Modifying the object inside the function will
//also modify the original object.

void F3(int A[]) { //F3(int * A) will equally work
	for (int i = 0; i < 5; i++) A[i]++;
}
//array argument will always apply call by reference

int main() {
	int a = 10; 
	F1(a);
	cout << a << endl;
	F2(a);
	cout << a << endl;
	int B[5] = { 0,1,2,3,4 };
	F3(B);
	for (int i = 0; i < 5; i++) {
		cout << B[i] << endl;
	}
	//This is recent new syntax for usig 
	//for loop
	for (int i : B) { cout << i << endl; }


	for (int i : B) { i++; } //call by value
	for (int i : B) { cout << i << endl; }
	//Notice that the values of B do not change.


	for (int& i : B) {i++;} //call by reference
	for (int i : B) { cout << i << endl; }
	//Notice that the values of B have been changed.






	getchar();
	getchar();
	return 0;
}