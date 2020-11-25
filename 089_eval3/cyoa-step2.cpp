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
    //load the story in the dir
    story.loadStory(argv[1]);
    //begin some check
    story.checkValidReference();
    story.checkIsReferenced();
    story.checkWinLosePages();
    Page curPage = story.findPage(1);  //get the page1
    while(true){
        curPage.printPage();
        //if current page is win or lose, exit
        if(curPage.isWIN() || curPage.isLOSE()){
            exit(EXIT_SUCCESS);
        }
        string str;
        cin >> str; // get a number from the user
        while(true){
            //check whether the input is correct
            if(story.isDigit(str)){ // if the input is a number
                size_t next = atoi(str.c_str());
                if(next > curPage.getReferencedPages().size() || next < 1){//if the number is out of the choices
                    cout << "That is not a valid choice, please try again" << endl;
                    cin >> str;
                }else{
                    //input is correct, go to the next page
                    curPage = story.findPage(curPage.getReferencedPages()[next - 1]);
                    break;
                }
                
            }else{
                //input is not a number
                cout << "That is not a valid choice, please try again" << endl;
                cin >> str;
            }
        }

    }
    
    exit(EXIT_SUCCESS);
   
}