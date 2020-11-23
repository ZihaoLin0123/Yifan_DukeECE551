#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "readFreq.h"
#include "node.h"
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){
  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);
  
  ifstream f(inFile);
  if(f.fail()){
    cerr << "can not open file" << endl;
    exit(EXIT_FAILURE);
  }
  char c;
  map<unsigned, BitString>::const_iterator it;
  while(f.get(c)){
    it = theMap.find((unsigned char)c);
    if(it != theMap.end()){
      bfw.writeBitString(it->second);
    }else{
      cerr << "unseen character" << endl;
      exit(EXIT_FAILURE);
    }
  }
  
  f.close();
  it = theMap.find(256);
  assert(it != theMap.end());
  bfw.writeBitString(it->second);
 
  //WRITE YOUR CODE HERE!
  //open the input file for reading

  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done. 
  //hint 2: you can look at the main from the previous tester for 90% of this
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * tree = buildTree (counts);
  delete[] counts;
  std::map<unsigned,BitString> theMap;
  BitString empty;
  tree->buildMap(empty, theMap);
   writeCompressedOutput(argv[1], argv[2], theMap);
  //printTable(theMap);
  delete tree;
  return EXIT_SUCCESS;
}
