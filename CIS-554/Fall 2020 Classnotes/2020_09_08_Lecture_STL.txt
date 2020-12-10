//STL (standard Template Library): vector, list, map, stack, queue --- STL containers
#include <iostream> //cin, cout
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <string> //"  .....   "

using namespace std;

int main() {

	vector<int> V1{ 11,12,13,14,15 };//V1 has 5 elements

	cout << V1[2] << " " << V1.size() << " " << V1.front() << " " << V1.back() << endl;

	//cout << V1[10] << endl; Error! vector will check for out-of-bound error

	V1.push_back(24);//add new element 24 to the end of vector
	V1.pop_back(); //remove the last element

	//Remember that array size cannot be changed

	//Iterator -- the special pointers required to point to elements of STL containers 
	//vector, list, map, etc. are all containers of STL library
	//The actual data types of  elements are not known to use, and thus we cannot use regular
	//pointer to point to container elements.



	vector<int>::iterator it1{ V1.begin() };//begin() returns the address of the first element
	cout << *it1 << endl;

	cout << *it1 << " " << *(it1 + 3) << " " << *(++it1) << " " << *(V1.end() - 2) << endl;

	auto it2{ V1.end() }; //end() returns the address after the last element
	//cout << *it2 << endl;  Error.  it2 points to the position after the last element

	auto i{ 56 };

	for (auto it3 = V1.begin(); it3 != V1.end(); it3++) {

		cout << *it3 << " ";
	}
	cout << endl;

	for (int i : V1) { cout << i << " ";  i++; }//call by value
	cout << endl;
	for (int i : V1) { cout << i << " "; } //values of V1's elements are unchanged.

	for (int& i : V1) { cout << i << " ";  i++; }//call by reference
	cout << endl;
	for (int i : V1) { cout << i << " "; }//value of V1's elements are incremented.
	cout << endl;

	vector<int>::iterator it4 = find(V1.begin(), V1.end(), 14);
	//find will return the address of the first matched element within the specified range.
	//Will return end() if no match found.

	if (it4 != V1.end()) V1.erase(it4);//erase will remove the node pointed by it4.
	//After removal, it4 will point to the node after the deleted one.
	
	vector<int> V2(10, 3);//size 10 and all of them with value 3
	vector<int> V3(8); //size 8 and all of them with value 0
	//vector < int * > V3(5); vetor size 5; all with value nullptr

	//STL containers will all assign initial default values if not specified.

	//LIST

	list<int> L1{ 11,22,33,44,55 };
	list<int> L2(10, 3);
	list<int> L3(5);//all 5 elements with value 0

	cout << L1.size() << " " << L1.front() << " " << L1.back() << endl;
	//cout << L1[2]<<endl; Error! list does not support subscripts like vector

	list<int>::iterator it11{ L1.begin() }, it12{ L1.end() };

	//auto it11{ L1.begin() }, it12{ L1.end() };

	cout << *it11 << " " << *(++it11) << " " << *(--it12) << " " << endl;

	//cout << *(it11 +1) << endl; Error!  
	//list iterator only allows ++ and --

	L1.push_back(100);
	L1.pop_back();
	L1.push_front(400);//Vector does not support this.
	L1.pop_front(); //vector does not support this.

	auto it13 = find(L1.begin(), L1.end(), 33);
	if (it13 != L1.end()) L1.erase(it13);

	for (int i : L1) { cout << i << " "; }
	//the iterator based loop will also work

	L1.remove(44);//remove the first node with value 44 if found; otherwise, do nothing.
	//Only list support this function.

	L1.front() = 5555;
	*(++L1.begin()) = 2000;
	cout << endl;
	list<int> L8{ 5,11,3,21,1 };
	L8.sort();//only list support sort.
	for (auto i : L8) { cout << i << " "; }
	cout << endl;





	//map
	//The two objects of each map element is called key and value

	cout << endl;

	map<int, string> M1{ {10, "Dave"}, {8, "John"}, {25, "Sanjay"}, {6, "Chen"} };


	for (pair<int, string> i : M1) { cout << i.first << " " << i.second << "   "; }
	//all map elements will automatically be sorted based on keys

	//adding new elements to map
	M1[55] = "Nancy"; //add {55, "Nancy"} to M1.
	M1.insert({ 31, "Bob" });
	cout << endl;
	for (pair<int, string> i : M1) { cout << i.first << " " << i.second << "   "; }

	M1[55] = "Mary"; //will override {55, "Nancy"};
	M1.insert({ 31, "Ben" });//will be ignored.
	cout << endl;

	for (pair<int, string> i : M1) { cout << i.first << " " << i.second << "   "; }


	cout << endl;
	cout << M1[8] << endl;//will print john

	for (auto it20 = M1.begin(); it20 != M1.end(); ++it20) {
		cout << it20->first <<" "<<it20 -> second<<  " ";
	}

	cout << endl;


	return 0;
}