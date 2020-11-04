#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


using namespace std;
void stripNewLine(char * str);
int main(){
  string str3, str4;
  char *str1 = NULL;
  char *str2 = NULL;
  size_t sz = 0;
  getline(&str1, &sz, stdin);
  getline(&str2, &sz, stdin);
  stripNewLine(str1);
  stripNewLine(str2);
  while(*str1 != '\0'){
    str3 = str3 + *str1;
    str1++;
  }
  while(*str2 != '\0'){
    str4 = str4 + *str2;
    str2++;
  }
  str3.append(str4);
  printf("%s", str3.c_str());
  free(str1);
  free(str2);
  return 0;
}




void stripNewLine(char * str){
  char * temp = strchr(str, '\n');
  if(temp != NULL){
    *temp = '\0';
  }
}