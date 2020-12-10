//standard template library (STL)
//There are many containers in STL such as vector, list, map, queue, stack, set, etc.#
#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

class ThreeD {
public:
	int ht;
	int wid;
	int dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	int getVol() const { return ht * wid * dep; }

	bool operator< (const ThreeD& t) { return (getVol() < t.getVol()); }
	bool operator==(const ThreeD& t) { return (getVol() == t.getVol()); }

};

ostream& operator<<(ostream& str, const ThreeD& t) {
	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}



int main() {
	vector<int> V1 = { 0,1,2,3,4 };
	cout << V1.size() <<" "<< V1.front() << " " << V1.back() << endl;
	//size() returns number of elements of V1.
	//front() and back() returns first and last element of V1, respectively.
	V1.push_back(5); //add a new element 5 to the back.
	V1.pop_back(); //remove the last element
	//vector only support push or pop at the end
	
	//Since each element of vector or listed has been wrapped with many new functions,
	//its exact data type is no longer clear to programmers.  If we want to use pointers to
	//point to elements of vector or list, we need to know their exact data type.
	//Thus, we can't use regular pointers.
	//To solve this problem, STL comes with a special type of pointers, called iterator.
	//Iterators behavior like regular pointers, and are required when pointing to elements of 
	//STL containers such as vector, list, map, etc.

	//In conclusion, iterators are special pointers that programmers are required to use within STL
	//to point to elements within STL.


	vector<int>::iterator it1 = V1.begin();
	//begin() returns the address of the first element
	//end() returns the address after the last element
	//auto it1 = V1.begin(); is equivalent to the above statement.
	//From V1.begin(), the compiler can "guess" for us the exact type of it1.


	while (it1 != V1.end()) {
		cout << *it1 << " ";
		it1++;
	}
	cout << endl;
	for (size_t i = 0; i < V1.size(); i++)
		cout << V1[i] << " ";
	//vector supports random access, i.e., the array index function

	cout << endl;
	for (int i : V1) { cout << i << " "; }
	//This is new syntax of for loop

	cout << endl;
	it1 = find(V1.begin(), V1.end(), 3);
	//
	//When using find, we need to specify the search range.
	//If find function finds a match, it will return the
	//address of the matched element.
	//When no match found, find returns end()



	if (it1 != V1.end()) V1.erase(it1);
	//if (it1==V1.end()) the erase function will crash the program.
	//Note that the erase function will take address (or iterator) as augument.



	list<int> L1 = { 5,2,11,1,6 };
	//list allows both push and pop at front and back.
	L1.push_back(1);
	L1.push_front(100);
	L1.pop_back();
	L1.pop_front();
	cout << L1.size() << " " << L1.front() << " " << L1.back() << endl;
	//Similar to vector, list supports size(), front(), and back().

	cout << endl;
	//You can use iterator to access elements of list
	list<int>::iterator it2 = L1.begin();
	while (it2 != L1.end()) {
		cout << *it2 << " ";
		it2++;
	}
	//list iterator only allows 4 operations:   it++, ++it, it--, --it
	//Note that even it= it+1; is not allowed for list
	//Random access (i.e., [] index) is not allowed for list


	//Only list supports sort
	L1.sort();
	cout << endl;
	
	//list also supports find and erase
	it2 = find(L1.begin(), L1.end(), 3);//When no match, find returns end()
	if (it2 != L1.end()) L1.erase(it2);

	//Only list support remove function; it does nothing if no match found
	L1.remove(2);

	cout << endl;

	it2 = L1.begin();
	while (it2 != L1.end()) {
		cout << *it2 << " ";
		it2++;
	}
	cout << endl;

	//We can use the new for loop syntax on list too.
	for (int i : L1) { cout << i << " "; }
	cout << endl;


	ThreeD t1(3, 4, 5), t2(1, 8, 7), t3(2, 3, 9);
	list <ThreeD> L2 = { t1, t2, t3 };
	for (ThreeD i : L2) { cout << i << endl; }
	L2.sort();
	//We need to overload operator< in ThreeD class to allow sort.
	for (ThreeD i : L2) { cout << i << endl; }

	auto it3 = L2.begin();

	it3 = find(L2.begin(), L2.end(), t2);
	//We need to overload operator== in ThreeD class to allow find

	getchar();
	getchar();
	return 0;

}


