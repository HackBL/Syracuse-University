//Smart pointers -- shared_ptr, unique_ptr, and weak_ptr
#include <iostream>
#include <memory>
#include <list>

using namespace std;

int main() {
	//Regualr * is referred to as raw pointers
	//Three types of smart pointers: shared_ptr, unique_ptr, and weak_ptr
	unique_ptr<int> up1 = make_unique<int>(5);
	//unique_ptr<int> up1 = make_unique<int>{5}; will not work
	//int * p1 = new int{5}; similar

	cout << *up1 << endl;
	//unique_ptr<int> up2 = up1;  Unique object can only be pointed by one unique_ptr
	up1.reset();//equivalent to up1 = nullptr;
	shared_ptr<int> sp1 = make_shared<int>(10);
	cout << sp1.use_count() << endl;//return the number of pointers that are pointing to the object; reference count
	{
		shared_ptr<int> sp2 = sp1;
		cout << sp1.use_count() << endl;//2
	}

	cout << sp1.use_count() << endl;//1
	//sp2 has been out of scope.
	sp1 = make_shared<int>(30);
	//sp1.reset();
	//object 10 with ref count = 0 will be automatically deleted by system
	weak_ptr<int> wp1 = sp1;
	cout << sp1.use_count() << endl;//1

	//cout << *wp1 << endl;//* -> do not work for weak_ptr
	//weak_ptr does not contribute to ref count
	//sp1.reset();
	//shared_ptr<int> sp3 = wp1;  YOu can't assign a weak_ptr to a shared_ptr or unique_ptr

	weak_ptr<int> wp2 = wp1;

	cout << *(wp1.lock()) << endl;
	//lock() returns a shared_ptr which points to the same object pointed by wp1
	shared_ptr<int> sp4 = wp1.lock();
	sp4.reset();
	sp1.reset();
	//object 20 is deleted.
	if (wp1.expired()) cout << "deleted" << endl;

	int* p1 = new int{ 50 };
	shared_ptr<int> sp5{ p1 };//sp5 and p1 both point to object 50
	if (sp5.get() == p1) cout << "equal" << endl;
	//check if a smart pointer is pointing to the same object pointed by a raw pointer

	cout << sp5.use_count() << endl;
	sp5 = make_shared<int>(22);
	//the object 50 will be deleted even though p1 is pointing to it
	cout << *p1 << endl;//will print junk

	sp5.reset(new int{ 77 });
	//sp5 = make_shared<int>(77); Both are OK, but this is faster

	shared_ptr<list<int>> sp10 = make_shared<list<int>>(initializer_list<int> { 1,2,3,4,5 });
	shared_ptr<list<shared_ptr<int>>> sp11 =
		make_shared<list<shared_ptr<int>>>(initializer_list<shared_ptr<int>> { make_shared<int>(1), make_shared<int>(2) });

	list<int*>* p5 = new list<int *> { new int {5}, new int {6} };







	




	return 0;
}