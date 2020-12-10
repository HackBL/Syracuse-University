#include <iostream>
using namespace std;


double Division(int a, int b) {
    // throw an exception when b == 0
    if (b == 0) {
        throw "Division by zero condition!";
    }
    return (double)a / (double)b;
}

void Func() {
    // You can see here that an exception is thrown if a division by zero error occurs, and the following array is not released.
    // So the exception is not handled after the exception is caught here, the exception is still left to the outside to deal with, then caught here again
    // Throw it again.
    int* array = new int[10];
    try {
        int len, time;
        cin >> len >> time;
        cout << Division(len, time) << endl;
    }
    catch (...) {
        cout << "delete []" << array << endl;
        delete[] array;
        throw;
    }

    // ...

    cout << "delete []" << array << endl;
    delete[] array;
}

int main() {
    try {
        Func();
    }
    catch (const char* errmsg) {
        cout << errmsg << endl;
    }

    return 0;
}
/*
10 0
delete []00C24FC8
Division by zero condition!
*/






