#include "function.h"
#include <iostream>
#include <math.h>
#include <assert.h>
using namespace std;
class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n), f(fn),mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};

int binarySearchForZero(Function<int, int> * f, int low, int high);

class function1 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) {  return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class function2 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 1; }
};


class function3 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return -1; }
};

class function4 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

class function5 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg - 4.5; }
};



void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int numbers;
  if (high > low) {
    numbers = log(high - low) / log(2) + 1;
  }
  else {
    numbers = 1;
  }
 
  CountedIntFn count(numbers, f, mesg);
 
  int ans = binarySearchForZero(&count, low, high);
 
  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main(){
    function1 f1;
    function2 f2;
    function3 f3;
    function4 f4;
    check(&f1, 0, 150000, 52359,  "error");
    check(&f2, -10, 10, -10, "error");
    check(&f3, -10, 10, 9, "error");
    check(&f4, 0, 0, 0, "error");
     check(&f4, 10, 10, 10, "error");
     check(&f4, -100, 100, 0, "error");
     
      check(&f4, -10, -5, -6, "error");
      check(&f4, 10, 15, 10, "error");
      check(&f4, -99999, 10000000, 0,  "error");
  check(&f4, -99999999, -1000, -1001,  "error");
  check(&f4, 2, 100000000, 2,  "error");
  check(&f4, 0, 0, 0,  "error");
  check(&f4, 10, 10, 10,  "error");
  check(&f4, -1, 10000000, 0,  "error");
  
  function5 f5;
  check(&f5, -10, 11, 5, "error");
  
    return EXIT_SUCCESS;
}