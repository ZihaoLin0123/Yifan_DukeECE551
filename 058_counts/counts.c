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

char* getContent(one_count_t * count){
  char * n = count -> name;
  int num = count -> number;
  char * str = malloc(50 * sizeof(*str));
  memset(str, '\0', 50);
    sprintf(str, "%s", n);
    sprintf(str + strlen(n), ": %d\n", num);

   return str;
   

}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  // int fputs( const char *s, FILE *fp )
  for(int i = 0; i < c -> knownNum; i++){
    char * str = getContent(c->countsArr[i]);
    if(fputs(str, outFile) == -1){
      perror("error");
      exit(EXIT_FAILURE);
    }
    free(str);
  }

  char * strNull = malloc(50 * sizeof(*strNull));
  memset(strNull, '\0', 50);
  sprintf(strNull, "<unknown> : %d\n", c -> unknownNum);
  fputs(strNull, outFile);
  free(strNull);

  
  
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
