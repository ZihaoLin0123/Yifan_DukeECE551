#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include "cyoa.h"
using namespace std;
int main(int argc, char ** argv){
    Story story;
    if(argc < 2){
        cerr << "Please enter a dir" << endl;
        exit(EXIT_FAILURE);
    }
    story.loadStory(argv[1]);
    story.checkValidReference();
    story.checkIsReferenced();
    story.checkWinLosePages();
    story.getReachableSet();
    exit(EXIT_SUCCESS);
   
}