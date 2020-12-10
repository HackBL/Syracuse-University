#include <iostream>//For now, let's always add these two statements.
using namespace std;//Will explain what they mean later in the semester.


int main() {

	int i;
	i = 100;
	int j{ 1000 };//Declare j to be an int variable and initialize its value to 1000.
	//int j = 1000; //will also work 
	//int j(1000); //will also work

	int* p1;//Declare p1 as a pointer to an int object.
	p1 = &i; //assign address of i to p1. & represents address of an object or variable.
	//Pointer is a variable type  whose value is address
	//Address are 4 bytes in 8 hexadecimal number, such as 45CA679F.
	//Each hexadecimal number has 4 bits (i.e., half a byte).

	cout << i << " " << *p1 << endl;//endl: end of line keyword
	//* operator returns the object whose address is carried in p1.
	// * is referred to as dereference function
	
	i = 200;
	*p1 = 400;//i becomes 400
	cout << p1 << endl;//Will print the address carried by p1, which is the address of variable i

	//When a pointer carries the address of an object, we say this pointer is pointing to this object.

	cin >> i;//program execution will pause here, waiting for you to enter an int value and assign it to i. 
	

	cout << i << endl;

	int k; // the value of j is undefined and cannot be used without assigning value to it.
	//cout <<k <<endl; Error!  the value of j is undefined.
	

	int A[5]{ 10,20,30,40,50 };//Declare an array of 5 int element:  A[0] ... A[4]

	cout << *A << endl;//will print 10
	//for 1-D array, array name without subscript (such as A here) is the address of first element of the array
	//i.e., A the same as &A[0]

	cout << A << "  " << A + 1 << endl;//print &A[0] and address of &A[1]
	//address arithmetic is logical 

	//A[3] will be converted by compiler to *(A+3)

	cout << 3[A] << " "<<A[3] << endl;//3[A] will be converted by *(3+A) and A[3] will be
	//converted to *(A+3).  They will give the same result.


	cout << A[25] << endl; //A[25] will be converted by compiler to *(A+25)
	//No error reported.  C++ compiler does not check out-of-bound error!

	cout << sizeof(int) << " " << sizeof(double) << " " << sizeof(char) <<" "<< sizeof(short) << endl;
	//Print the number of bytes for various data type

	return 0;
}

