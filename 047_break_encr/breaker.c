#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>




int count(FILE *f){
  int c;
  int arr[26] = {0};
  int max = 0;
  int found;
  while ( (c = fgetc(f)) != EOF ){
    
    if(isalpha(c)){
      arr[c-'a']++;
    }

  }

  for (int i = 0; i < 26; i++){
    if( max < arr[i]){
      max = arr[i];
      found = i;
    }
  }

  return found + 'a';

}

int main(int argc, char ** argv){

  if(argc != 2){
    fprintf(stderr,"please indicate the input file");
    return EXIT_FAILURE;
  }

  FILE *f = fopen(argv[1], "r");

  if (f == NULL){
    fprintf(stderr,"count not find the file ");
     return EXIT_FAILURE;
  }

  int key = (count(f) - 'e' + 26 ) % 26;

  if(0 <= key && key < 25){
    fprintf(stdout,"%d\n", key);
  }else{
    fprintf(stderr,"count not find the file ");
     return EXIT_FAILURE;
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;

}
