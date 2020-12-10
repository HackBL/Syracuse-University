//Anonymous object
#include <iostream>
#include <list>

using namespace std;

struct ThreeD {
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k): ht(i), wid(j), dep(k){}
	ThreeD() { ht = wid = dep = 0; }
	int getVol() { return ht * wid * dep; }

} t1{3,4,5}, t2;

class myCompare {
public:
	bool operator()(const int& i, const int& j) const { return i%3 < j%3; }
} f3;



int main() {

	cout << t1.getVol() << endl;
	cout << t2.getVol() << endl;
	cout << ThreeD{ 5,6,7 }.getVol() << endl;//anonymous object
	list<int> L1{ 7,4,22,66,8 };
	L1.sort(f3);//f3 is an object of class myCompare
	L1.sort(myCompare());//anonymous objec to class myCompare
	//The above two statements do the same thing.
	for (auto& i : L1) { cout << i << " "; }
	cout << endl;

	return 0;
}