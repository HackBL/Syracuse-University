//Operator Overloading
#include <iostream>
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	int getArea() { return ht * wid * dep; }
	ThreeD operator+(const ThreeD &t);//const will ensure that t won't be modified
	//ThreeD operator*(const ThreeD& t);  You can do it in a similar way
	ThreeD operator++();//prefix
	ThreeD operator++(int neverUsed); //post fix
	int & operator[](int k);//return by reference
};

int & ThreeD::operator[](int k) {//Return by reference will allow a
	//function to appear on the left hand side of a starement
	//which is necessary for [].  See the main function
	switch (k)
	{
	case 0: return ht;
	case 1: return wid;
	case 2: return dep;
	}
}


ThreeD ThreeD::operator++() { //prefix
	++ht;
	++wid;
	++dep;
	return *this;//"this" is a pointer pointing to the current object
}

ThreeD ThreeD::operator++(int neverUsed) {//post fix
	ThreeD temp = *this;
	ht++;
	wid++;
	dep++;
	return temp;
}

ThreeD ThreeD::operator+(const ThreeD &t) {
	ThreeD temp;
	temp.ht = ht + t.ht;
	temp.wid = wid + t.wid;
	temp.dep = dep + t.dep;
	return temp;
}

istream& operator>>(istream& str, ThreeD &t) {
	str >> t.ht >> t.wid >> t.dep;
	return str;
}

ostream& operator<<(ostream& str, const ThreeD &t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}


int main() {

	ThreeD t1(3, 4, 5), t2(10, 20, 30), t3, t4;
	t3 = t1 + t2;
	//Compiler will convert this into
	//t3 = t1.operator+(t2);
	//This explains why only one argument for the function
	
	t1++;//postfix
	t3 = ++t1; //prefix

	//cout << t3[1] << endl;

	cin >> t4;
	cout << t4 << endl;

	t4[1] = 100;//Note that return by reference allows t4[1] to appear on the
	//left hand side of a statement.
	cout << t4[2]<< endl;
	cout << t4 << endl;

	getchar();
	getchar();
	return 0;
}