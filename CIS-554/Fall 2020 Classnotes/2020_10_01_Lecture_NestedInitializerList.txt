#include <iostream>
#include <vector>
using namespace std;

class V {
public:
	vector<vector<int>> Vec;
	V(){}
	V(const initializer_list<initializer_list<int>>& I);
};

V::V(const initializer_list<initializer_list<int>>& I) {

	int num_rows, num_cols;
	num_rows = I.size();
	num_cols = (*I.begin()).size();

	for (auto i : I) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}



}

int main() {

	V v1{ {1,2,3},{4,5,6} };

	return 0;
}