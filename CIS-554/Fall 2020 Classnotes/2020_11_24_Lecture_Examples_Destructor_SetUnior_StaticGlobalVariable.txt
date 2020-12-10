
//Example of destructor
//Static global variable
//set unior
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <fstream>


using namespace std;

static int w{ 100 };// A static global variable
                    //can only be accessed within the current file.

class myClass1 {
	//private:
	ofstream out;
public:
	myClass1() {
		out.open("text.txt");
	}
	~myClass1() {
		out.close();
	}
};


class myClass2 {
public:

	vector<vector<int*>*>  V;
	myClass2() {}

	~myClass2() {
		for (auto& i : V) {
			for (auto &j : *i) {
				delete j;
			}
			delete i;
		}
	}
	//...
};


int main() {

	set<int> S1{ 1,3,5,7 }, S2{ 8,4,2,6 , 1, 5};
	S1.insert(S2.begin(), S2.end());//set union

	for (auto& i : S1) { cout << i << " "; }
	{	
		myClass2 m1;
	}



	return 0;
}