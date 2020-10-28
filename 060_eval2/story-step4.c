#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv){
    if(argc < 3){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
    int option = 0;
    FILE *categoryFile = NULL;
    FILE *storyFile = NULL;
    if(argc == 3){
        categoryFile = fopen(argv[1], "r");
        storyFile = fopen(argv[2], "r");
    }else if(argc == 4){
        if(strcmp(argv[1], "-n") == 0){
            option = 1;
        }else{
            fprintf(stderr, "invalid option instruction");
            exit(EXIT_FAILURE);
        }
        categoryFile = fopen(argv[2], "r");
        storyFile = fopen(argv[3], "r");
    }
        
    if(categoryFile == NULL || storyFile == NULL){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }

    catarray_t * catarray = buildCategoryArray(categoryFile);
    category_t * usedWords = malloc(sizeof(*usedWords));
    usedWords->name = "usedWords";
    usedWords->words = NULL;
    usedWords->n_words = 0;
    char *line = NULL;
    size_t sz = 0;
    while(getline(&line, &sz, storyFile) >= 0){
       char * str = constructLine(line, catarray, usedWords, option);
       printf("%s", str);
       free(str);
    }
    free(line);
    freeCatarray(catarray);
    freeCategory(usedWords);
    if (fclose(categoryFile) != 0 || fclose(storyFile) != 0) {
        fprintf(stderr, "Failed to close the input file!");
        exit(EXIT_FAILURE);
    }
}