
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int main() {
	int * p1 = new int(10);
	shared_ptr<int> sp1(p1);//object 10 has a ref count = 1
	sp1.reset(new int(20));//object 10 will be deleted even though it was
	// pointed by p1; p1 in this case behaves like a weak_ptr
	shared_ptr<int> sp2(new int(100));
	shared_ptr<int> sp3 = make_shared<int>(100);//this is faster than the above
	int * p2 = new int(50);
	shared_ptr<int> sp4(p2);
	if (sp4.get() == p2) cout << "p2 and sp4 point to the same objet" << endl;
	//get() return the raw address 
	cout << *p2 << " " << *sp4 << endl;
	shared_ptr<int> sp5 = sp4;
	cout << sp5.use_count() << endl;//use_count() return ref count

	cout << boolalpha << sp5.unique() << endl;
	sp4.reset();
	cout << noboolalpha << sp5.unique() << endl;
	//unique() return true if ref count is 1;otherwise, false
	//boolalpha and noboolalpha are flags which set printing mode
	//for boolean value.
	//boolalpha will have boolean values be printed as true or false
	//noboolalpha will have boolean values be printed as 1 or 0

	shared_ptr<int> sp6 = make_shared<int>(44);
	shared_ptr<int> sp7 = make_shared<int>(55);
	sp7.swap(sp6);
	cout << *sp6 << " " << *sp7 << endl;
		
	int * p10 = new int(25);
	int * p11 = new int(35);
	swap(p10, p11);
	swap(sp6, sp7);//slower than sp6.swap(sp7);

	cout << *p10 << " " << *p11 << " " << *sp6 << " " << *sp7 << endl;
	
	getchar();
	getchar();
	return 0;

}