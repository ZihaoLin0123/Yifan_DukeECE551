#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1;
  char * ans = malloc(len * sizeof(*ans));
  strcpy(ans, inputName);
  strcpy((ans+strlen(inputName)), suffix);
  // ans[strlen(inputName)] = suffix;
  return ans;

}
