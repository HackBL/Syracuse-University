
//"Three files" are in this file
//They are: Source.cpp  Header.h   Source1.cpp 

//Source.cpp
#include <iostream>
#include "Header.h" //header files will be copied to files that include them during compile time
//external .cpp file will be compiled separately into object files
//Objects files will then be combined by linker to form an executable.

//Such a concept of exteranl .cpp files allows incremental compilation.
//It will speed up compile time for large projects.



//no need to include .cpp file
using namespace std;

extern int f1(int i);//prototype is needed; keyword extern is optional for function

extern int i; //prototype is needed; 


int main() {

	cout << i << endl;

	cout << f1(20) << endl;

	myClass1 m1{ 3,4 };//aggregate initialization
	cout << m1.f() << endl;

	return 0;
}


//Header.h
//header file is for normally declaring prototypes of functionsand classes

class myClass1 {
public:
	int A;
	int B;
	int f();// { return A * B + B * 100 + A + 5000; }
};

int f1(int i);






//Source1.cpp

#include "Header.h"
//#include <iostream>
//using namespace std;
int i{ 10 };

int f1(int i) { return i * i * i; }

int myClass1::f() {   return A * B + B * 100 + A + 5000; }


