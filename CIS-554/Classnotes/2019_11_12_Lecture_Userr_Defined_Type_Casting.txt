#include <iostream>
#include <string>
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	operator int() { return ht + wid + dep; }
	operator string() { return "This is funny!"; }

};

int main() {

	short s = 21;
	int i = (int) s;//
	int j = static_cast<int>(s);

	short* p1 = new short(11);
	short* p2 = new short(12);
	int* p3 = (int*)p1;//no error reported
	//int* p4 = static_cast<int*>(p1);
	//static_cast is similar to raw type casting
	//that C++ inherits from C
	//However, it is safer.
	//static_cast is only performed during compile time


	ThreeD t1{ 3,4,5 };
	int m = t1;
	cout << m << endl;
	cout << static_cast<string>(t1) << endl;
	

	//type casting during run time
	//dynamic_cast




	cin.get();
	return 0;

}