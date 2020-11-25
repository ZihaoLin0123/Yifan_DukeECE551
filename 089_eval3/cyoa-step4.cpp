#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <stack>
#include "cyoa.h"
using namespace std;

int main(int argc, char ** argv){
    Story story;
    //load story
    story.loadStory(argv[1]);
    //some check
    story.checkValidReference();
    story.checkIsReferenced();
    story.checkWinLosePages();
    //get reachable set
    set<int> s = story.getReachableSet();
    //find the win path
    story.findWinPath(s);
    exit(EXIT_SUCCESS);
}