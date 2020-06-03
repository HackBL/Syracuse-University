#include <iostream>
#include <map>
#include <algorithm> //for_each
using namespace std;
class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) : ht(i*10), wid(j*10), dep(k*10){}
	ThreeD(const initializer_list<int>& I);
	int getVol() const { return ht * wid * dep; }
};
ThreeD::ThreeD(const initializer_list<int>& I) {
	auto it = I.begin();
	ht = *it*100;
	it++;
	wid = *it*100;
	it++;
	dep = *it*100;
}
class my_compare_class {
public:
	bool operator() (ThreeD *p1, ThreeD *p2) const {
		return p1->getVol() < p2->getVol();
	}

};

ostream& operator<<(ostream& str, const ThreeD& t) {
	str << t.ht << " " << t.wid <<" "<< t.dep;
	return str;
}

int main(){
	ThreeD t1{ 2,3,4 };
	cout << t1.ht << " " << t1.wid << " " << t1.dep << endl;
	
	ThreeD* p1{ new ThreeD{2,3,4} }, * p2{ new ThreeD{1,2,3} };
	map<ThreeD*, int, my_compare_class> M{ {p1, 4},{p2,2} };
	for (auto i : M) { cout << *i.first << " " << i.second<< " "; }

	cin.get();
	return 0;
}
/*
Precedence: initializer_list > user-defined constructor > system defined 
			default constructor

*/