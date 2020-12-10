//Lvalue and Rvalue

/*
	Any expressions or entity that can ONLY be placed on the
	right side of an assignment statement is called an Rvalue;
	otherwise, it is an Lvalue

	i = j+1;//j+1 is Rvalue
	L4 = L1.ThreeTimes();//L1.ThreeTimes() is Rvalue
	Compiler will change it to
	L4.operator=(L1.ThreeTimes());
	i, L4 are both Lvalue
	int A[3] {1,2,3};

	A[1] = 2;//2 is Rvalue, A[1] is Lvalue
	i = A[2];//i is L value
	
*/

#include <iostream>
using namespace std;

void f1(int& i) {//Lvalue reference
	cout << i *2 << endl;
}


void f1(int&& i) {//Rvalue reference &&

	cout << i * 10 << endl;
}
int main() {

	int k{ 10 };

	f1(k);//K: Lvalue  
	f1(k + 1); //k+1: Rvalue
	f1(move(k));  //Rvalue
	//move change an Lvalue entity to Rvalue entiry

	//k + 1 = 10;
	


	return 0;
}