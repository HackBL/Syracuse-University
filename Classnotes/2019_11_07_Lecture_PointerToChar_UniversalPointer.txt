#include <iostream>
using namespace std;

int main() {

	int* p1 = new int{ 5 };
	cout << *p1 << " " << p1 << endl;
	char* p2 = new char{ 'A' };
	cout << *p2 << " " << p2 << endl;
	//the printing for p2 will be first 'A', and then maybe something depending on systems.
	//To print the address in p2, use the following:

	cout << *p2 << " " << (void*)p2 << endl;


	//Universal pointers

	void* p3; //p3 is a pointer to anything
	p3 = new int{ 8 };
	p3 = new double{ 3.45 };
	//cout << *p3 << endl;  Error!
	cout << *((double*)p3);

	cin.get();
	return 0;
}