#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts -> countsArr = NULL;
  counts -> unknownNum = 0;
  counts -> knownNum = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int arrNum = c -> knownNum;
  // const  char * n = name;
  if(name == NULL){
    c -> unknownNum++;
    return;
  }
  
  // if num is not 0, judge whether is in
   if(arrNum != 0){
      for(int i = 0; i < arrNum; i++){
	if(strcmp(c -> countsArr[i] -> name, name) == 0){
	c -> countsArr[i] -> number++;
	return;
      }
    } 
   }

   //if arrNum is 0, or is not in, create new count
  
    int len = strlen(name);
    arrNum++;
    c -> knownNum = arrNum;
    c -> countsArr = realloc(c -> countsArr, arrNum * sizeof(* c -> countsArr) );
    
    one_count_t * one_count = malloc(sizeof(*one_count));
    
    one_count -> name = malloc((len + 1) * sizeof(*one_count -> name));
    strcpy(one_count -> name, name);
    
    one_count -> number = 1;
    c -> countsArr[arrNum - 1] = one_count;
   
    
}


void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  // int fputs( const char *s, FILE *fp )
  for(int i = 0; i < c -> knownNum; i++){
  
    fprintf(outFile, "%s:%d\n", c->countsArr[i]->name, c->countsArr[i]->number);   
    
  }

   if(c -> unknownNum > 0){
  fprintf(outFile, "<unknown>: %d\n", c -> unknownNum);
  }

 

  
  
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(int i = 0 ;i < c -> knownNum; i++){
    free(c -> countsArr[i]->name);
    free(c -> countsArr[i]);
   
  }
   free(c -> countsArr);
    free(c);
}
