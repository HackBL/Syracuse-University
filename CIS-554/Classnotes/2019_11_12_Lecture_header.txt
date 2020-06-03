int global_v = 100;
class ThreeD {

public:
	int ht;
	int wid;
	int dep;
	ThreeD(int i, int j, int k) { ht = i; wid = j; dep = k; }
	ThreeD(){}
};

void  func1(int i) {


	cout << i * i << endl;
}
