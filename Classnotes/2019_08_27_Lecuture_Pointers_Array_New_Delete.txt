#include <iostream>
using namespace std;

int main() {
	//cin and cout: console input and console output
	/*
	int i, j;
	cout << " input i and j" << endl;
	cin >> i >> j;

	cout << "i = " << i << " j = " << j << endl;

	char c;
	cin >> c;
	*/
	//Pointers -- a type of variables whose values are addresses
	int k = 10, q = 15;
	int* p1; //p1 is a pointer which carries the address of an int object
	p1 = &k; //assign the address of k to p1
	cout << *p1 << " " << k << endl;
	// * is a function which returns the value stored at the address;

	//array
	int A[5] = { 1,2,3,4,5 };

	cout << *A << endl;//array name without index is the address of its first element
	//A is the same as &A[0]
	//  *A is the same as A[0]
	//  *A is also the same as *(&A[0]) 

	cout << *(A + 2) << endl; //the same as cout << A[2]
	cout << 2[A] << endl;//No error!  Both A[2] and 2[A] will be converted to *(A+2)
	//address arithmathcs are logical rather than physical

	cout << A[8] << endl;//c++ won't check for out-of_bound error
	//starting A, it will move 8 logical positions and obtain whatever stored in the locaiton

	//dynamic memory allocation

	int* p2;
	p2 = new int(100);//new is a function which asks system to create a storage space and returns 
	//the address of this memory space
	//The initial value of the int object will be 100.
	//Whatever objects created by new are global objects.


	delete p2;//Return the object pointed by p2 to the system
	p2 = A + 1; //The pointed itself is not deleted and can still be used.

	//delete p2;  will cause error becaise A[1] cannot be deleted; it is not created dynamically by new
	//Only objects created by new can be deleted

	//new an array
	p2 = new int[10]; //Dynamically create an array of 10 int objects and returns
	//the address of the first element of the array to p2.


	p2[3] = 25;
	cout << *(p2 + 3) << " " << p2[3] << endl;    //*(p2+3) is the same as p2[3]
	int i1 = *(p2 + 3);//i1 will be 25
	*(p2 + 3) = 10000;

	delete [] p2;//delete the entire array
	//Dynamically created array should be deleted entirely rather than partially
	//Partially deleting a dynamically created array can cause unsafe behavior and should be avoided

	
	//Delete [] p2 will delete the array pointed by p2.  P2 itself is not deleted and can still be used.
	p2 = A;



	getchar();//These two getchar() will keep the console output.
	getchar();
	return 0;
}


