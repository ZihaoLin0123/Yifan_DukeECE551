#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include "cyoa.h"
using namespace std;

int main(int argc, char ** argv){
    ifstream file;
    Page page;
    if(argc < 2){
      cerr << "please enter a valid page" << endl;
      exit(EXIT_FAILURE);
    }
    file.open(argv[1]);
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
    if(vec.size() == 0){
        cerr << "blank page is not allowed" << endl;
        exit(EXIT_FAILURE);
    }
    page.setPageContent(vec);
    page.constructPage();
    page.printPage();
    exit(EXIT_SUCCESS);
}

