#include "node.h"
#include <assert.h>
using namespace std;
void Node::buildMap(BitString b, std::map<unsigned, BitString> &theMap)
{
  //WRITE ME!
  if (sym != NO_SYM){
    assert(left == NULL && right == NULL);
    theMap.insert(pair<unsigned, BitString>(sym, b));
  }else{
    assert(left != NULL && right != NULL);
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}

