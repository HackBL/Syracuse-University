// exception example
#include <iostream>       // std::cerr
#include <typeinfo>       // operator typeid
#include <exception>      // std::exception
using namespace std;
class Polymorphic { virtual void member() = 0; };

int main() {

    try
    {
        Polymorphic *pb = nullptr;
        cout << typeid(*pb).name() << endl;;  // throws a bad_typeid exception
    }
    catch (std::exception& e)
    {
        std::cerr << "exception caught: " << e.what() << '\n';
    }
    return 0;
}



// bad_alloc standard exception
#include <iostream>
#include <exception>
using namespace std;

int main () {
  try
  {
    int* myarray= new int[1000];
  }
  catch (exception& e)
  {
    cout << "Standard exception: " << e.what() << endl;
  }
  return 0;
}