#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printArr(FILE * f){
   size_t size = 0;
    char ** myArr = NULL;
  char * line = NULL;
  size_t len = 0;
  
   while(getline(&line, &len, f) >= 0){
       size++;
       myArr =realloc( myArr, size * sizeof(*myArr));
       myArr[size - 1] = line;
       line = NULL;
       
   }
    free(line);
     
     sortData(myArr, size);

  
  for (size_t i = 0; i < size; i++){
    printf("%s", myArr[i]);
    free(myArr[i]);
    }

    free(myArr);

}
int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
 
  if (argc == 1) {
      FILE* f = stdin;
      if (f == NULL){
       fprintf(stderr,"count not find the file ");
      return EXIT_FAILURE;
      }
      printArr(f);   
  }else{
    for(size_t i = 1; i < argc; i++ ){
      FILE *f = fopen(argv[i], "r");

      if (f == NULL){
    fprintf(stderr,"count not find the file ");
     return EXIT_FAILURE;
     
  }
      printArr(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }


    }
    

  }
  
  return EXIT_SUCCESS;
}
