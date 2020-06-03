
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
int main() {
	stack<int> S;
	S.push(5);
	S.push(6);
	S.push(7);
	cout << S.top() << endl;
	S.pop();
	cout << S.top() << endl;
	if (!S.empty()) cout << "It is not empty" << endl;
	cout << S.size() << endl;
	queue<int> Q;
	Q.push(19);
	Q.push(5);
	cout << Q.size() << " " << Q.front() << " " << Q.back() << endl;
	Q.pop();

	cin.get();
	return 0;
}