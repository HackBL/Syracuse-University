//2-D array, new, delete, class, linked list, call by value vs call by reference
//pass by value vs pass by reference
#include <iostream>
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
};
class ThreeD2{
public:
	int ht;//data member
	int wid;
	int dep;
	//constructor for user-defined initialization
	//constructor has a higher precedence than the default aggregate initialization
	ThreeD2(int i, int j, int k) { ht = 10 * i; wid = 2 * j; dep = k; }
	//constructor is a function whose name is the same as class name, and 
	//no return value specified.
	//Constructor will always be used by compiler.
	//Constructor cannot be explicitly invoked by users' code.


	//Alternatively,we can write it as
	//ThreeD2(int i, int j, int k): ht(10*i), wid(2*j), dep(k){}
};

class Node {
public:
	int value;
	Node* next;
	Node(int i) { value = i; next = nullptr; }
	Node() { next = nullptr; } //Default constructor --- not including argument.
	//We can overload constructor, by having difference in parameter stucture
};

void f1(int i) { i++; }//call by value or pass by value
//A new copy of argument is created and used under the name i inside the function
//Modifying the value of i does not affect the original copy outside the function,


void f2(int& i) { i++; } //call by reference or pass by reference
//the original copy outside the function is being actually used inside the function.
//Modifying it inside the function will actually modify the original copy outside the function
//There is only one copy inside and outside of the function.


int main() {

	int A[3][5]{ {1,2,3,4,5},{6,7,8,9,10}, {11,12,13,14,15} };

	cout << A[1][3] << " " << *(A[1] + 3) << " " << *(*(A + 1) + 3) << " "
		<< *(&A[0][0] + 5 * 1 + 3) << endl;

	//Dynamic memory management (dynamic memory allocation and deallocation)

	int *p1 = new int{ 10 };//int *p; int* p; int * p;all three are the same
	//new is a function that requests system to allocate a stroge space and return the address
	//of the storage space.

	delete p1;//Delete the object pointed by p1, and return the storage space to system.
	//Delete will delete object pointed by pointer, the pointer can still be used.
	//Only dynamic object can be deleted.

	int k{ 100 }; //k is statically created, and can't be deleted
	p1 = &k;//
	//delete p1;  Error! the objected pointed by p1 is a static object, and can't be deleted.


	int* p2 = new int[5]{ 2,3,4,5,6 };

	cout << *p2 << *(p2 + 1) << p2[2] << endl; //will print 2,3,4
	//p2[2] will be converted by compiler to  *(p2+2)

	delete [] p2;
	//Delete the whole dynamic array
	//delete p2 (without the []); will lead to unpredictable problem.
	//For dynamic arrays, either delete the whole array or nothing.
	//Do not delete a dynamic array partially.


	char c1{ 't' };

	ThreeD t1{ 3,4,5 };//using aggregate initializaiton
	ThreeD2 t2{ 5, 6, 7 };
	cout << t2.ht << endl;

	ThreeD2 * p5{ &t2 };
	(*p5).ht = 20;//the same as t2.ht = 20;
	p5->ht = 25;//the same as (*p5).ht = 25;
	//-> will be pronounced as arrow in this class.
	//I used to pronounce it as "select" in prior semesters.
	


	int w{ 10 };
	int* p10 = &w;
	w = 20;
	*p10 = 20;//*p10 and w are the same.


	//Linked List
	Node* head{ nullptr };//Node * head = nullptr; Node * head(nullptr); also OK.

	for (int i = 0; i < 5; i++) {
		Node* p1 = new Node(10 * i);
		p1->next = head;
		head = p1;
	}
	
	cout << endl;
	Node* p3 = head;
	while (p3) {
		cout << p3->value << " ";
		p3 = p3->next;
	}

	//Call/pass by value
	int x{ 1 };
	f1(x);
	cout << endl;
	cout << x << endl;//will print 1

	//Call/pass by reference
	f2(x);
	cout << x << endl;//will print 2.



	return 0;
}