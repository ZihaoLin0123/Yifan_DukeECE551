#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;
//
class Page{
private:
    int index;
    vector<string> pageContent;  //read from the file
    vector<pair<string, string> > choices;
    vector<string> text;   //content after '#'
    vector<int> nextPages;
    bool isWin;
    bool isLose;

public:
    Page(int num) :index(num), isWin(false), isLose(false) {}
    ~Page(){}

    void printPage(){
        vector<string>::const_iterator pageText = text.begin();
        while(pageText != text.end()){
            cout << *pageText << endl;
            ++pageText;
        }
        cout << endl;
        if(isWin){
            cout << "Congratulations! You have won. Hooray!" << endl;
        }else if(isLose){
            cout << "Sorry, you have lost. Better luck next time!" << endl;
        }else{
            cout << "What would you like to do?" << endl;
            cout << endl;
            vector<pair<string, string> >::const_iterator choice = choices.begin();
            int num = 1;
            while(choice != choices.end()){
                cout <<" " << num << ". " << (*choice).second << endl;
                ++num;
                ++choice;
            }

        }
        
    }

    void constructPage(){
        pageFormatCheck();
        vector<string>::const_iterator it = pageContent.begin();
        while(it != pageContent.end()){
            if((*it).at(0) != '#'){
                addChoices(*it);
            }else{
                addText(++it);
                return;
            }

            ++it;
        }
                
        
    }

    void addText(vector<string>::const_iterator& it){
         while(it != pageContent.end()){
             text.push_back(*it);
             ++it;
         }
    }

    void addChoices(string str){
        if(str == "WIN"){
            isWin = true;
        }else if(str == "LOSE"){
            isLose = true;
        }else{
            string pageNum;
            string choice;
            choiceFormatCheck(str);
            size_t pos = str.find_first_of(':');
            pageNum = str.substr(0, pos);
            choice = str.substr(pos + 1);
            pair<string, string> item(pageNum, choice);
            choices.push_back(item);
            nextPages.push_back(atoi(pageNum.c_str()));
        }
    }

    void pageFormatCheck(){
        bool hasSeparator = false;
        vector<string>::const_iterator it = pageContent.begin();
        try{
            if((*it).at(0) == '#'){
                cerr << "Page must have a choice!" << endl;
                exit(EXIT_FAILURE);
            }
            if((*it) == "WIN" ||(*it) == "LOSE"){ 
                ++it;
                if(it == pageContent.end() || (*it).at(0) != '#'){
                    cerr << "Invalid content after Win or Lose choice" << endl;
                    exit(EXIT_FAILURE);
                }
            }else{
                while(it != pageContent.end()){
                    if ((*it).length() == 0){
                        cerr << "Blank choice is not allowed!" << endl;
                        exit(EXIT_FAILURE);
                    }
                    if((*it).at(0) == '#'){
                        hasSeparator = true;
                        return;
                    }
                    choiceFormatCheck(*it);
                    ++it;
                }
                if(!hasSeparator){
                    cerr << "No #" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }catch(...){
            cerr << "Blank is not allowed before #" << endl;
            exit(EXIT_FAILURE);
        }

    }

    void choiceFormatCheck(string str){
       if(str == "WIN" || str == "LOSE"){
           return;
        }
       for(size_t i = 0; i < str.length(); ++i){
           if(str.at(i) != ':'){
               if(isdigit(str.at(i)) == 0){
                    cerr << "Invalid page number" << endl;
                    exit(EXIT_FAILURE);
               }
           }else{
               if(i == 0){
                    cerr << "Invalid page number" << endl;
                    exit(EXIT_FAILURE);
               }
               return;  //':' appears, format is valid
           }
       }
   
   }

    void setPageContent(vector<string> vec){
       pageContent = vec;
   }

    vector<int>& getReferencedPages(){
        return nextPages;
    }

    bool isWIN(){
        return isWin;
    }
    bool isLOSE(){
        return isLose;
    }

};

class Story{
private:
    map<int, Page> pages;
    int totalPage;
public:
    Story() : totalPage(0){};
    void loadStory(string dir){
        while(true){
            stringstream fileName;
            fileName << dir << "/page" << totalPage + 1 << ".txt";
            cout << "path" << fileName.str() << endl;
            ifstream file(fileName.str().c_str());
            //file.open(fileName.str().c_str());
            
            if(file.fail()){
                if(totalPage == 0){
                    cerr << "can not open page1.txt" << endl;
                    exit(EXIT_FAILURE);
                }else{
                    return;
                }
            }
            string str;
            vector<string> vec;
            ++totalPage;
            while(getline(file, str)){
                vec.push_back(str);
            }
            Page page(totalPage);
            page.setPageContent(vec);
            page.constructPage();
            pages.insert(pair<int, Page>(totalPage, page));
            file.close();
        }        
    }

    void checkValidReference(){
        map<int, Page>::iterator it = pages.begin();
        while(it != pages.end()){
            vector<int> referencedPages = (it->second).getReferencedPages();
            vector<int>::iterator nextPage = referencedPages.begin();
            while(nextPage != referencedPages.end()){
                if(pages.end() == pages.find(*nextPage)){
                    cerr << "Invalid referenced pages:" << it->first << "refers to" << *nextPage << endl;
                    exit(EXIT_FAILURE);
                }
                ++nextPage;
            }
            ++it;
        }
    }

    void checkIsReferenced(){
        set<int> referencedPagesSet;
        referencedPagesSet.insert(1);
        map<int, Page>::iterator it = pages.begin();
        while(it != pages.end()){
            vector<int> referencedPages = (it->second).getReferencedPages();
            vector<int>::iterator nextPage = referencedPages.begin();
            while(nextPage != referencedPages.end()){
                referencedPagesSet.insert(*nextPage);
                ++nextPage;
            }
            ++it;
        }
        for(int i = 1; i <= totalPage; i++){
            if(referencedPagesSet.find(i) == referencedPagesSet.end()){
                cerr << "There are pages which are not referenced by other pages, it is page" << i << endl;
                exit(EXIT_FAILURE);
            }
        }

    }

    void checkWinLosePages(){
        bool hasWin = false;
        bool hasLose = false;
        map<int, Page>::iterator it = pages.begin();
        while(it != pages.end()){
            if(it->second.isWIN()){
                hasWin = true;
            }else if(it->second.isLOSE()){
                hasLose = true;
            }
            ++it;
        }
        if(!(hasWin && hasLose)){
            cerr << "Lost win or lose page!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    Page & findPage(int index){
       map<int, Page>::iterator it = pages.find(index);
       if(it != pages.end()){
           return it->second;
       }else{
           cerr << "Page is not existed!" << endl;
           exit(EXIT_FAILURE);
       }
    }

    bool isInStory(int index){
        if(index >= 1 && index <= totalPage){
            return true;
        }else{
            return false;
        }
    }

    bool isDigit(string str){
        for(size_t i = 0; i < str.length(); ++i){
            if(isdigit(str.at(i)) == 0){
                return false;
            }
        }
        return true;   
    }

};





int main(int argc, char ** argv){
    Story story;
    story.loadStory(argv[1]);
    story.checkValidReference();
    story.checkIsReferenced();
    story.checkWinLosePages();
    Page &curPage = story.findPage(1);
    while(true){
        curPage.printPage();
        if(curPage.isWIN() || curPage.isLOSE()){
            exit(EXIT_SUCCESS);
        }
        string str;
        cout << "Please make the choice!" << endl;
        cin >> str;
        while(true){
            if(story.isDigit(str)){
                size_t next = atoi(str.c_str());
                if(next > curPage.getReferencedPages().size()){
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
   
}