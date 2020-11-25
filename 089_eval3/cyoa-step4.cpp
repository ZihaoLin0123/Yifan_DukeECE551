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
    story.loadStory(argv[1]);
    story.checkValidReference();
    story.checkIsReferenced();
    story.checkWinLosePages();
    set<int> s = story.getReachableSet();
    story.findWinPath(s);
    exit(EXIT_SUCCESS);
}