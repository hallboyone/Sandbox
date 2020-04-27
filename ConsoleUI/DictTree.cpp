#include "DictTree.hpp"
#include <stdexcept> //invalid_argument
#include <stdio.h>

HB1::DictTree::DictTree(){
  root_ = new DictNode;
  tryNum_ = 0;
  maxDepth_ = 0;
}

HB1::DictTree::~DictTree(){
  delete root_;
}

void HB1::DictTree::addWord(const char * word, int len){
  //Allocate space for entire word
  char * w = new char[len+1];

  //Copy word into our array
  for(int i = 0; i<len; i++){
    w[i] = word[i];
  }
  w[len] = '\0';
  
  //Update max depth
  maxDepth_ = (len > maxDepth_ ? len : maxDepth_);

  //Start recursive calls
  root_->addWord(w);
  delete[] w;
}
  
/* 
 Returns pointer to array with completed word. If the search is not reset, 
 an internal counter keeps track of the number of searchs and skips the previous results
*/			     
const char * HB1::DictTree::findCompletion(const char * seed, int len, bool resetSearch){
  //Allocate space for entire word
  char * w = new char[len+1];
  char * completion = new char[maxDepth_ + 1];
  
  //Copy word into our array
  for(int i = 0; i<len; i++){
    w[i] = word[i];
  }

  w[len] = '\0';
  completion[maxDepth_] = '\0';

  
}
 

HB1::DictTree::DictNode::DictNode(){
  eow_ = false;
  for(int i=0; i<36; i++){
    branchNodes_[i] = NULL;
  }
}

void HB1::DictTree::DictNode::addWord(char * word){
  if(*word == '\0'){
    eow_ = true;
    return;
  }
  else{
    int idx = 0;
    if(*word - 'A' >= 0 && *word - 'A' < 26){//Uppercase
      idx = *word - 'A';
    }
    else if(*word - 'a' >= 0 && *word - 'a' < 26){//Lowercase
      idx = *word - 'a';
    }
    else if(*word - '0' >= 0 && *word - '0' < 9){//Digit
      idx = *word - '0' + 26;
    }
    else{
      //Throw exception
      throw std::invalid_argument("Non numeric digit found");
    }

    //If branch is unused, allocate space for it
    if(branchNodes_[idx] == NULL){
      branchNodes_[idx] = new DictNode;
    }

    branchNodes_[idx]->addWord(word+1);
  }
}

HB1::DictTree::DictNode::~DictNode(){
  for(int i=0; i<36; i++){
    if(branchNodes_[i] != NULL){
      delete branchNodes_[i];
    }
  }
}
