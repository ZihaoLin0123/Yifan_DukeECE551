#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"
#include "rand_story.h"


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
   
    char *line = NULL;
    size_t sz = 0;
    while(getline(&line, &sz, f) >= 0){
       char * str = constructLine(line, NULL, NULL, -1);
       printf("%s", str);
       free(str);
    }
    free(line);
    
    
    if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file!");
        exit(EXIT_FAILURE);
    }
   
}
