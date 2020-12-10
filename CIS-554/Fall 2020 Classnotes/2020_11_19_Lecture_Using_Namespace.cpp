#include <iostream>
#include <vector>
using namespace std;

int x{ 1000 };
int w{ 3 };



namespace one {

	int x{ 1 };
	int z{ 100 };
	namespace one_one {

		int x_x{ 11 };


	}


}
namespace two {
	int x{ 2 };
	int y{ 22 };
	int w{ 33 };
}


int main() {

	typedef int easy;
	easy d1{ 30 };
	cout << d1 << endl;
	using easy1 = float;
	easy1 f1{ 3.5 };
	cout << f1 << endl;
	typedef vector<vector<vector<int>>> V3;
	using v4 = vector<vector<vector<vector<int>>>>;


	int w{ 333 };
	//using namespace one;
	using namespace one::one_one;
	namespace NEW = one::one_one;
	using namespace NEW;
	using namespace two;
	cout << w << endl;
	cout << x_x << endl;
	cout << one::z << endl;
	cout << ::x << endl;

	typedef vector<vector<vector<int>>> V3;
	using v4 = vector<vector<vector<vector<int>>>>;



	
	




	return 0;
}
