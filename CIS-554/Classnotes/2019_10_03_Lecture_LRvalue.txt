#include <iostream>
using namespace std;
/*
Entity or expression that can only appear on right side of an assignment statement is Rvalue
Entity that can appear on either side of an assignment statement is Lvalue
*/

void addValue(int &value) { cout << value+10<< endl; } //Lvalue reference version
void addValue(int&& value) { cout << value +100<<endl; } //Rvalue reference version
int main() {
	int i{ 1 }, j{ 2 };
	addValue(i); //i is Lvalue; will call Lvalue version
	addValue(j + 5); //j+5 is Rvalue; will call Rvalue version
	addValue(500); //500 is Rvalue; will call Rvalue version
	addValue(move(i)); //move(i) will temporarily cast i as R-value; and will call Rvalue vaersion
	addValue(i);//i is still Lvalue; will call Lvalue version
	cin.get();
	return 0;
}