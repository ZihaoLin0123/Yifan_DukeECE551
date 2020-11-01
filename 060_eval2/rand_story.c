#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
find the start of the next word after '_'
*/
char * findNextWord(char * index){
    while(*index != '_'){
        index++;
    }
    *index = '\0';
    return index + 1;
}

/*
check the foramt of a line in the story
*/
void checkStoryFormat(char * line){
    size_t count = 0;
    while(*line != '\0'){
        if (*line == '_' ){
            count++;
        }
        line++;
    }
    if(count % 2 != 0){
        fprintf(stderr, "invalid _name_");
        exit(EXIT_FAILURE);
    }
}

/*
append a string from the source to the target
count: current size of the target
*/
char* copyString(char * target, size_t * count, const char * source){
    if(target == NULL){
        //realloc the target and copy the string
        target = realloc(target, (strlen(source) + 1) * sizeof(*target));
        target = strcpy(target, source);
    }else{
        //increase the count
        size_t length = strlen(source) + *count + 1;
        *count = length;
        //append the new content into the target
        target = realloc(target, (length + 1) * sizeof(*target));
        target = strcat(target, source);
    }
    return target;

}


/*
build a catarray from the given file
*/
catarray_t * buildCategoryArray(FILE * f){
    catarray_t *catarray = malloc(sizeof(*catarray));
    catarray->arr = NULL;
    catarray->n = 0;
    char *line = NULL;
    size_t sz = 0;
    while(getline(&line, &sz, f) >= 0){
        //add a entry into the catarray
        addEntry(line, catarray);
    }
    free(line);
    return catarray;    
}

/*
add one entry into the catarray
*/
void addEntry(char * line, catarray_t * catarray){
    stripNewLine(line);
    //check the format, there must a ':'
    if(strchr(line, ':') == NULL){
        fprintf(stderr, "invalid input");
        exit(EXIT_FAILURE);
    }
    //locate the ':', replace it with '\0'
    //then, seperatly extract the category name and word
    char *splitIndex = strchr(line, ':');
    *splitIndex = '\0';
    char * categoryName  = copyString(NULL, NULL,line);//extract categoryName 
    char * word  = copyString(NULL, NULL,splitIndex + 1);//extract word 
    if(catarray->arr == NULL){
        buildCategory(categoryName, word, catarray);
    }else{
        addWord(categoryName, word, catarray);
    }
}

/*
add a new category into categoryName
*/
void buildCategory(char * categoryName, char * word, catarray_t * catarray){
    catarray->n++;
    catarray->arr = realloc(catarray->arr, catarray->n * sizeof(*catarray->arr));
    catarray->arr[catarray->n - 1].name = categoryName;
    //put the word into the category
    catarray->arr[catarray->n - 1].words = malloc(sizeof(*(catarray->arr[catarray->n - 1].words)));
    catarray->arr[catarray->n - 1].words[0] = word;
    catarray->arr[catarray->n - 1].n_words = 1;
}

/*
add a word into the catarray
*/
void addWord(char * categoryName, char * word, catarray_t * catarray){
    for (size_t i = 0; i < catarray->n; i++){
        if(strcmp(catarray->arr[i].name, categoryName) == 0){ //judge whether the category name is existed.
            free(categoryName);//if yes, don't need to add it again. 
            //add the word into the existed category
            catarray->arr[i].n_words += 1;
            catarray->arr[i].words = realloc(catarray->arr[i].words, 
                                            catarray->arr[i].n_words * sizeof(*(catarray->arr[i].words)));
            catarray->arr[i].words[catarray->arr[i].n_words - 1] = word;
            return;
        }
    }
    //if the word belongs to a new category, we create a new category.
    buildCategory(categoryName, word, catarray);
}

/*
replace '\n' with '\0'
*/
void stripNewLine(char * line){
    char * index = strchr(line, '\n');
    if(index != NULL){
        *index = '\0';
    } 
}

/*
free catarray
*/
void freeCatarray(catarray_t * catarray){
    for (size_t i = 0; i < catarray->n; i++){
        for(size_t j = 0; j < catarray->arr[i].n_words; j++){
            free(catarray->arr[i].words[j]);
        }
        free(catarray->arr[i].words);
        free(catarray->arr[i].name);
    }
    free(catarray->arr);
    free(catarray);
}

/*
free category
*/
void freeCategory(category_t * usedWords){
    for(size_t j = 0; j < usedWords->n_words; j++){
            free(usedWords->words[j]);
        }
        free(usedWords->words);
        free(usedWords);

}

/*
delete a used word
*/
void deleteUsedWord(const char * word, const char * categoryName, catarray_t * catarray){
    char ** mywords = NULL; // new category
    for (size_t i = 0; i < catarray->n; i++){
        //when find the category the word belongs to
        if(strcmp(categoryName, catarray->arr[i].name) == 0){
            //if only one word left in the category, then free it and set the category to NULL
            if(catarray->arr[i].n_words == 1){
                free(catarray->arr[i].words[0]);
                free(catarray->arr[i].words);
                catarray->arr[i].words = NULL;
                catarray->arr[i].n_words = 0;
                return;
            }
            //copy the unsed word into the new category "mywords"
            size_t number = 0;
            for (size_t j = 0; j < catarray->arr[i].n_words; j++){
                if(strcmp(word, catarray->arr[i].words[j]) != 0){
                    mywords = realloc(mywords, (number + 1) * sizeof(*mywords));
                    mywords[number] = malloc((strlen(catarray->arr[i].words[j]) + 1) * sizeof(*mywords[number]));
                    mywords[number] = strcpy(mywords[number], catarray->arr[i].words[j]);
                    number++;
                }
            }
            //free the old category
            for (size_t j = 0; j < catarray->arr[i].n_words; j++){
              free(catarray->arr[i].words[j]);
            }
            free(catarray->arr[i].words);
            //update the category
            catarray->arr[i].words = mywords;
            catarray->arr[i].n_words = number;
            return;
        }
    }
}


/*
judge whether the given str is a number
*/
int isNumber(char * str){
    if(*str == '\0'){
        return 0;
    }
    while(*str != '\0'){
        if(isdigit(*str) == 0){
            return 0;
        }
        str++;
    }
    return 1;
}

/*
add a used word into used word array
*/
void addUsedWords(category_t * usedWords, const char * word){
    usedWords->words = realloc(usedWords->words, (usedWords->n_words + 1) * sizeof(*(usedWords->words)));
    usedWords->words[usedWords->n_words] = malloc((strlen(word) + 1) * sizeof(*(usedWords->words[usedWords->n_words])));
    usedWords->words[usedWords->n_words] = strcpy(usedWords->words[usedWords->n_words], word);
    usedWords->n_words++;
}

/*
choose a used word based on the given index
*/
char * chooseUsedWords(size_t index, category_t * usedWords){
    //check whether the index is valid
    if (index > usedWords->n_words || index < 1){
        fprintf(stderr, "number in the blank is too large");
        exit(EXIT_FAILURE);
    }else{
        char * word = usedWords->words[usedWords->n_words - index];
        addUsedWords(usedWords, word);
        return word;
    }
}
