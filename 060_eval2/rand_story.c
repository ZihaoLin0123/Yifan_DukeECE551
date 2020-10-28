#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//step1
void deleteUsedWord(const char * word, const char * categoryName, catarray_t * catarray){
    char ** mywords = NULL;
    for (size_t i = 0; i < catarray->n; i++){
        if(strcmp(categoryName, catarray->arr[i].name) == 0){
            if(catarray->arr[i].n_words == 1){
                free(catarray->arr[i].words[0]);
                free(catarray->arr[i].words);
                catarray->arr[i].words = NULL;
                catarray->arr[i].n_words = 0;
                return;
            }
           
            size_t number = 0;
            for (size_t j = 0; j < catarray->arr[i].n_words; j++){
                 
                if(strcmp(word, catarray->arr[i].words[j]) != 0){
                   
                    mywords = realloc(mywords, (number + 1) * sizeof(*mywords));
                    mywords[number] = malloc((strlen(catarray->arr[i].words[j]) + 1) * sizeof(*mywords[number]));
                    mywords[number] = strcpy(mywords[number], catarray->arr[i].words[j]);
                    
                    number++;
                }
              
               
                
            }
            for (size_t j = 0; j < catarray->arr[i].n_words; j++){
              free(catarray->arr[i].words[j]);
            
            }
            
            free(catarray->arr[i].words);
            catarray->arr[i].words = mywords;
            catarray->arr[i].n_words = number;

            return;
        }
    }
    
}

int isNumber(char * str){
    while(*str != '\0'){
        if(isdigit(*str) == 0){
            return 0;
        }
        str++;
    }
    return 1;
}

void addUsedWords(category_t * usedWords, const char * word){
    usedWords->words = realloc(usedWords->words, (usedWords->n_words + 1) * sizeof(*(usedWords->words)));
    usedWords->words[usedWords->n_words] = malloc((strlen(word) + 1) * sizeof(*(usedWords->words[usedWords->n_words])));
    usedWords->words[usedWords->n_words] = strcpy(usedWords->words[usedWords->n_words], word);
    usedWords->n_words++;
}

char * chooseUsedWords(size_t index, category_t * usedWords){
    if (index > usedWords->n_words || index < 1){
        fprintf(stderr, "number in the blank is too large");
        exit(EXIT_FAILURE);
    }else{
        char * word = usedWords->words[usedWords->n_words - index];
        addUsedWords(usedWords, word);
        return word;
    }
}

void printStory(FILE * f){
    char *line = NULL;
    size_t sz = 0;
    while(getline(&line, &sz, f) >= 0){
       char * str = constructLine(line, NULL, NULL, 0);
       printf("%s", str);
       free(str);
    }
    free(line);
}

char * constructLine(char * line, catarray_t * catarray, category_t * usedWords, int option){
    size_t count = 0;
    size_t *count_p = &count;
    char * start = line;
    char * end = NULL;
    checkStoryFormat(line);
    char * str = malloc(sizeof(*str));
    str[0] = '\0';
    while(*line != '\0'){
        if(*line == '_'){
            end = line;
            *end = '\0';
            line = findNextWord(line);
            //printf("next word %c", *line);
            str = copyString(str, count_p, start);
            //printf("%s", str);
            char *categoryName = end + 1;
            const char * chosenWord = NULL;
            if(option == -1){
                chosenWord = chooseWord(categoryName, NULL);
                str = copyString(str, count_p, chosenWord);
            }else if(isNumber(categoryName) == 0){ 
                chosenWord = chooseWord(categoryName, catarray);
                str = copyString(str, count_p, chosenWord);
                addUsedWords(usedWords, chosenWord);
                if(option == 1){
                    deleteUsedWord(chosenWord, categoryName, catarray);
                }
                //str = insertCategory(str, categoryName, count_p, catarray, usedWords);
            }else if(usedWords != NULL){
                chosenWord = chooseUsedWords(atoi(categoryName), usedWords);
                str = copyString(str, count_p, chosenWord);
            }
            
            
            start = line;
            end = NULL;
        }else{
            line++;
        }
    }
    if(*start != '\0'){
        str = copyString(str, count_p, start);
    }
    return str;
}
char * findNextWord(char * index){
    while(*index != '_'){
        index++;
    }
    *index = '\0';
    return index + 1;
}



void checkStoryFormat(char * line){
    size_t count = 0;
    char * start = NULL;
    while(*line != '\0'){
        if (*line == '_' ){
            count++;
            if(count % 2 == 1){
                start = line;
            }else if(count > 0){
                if(start + 1 == line){
                    fprintf(stderr, "empty category name in the blank!");
                    exit(EXIT_FAILURE);
                }
            }
        }
        line++;
    }
    if(count % 2 != 0){
        fprintf(stderr, "invalid _name_");
        exit(EXIT_FAILURE);
    }
}







//step2






char* copyString(char * target, size_t * count, const char * source){
    if(target == NULL){
        target = realloc(target, (strlen(source) + 5) * sizeof(*target));
        target = strcpy(target, source);
    }else{
    size_t length = strlen(source) + *count + 1;
    *count = length;
    target = realloc(target, (length + 1) * sizeof(*target));
    target = strcat(target, source);
    }
    return target;

}



catarray_t * buildCategoryArray(FILE * f){
    catarray_t *catarray = malloc(sizeof(*catarray));
    catarray->arr = NULL;
    catarray->n = 0;
    char *line = NULL;
    size_t sz = 0;
    while(getline(&line, &sz, f) >= 0){
        addEntry(line, catarray);
        //line = NULL;
    }
    free(line);
    return catarray;    
}

void addEntry(char * line, catarray_t * catarray){

    stripNewLine(line);
    checkFormat(line);
    
    //char * categoryName = line;
    char *splitIndex = strchr(line, ':');
    //char *word = splitIndex + 1;
    *splitIndex = '\0';
    char * categoryName  = copyString(NULL, NULL,line); 
    ///char * categoryName = malloc((strlen(line) + 1) * sizeof(*categoryName));
    //categoryName = strcpy(categoryName, line);
    char * word  = copyString(NULL, NULL,splitIndex + 1); 

    if(catarray->arr == NULL){
        buildCategory(categoryName, word, catarray);
    }else{
        addWord(categoryName, word, catarray);
    }
}

void buildCategory(char * categoryName, char * word, catarray_t * catarray){
    catarray->n++;
    catarray->arr = realloc(catarray->arr, catarray->n * sizeof(*catarray->arr));
    catarray->arr[catarray->n - 1].name = categoryName;
    catarray->arr[catarray->n - 1].words = malloc(sizeof(*(catarray->arr[catarray->n - 1].words)));
    catarray->arr[catarray->n - 1].words[0] = word;
    catarray->arr[catarray->n - 1].n_words = 1;
}


void addWord(char * categoryName, char * word, catarray_t * catarray){
    for (size_t i = 0; i < catarray->n; i++){
        if(strcmp(catarray->arr[i].name, categoryName) == 0){
            free(categoryName);
             
                for (size_t j = 0; j < catarray->arr[i].n_words; j++){
                    if(strcmp(catarray->arr[i].words[j], word) == 0){
                        free(word);
                        return;
                    }
                }
            
            catarray->arr[i].n_words += 1;
            catarray->arr[i].words = realloc(catarray->arr[i].words, 
                                            catarray->arr[i].n_words * sizeof(*(catarray->arr[i].words)));
            catarray->arr[i].words[catarray->arr[i].n_words - 1] = word;
            return;
        }
    }
    buildCategory(categoryName, word, catarray);
    
}




void checkFormat(char * line){
    if(strlen(line) < 3){
        fprintf(stderr, "invalid category file!");
        exit(EXIT_FAILURE);
    }
    char* index = line;
    size_t count = 0;
    while(*index != '\0'){
        if(*index == ':'){
            count++;
            if(count > 1){
                fprintf(stderr, "invalid category file!");
                exit(EXIT_FAILURE);
            }else if(index == line){
                fprintf(stderr, "invalid category file!");
                exit(EXIT_FAILURE);
            }
        }
        index++;
    }
    
}


void stripNewLine(char * line){
    char * index = strchr(line, '\n');
    if(index != NULL){
        *index = '\0';
    } 
}

void freeCatarray(catarray_t * catarray){
    printf("freecataary");
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

void freeCategory(category_t * usedWords){
    for(size_t j = 0; j < usedWords->n_words; j++){
            free(usedWords->words[j]);
        }
        free(usedWords->words);
        free(usedWords);

}