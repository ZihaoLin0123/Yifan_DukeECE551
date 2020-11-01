#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//any functions you want your main to use
void checkStoryFormat(char *line);
char *findNextWord(char *index);
char *copyString(char *str, size_t *count, const char *start);
char * constructLine(char *line, catarray_t * catarray, category_t * usedWords, int option);
int isNumber(char * str);
void addUsedWords(category_t * usedWords, const char * word);
void deleteUsedWord(const char * word, const char * categoryName, catarray_t * catarray);
char * chooseUsedWords(size_t index, category_t * usedWords);
void addEntry(char *line, catarray_t *catarray);
void buildCategory(char *categoryName, char * word, catarray_t *catarray);
void addWord(char *categoryName, char *word, catarray_t *catarray);
void stripNewLine(char *line);
catarray_t * buildCategoryArray(FILE * f);
char* copyString(char * target, size_t * count, const char * source);
void freeCatarray(catarray_t * catarray);
void freeCategory(category_t * usedWords);
#endif
