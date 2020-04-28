#include "DictTree.hpp"
#include <stdexcept> //invalid_argument
#include <stdio.h>
#include <ctype.h>
#include <string.h>

HB1::DictTree::DictTree(){
  root_ = new DictNode;
  tryNum_ = 0;
  maxDepth_ = 0;
  completion_ = NULL;
}

HB1::DictTree::~DictTree(){
  delete root_;
  if (completion_ != NULL) delete[] completion_;
}

void HB1::DictTree::addWord(const char * word, int len){
  //Allocate space for entire word
  char * w = new char[len+1];

  //Copy word into our array as lowercase 
  for(int i = 0; i<len; i++){
    //Make sure digit is valid
    if(!isalnum(word[i])) throw std::invalid_argument("Non numeric digit found");

    //Add the digit and convert to lower case if needed
    w[i] = tolower(word[i]);
    
    if(w[i]=='\0') break;
  }
  w[len] = '\0';
  
  //Update max depth
  maxDepth_ = (len > maxDepth_ ? len : maxDepth_);

  //Start recursive calls
  root_->addWord(w);

  //Delete the temp word var
  delete[] w;
}
  
/* 
 Returns pointer to array with completed word. If the search is not reset, 
 an internal counter keeps track of the number of searchs and skips the previous results
*/			     
const char * HB1::DictTree::findCompletion(const char * seed, int len, bool resetSearch){
  //Delete previous completion
  if (completion_ != NULL) delete[] completion_;

  //Allocate memory for the completed word
  completion_ = new char[maxDepth_ + 1];
  memset(completion_, '\0', sizeof(char)*(maxDepth_+1));

  //Allocate space for entire word and copy seed into it
  char * s = new char[len+1];
  for(int i = 0; i<len; i++){
    //Make sure digit is valid
    if(!isalnum(seed[i])) throw std::invalid_argument("Only alpha-numeric chars allowed");

    //Add the digit and convert to lower case if needed
    s[i] = tolower(seed[i]);
    
    if(s[i]=='\0') break;
  }
  s[len] = '\0';

  //Reset search if needed
  if(resetSearch) tryNum_ = 0;

  //Start recursive calls
  if(root_->findCompletion(s, completion_, tryNum_) >= 0){
    //If tryNum is larger than the number of options
    tryNum_ = 0;
    //completion_[0] = '\0';
  }
  else{
    tryNum_++;
  }
  
  delete[] s;
  
  return completion_;
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
    int idx = c2idx(*word);
    //If branch is unused, allocate space for it
    if(branchNodes_[idx] == NULL){
      branchNodes_[idx] = new DictNode;
    }

    branchNodes_[idx]->addWord(word+1);
  }
}

int HB1::DictTree::DictNode::findCompletion(char * seed, char * dest, int skips){
  if(*seed != '\0'){//Not yet to end of seed, continue down trail
    if(branchNodes_[c2idx(*seed)] != NULL){//If there is a completion from here
      //*dest = *seed; //Save char to completion
      return branchNodes_[c2idx(*seed)]->findCompletion(seed+1, dest, skips); //Recursive call
    }
    else{//End of the road. No solution found
      return skips;
    }
  }
  else{//Out of 'find seed' mode, iterate through possible completions
    if(eow_){//If we are at the end of seed and this is an eow, we found a full completion
      skips--;
      if(skips < 0){
	return skips;
      }
    }
    for(int i=0; i<36; i++){
      if(branchNodes_[i] != NULL){//If branch has options
	//If, along this branch, we found the eow we where seeking
	if((skips=branchNodes_[i]->findCompletion(seed, dest+1, skips)) < 0){
	  *dest = idx2c(i);
	  return -1;
	}	
      }
    }
  }
  return skips;
}

int HB1::DictTree::DictNode::c2idx(const char c){
  char lcC = tolower(c);
  if(!isalnum(lcC)) throw std::invalid_argument("char must be alpha-numeric to convert to index");

  int idx;

  if(lcC - '0' >=0 && lcC - '0' < 10){
    idx = lcC - '0';
  }
  else{
    idx = lcC - 'a' + 10;
  }
  return idx;
}

char HB1::DictTree::DictNode::idx2c(const int idx){
  if(idx >= 0 && idx < 10){
    return '0' + idx;
  }
  else if(idx >= 10 && idx < 36){
    return 'a' + idx - 10;
  }
  else{
    throw std::invalid_argument("char must be alpha-numeric to convert to index");
  }
}


HB1::DictTree::DictNode::~DictNode(){
  for(int i=0; i<36; i++){
    if(branchNodes_[i] != NULL){
      delete branchNodes_[i];
    }
  }
}
