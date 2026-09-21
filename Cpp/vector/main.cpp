#include <iostream>
#include <string>
#include "MyVector.hpp"

void print_vector_info(const std::string& name, const MyVector<int>& vec) {
    std::cout << name << " | Size: " << vec.size() 
              << " | Capacity: " << vec.capacity() 
              << " | Empty: " << (vec.empty() ? "Yes" : "No") << "\nElements: [ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "]\n\n---------------------------------------------------\n\n";
}

int main() {
    // instantiation and size constructor
    MyVector<int> v1;
    print_vector_info("v1 (Default)", v1);

    MyVector<int> v2(5);
    print_vector_info("v2 (Size = 5)", v2);

    // modifiers: push_back and dynamic expansion
    std::cout << "[2] Pushing Elements & Dynamic Expansion\n";
    for (int i = 10; i <= 50; i += 10) {
        v1.push_back(i);
        std::cout << "Pushed: " << i << " -> Size: " << v1.size() << ", Capacity: " << v1.capacity() << "\n";
    }
    print_vector_info("v1 (After Pushes)", v1);

    // element access operations
    std::cout << "[3] Element Access Mechanics\n";
    std::cout << "v1.front() : " << v1.front() << "\n";
    std::cout << "v1.back()  : " << v1.back() << "\n";
    std::cout << "v1[2]      : " << v1[2] << "\n";
    std::cout << "v1.at(3)   : " << v1.at(3) << "\n";

    try {
        std::cout << "Attempting out-of-bounds access via at(100)...\n";
        v1.at(100);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught Exception: " << e.what() << "\n";
    }
    std::cout << "---------------------------------------------------\n";

    // modifiers: pop_back
    std::cout << "[4] Popping Elements\n";
    v1.pop_back();
    print_vector_info("v1 (After pop_back)", v1);

    // memory management: reserve and shrink_to_fit
    std::cout << "[5] Capacity Controls (reserve & shrink_to_fit)\n";
    v1.reserve(20);
    print_vector_info("v1 (After reserve(20))", v1);

    v1.shrink_to_fit();
    print_vector_info("v1 (After shrink_to_fit())", v1);

    // resizing mechanics
    std::cout << "[6] Resizing Operations\n";
    v1.resize(8);
    print_vector_info("v1 (After resize(8))", v1);

    v1.resize(2);
    print_vector_info("v1 (After resize(2))", v1);

    // copy constructor and assignment operator
    std::cout << "[7] Copy Semantics\n";
    MyVector<int> v3 = v1; // Copy Construction
    print_vector_info("v3 (Copy of v1)", v3);

    MyVector<int> v4;
    // copy Assignment
    v4 = v1;
    print_vector_info("v4 (Assigned from v1)", v4);

    // clear mechanics
    std::cout << "[8] Clearing Container\n";
    v1.clear();
    print_vector_info("v1 (After clear())", v1);

    return 0;
}
