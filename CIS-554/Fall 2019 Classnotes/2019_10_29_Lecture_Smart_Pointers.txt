//Smart pointers
#include <iostream>
#include <memory> //smart pointers
using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
};

class node {
public:
	/*
	node * next;
	int value;
	node() { next = nullptr; }
	node(int i) { next = nullptr; value = i; }
	*/
	shared_ptr<node> next;
	int value;
	node() {}
	node(int i) { value = i; }
};
class linked_list {
public:
	//node * head;
	shared_ptr<node> head;
	//linked_list() { head = nullptr; }
	linked_list() {}
	linked_list(const initializer_list<int>& V) {
		auto it1 = V.end() - 1;
		while (it1 != V.begin() - 1) {
			//node * p1 = new node(*it1);
			shared_ptr<node> p1 = make_shared<node>(*it1);
			p1->next = head;
			head = p1;
			it1--;
		}
	}
};






int main() {
	//Raw pointers refer to the original pointers
	//Three types of smart pointers: unique_ptr, shared_ptr, weak_ptr
	unique_ptr<int> up1 = make_unique<int>(10);
	up1.reset();// up1 becomes empty; object 10's ref count = 0 and will be deleted automatically.
	up1 = make_unique<int>(15);
	cout << *up1 << endl;
	//unique_prt<int> up2 = up1; error! because the unique object can only be pointed by
	//one unique pointer

	shared_ptr<int> sp1 = make_shared<int>(20); //object 20's reference count is 1
	shared_ptr<int> sp2 = sp1; //reference count is 2
	shared_ptr<int> sp3 = make_shared<int>(30);
	sp2 = sp3; //ref count for object 20 is 1
	sp1 = sp3; //ref count for object 20 is 0 and the object 20 will be automatically deleted.
	weak_ptr<int> wp1;
	cout << sp1.use_count() << endl;//use_count returns reference count of the object pointed by sp1
	shared_ptr<int> sp4;
	wp1 = sp3; //ref count for object 30 remains 3; weak_ptr does not contribute to ref count
			   //sp4 = wp1; error! can't assign weak_ptr to shared_ptr
	sp4 = wp1.lock();//lock() type casting weak_ptr to shared_prt
	cout << *sp1 << endl;
	//cout << *wp1 << endl; Error! weak_ptr does not support * , ->
	cout << *(wp1.lock()) << endl;
	shared_ptr<ThreeD> sp5 = make_shared<ThreeD>(3, 4, 5);
	weak_ptr<ThreeD> wp2 = sp5;
	cout << sp5->ht << endl;
	cout << wp2.lock()->ht << endl;
	sp5.reset(); //the object (3,4,5) will be deleted
	if (wp2.expired()) { cout << "Object has been deleted" << endl; }
	//Reset funcitons are available to all three types of smart pointers
	sp1.reset(new int(40));
	sp1 = make_shared<int>(40);//this is faster than the above
							   //sp1.reset(make_shared<int>(40)); will not compile

							   //weak_ptr<int> wp3 = make_weak<int>(10); make_weak does not exist
	weak_ptr<int> wp3 = make_shared<int>(99);//object 99 is created and immediately deleted because ref count is 0

	linked_list L1 = { 11,2,3,4,5 };
	cout << L1.head->value << endl;

	shared_ptr<linked_list> sp11 = make_shared<linked_list>(initializer_list<int>{ 66, 7, 8, 9, 10 });//notice the
	//new syntax for initializer_list here

	cout << sp11->head->value << endl;
	getchar();
	getchar();
	return 0;
}