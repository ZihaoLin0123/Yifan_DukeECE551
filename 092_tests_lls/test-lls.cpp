#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "il.h"

void testList(void) {
  IntList list1;
  assert(list1.head == NULL);

  assert(list1.tail == NULL);
  if (list1.getSize() != 0)
    exit(EXIT_FAILURE);
  list1.addFront(3);
  if (list1.head != list1.tail)
    exit(EXIT_FAILURE);
  if (list1.getSize() != 1)
    exit(EXIT_FAILURE);
  if (list1.head->data != 3)
    exit(EXIT_FAILURE);
  list1.addFront(4);
  if (list1.head->next != list1.tail)
    exit(EXIT_FAILURE);
  if (list1.head->data != 4)
    exit(EXIT_FAILURE);
  if (list1.getSize() != 2)
    exit(EXIT_FAILURE);
  IntList list2;
  list2.addBack(3);
  if (list2.head != list2.tail)
    exit(EXIT_FAILURE);
  if (list2.getSize() != 1)
    exit(EXIT_FAILURE);
  if (list2.head->data != 3)
    exit(EXIT_FAILURE);
  list2.addBack(4);
  if (list2.head->next != list2.tail)
    exit(EXIT_FAILURE);
  if (list2.head->data != 3)
    exit(EXIT_FAILURE);
  if (list2.getSize() != 2)
    exit(EXIT_FAILURE);
  IntList list3(list1);
  if (list3.head == list1.head)
    exit(EXIT_FAILURE);
  if (list3.head->next == list1.head->next)
    exit(EXIT_FAILURE);
  if (list1.tail == list3.tail)
    exit(EXIT_FAILURE);
  if (list3.head->data != list1.head->data)
    exit(EXIT_FAILURE);
  list1 = list2;
  if (list2.head == list1.head)
    exit(EXIT_FAILURE);
  if (list2.head->next == list1.head->next)
    exit(EXIT_FAILURE);
  if (list1.tail == list2.tail)
    exit(EXIT_FAILURE);
  if (list2.head->data != list1.head->data)
    exit(EXIT_FAILURE);
  list1.addBack(3);
  if (list1.find(2) != -1)
    exit(EXIT_FAILURE);
  if (list1.find(3) != 0)
    exit(EXIT_FAILURE);
  if (list1.find(4) != 1)
    exit(EXIT_FAILURE);
  if (list1.remove(4) != true)
    exit(EXIT_FAILURE);
  if (list1.remove(2) != false)
    exit(EXIT_FAILURE);
  if (list1.head->next != list1.tail)
    exit(EXIT_FAILURE);
  if (list1.getSize() != 2)
    exit(EXIT_FAILURE);
  if (list1.head->data != 3)
    exit(EXIT_FAILURE);
  if (list1.remove(3) != true)
    exit(EXIT_FAILURE);
  if (list1.head != list1.tail)
    exit(EXIT_FAILURE);
  if (list1.getSize() != 1)
    exit(EXIT_FAILURE);
  if (list1.head->data != 3)
    exit(EXIT_FAILURE);
  if (list1.remove(3) != true)
    exit(EXIT_FAILURE);
  if (list1.head != NULL)
    exit(EXIT_FAILURE);
  if (list1.getSize() != 0)
    exit(EXIT_FAILURE);
  if (list1.remove(3) != false)
    exit(EXIT_FAILURE);
  if (list1.getSize() != 0)
    exit(EXIT_FAILURE);
  if (list1.head != list1.tail)
    exit(EXIT_FAILURE);
  list2.addBack(5);
  list2.addFront(6);
  if (list2.getSize() != 4)
    exit(EXIT_FAILURE);
  if (list2[3] != list2.tail->data)
    exit(EXIT_FAILURE);
  if (list2[0] != 6 || list2[1] != 3)
    exit(EXIT_FAILURE);
  if ((list2[0]) != list2.head->data)
    exit(EXIT_FAILURE);
  list2[2] = 8;
  if (list2[2] != 8)
    exit(EXIT_FAILURE);
  list2.remove(list2[2]);
  if (list2.getSize() != 3)
    exit(EXIT_FAILURE);
  if (list2.tail->data != 5)
    exit(EXIT_FAILURE);
  if (list2.head->next != list2.tail->prev)
    exit(EXIT_FAILURE);
    }
    
    int main(void) {
  testList();
  return EXIT_SUCCESS;
}