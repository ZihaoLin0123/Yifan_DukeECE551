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
    //load the story
    story.loadStory(argv[1]);
    story.checkValidReference();
    story.checkIsReferenced();
    story.checkWinLosePages();
    //get reachable set
    set<int> visited = story.getReachableSet();
    //for those not in hte reachable set, print it out
    for (int i = 1; i <= story.getTotalPage(); i++){
        if(visited.count(i) == 0){
            cout << "Page " << i << " is not reachable" << endl;
        }
    }
        
    exit(EXIT_SUCCESS);
   
}