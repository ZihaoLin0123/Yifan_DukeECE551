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
    Page curPage = story.findPage(1);
    while(true){
        curPage.printPage();
        if(curPage.isWIN() || curPage.isLOSE()){
            exit(EXIT_SUCCESS);
        }
        string str;
        cin >> str;
        while(true){
            if(story.isDigit(str)){
                size_t next = atoi(str.c_str());
                if(next > curPage.getReferencedPages().size() || next < 1){
                    cout << "That is not a valid choice, please try again" << endl;
                    cin >> str;
                }else{
                    curPage = story.findPage(curPage.getReferencedPages()[next - 1]);
                    break;
                }
                
            }else{
                cout << "That is not a valid choice, please try again" << endl;
                cin >> str;
            }
        }

    }
    
    exit(EXIT_SUCCESS);
   
}