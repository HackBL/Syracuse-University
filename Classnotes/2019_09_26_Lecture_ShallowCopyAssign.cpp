#include <iostream>
#include <vector>

using namespace std;

class SimpleData {
public:
	int first;
	int * pSecond;
	int* pThird;
	SimpleData() { first = 0; pSecond = pThird = nullptr; }
	SimpleData(int i1, int i2, int i3) { first = i1; pSecond = new int{ i2 }; pThird = new int{ i3 }; }
	void print() { cout << first << " " << *pSecond <<" "<< *pThird<< endl; }
};

int main() {
	SimpleData s1(2, 5, 8);
	s1.print(); //Will print 2 5 8
	SimpleData s2 = {s1}; //copy -- will call copy constructor
	//decard s2 and immediately copy values from s1 to s2
	//These three forms are also correct: SimpleData s2 = {s1}; SimpleData s2(s1);  SimpleData s2=s1;
	
	s2.print(); //Will print 2 5 8
	*(s1.pSecond) = 50;
	*(s2.pThird) = 80;
	s1.print();  //Will print 2 50 80
	s2.print();  //Will print 2 50 80

	SimpleData s3(4, 5, 6), s4;
	s3.print();  //Will print 4 5 6
	s4 = s3; //assign -- will call operator=
	s4.print(); //Will print 4 5 6
	*s3.pSecond = 50;
	*s4.pThird = 60;
	s3.print();  //Will print 4 50 60
	s4.print();  //Will print 4 50 60

	cin.get();
	return 0;
}