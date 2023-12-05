#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <stdexcept>
//#include<stdexception>
//YOUR CODE GOES HERE
class Tester;
template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node(T data) : data(data), next(NULL), prev(NULL) {}
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  void addFront(const T & item) {
    Node * nodeToadd = new Node(item, head, NULL);
    if (head != NULL) {
      head->prev = nodeToadd;
    }
    head = nodeToadd;

    if (tail == NULL) {
      tail = nodeToadd;
    }
    size++;
  }
  void addBack(const T & item) {
    Node * nodeToadd = new Node(item, NULL, tail);
    if (tail != NULL) {
      tail->next = nodeToadd;
    }
    tail = nodeToadd;
    if (head == NULL) {
      head = nodeToadd;
    }
    size++;
  }

  bool remove(const T & item) {
    Node * current = head;
    while (current != NULL) {
      if (item == current->data) {
        if (current == head) {
          if (current->next != NULL) {
            current->next->prev = NULL;
            head = current->next;
          }
          else {
            head = NULL;
            tail = NULL;
          }
        }
        else if (current == tail) {
          if (current->prev != NULL) {
            current->prev->next = NULL;
            tail = current->prev;
          }
          else {
            head = NULL;
            tail = NULL;
          }
        }

        else {
          current->next->prev = current->prev;
          current->prev->next = current->next;
        }
        delete current;  //delete node
        size--;
        return true;
      }
      current = current->next;
    }
    // delete current;
    return false;
  }
  /*
  bool remove(const T & item) {
    Node * traverse = head;
    while (traverse != NULL && traverse->data != item) {
      traverse = traverse->next;
    }
    if (traverse == NULL) {
      return false;
    }
    Node * nextN = traverse->next;
    Node * prevN = traverse->prev;
    if (nextN != NULL) {
      nextN->prev = prevN;
    }
    else {
      tail = prevN;
    }
    if (prevN != NULL) {
      prevN->next = nextN;
    }
    else {
      head = nextN;
    }
    size -= 1;
    delete traverse;
    return true;
  }
  */
  T & operator[](int index) {
    if (index > size - 1 || index < 0) {
      throw std::out_of_range("the index is out of range!");
    }
    // int count=0;
    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index > size) {
      throw std::out_of_range("the index is out of range");
    }
    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }
  int find(const T & item) const {
    Node * current = head;
    int count = 0;
    while (current != NULL) {
      if (current->data == item) {
        return count;
      }
      count++;
      current = current->next;
    }
    return -1;
  }
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * current = rhs.head;
    while (current != NULL) {
      this->addBack(current->data);
      //  tail = current;
      current = current->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList * temp = new LinkedList(rhs);
      Node * tmphead = NULL;
      Node * tmptail = NULL;
      //  int tmpsize=0;
      tmphead = head;
      head = temp->head;
      temp->head = tmphead;
      tmptail = tail;
      tail = temp->tail;
      temp->tail = tmptail;
      size = temp->size;
    }
    return *this;
  }
  /*
  ~LinkedList() {
    Node * current = head;
    while (head != NULL) {
      current = current->next;
      delete head;
      head = current;
    }
  }
  */
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  int getSize() const { return size; }
  friend class Tester;
};
#endif
