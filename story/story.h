Yifan Shao   ys319
Yizheng Lin yl727
Xiangzhou Luo xl351

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

//Category contains the content for one specific category
class Category{
private:
  std::string name;
  std::vector<std::string> words;
public:
  Category():name(std::string()),words(std::vector<std::string>()){}
  std::string getName() const{
	  return name;
  }
  size_t getWordNum() const{
	  return words.size();
  }
  void extendKey (const std::string key) {
	  name.assign(key);
  
  }
  void extendWord(const std::string word){
	  words.push_back(word);
  
  }
  //look up for a word in the category
  bool lookupWord(const std::string word) const{
	  for( size_t i = 0 ; i < words.size(); i++){
		  if(words[i] == word){
			  return true;
		  }
          }
	  return false;
  }
  //print out the category
  void printcat() const{
	  std::cout<<name<<":"<<std::endl;
	  for (size_t i = 0; i < words.size(); i++){
		  std::cout << words[i]<< " ";
	  }
  }
  //generate a random index to deliver a word from the category
  string getWord(){
      size_t index = rand() % (words.size());
      return words[index];
  }
  ~Category(){};
};

//contains some categories
class CategoryArr{
private:
  std::vector<Category> arr;
public:
    CategoryArr(){}

    //add content intp the category
    void addIntoCategory(std::string line){
        bool update = false;
        std::string key;
        std::string word;
        size_t colon = line.find(":");
        if (line.length() != 0 && colon == string::npos){
        std::cout << "No colon found!~" << line << std::endl;
        exit(EXIT_FAILURE);
    }
    key.assign(line, 0, colon);
    word.assign(line, colon + 1, line.length()- colon - 1); 
    for (size_t i = 0; i < arr.size(); i++){
        if(arr[i].getName() == key){
            if(!arr[i].lookupWord(word)){
                arr[i].extendWord(word);
            }
            update = true;
        }
    }
    if(!update){
        Category newcat;
        newcat.extendKey(key);
        newcat.extendWord(word);
        arr.push_back(newcat);
    }
  }

  //print the arr
  void printarr() const{
	  for (size_t i = 0; i < arr.size(); i ++){
		  arr[i].printcat();
		  std::cout << "\n";
	  }
  }

    //find a word from the dict
  string findWord(string str){
      vector<Category>::iterator it = arr.begin();
        while(it != arr.end()){
            if (it->getName() == str){ 
                return it->getWord();
            }
        ++it;
      }
      // if no valid word is found, exit with failure
      cerr << "No such word  " << endl;
      exit(EXIT_FAILURE);
  }
};

//the words which have been used
class UsedWords{
    private:
    int sz;
    std::vector<std::string> words;
    public:
    UsedWords():sz(0){}

    //get a used word based on the given index
    std::string getword(int index) const{
       
        if(index>= 1 && (sz - index) >= 0 ){
          
            return words[sz-index];
        }
        else {
            //if the index is not valid, return with failure
            cerr << index<< "index is not valid, size is" << sz << endl;
            exit(EXIT_FAILURE);
        }

    }

    //add a word into the used words
    void addWord(const std::string word){
        words.push_back(word);
        ++sz;
    }
};


//contains the necessary information for a story
class Story{
private:
    CategoryArr catArr;
    UsedWords usedWords;
    vector<string> rawData;
    vector<string> constructedData;

public:
    //add the raw data from the input file line by line
    void addintoRawData(string str){
        rawData.push_back(str);
    }

    CategoryArr& getCategoryArr(){
        return catArr;
    }
    UsedWords & getUsedWords(){
        return usedWords;
    }

    //print the constructed story
    void printStory(){
        vector<string>::iterator it = rawData.begin();
        while(it != rawData.end()){
            cout << constructLine(*it) << endl;
            ++it;
        }
    }
    
    //construct a line for the story based on the raw data
    string constructLine(string line){
        int num = count(line.begin(),line.end(),'_'); //format check
        if(num % 2 != 0){
            cerr << "Invalid line" << endl;
            exit(EXIT_FAILURE);
        }
        string ans;
        string replaceWord;
        string word;
        size_t cur;
        while(line.find('_') != string::npos){
            cur = line.find('_');
            ans.append(line.substr(0, cur));
            line = line.substr(cur + 1);
            cur = line.find('_');
            word = line.substr(0, cur);
            if(isDigit(word)){ //if the word is a number, then find the answer from the used words
                size_t index = atoi(word.c_str());
                replaceWord = usedWords.getword(index);
               
            }else{
                //else, look from the categoryArr
                replaceWord = catArr.findWord(word);
            }
            usedWords.addWord(replaceWord); //add usedWords
            ans.append(replaceWord); //append the found replaced word
            if(cur == (line.length() - 1)){
                return ans;
            }
            line =  line.substr(cur + 1);
        }
        //append the remaining content into the answer
        ans.append(line);
        return ans;  
    }

    //judge whether the input string is a valid positive integer
    bool isDigit(string str){
        for (size_t i = 0; i < str.length(); i++){
            if(isdigit(str.at(i)) == 0){
                return false;
            }
        }
        return true;
    }
};

