#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <stack>
using namespace std;

/*
Page class contains the information for one page.
All page related functions are implemented in this class
*/
class Page{
private:
    int index; //the page number of the page
    vector<string> pageContent;  //raw data read from the input page file
    vector<pair<string, string> > choices; // content in pair: first: next page number  second:choice text
    vector<string> text;   //content after '#'
    vector<int> nextPages; //cotains all referenced pages
    bool isWin;
    bool isLose;
    bool visited;  //used for dfs
    Page *pre;

public:
    Page(int num) : index(num), isWin(false), isLose(false), visited(false), pre(NULL) {}
    Page() : index(0), isWin(false), isLose(false), visited(false), pre(NULL) {}
    ~Page(){}
    
    //print the page
    void printPage(){
        //first print out the content after #
        vector<string>::const_iterator pageText = text.begin();
        while(pageText != text.end()){
            cout << *pageText << endl;
            ++pageText;
        }
        cout << endl;
        //if win or lose, print related content
        //else, display choices
        if(isWin){
            cout << "Congratulations! You have won. Hooray!" << endl;
        }else if(isLose){
            cout << "Sorry, you have lost. Better luck next time!" << endl;
        }else{
            cout << "What would you like to do?" << endl;
            cout << endl;
            //display choices
            vector<pair<string, string> >::const_iterator choice = choices.begin();
            int num = 1;
            while(choice != choices.end()){
                cout <<" " << num << ". " << (*choice).second << endl;
                ++num;
                ++choice;
            }
        } 
    }

    //construct the page content based on the raw content
    //fill in "choices"
    //fill in "text"
    void constructPage(){
        pageFormatCheck();  // check the format of the input file
        vector<string>::const_iterator it = pageContent.begin();
        while(it != pageContent.end()){
            if((*it).at(0) != '#'){ // content before #, add them into choices
                addChoices(*it);
            }else{
                addText(++it); // content after #, add them into text
                return;
            }
            ++it;
        }       
    }

    //add content into text
    void addText(vector<string>::const_iterator& it){
         while(it != pageContent.end()){
             text.push_back(*it);
             ++it;
         }
    }
    
    //add content into choices
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

    //check the format of the input file
    void pageFormatCheck(){
        bool hasSeparator = false;
        vector<string>::const_iterator it = pageContent.begin();
        try{
            if((*it).at(0) == '#'){  //no content before #
                cerr << "Page must have a choice!" << endl;
                exit(EXIT_FAILURE);
            }
            if((*it) == "WIN" ||(*it) == "LOSE"){ 
                ++it;
                if(it == pageContent.end() || (*it).at(0) != '#'){ //if choice is win or lose, # must be the next line
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
                if(!hasSeparator){ // must have #
                    cerr << "No #" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }catch(...){
            cerr << "Blank is not allowed before #" << endl;
            exit(EXIT_FAILURE);
        }

    }
    
    
    //check the format of one choice line
    void choiceFormatCheck(string str){
       if(str == "WIN" || str == "LOSE"){
           return;
        }
        size_t found = str.find(":");
        if (found == string::npos){
            cerr << "lacks :" << endl; // check ":"
            exit(EXIT_FAILURE);       
        } 
       for(size_t i = 0; i < str.length(); ++i){
           if(str.at(i) != ':'){
               if(isdigit(str.at(i)) == 0){
                    cerr << "Invalid page number" << endl; // validate the page number
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
    
    void setVisited(bool b){
        visited = b;
    }
    void setPre(Page *p){
        pre = p;
    }
    bool isVisited() const{
        return visited;
    }
    Page* getPre() const{
        return pre;
    }
    int getIndex() const{
        return index;
    }

};

/*
contains the content for a whole story
has many pages
*/
class Story{
private:
    map<int, Page> pages;
    int totalPage; // total page number
public:
    Story() : totalPage(0){};
    
    //load story based on the given dir
    void loadStory(string dir){
        while(true){
            stringstream fileName;
            fileName << dir << "/page" << totalPage + 1 << ".txt";//construct the file name, start from page1.txt
            ifstream file(fileName.str().c_str());
            if(file.fail()){
                if(totalPage == 0){ // page1 must exist
                    cerr << "can not open page1.txt" << endl;
                    exit(EXIT_FAILURE);
                }else{
                    return;
                }
            }
            string str;
            vector<string> vec;
            ++totalPage;
            //get the content in one page file
            while(getline(file, str)){
                vec.push_back(str);
            }
            //blank file is not allowed
            if(vec.size() == 0){
                cerr << "blank page is not allowed" << endl;
                exit(EXIT_FAILURE);
            }
            //construct a page
            Page page(totalPage);
            page.setPageContent(vec);
            page.constructPage();
            pages.insert(pair<int, Page>(totalPage, page));
            file.close();
        }        
    }
    
    //check whether the referenced pages are in the story
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
    
    //check whether all pages in the story are referenced by other page
    void checkIsReferenced(){
        set<int> referencedPagesSet; //contains pages which are referenced by other pages
        referencedPagesSet.insert(1);
        //traverse all pages in the story
        //put referenced pages into the referencedPagesSet
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
        //if there is one page not in the referencedPages set, then it is not referenced by other page
        for(int i = 1; i <= totalPage; i++){
            if(referencedPagesSet.find(i) == referencedPagesSet.end()){
                cerr << "There are pages which are not referenced by other pages, it is page" << i << endl;
                exit(EXIT_FAILURE);
            }
        }

    }
    
    //check the story must have at least one win and one lose page
    void checkWinLosePages(){
        bool hasWin = false;
        bool hasLose = false;
        //traverse all pages, and detect win and lose page
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
    
    //find one page according to the given page number
    Page & findPage(int index){
       map<int, Page>::iterator it = pages.find(index);
       if(it != pages.end()){
           return it->second;
       }else{
           cerr << "Page is not existed!" << endl;
           exit(EXIT_FAILURE);
       }
    }
    
    //check whether the given page number is in the story
    bool isInStory(int index){
        if(index >= 1 && index <= totalPage){
            return true;
        }else{
            return false;
        }
    }
    
    //check whether the given string is a number
    bool isDigit(string str){
        for(size_t i = 0; i < str.length(); ++i){
            if(isdigit(str.at(i)) == 0){
                return false;
            }
        }
        return true;   
    }
    
    //generate the reachable set, use dfs
    set<int> getReachableSet(){
        resetPages();
        stack<int> unvisited; // contains the neighbor of one page
        set<int> visited;  //reachable pages
        unvisited.push(1); //start from the page1
        //implement dfs
        while(unvisited.empty() == false){
            size_t index = unvisited.top();
            visited.insert(index);
            unvisited.pop();
            Page &page = findPage(index);
            vector<int> &referencedPages = page.getReferencedPages();
            vector<int>::iterator it = referencedPages.begin();
            //only push those not visited pages into visited
            while(it != referencedPages.end()){
                if(visited.count(*it) == 0){
                    unvisited.push(*it);
                }
                ++it;
            }
        }
        return visited;
    }
    
    //construct the win path
    //use dfs, traverse all reachable pages, and set their parent page
    void findWinPath(set<int> reachableSet){
        //if there is no win page in the reachable set, then print "can not win"
        bool canWin = false;
        set<int>::iterator it = reachableSet.begin();
        while(it != reachableSet.end()){
            if(findPage(*it).isWIN()){
                canWin = true;
                break;
            }
            ++it;
        }
        if(canWin){
            resetPages(); //set pre = NULL, visited = false for each page, prepare for the dfs
            stack<int> unvisited;
            set<int> visited;
            unvisited.push(1);
            //implement dfs
            while(unvisited.empty() == false){
                size_t index = unvisited.top();
                visited.insert(index);
                unvisited.pop();
                Page &page = findPage(index);
                page.setVisited(true);
                vector<int> &referencedPages = page.getReferencedPages();
                //traverse the neighbor page for the current page
                vector<int>::iterator it = referencedPages.begin();
                while(it != referencedPages.end()){
                    Page &child = findPage(*it);
                    if (!child.isVisited()){
                        child.setPre(&page); // set the parent page
                        child.setVisited(true);
                        unvisited.push(*it);
                    }
                    ++it;
                }
            }
            printWinPath(reachableSet); // print out the win path
        }else{
            cout << "There is no way to win" << endl;
        }
    }
    
    //print out the win path
    void printWinPath(set<int> reachableSet){
        set<int>::iterator it = reachableSet.begin();
        vector<string> ans; //win path
        //found a win page
        while(it != reachableSet.end()){
           Page& p = findPage(*it);
            if(p.isWIN()){
                //begin to get the path
                stringstream sstr;
                sstr << "Page " << *it << " WIN";
                ans.push_back(sstr.str());
                Page *cur = &p;
                //traverse the parent page of the win page
                while(cur->getPre() != NULL){
                    stringstream temp;
                    int choice = 1;
                    vector<int>::iterator it = cur->getPre()->getReferencedPages().begin();
                    while(it != cur->getPre()->getReferencedPages().end()){
                        if(*it == cur->getIndex()){
                            break;
                        }
                        ++choice;
                        ++it;
                    }
                    temp << "Page " << cur->getPre()->getIndex() << " Choice " << choice;
                    ans.push_back(temp.str());
                    cur = cur->getPre();
                }
                break;
            }
            ++it;
        }
        //traverse the win path vector inversely
        int size = (int)ans.size();
        for (int i = (size - 1); i >= 0; --i){
	          cout << ans.at(i) << endl;
        }

    }

    //set pre to NULL, visited to false for each pate
    //prepare for dfs
    void resetPages(){
        map<int, Page>::iterator it = pages.begin();
        while(it != pages.end()){
            it->second.setVisited(false);
            it->second.setPre(NULL);
            ++it;
        }
    }
    
    int getTotalPage(){
      return totalPage;
    }
    
    

};