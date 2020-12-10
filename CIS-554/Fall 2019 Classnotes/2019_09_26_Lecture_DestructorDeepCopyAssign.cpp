#include <iostream>
#include <vector>

using namespace std;

class BigData {
public:
	bool is_Hundred;
	vector<int>* pBigVector;

	BigData() { 
		pBigVector = new vector<int>; 
		is_Hundred = false; 
	}

	BigData(int i) {//destructor: will be called when an object goes out of scope; 
		//or when delte p; //where p is pointer to object of this type
		pBigVector = new vector<int>(i); 

		if (i >= 100) 
			is_Hundred = true; 
		else 
			false;
	}

	~BigData() { 
		delete pBigVector; 
		cout << "Leaving Destructor" << endl; 
	}

	BigData(const BigData& B) {//copy constructor

		is_Hundred = B.is_Hundred;
		pBigVector = new vector<int>;
		*pBigVector = *(B.pBigVector);
		cout << "Leaving copy constructor!" << endl;
	}

	BigData operator=(BigData B) { //L-value operator=
		//pBigVector->clear() ;
		is_Hundred = B.is_Hundred;
		*pBigVector = *(B.pBigVector);
		cout << "Leaving L-value operator=" << endl;
		return *this;
	}

	BigData getThreeTimes();
	void print();
};
BigData BigData::getThreeTimes() {
	BigData temp(pBigVector->size());
	temp.is_Hundred = is_Hundred;
	*temp.pBigVector = *pBigVector;
	for (int& i : *temp.pBigVector) { i *= 3; }
	return temp;
}
void BigData::print() { for (int i : *pBigVector) { cout << i << " "; } }

int main() {
	BigData t1(10), t2, t3, t4, t5;
	for (size_t i = 0; i < t1.pBigVector->size(); i++) { 
		(*(t1.pBigVector))[i] = 10 * i; 
	}

	t1.print();
	cout << endl;

	t2 = t1;		// Copy 
	t2.print();

	cout << endl;
	t3 = t1.getThreeTimes(); //Compiler will convert it to: t2.operator=(t1.getThreeTimes());
	t3.print();
	cout << endl;
	t4 = t5 = t1;//Compiler will convert it to: t4.operator=(t5.operator=(t1))
	cout << endl;
	t4.print();
	cout << endl;
	t5.print();
	cin.get();
	return 0;
}

/*
0 10 20 30 40 50 60 70 80 90
Leaving copy constructor!
Leaving L-value operator=
Leaving copy constructor!
Leaving Destructor
Leaving Destructor
0 10 20 30 40 50 60 70 80 90
Leaving copy constructor!
Leaving Destructor
Leaving L-value operator=
Leaving copy constructor!
Leaving Destructor
Leaving Destructor
0 30 60 90 120 150 180 210 240 270
Leaving copy constructor!
Leaving L-value operator=
Leaving copy constructor!
Leaving Destructor
Leaving L-value operator=
Leaving copy constructor!
Leaving Destructor
Leaving Destructor

0 10 20 30 40 50 60 70 80 90
0 10 20 30 40 50 60 70 80 90


*/