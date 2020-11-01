#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "provided.h"
#include "rand_story.h"

char * constructStoryLine(char * line);
/*
replace the blank in the template file with "cat"
*/
int main(int argc, char ** argv){
    if(argc != 2){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
    FILE* f = fopen(argv[1], "r");//open file
    if(f == NULL){
        fprintf(stderr, "no file is found!");
        exit(EXIT_FAILURE);
    }
   
    char *line = NULL;
    size_t sz = 0;
    //read each line from the input file
    while(getline(&line, &sz, f) >= 0){
        //replace the blank in one line
        char * str = constructStoryLine(line);
        printf("%s", str);
        free(str);
    }
    free(line);
    if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file!");
        exit(EXIT_FAILURE);
    }
   
}

/*
replace the blanks in one line with the chosen word
*/
char * constructStoryLine(char * line){
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
            const char * chosenWord = chooseWord(categoryName, NULL);
            str = copyString(str, &count, chosenWord);//append the chosen word into str
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
