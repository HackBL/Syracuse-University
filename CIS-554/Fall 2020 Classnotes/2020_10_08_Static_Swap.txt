//static
#include <iostream>
using namespace std;

//Midterm exam will be on Saturday (10/17) 10:30am-12:00pm (Syracuse time)

class myClass {
public:
	static int Num_Objects;
	myClass() {
		++Num_Objects;
	}

	static int getNumObjects() {
		return Num_Objects;
	}
};
int myClass::Num_Objects{ 0 };


void f1() {
	static int Num_Func_Calls{ 0 };//assigned to 0 only performed the first time
	//this function is called
	Num_Func_Calls++;
	cout << Num_Func_Calls << endl;
}



int main() {

	cout << myClass::Num_Objects << endl;

	cout << myClass::getNumObjects() << endl;
	myClass m1, m2, m3;
	cout << myClass::Num_Objects << endl;
	cout << myClass::getNumObjects() << endl;

	cout << m1.Num_Objects << endl;
	cout << m1.getNumObjects() << endl;

	f1();
	f1();
	f1();


	int x1{ 10 }, x2{ 20 };
	cout << x1 << " " << x2 << endl;
	swap(x1, x2);
	cout << x1 << " " << x2 << endl;

	int* p1 = new int{ 100 };
	int* p2 = new int{ 200 };
	swap(p1, p2);
	cout << *p1 << " " << *p2 << endl;

	int y1{ 30 }, y2{ 40 };
	int& r1{ y1 };
	int& r2{ y2 };
	swap(r1, r2);
	cout << r1 << " " << r2 << endl;

	return 0;
}





