#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n){
  if(n == 0){
    return 0;
  }
  size_t count = 1;
  size_t max = 0;
  for(size_t i = 0; i < n - 1; i++){
    if(array[i] < array[i + 1]){
      count++;
      
    }else{
      if(count > max){
        max = count;
      }
      count = 1;
      
    }
    



  }
  if(count > max)
  {return count;}
  else{return max;}
  


}
