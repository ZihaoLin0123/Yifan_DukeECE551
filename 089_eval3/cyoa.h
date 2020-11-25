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
    bool visited;
    Page *pre;

public:
    Page(int num) : index(num), isWin(false), isLose(false), visited(false), pre(NULL) {}
    Page() : index(0), isWin(false), isLose(false), visited(false), pre(NULL) {}
    ~Page(){}
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
            ifstream file(fileName.str().c_str());
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
            if(vec.size() == 0){
              cerr << "blank page is not allowed" << endl;
              exit(EXIT_FAILURE);
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

    set<int> getReachableSet(){
        resetPages();
        stack<int> unvisited;
        set<int> visited;
        unvisited.push(1);
        while(unvisited.empty() == false){
            size_t index = unvisited.top();
            visited.insert(index);
            unvisited.pop();
            Page &page = findPage(index);
            vector<int> &referencedPages = page.getReferencedPages();
            vector<int>::iterator it = referencedPages.begin();
            while(it != referencedPages.end()){
                if(visited.count(*it) == 0){
                    unvisited.push(*it);
                }
                ++it;
            }
        }
        /*
        for (int i = 1; i <= totalPage; i++){
            if(visited.count(i) == 0){
                cout << "Page " << i << " is not reachable" << endl;
            }
        }
        */
        

        return visited;
    }

    void printWinPath(set<int> reachableSet){
        set<int>::iterator it = reachableSet.begin();
        vector<string> ans;
        while(it != reachableSet.end()){
           Page& p = findPage(*it);
            if(p.isWIN()){
                stringstream sstr;
                sstr << "Page " << *it << " WIN";
                ans.push_back(sstr.str());
                Page *cur = &p;
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
        
        int size = (int)ans.size();
        for (int i = (size - 1); i >= 0; --i)
        {
	          cout << ans.at(i) << endl;
        }

    }

    void findWinPath(set<int> reachableSet){
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
            resetPages();
            stack<int> unvisited;
            set<int> visited;
            unvisited.push(1);
            while(unvisited.empty() == false){
                size_t index = unvisited.top();
                visited.insert(index);
                unvisited.pop();
                Page &page = findPage(index);
                page.setVisited(true);
                vector<int> &referencedPages = page.getReferencedPages();
                vector<int>::iterator it = referencedPages.begin();
                while(it != referencedPages.end()){
                    Page &child = findPage(*it);
                    if (!child.isVisited()){
                        child.setPre(&page);
                        child.setVisited(true);
                        unvisited.push(*it);
                    }
                    ++it;
                }
            }
            printWinPath(reachableSet);
        }else{
            cout << "There is no way to win" << endl;
        }
    }

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