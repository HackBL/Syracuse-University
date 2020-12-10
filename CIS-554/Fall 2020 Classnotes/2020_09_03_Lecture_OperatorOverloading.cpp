//Operator Overloading
#include <iostream> //cin cout console
#include <fstream> //input output for file
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j , int k): ht(10* i), wid(10*j), dep(10*k){}
	ThreeD() { ht = wid = dep = 0; }
	ThreeD operator+(const ThreeD &t);//t3 = t1+t2;
	ThreeD operator++();//prefix;  return the value after increment
	ThreeD operator++(int NeverUsed);//postfix; return the value before increment
	//By including the NeverUsed parameter, the compiler can distinguish between this 
	//and the prefix.

	int  & operator[](int i);//return by reference.
	//the function can appear on the left side of a statement.
};
int & ThreeD::operator[](int i) {
	switch (i) {
	case 0: return ht;
	case 1: return wid;
	case 2: return dep;
	}

}

ThreeD ThreeD::operator++(int NeverUsed) {
	ThreeD temp{ *this };
	//In main function, t4 = t3++; then "this" is a pointer pointing to object t3.
	ht++;
	wid++;
	dep++;
	return temp;

}

ThreeD ThreeD::operator++() {//prefix
	++ht;
	++wid;
	++dep;
	return *this;//"this" is a pointer pointing to the current object
	//In main function, t5 = ++t4; then "this" is a pointer pointing to object t4.
}




ThreeD ThreeD::operator+(const ThreeD &t) {//t will be read only inside this function
	ThreeD temp;
	temp.ht = ht + t.ht;
	temp.wid = wid + t.wid;
	temp.dep = dep + t.dep;
	return temp;

}
/*

int& f2(int i) {//return by reference

	i++;
	return i;

}

f2(10) = 5;

b = f2(7); //
*/
ostream& operator<<(ostream& str, const ThreeD &t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

istream& operator>>(istream& str, ThreeD& t) {
	str >> t.ht >> t.wid >> t.dep;
	return str;
}



int main() {

	int i{ 5 }, j{ 10 }, k;
	k = i + j;
	cout << k << endl;


	ThreeD t1{ 3,4,5 }, t2{ 7,8,9 }, t3, t4, t5;
	t3 = t1 + t2;
	//compiler will change it to  t3 = t1.operator+(t2);
	
	cout << t3 << endl;

	cin >> t4;
	cout << t4 << endl;

	k = i++;//postfix
	k = ++i;//prefix
	i++;

	t4 = t3++;//postfix
	//compiler will change it to t4 = t3.operator++(dummy int);


	t5 = ++t4;//prefix
	//compiler will change it to 54 = t4.operator++();

	cout << t4 << " " << t5 << endl;

	cout << t4[2] << endl;
	i = t4[0];//compiler change it to i = t4.operator[](0);
	t4[1] = 65;//This statement requires that the function operator[] return by reference.
	cout << t4 << endl;

	ofstream out("text1.txt");//If the file does not exist, a new one will be created.
	//If there is an existing file of the same name, the contents of the existing file will all be
	//deleted first.  Be careful to save the contents.
	//The file is in the same directory as source code file.

	out << i << " " << j << " "<< k<<endl;//cout refers to console; here out is another I/O device "text1.txt"


	out.close();
	
	ifstream in("text1.txt");

	in >> t4;
	cout << t4 << endl;
	in.close();

	int* p1;
	p1 = &i;
	cout << *p1 << " " << i << endl; // *p1 and i are idential

	const int* p2 = &i;//Object pointed by the pointer is const .
	//int const * p2; the same as above.


	//*p2 = 10; Error! Objected pointed by p2 is const
	i = 100;//OK but not *p2

	p2 = &k;//pointer p2 is not const

	int* const p3 = &i;//The pointer rather than the object pointed by it is const.
	*p3 = 1000;//object pointed by p3 is not const
	//p3 = &k; Error! pointer p3 itself is const

	const int* const p4 = &i; // Both pointer and the object pointed by it are const

	//*p4 = 24; objected pointed by p4 is const
	//p4 = &k; p4 is const

	/*
	
	The reasons to use call/pass by reference:
	1. Want to modify the object inside function.
	2. Want to save the overhead of creating a new copy.
	Including const such as f(const ThreeD &t) is to avoid being modified in function, but still
	save the overhead of creating a new copy.  t will be read only in function f.
	
	*/


	return 0;
}

/*
int f1(int i) {....} //i is a parameter of function f1



in main:
f1(k);//k is an argument to function f1.

*/