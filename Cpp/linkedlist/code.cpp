#include <iostream>
#include <vector>

#include "linkedlist.hpp"

struct Student {
   std::string name;
   int age;
   int id;
};

int main() {
   LinkedList::List<int> intList;

   intList.insertFirst(4);
   intList.insertLast(10);
   intList.insertAt(1, 7);
   /*intList.removeFirst();*/
   /*intList.removeLast();*/
   intList.insertFirst(9);
   /*intList.removeAt(2);*/
   intList.insertFirst(4);
   intList.insertLast(10);
   intList.insertAt(1, 7);
   std::cout << "Size: " << intList.getSize() << std::endl;
   intList.clear();
   std::cout << "Size: " << intList.getSize() << std::endl;
   /**/
   /*auto temp = intList.getFirst();*/

   /*while(temp != nullptr) {*/
   /*   std::cout << temp->data << std::endl;*/
   /*   temp = temp->next;*/
   /*}*/
}
