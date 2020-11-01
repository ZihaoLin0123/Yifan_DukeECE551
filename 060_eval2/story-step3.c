#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"
#include "rand_story.h"

char * constructStoryLine(char * line, catarray_t * catarray, category_t * usedWords);
/*
replace blanks in the story with a chosen word
a category will be used to track the used words
if the category name in the blank is a number, then prev used words will be used.
*/
int main(int argc, char ** argv){
    if(argc != 3){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
    FILE* categoryFile = fopen(argv[1], "r");
    FILE* storyFile = fopen(argv[2], "r");
    if(categoryFile == NULL || storyFile == NULL){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
    //build the catarray
    catarray_t * catarray = buildCategoryArray(categoryFile);
    //used to track the used words
    category_t * usedWords = malloc(sizeof(*usedWords));
    usedWords->name = "usedWords";
    usedWords->words = NULL;
    usedWords->n_words = 0;
    char *line = NULL;
    size_t sz = 0;
    while(getline(&line, &sz, storyFile) >= 0){
       char * str = constructStoryLine(line, catarray, usedWords);
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

char * constructStoryLine(char * line, catarray_t * catarray, category_t * usedWords){
    size_t count = 0; //size of the replaced content
    char * start = line; //the start of the content seperated by '_'
    char * end = NULL;  // the end of the content seperated by '_'
    checkStoryFormat(line); //check the format of the line before further action
    char * str = malloc(sizeof(*str));
    str[0] = '\0';
    while(*line != '\0'){
        if(*line == '_'){ //when meet a '_', it is time to replace the word
            end = line;
            *end = '\0';
            // line point to the start of the word after the category name
            // e.g a_b_c   start->'a'  end->first '_'   line->'c'
            line = findNextWord(line); 
            str = copyString(str, &count, start);//append the content before the category name into str
            char *categoryName = end + 1;
            const char *chosenWord = NULL;
            //judge whether the category name is a number
            if (isNumber(categoryName) == 0){
                //if not a number, choose word from the category array
                chosenWord = chooseWord(categoryName, catarray);
                str = copyString(str, &count, chosenWord);
                //add the word into used words array
                addUsedWords(usedWords, chosenWord);
            }else if (usedWords != NULL){
                //if category name is a number, then choose the word from used words
                chosenWord = chooseUsedWords(atoi(categoryName), usedWords);
                str = copyString(str, &count, chosenWord);
            }
            start = line;//loop from the content after the category name
            end = NULL;
        }else{
            line++;
        }
    }
    //append the content after the last category name
    if(*start != '\0'){
        str = copyString(str, &count, start);
    }
    return str;
}