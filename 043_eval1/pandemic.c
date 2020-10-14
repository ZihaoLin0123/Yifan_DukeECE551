#include "pandemic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint64_t findNumber(char * line);
void stripNewLine(char * str);

/*
Translate given line into the country struct
country_name,population
*/
country_t parseLine(char * line) {
  country_t ans;
  if(line == NULL){
    perror("No data");
    exit(EXIT_FAILURE);
  }
  stripNewLine(line);
  size_t i = 0;
  //read the data before comma
  while(line[i] != ',' && line[i] != '\0'){
    //judge whether the country name is longer than the length of array
    if(i == 63){
      perror("Country name is too long!");
      exit(EXIT_FAILURE);
    }
    ans.name[i] = line[i];
    i++;
  }
  if(i == 0){
    perror("No country name");
    exit(EXIT_FAILURE);
  }
  ans.name[i] ='\0';
  ans.population = findNumber(line);//get the population number
  return ans;
}

/*
Translate a string of population into number
*/
uint64_t findNumber(char * line){
  char *p = strchr(line, ',');
  if(p == NULL){
    perror("No comma");
    exit(EXIT_FAILURE);
  }
  p++;
  char *tempt = p;
  //judge whether each character is a number
  while (*tempt != '\0'){
    if(*tempt < '0' || *tempt > '9'){
      printf("%d",*tempt);
      perror("Invalid population");
      exit(EXIT_FAILURE);
    }
    tempt++;
  }
  if(tempt == p){//if pointer tempt is not moved, then there is no data
    perror("No population data!");
    exit(EXIT_FAILURE);
  }
  return atoi(p);
}

/*
Replace '\n' in the str into '\0';
*/
void stripNewLine(char * str){
  char * p = strchr(str, '\n');
  if(p != NULL){
    *p = '\0';
  }
}

/*
calculates the seven-day running average of case data.
*/
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  if(data == NULL || avg == NULL){
    perror("Null array!");
    exit(EXIT_FAILURE);
  }
  if(n_days < 7){
    perror("Invalid number of days");
    exit(EXIT_FAILURE);
  }
  //There are total n_days - 6 possible 7-day avg
  for(size_t i = 1; i <= n_days - 6; i++){
    unsigned totalNum = 0;
    //Calculate the total cases of 7 days
    for(size_t j = 0; j <= 6; j++){
      totalNum += data[i + j - 1];
    }
    avg[i - 1] = (double)(totalNum / 7.0);
  }
}

/*
calculates the cumulative number of cases that day per 100,000 people
*/
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  if(data == NULL || n_days <= 0 || pop <= 0 || cum == NULL ){
    perror("Invalid data!");
    exit(EXIT_FAILURE);
  }
  uint64_t totalNum = 0;
  //Calculate the cumulative cases for each day
  for(size_t i = 0; i < n_days; i++){
    totalNum += data[i];
    cum[i] = totalNum / (double)pop * 100000;
  }
}

/*
print the country with max daily cases
*/
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  char *maxCountryName = NULL;
  unsigned maxNumberCase = 0;
  //Traverse all countries
  for (size_t i = 0; i < n_countries; i++){
    //Traverse all days for a country to get the max day cases
    for (size_t j = 0; j < n_days; j++){
      if(data[i][j] > maxNumberCase){
        maxNumberCase = data[i][j];
        maxCountryName = countries[i].name;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", maxCountryName, maxNumberCase);
}
