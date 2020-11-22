#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Page{
private:
    vector<string> pageContent;  //read from the file
    vector<pair<string, string> > choices;
    vector<string> text;   //content after '#'
    bool isWin;
    bool isLose;

public:
    string test;
    Page() : isWin(false), isLose(false) {}
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
};



int main(int argc, char ** argv){
    ifstream file;
    Page page;
    //const char *fileName = "story1/page1.txt";
    string fileName("story1/page1.txt");
    file.open(fileName.c_str());
    //ifstream file(name, ios::in);
    string str;
    vector<string> vec;
    if(file.fail()){
        cerr << "fail to open file" << endl;
        exit(EXIT_FAILURE);
    }
    while(getline(file, str)){
        vec.push_back(str);
    }
    file.close();

    page.setPageContent(vec);
    page.constructPage();
    page.printPage();
    return 0;
}

// 47:Try to sneak past the sleeping dragon 47:Try to sneak past the sleeping d