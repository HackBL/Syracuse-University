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
	operator int() { return ht + wid + dep; } //User define type casting -- from ThreeD to int
	operator string() { return "This is funny!"; } //User define type casting -- from ThreeD to string

	//Note the special syntax for user-defined type casting

};

int main() {

	ThreeD t1{ 3,4,5 };
	int i = (int)t1; //casting t1 from type ThreeD to int
	int j = static_cast<int>(t1); //casting t1 from type ThreeD to int
	cout << i << endl;
	cout << j << endl;

	cout << (string)t1 << endl;
	cout << static_cast<string>(t1) << endl;

	cin.get();
	return 0;
}