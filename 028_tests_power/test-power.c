#include <stdio.h>
#include <stdlib.h>


unsigned power (unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans);

int  main(){
  run_check(2, 3, 8);
  run_check(0, 0, 1);
  run_check(2, 0, 1);
  run_check(1, 1, 1);
  run_check(1, 5, 1);
  run_check(5, 0, 1);
  run_check(-3, 2, 9);
  run_check(-3, 3, -27);
  
  
  run_check(2, 0, 1);
  run_check(0, 0, 1);
  run_check(-2, 3, -8);
  run_check(2, 3, 8);
  run_check(0, 0, 1);
  return 0;

}

void run_check(unsigned x, unsigned y, unsigned expected_ans){

  unsigned ans = power(x, y);
  if(ans == expected_ans){
    //succeed
  }else{
    exit(EXIT_FAILURE);
  }


}


