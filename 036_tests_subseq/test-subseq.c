#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n);
void run_check(int * array, size_t n, size_t expectedAnswer);

int main(){
  int arr1[] = {1, 2, 3, 4};
  int arr2[] = {1, 2, 1, 5};
  int arr3[] = {1, 2, 3, -1, 4,7,9,11};
  int arr4[] = {3,2,1,0};
  int arr5[] = {1,3,5,1,3,5,2,2};
  int arr6[] = {2,2,3,3};
  int arr7[] = { -4,0};
  int arr8[] = {0};
  int arr9[0];
  run_check(arr1, 4, 4);
  run_check(arr2, 4, 2);
  run_check(arr3, 8, 5);
  run_check(arr4, 4, 1);
  run_check(arr5, 8, 3);
  run_check(arr6, 4, 2);
  run_check(arr7, 2, 2);
  run_check(arr8,1,1);
  run_check(arr9,0,0);
  
  
  return 0;


}


void  run_check(int * array, size_t n, size_t expectedAnswer){

  if(expectedAnswer == maxSeq(array, n)){
    //succeed
    printf("Succeed\n");
  }else{
    //fail
    exit(EXIT_FAILURE);

  }





}


