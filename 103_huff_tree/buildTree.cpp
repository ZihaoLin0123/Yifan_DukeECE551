#include "node.h"
#include <stdio.h>
#include <cstdlib>

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  unsigned index = 0;
  while(index <= 256){
    if(counts[index] != 0){
      pq.push(new Node(index, counts[index]));
    }
    ++index;
  }
  Node *node1;
  Node *node2;

  while(pq.size() > 1){
    node1 = pq.top();
    pq.pop();
    node2 = pq.top();
    pq.pop();
    Node *parentNode = new Node(node1, node2);
    pq.push(parentNode);
  }
  return pq.top();
}

