#include <iostream>
#include <stdexcept>
#include "bstmap.h"

int main(){
    
    BstMap<int, int> map;
    map.remove(5);
    map.add(5, 5);
    map.add(3, 3);
    map.add(7, 7);
    map.add(2, 2);
   // map.add(4, 4);
    //map.add(6, 6);
    //map.add(8, 8);

    map.add(7, 100);
    map.pre();
    cout << map.lookup(7) << endl;
    map.add(7, 7);
    //map.remove(8);
    map.remove(5);
     map.remove(3);
      map.remove(7);
       map.pre();
       map.remove(2);
        map.pre();
        map.remove(2);
    map.pre();

  map.remove(1);
    return 0;
}