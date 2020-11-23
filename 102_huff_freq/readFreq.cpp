#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>
using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  ifstream f(fname);
  
  if(f.fail()){
    cerr << "can not open file" << endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * ans = new uint64_t[257]();
  char c;
  while(f.get(c)){
    ++ans[(unsigned char)c];
    ++fname;
  }
  ans[256] = 1;
  f.close();
  return ans;
  
}
