    //upcasting and downcasting
#include <iostream>
using namespace std;


class B {//base class

	int b1 = 1;
protected:
	int b2 = 2;
public:
	int b3 = 3;
	void f1() {
		cout << "B::f1" << endl;
	}
	virtual void f2() { //virtual member function can be redefined in the derived class
		cout << "B::f2" << endl;
		cout << b3 * b3 << endl;
	}
};

class D : public B {

	int d1 = 4;
protected:
	int d2 = 5;
public:
	int d3 = 6;
	void f2() {
		cout << "D::f2" << endl;
		cout << d3 * d3 << endl;
	}
};

class E : public B {

	int e1 = 7;
protected:
	int e2 = 8;
public:
	int e3 = 9;
	void f2() {
		cout << "E::f2" << endl;
		cout << e3 * e3 << endl;
	}
};

int main() {

	D d;
	B* p1 = dynamic_cast<B*>(&d); //upcasting
	p1->f1(); //will print B::f1
	p1->f2(); //will print D::f2
	cout << p1->b3 << endl; //will print 3

	B b;
	//D* p2 = Dynamic_cast<D*>(&b); //Compile Error! downcasting

	D o1;
	B* p3 = static_cast<B*>(&o1); //upcasting
	D* p4 = dynamic_cast<D*>(p3); //downcasting
	if (!p4) cout << "p4 is nullptr" << endl; //p4 is not nullptr; 
	else { //This else part will be executed
		//p4 has access to b3, d3, f1 and f2
		p4->f1();//prints B::f1
		p4->f2();//prints B::f2 and, in the next line, 9
		cout << p4->d3 << endl;//prints 12515912 (just something arbitrary)
	}

	E o2;
	B* p5 = static_cast<B*>(&o1); //upcasting
	D* p6 = dynamic_cast<D*>(p3); //downcasting
	if (!p6) cout << "p6 is nullptr" << endl; //p6 is  nullptr; 
	else { //This else part will not be executed
		//p6 has access to b3, d3, f1 and f2
		p6->f1();//prints B::f1
		p6->f2();//prints B::f2 and, in the next line, 9
		cout << p6->d3 << endl;//prints 12515912 (just something arbitrary)
	}

	D o3;
	D& rd = o3;
	B& rb = static_cast<B&>(rd);//upcasting
	D& rd1 = dynamic_cast<D&>(rb); //downcasting
	rd1.f1();//Will print B::f1
	rd1.f2();//Will print D::f2 and in the next line 36

	B o4;
	B& rb1 = o4;
	//D& rd2 = dynamic_cast<D&>(rd1); 
	//Compiler will not report error.
	//It will fail during run time. 
	//An exception will be thrown and the program will exit.
	cin.get();
	return 0;
}