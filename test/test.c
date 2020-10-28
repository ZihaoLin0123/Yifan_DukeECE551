#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void checkFormat(char *line);
char *findNextWord(char *index);
char *insertCategory(char *str, char *start, size_t *count);
char *copyString(char *str, size_t *count, const char *start);
void printLine(char * line){
    size_t count = 0;
    size_t *count_p = &count;
    char * start = line;
    char * end = NULL;
    checkFormat(line);
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
            str = insertCategory(str, end + 1, count_p);
            //printf("%s", str);
            start = line;
            end = NULL;
        }else{
            line++;
        }
    }
    if(*start != '\0'){
        str = copyString(str, count_p, start);
    }
    printf("%s", str);

}
char * findNextWord(char * index){
    while(*index != '_'){
        index++;
    }
    return index + 1;

}
char* insertCategory(char * str, char * start, size_t * count){
    char * end = start;
    while(*end != '_'){
        end++;
    }
    *end = '\0';
    const char * categoryName = "hello";
    str = copyString(str, count, categoryName);
    return str;
}

char* copyString(char * str, size_t * count, const char * start){
    size_t length = strlen(start) + *count + 1;
    *count = length;
    str = realloc(str, (length + 1) * sizeof(*str));
    str = strcat(str, start);
    return str;

}

void checkFormat(char * line){
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

int main(){
    char str[] = "ab_fdsf__a_cd";
    printLine(str);
}