#include "pandemic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  int i = 0;
  while(line[i] != ',' || line[i] == '\0'){
    if(i == 63){
      perror("Country name is too long!");
      exit(EXIT_FAILURE);
    }
    ans.name[i] = line[i];
    i++;
  }
  
  ans.name[i] ='\0';

  char * p = strchr(line, ',') + 1;
  if(p == NULL || *p == '\0'){
    perror("No population data");
    exit(EXIT_FAILURE);
  }
  

 uint64_t num = atoi(p);
 if(num == 0){
   perror("Invalid population");
   exit(EXIT_FAILURE);
 }else{
  ans.population = num;
 }
 

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if(n_days < 7){
    perror("Invalid number of days");
    exit(EXIT_FAILURE);
  }
  
  for(size_t i = 1; i <= n_days - 6; i++){
    unsigned totalNum = 0;
    for(size_t j = 0; j <= 6; j++){
      totalNum += data[i + j - 1];
    }
    avg[i - 1] = (double)(totalNum / 7.0);
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if(data == NULL || n_days <= 0 || pop <= 0 || cum == NULL ){
    perror("Invalid data!");
    exit(EXIT_FAILURE);
  }
  int totalNum = 0;
  for(size_t i = 0; i < n_days; i++){
    totalNum += data[i];
    cum[i] = totalNum / (double)pop * 100000;

  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  char *maxCountryName = NULL;
  unsigned maxNumberCase = 0;
  for (size_t i = 0; i < n_countries; i++){
    for (size_t j = 0; j < n_days; j++){
      if(data[i][j] > maxNumberCase){
        maxNumberCase = data[i][j];
        maxCountryName = countries[i].name;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", maxCountryName, maxNumberCase);
}
