#include <iostream>
using namespace std;

class BigArray {
public:
	int size;
	int* pArray;
	BigArray() { size = 0; pArray = nullptr; }
	BigArray(int i) { size = i; pArray = new int[i]; }
	~BigArray();//destructor
	BigArray(const BigArray& b);//copy constructor
	void operator=(const BigArray& b);//Lvalue operator=
	BigArray(BigArray&& b); //move constructor
	void operator=(BigArray&& b); //Rvalue opeartor=
	BigArray get3times();
	void print();
};
BigArray BigArray::get3times() {
	BigArray temp(size);
	for (int i = 0; i < size; i++) {
		temp.pArray[i] = 3* pArray[i];
	}
	cout << "Leave get3times" << endl;
	return temp;
}
BigArray::~BigArray() { delete[] pArray; }//destructor
BigArray::BigArray(const BigArray& b) { //copy constructor
	size = b.size;
	pArray = new int[size];
	for (int i = 0; i < size; i++) {
		pArray[i] = b.pArray[i];
	}
	cout << "Leave copy constructor" << endl;
}
void BigArray::operator=(const BigArray& b) {//Lvalue operator=
	size = b.size;
	delete [] pArray;
	pArray = new int[size];
	for (int i = 0; i < size; i++) { pArray[i] = b.pArray[i]; }
	cout << "Leave Lvalue operator=" << endl;
}
BigArray::BigArray(BigArray&& b) {//move constructor
	size = b.size;
	pArray = b.pArray;
	b.pArray = nullptr;
	cout << "Leave move constructor" << endl;
}

void BigArray::operator=(BigArray&& b) { //Rvalue opeartor=
	size = b.size;
	delete [] pArray;
	pArray = b.pArray;
	b.pArray = nullptr;
	cout << "Leave Rvalue operator=" << endl;
}
void BigArray::print() {
	for (int i = 0; i < size; i++) {
		cout << pArray[i] << " ";
	}
	cout << endl;
}

int main() {
	BigArray b1{ 10 };
	for (int i = 0; i < b1.size; i++) { b1.pArray[i] = i; }
	b1.print();
	BigArray b2{ b1 };     
	b2.print();
	BigArray b3;
	b3 = b1;
	b1.print();
	b3 = b1.get3times();
	b3.print();
	cin.get();
	return 0;
}