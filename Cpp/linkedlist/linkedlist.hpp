#pragma once

#include <cstdlib>
#include <stdexcept>

namespace LinkedList {

template<typename T>
struct Node {
   T data;
   Node<T>* next = nullptr;
   Node<T>* prev = nullptr;
};

template<typename T>
class List {

private:
   Node<T>* first = nullptr;
   Node<T>* last = nullptr;
   std::size_t size = 0;

public:

   ~List() {
      Node<T>* curr = first;
      Node<T>* next = nullptr;

      while(curr != nullptr) {
         next = curr->next;
         delete curr;
         curr = next;
      }
   }

   Node<T>* insertFirst(const T& node) {
      Node<T>* newNode = new Node<T>();
      newNode->data = node;

      if(first == nullptr) {
         first = newNode;
         last = newNode;
      }else {
         first->prev = newNode;
         newNode->next = first;
         first = newNode;
      }

      size++;
      return newNode;
   }

   Node<T>* insertLast(const T& node) {
      Node<T>* newNode = new Node<T>();
      newNode->data = node;

      if(isEmpty()) {
         first = newNode;
         last = newNode;
      }else {
         last->next = newNode;
         newNode->prev = last;
         last = newNode;
      }

      size++;
      return newNode;
   }

   Node<T>* insertAt(std::size_t position, const T& node) {

      if(position < 1 || position > size + 1) {
         throw std::runtime_error("Position out of bound");
      }

      if(position == 1) {
         return insertFirst(node);
      } else if(position == size + 1) {
         return insertLast(node);
      }

      Node<T>* newNode = new Node<T>();
      newNode->data = node;

      Node<T>* positionNode = getAt(position);
      newNode->next = positionNode;
      newNode->prev = positionNode->prev;
      positionNode->prev->next = newNode;
      positionNode->prev = newNode;
      positionNode = newNode;

      size++;
      return newNode;
   }

   Node<T>* getFirst() const {
      return first;
   }

   Node<T>* getLast() const {
      return last;
   }

   Node<T>* getAt(const std::size_t position) const {
      if(position < 1 || position > size) {
         throw std::runtime_error("Position out of bound");
      }

      Node<T>* curr = first;
      std::size_t i = 1;

      while(i != position) {
         curr = curr->next;
         i++;
      }

      return curr;
   }

   void removeFirst() {
      if(isEmpty()) {
         return;
      }

      if(size == 1) {
         delete first;
         first = nullptr;
         last = nullptr;
         size = 0;
         return;
      }

      Node<T>* temp = first;
      first = first->next;
      first->prev = nullptr;
      delete temp;
      size--;
   }

   void removeLast() {
      if(isEmpty()) {
         return;
      }

      if(size == 1) {
         delete last;
         first = nullptr;
         last = nullptr;
         size = 0;
         return;
      }

      Node<T>* temp = last;
      last = last->prev;
      last->next = nullptr;
      delete temp;
      size--;
   }

   void removeAt(const std::size_t position) {
      if(position < 1 || position > size) {
         throw std::runtime_error("Position out of bound");
      }

      if(position == 1) {
         removeFirst();
         return;
      } else if(position == size) {
         removeLast();
         return;
      }

      Node<T>* positionNode = getAt(position);
      positionNode->prev->next = positionNode->next;
      positionNode->next->prev = positionNode->prev;
      delete positionNode;
      size--;
   }

   void clear() {
      while(!isEmpty()) {
         removeFirst();
      }
   }

   bool isEmpty() const {
      return size == 0;
   }

   std::size_t getSize() const {
      return size;
   }
};
}
