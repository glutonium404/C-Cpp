#include <iostream>
#include <utility>
#include "MyVector.hpp"

using namespace std;

int main() {
    // instantiation and size constructor
    MyVector<int> v1; // default
    MyVector<int> v2 = { 1, 3, 4, 2 }; // initialiser list
    MyVector<int> v3(5); // initial size
    MyVector<int> v4(5, 420); // with default value of 420
    MyVector<pair<int, bool>> v5({ {1, true}, {2, false}, {3, true} }); // use of generics

    for (int i = 10; i <= 50; i += 10) {
        v1.push_back(i); // append item
    }

    v1.pop_back(); // pop from the back

    // element access operations
    cout <<   v1.front()   << "\n"; // first value
    cout <<   v1.back()    << "\n"; // last value
    cout <<   v1[2]        << "\n"; // value at index 2
    cout <<   v1.at(3)     << "\n"; // value at index 3

    // error handling, index out of bound
    try { v1.at(100); } // throws error
    catch (const out_of_range& e) { }

    // memory management: reserve and shrink_to_fit
    v1.reserve(20);
    v1.shrink_to_fit();

    // resizing mechanics
    v1.resize(8);

    // copy constructor and assignment operator
    MyVector<int> v6 = v1;

    // copy Assignment
    MyVector<int> v7;
    v4 = v1;

    // clear mechanics
    v1.clear();

    return 0;
}
