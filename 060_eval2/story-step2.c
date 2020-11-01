#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"
#include "rand_story.h"

/*
read a file and build a category array
print it out
*/
int main(int argc, char ** argv){
    if(argc != 2){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
    FILE* f = fopen(argv[1], "r");
    if(f == NULL){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
    //construct the category array.
    catarray_t *catarray = buildCategoryArray(f);
    //print it
    printWords(catarray);
    //free it
    freeCatarray(catarray);
    if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file!");
        exit(EXIT_FAILURE);
    }
   
}


