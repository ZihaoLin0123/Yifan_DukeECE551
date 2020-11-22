#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "story.h"
using namespace std;

int main(int argc, char ** argv){
  string in_story;
  string in_cat;
  ifstream load_story;
  ifstream load_cat;
  Story story;
  CategoryArr & arr = story.getCategoryArr();
  
  if (argc == 3){
    
      load_story.open(argv[2]);
      load_cat.open(argv[1]);
      if(load_story.fail()|load_cat.fail()){
        cerr << "cannot open file" << endl;
        return EXIT_FAILURE;
      }
      while (!load_story.eof()){
        getline(load_story,in_story);
        story.addintoRawData(in_story);
      }
      load_story.close();
      
      while (!load_cat.eof()){
        getline(load_cat,in_cat);
        arr.addIntoCategory(in_cat);
      }
      load_cat.close();
      
      story.printStory();
      exit(EXIT_SUCCESS);
    }
  else{
        cerr << "wrong format of input" << endl;
        exit(EXIT_FAILURE);
  }
 
}