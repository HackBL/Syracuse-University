// CPP program to demonstrate working of  
// reinterpret_cast 
//data_type *var_name =  reinterpret_cast <data_type *>(pointer_variable);
#include <iostream> 
using namespace std; 
  
int main() 
{ 
    int* p = new int(65); 
    char* ch = reinterpret_cast<char*>(p); 
    cout << *p << endl; 
    cout << *ch << endl; 
    cout << p << endl; 
    cout << ch << endl; 
    return 0; 
} 
Output:
65
A
0x1609c20
A


// CPP code to illustrate using structure 
#include <bits/stdc++.h> 
using namespace std; 
  
// creating structure mystruct 
struct mystruct { 
    int x; 
    int y; 
    char c; 
    bool b; 
}; 
  
int main() 
{ 
    mystruct s; 
  
    // Assigning values 
    s.x = 5; 
    s.y = 10; 
    s.c = 'a'; 
    s.b = true; 
  
    // data type must be same during casting 
    // as that of original 
  
    // converting the pointer of 's' to, 
    // pointer of int type in 'p'. 
    int* p = reinterpret_cast<int*>(&s); 
  
    cout << sizeof(s) << endl; 
  
    // printing the value currently pointed by *p 
    cout << *p << endl; 
  
    // incrementing the pointer by 1 
    p++; 
  
    // printing the next integer value 
    cout << *p << endl; 
  
    p++; 
  
    // we are casting back char * pointed 
    // by p using char *ch. 
    char* ch = reinterpret_cast<char*>(p); 
  
    // printing the character value 
    // pointed by (*ch) 
    cout << *ch << endl; 
  
    ch++; 
  
    /* since, (*ch) now points to boolean value, 
    so it is required to access the value using  
    same type conversion.so, we have used  
    data type of *n to be bool. */
  
    bool* n = reinterpret_cast<bool*>(ch); 
    cout << *n << endl; 
  
    // we can also use this line of code to 
    // print the value pointed by (*ch). 
    cout << *(reinterpret_cast<bool*>(ch)); 
  
    return 0; 
} 
Output:
12
5
10
a
1
1



// CPP code to illustrate the pointer reinterpret 
#include <iostream> 
using namespace std; 
  
class A { 
public: 
    void fun_a() 
    { 
        cout << " In class A\n"; 
    } 
}; 
  
class B { 
public: 
    void fun_b() 
    { 
        cout << " In class B\n"; 
    } 
}; 
  
int main() 
{ 
    // creating object of class B 
    B* x = new B(); 
  
    // converting the pointer to object 
    // referenced of class B to class A 
    A* new_a = reinterpret_cast<A*>(x); 
  
    // accessing the function of class A 
    new_a->fun_a(); 
    return 0; 
} 
Output:
In class A