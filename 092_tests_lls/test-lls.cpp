#include <assert.h>

#include <cstdlib>

#include "il.h"

void testList(void) {
  //create Intlist l1:21

  IntList mylist;
 assert(mylist.head == NULL && mylist.tail == NULL);
  assert(mylist.getSize() == 0);
  assert(mylist.size == 0);


  IntList list1;
    assert(list1.head == NULL && list1.tail == NULL);
  assert(list1.getSize() == 0);
  assert(list1.size == 0);

  

  list1.addBack(1);
  assert(list1.getSize() == 1 && list1.size == 1);
  assert(list1.head != NULL && list1.head == list1.tail);
  list1.addFront(2);
  assert(list1.getSize() == 2 && list1.size == 2);
  assert(list1[0] == 2);
  assert(list1[1] == 1);
  assert(list1.head->next->next == NULL);
  assert(list1.head == list1.head->next->prev);
  assert(list1.tail == list1.head->next);
  
  IntList list2;
  list2 = list1;
    assert(list2[0] == 2);
    assert(list2[1] == 1);
    assert(list2.getSize() == 2 && list2.size == 2);
    assert(list2.head == list2.head->next->prev);
    assert(list2.tail == list2.head->next);
    assert(list2.head->next->next == NULL);
 
  IntList list3(list1);
   assert(list3[0] == 2);
  assert(list3.getSize() == 2 && list3.size == 2);
  assert(list3[1] == 1);
  assert(list3.head == list3.head->next->prev);
  assert(list3.head->next->next == NULL);
  assert(list3.tail == list3.head->next);
 
  list1.addFront(3);
  list1.addFront(4);
  list1.addFront(2);
  list1.addFront(2);
assert(list1.size == 6 && list1.getSize() == 6);
  assert(list1[0] == 2 && list1[1] == 2 && list1[2] == 4);
 
  bool i = list1.remove(2);
assert(i == true);
  assert(list1.size == 5 && list1.getSize() == 5);
  assert(list1[0] == 2 && list1[3] == 2);
   assert(list1.head->next->data == 4);
  assert(list1.head->data == 2);
 
int temp = list1.find(9);
  assert(temp == -1);
   i = list1.remove(10);
  assert(i == false);
  temp = list1.find(2);
  assert(temp == 0);
   temp = list1.find(4);
  assert(temp == 1);
  
 
  list1.addBack(500);
  list1.addBack(100);
  assert(list1[5] == 500 && list1[6] == 100);
  assert(list1.size == 7 && list1.getSize() == 7);
  
 
  list2.remove(2);
  list2.remove(1);
  assert(list2.size == 0 && list2.getSize() == 0 && list2.head == NULL && list2.tail == NULL);
 
  list3.remove(2);
  assert(list3.getSize() == 1 && list3.size == 1 && list3.head == list3.tail && list3.head != NULL);
  assert(list3[0] == 1);
  assert(list3.head->next == NULL && list3.head->prev == NULL);
  
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}