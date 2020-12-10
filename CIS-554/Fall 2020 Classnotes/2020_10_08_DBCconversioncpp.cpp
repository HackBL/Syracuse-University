//DB conversion
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <class T> ostream& operator<<(ostream& str, vector<T>& V);
template <class T> ostream& operator<<(ostream& str, list<T>& L);
template <class T> ostream& operator<<(ostream& str, vector<T *>& V);
template <class T> ostream& operator<<(ostream& str, list<T *>& L);

void DB1_to_DB2(vector<list<int>> & DB1, list<vector<int>>& DB2);
void DB1_to_DB3(vector<list<int>>& DB1, list<vector<int> *> & DB3);
void DB1_to_DB4(vector<list<int>>& DB1, list<vector<int *>*>& DB4);
int main(){
	vector<list<int>> DB1{ {1,2,3,4}, {5,6}, {7,8,9} };
	cout << DB1 << endl;
	
	vector<list<list<int>>> S2 = { {{1,1,1},{2,2,2},{3,3,3}}, {{11,11,11},{22,22,22},{33,33,33}}   };
	cout << S2 << endl; 
	
	list<vector<int>> DB2;
	DB1_to_DB2(DB1, DB2);
	cout << DB2 << endl;
	list<vector<int>*> DB3;
	DB1_to_DB3(DB1, DB3);
	cout << DB3 << endl;
	list<vector<int*>*> DB4;
	DB1_to_DB4(DB1, DB4);
	cout << DB4 << endl;

	

return 0;
}
template <class T> ostream& operator<<(ostream& str, vector<T>& V) {
	str << "[ ";
	for (auto i : V) { str << i << " "; }
	str << "]";
	return str;


}
template <class T> ostream& operator<<(ostream& str, list<T>& L) {
	str << "< ";
	for (auto i : L) { str << i << " "; }
	str << ">";
	return str;

}

template <class T> ostream& operator<<(ostream& str, vector<T *>& V) {
	str << "[ ";
	for (auto i : V) { str << *i << " "; }
	str << "]";
	return str;


}
template <class T> ostream& operator<<(ostream& str, list<T *>& L) {
	str << "< ";
	for (auto i : L) { str << *i << " "; }
	str << ">";
	return str;

}

void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int>>& DB2) {

	for (auto i : DB2) {
		i.clear();
	}
	DB2.clear();

	for (auto i : DB1) {
		vector<int> V1;
		for (auto j : i) {
			V1.push_back(j);
		}
		DB2.push_back(V1);
	}
}


void DB1_to_DB3(vector<list<int>>& DB1, list<vector<int>*>& DB3) {
	for (auto i : DB3) {
		delete i;
	}
	DB3.clear();

	for (auto i : DB1) {
		vector<int>* p1 = new vector<int>;
		for (auto j : i) {
			p1->push_back(j);
		}
		DB3.push_back(p1);
	}
}
//The following is incorrect.
/*
void DB1_to_DB3(vector<list<int>>& DB1, list<vector<int>*>& DB3) {
	for (auto i : DB1) {
		vector<int> V1;
		for (auto j : i) {
			V1.push_back(j);
		}
		DB3.push_back(&V1);
	}
}
*/

void DB1_to_DB4(vector<list<int>>& DB1, list<vector<int *>*>& DB4) {
	for (auto i : DB4) {
		for (auto j : *i) {
			delete j;
		}
		delete i;
	}
	DB4.clear();


	for (auto i : DB1) {
		vector<int *>* p1 = new vector<int *>;
		for (auto j : i) {
			p1->push_back(new int{ j });
		}
		DB4.push_back(p1);
	}
}