
#include <iostream>
using namespace std;

class my_class {
public:
	static int num_objects;//static members are associated with class, rather than objects of the class
	my_class() { num_objects++; }

	static void get_num_objects() { cout << num_objects << endl; }
};
int my_class::num_objects = 0; //static data member has to be initialized outside the class.


void fun1() {
	static int num_fun1_calls = 1; //Static variable will only be initialized when the function
					// is invoked for the first time.
					//The value of static variable will continue into next time when
					//the function is invoked.
	cout << "num_fun1_calls = " << num_fun1_calls++ << endl;

}

int main() {
	my_class m1, m2, m3;

	//Both the following two statements are valid to access num_objects
	cout << my_class::num_objects << endl; 
	cout << m1.num_objects << endl;
	m1.get_num_objects();
	fun1();
	fun1();
	fun1();
	fun1();
	getchar();
	getchar();
	return 0;
}
