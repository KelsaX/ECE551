#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);

    IntList il2(il);
    assert(il2.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il3;
    il3.addFront(5);
    IntList::Node * node1 = il3.head;

    //      il3.addFront(5);
    assert(il3[0] == 5);
    assert(il3.tail == il3.head);
    assert(il3.tail->next == NULL);
    assert(il3.head->prev == NULL);
    assert(il3.getSize() == 1);
    /////////////////
    assert(node1->data == 5);
    assert(node1->prev == NULL);
    assert(node1->next == NULL);
    /////////////
    assert(il3.tail = node1);

    //    assert(il3.find(5) == 1);

    il3.addFront(6);

    IntList::Node * node2 = il3.head;

    assert(il3.head == node2);
    assert(il3.tail == node1);
    assert(node2->data == 6);
    assert(node1->data == 5);
    assert(node1->prev == node2);
    assert(node1->next == NULL);
    assert(node2->prev == NULL);
    assert(node2->next == node1);
    ////////////////////
    assert(il3.head == node2);
    assert(il3.tail == node1);
    assert(il3[0] == 6);
    assert(il3[1] == 5);

    ///////////////
    assert((*(il3.tail)).prev == il3.head);
    assert((il3.tail)->next == NULL);
    assert(il3.head->data == 6);
    assert(il3[1] == 5);
    assert(il3[0] == 6);
    assert((*(il3.head)).prev == NULL);
    assert((il3.head)->next == il3.tail);
    assert(node1->data == 5);
    assert(node2->data == 6);

    // WRITE ME
  }
  // many more tester methods

  void testAddBack() {
    IntList il4;
    ///////add 1 num
    il4.addBack(8);
    IntList::Node * node1 = il4.head;
    ////////////list
    assert(il4.head == node1);
    assert(il4.tail == node1);
    assert(il4[0] = 8);
    //////////node
    assert(node1->prev == NULL);
    assert(node1->next == NULL);
    assert(node1->data == 8);
    assert(il4.head->data == 8);
    assert(il4.head == il4.tail);
    ///////////add 2 num
    il4.addBack(9);
    IntList::Node * node2 = il4.tail;
    ///////list
    assert(il4.head == node1);
    assert(il4.tail == node2);
    assert(il4[0] == 8);
    assert(il4[1] == 9);
    /////////////////node

    assert(node2->next == NULL);
    assert(node2->prev == node1);
    assert(node2->data == 9);
    assert(node1->prev == NULL);
    assert(node1->next == node2);
    assert(node1->data == 8);
    assert(il4[1] = 9);
    assert(il4[0] = 8);
    assert(il4.head->prev == NULL);
    assert(il4.head->next == il4.tail);
  }
  void ruleOfThree() {
    ////////////////////////////////    ///////////copy constructor

    IntList il5;
    ///add num 1
    il5.addBack(6);
    //il5.addBack(5);
    IntList il6(il5);
    IntList::Node * node1 = il6.head;
    //////list6
    assert(il6[0] == 6);
    assert(il6.getSize() == 1);
    assert(il6.head = il6.tail);
    ////////node1
    assert(node1->data == 6);
    assert(node1->prev == NULL);
    assert(node1->next == NULL);
    assert(node1 != il5.head);
    ////////////add num2
    il5.addBack(5);
    IntList il8(il5);
    IntList::Node * node2 = il8.head;
    IntList::Node * node3 = il8.tail;
    //////list8
    assert(il8[0] == 6);
    assert(il8[1] == 5);
    assert(il8.head != il5.head);
    assert(il8.tail != il5.tail);
    /////////////////node
    assert(node2->data == 6);
    assert(node3->data == 5);
    assert(node2->prev == NULL);
    assert(node2->next == node3);
    assert(node3->prev == node2);
    assert(node3->next == NULL);

    //////////////////////////////////////////////////////////assign copy
    //  il5.addBack(8);
    IntList il88;
    il88 = il5;
    assert(il5.head != il88.head);
    assert(il5.tail != il88.tail);
    assert(il88.getSize() == 2);
    assert(il88[0] == 6);
    assert(il88[1] == 5);
    assert(il88.tail->next == NULL);
    IntList il99;
    il88.addBack(8);
    il99.addBack(1);
    il99.addBack(3);
    il99.addBack(2);
    il99.addBack(0);
    il99 = il88;
    assert(il99.tail != il88.tail);
    assert(il99.getSize() == 3);
    assert(il99.head != il88.head);
    assert(il99.tail->next == NULL);
    assert(il99.tail->prev->data == 5);

    assert(il99.tail->data == 8);

    assert(il99.head->data == 6);
    assert(il99.head->next->data == 5);
    assert(il99.head->prev == NULL);

    // IntList::Node * node5 = il6.head;
    /////////////////////////delete
    IntList * il9 = new IntList(il6);
    IntList * il10 = new IntList();
    delete il10;
    delete il9;
    /*
    /////////////new
    IntList * dut1 = new IntList();
    dut1->addFront(1);
    IntList * dut2 = new IntList(*dut1);
    assert(dut1->head != dut2->head);
    assert(dut1->tail != dut2->tail);
    delete dut2;
    dut1->addBack(2);
    IntList * dut3 = new IntList(*dut1);
    delete dut1;
    dut3->remove(1);
    delete dut3;
        IntList * dut1 = new IntList();
    dut1->addBack(1);
    dut1->addBack(2);
    IntList * dut2 = new IntList();
    dut2->addFront(1);
    dut2->addFront(2);
    dut2->addFront(3);
    *dut2 = *dut1;
    assert(dut2->getSize() == 2);
    assert(dut1->head != dut2->head);
    assert(dut1->tail != dut2->tail);
    assert(dut2->tail->next == NULL);
    delete dut1;
    delete dut2;
    */
    // IntList * il11 = new IntList();
    // IntList * il12 = new IntList(*il11);
    // assert(il11->head != il12->head);
    // assert(il12->head == il12->tail);
    // assert(il12->head == NULL);
    // assert(il12->head == NULL);
    // assert(il12->getSize() == 0);
    // delete il11;
  }
  /*
  void testCopyCtor() {
    IntList il0;
    il0.addBack(1);
    il0.addBack(-1);
    il0.addBack(0);

    IntList il1(il0);
    assert(il0.getSize() == 3);
    assert(il1.getSize() == 3);  // test 10
    IntList::Node * curr0 = il0.head;
    IntList::Node * curr1 = il1.head;
    assert(curr1->data == 1 && curr1->prev == NULL && curr1->next != NULL);
    assert(curr0 != curr1);  // test 11
    curr1 = curr1->next;
    curr0 = curr0->next;
    assert(curr1->data == -1 && curr1->prev != NULL && curr1->next != NULL);
    assert(curr1->prev->data == 1);
    assert(curr0 != curr1);
    assert(curr0->prev != curr1->prev);
    curr1 = curr1->next;
    curr0 = curr0->next;
    assert(curr1->data == 0 && curr1->prev != NULL && curr1->next == NULL);
    assert(curr1->prev->data == -1);
    assert(curr0 != curr1);
    assert(curr0->prev != curr1->prev);
    assert(il1.tail == curr1);

    IntList il2;
    IntList il3(il2);
    assert(il3.head == NULL && il3.tail == NULL);
   */
  /*
  void testAssignOp() {
    IntList il0;
    il0.addBack(1);
    il0.addBack(-1);
    il0.addBack(0);
    il0 = il0;
    assert(il0.getSize() == 3);
    assert(il0[0] == 1 && il0[1] == -1 && il0[2] == 0);
    assert(il0.head->data == 1);
    assert(il0.tail->data == 0);

    IntList il1;
    il1.addBack(4);
    il1.addBack(-90);
    il1.addBack(213);
    il1.addBack(32);
    il1 = il0;
    assert(il1.getSize() == 3);
    assert(il1[0] == 1 && il1[1] == -1 && il1[2] == 0);
    assert(il1.head->data == 1);
    assert(il1.tail->data == 0);
  }
  */
  void testRemove() {
    //////empty list
    IntList il1;

    assert(il1.remove(1) == false);
    /////////no find
    il1.addBack(5);
    IntList::Node * node1 = il1.tail;
    il1.addBack(6);
    IntList::Node * node2 = il1.tail;
    il1.addBack(8);
    IntList::Node * node3 = il1.tail;
    il1.addBack(6);
    IntList::Node * node4 = il1.tail;

    ///no find
    assert(il1.remove(2) == false);
    ///delete 6
    assert(il1.remove(6) == true);
    assert(node1->data == 5);
    assert(node3->data == 8);
    assert(node4->data == 6);
    assert(il1.getSize() == 3);
    assert(node1->next == node3);
    assert(node1->prev == NULL);
    assert(node3->next == node4);
    assert(node3->prev == node1);
    assert(node4->next == NULL);
    assert(node4->prev == node3);
    assert(il1.head == node1);
    assert(il1.tail == node4);
    assert(il1[0] == 5);
    assert(il1[1] == 8);
    assert(il1[2] == 6);
    assert(il1.getSize() == 3);
    ///delete 6
    assert(il1.remove(6) == true);
    assert(node1->data == 5);
    assert(node3->data == 8);
    assert(node1->next == node3);
    assert(node1->prev == NULL);
    assert(node3->next == NULL);
    assert(node3->prev == node1);
    assert(il1.head == node1);
    assert(il1.tail == node3);
    assert(il1[0] == 5);
    assert(il1[1] == 8);
    assert(il1.getSize() == 2);
    ///delete 5
    assert(il1.remove(5) == true);
    assert(node3->data == 8);
    assert(node3->next == NULL);
    assert(node3->prev == NULL);
    assert(il1.head == node3);
    assert(il1.tail == node3);
    assert(il1[0] == 8);
    assert(il1.getSize() == 1);
    ///delete 8
    assert(il1.remove(8) == true);
    assert(il1.head == NULL);
    assert(il1.tail == NULL);
    assert(il1.getSize() == 0);
  }
  // many more tester methods
};
int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.ruleOfThree();
  // t.testCopyCtor();
  //  t.testAssignOp();

  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
