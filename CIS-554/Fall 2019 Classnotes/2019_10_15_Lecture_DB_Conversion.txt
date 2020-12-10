
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename T> ostream& operator<<(ostream& str, vector<T> V)
{
	str << endl;
	for (auto i : V) { str << i << " "; }
	return str;
}
template <typename T> ostream& operator<<(ostream& str, list<T> L)
{
	str << endl;
	for (auto i : L) { str << i << " "; }
	return str;
}
template <typename T> ostream& operator<<(ostream& str, vector<T *> V)
{
	str << endl;
	for (auto i : V) { str << *i << " "; }
	return str;
}
template <typename T> ostream& operator<<(ostream& str, list<T*> L)
{
	str << endl;
	for (auto i : L) { str << *i << " "; }
	return str;
}



void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int*>*>& DB2);
void DB2_to_DB3(list<vector<int*>*>& DB2, list<list<int>*>& DB3);

int main() {
	vector<list<int>> DB1{ {1,2,3},{4,5},{6,7,8,9},{10, 11} };
	cout << DB1;
	list<vector<int*>*> DB2;
	DB1_to_DB2(DB1,DB2);
	cout << DB2;
	list<list<int>*> DB3;
	DB2_to_DB3(DB2, DB3);
	cout << DB3;
	cin.get();
	return 0;
}
void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int*>*>& DB2) {
	for (auto i : DB1) {
		vector<int*>* p1 = new vector<int *>;
		for (auto j : i) {
			int* p2 = new int(j);
			p1->push_back(p2);
		}
		DB2.push_back(p1);
	}
}

void DB2_to_DB3(list<vector<int*>*>& DB2, list<list<int>*>& DB3) {
	for (auto i : DB2) {
		list<int>* p1 = new list<int>;
		for (auto j : *i) {
			p1->push_back(*j);
		}
		DB3.push_back(p1);
	}
}