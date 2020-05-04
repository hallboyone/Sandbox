#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <string>
#include <iostream>
#include <limits>//numeric_limits

//Check if char is valid within block
bool validBlockChar(const char & c){
  if(isalpha(c) || c=='=' || c==';' || c=='"') return true;
  else return false;
}

//Finds the first '{' not in a comment
int move2BlockStart(std::ifstream & f){
  char next_char;

  //Move to start of block, skipping any comments or extra chars
  while(f.get(next_char)){
    if(next_char == '{'){
      break;
    }
    else if(next_char == '/' && f.peek()=='/'){
      //Move to end of comment
      f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  //If no valid open brace was found before EOF
  if(f.eof()) return 0;
  return 1;
}

//Extracts from the ifstream into block until the closing brace
int extractNextBlock(std::ifstream & f, std::string & block){
  if(!move2BlockStart(f)){
    return 0;
  }
  
  char next_char;
  bool in_quotes = false;
  
  block.clear();
  while(f.get(next_char)){
    if(next_char == '"'){
      in_quotes = !in_quotes;
    }

    if(!in_quotes){
      if(next_char == '}'){
	break;
      }
      else if(next_char == '/' && f.peek()=='/'){
	//Move to end of comment
	f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else if(validBlockChar(next_char)){ 
	block.append(&next_char);
      }
    }
    else{
      block.append(&next_char);
    }
  }
  //If no valid open brace was found before EOF
  if(f.eof()) return 0;
  return 1;
}

//Looks in a string for the key, reads the value after it up to the deliminator
int readKeyValue(std::string & s, const char * key, size_t len, std::string & val, char delim = ';'){
  
  size_t start_of_key = s.find(key);
  if(start_of_key == std::string::npos){
    return 0;
  }
  
  size_t start_of_val = start_of_key + len;
  size_t end_of_val = s.find_first_of(delim, start_of_val);
  if(end_of_val == std::string::npos){
    return 0;
  }
  
  val = s.substr(start_of_val, end_of_val-start_of_val);
  return 1;
}

//From a template string, build a flag
int Flag(std::string & s){
  std::string name;
  std::string desc;
  std::string sh;
  std::string para;

  //Get name
  if(!readKeyValue(s, "name=", 5, name)) {
    return 0;
  }
  std::cout<<"Name: "<<name<<std::endl;
  
  //Get description
  if(!readKeyValue(s, "desc=\"", 6, desc, '"')) {//with quotes
    if(!readKeyValue(s, "desc=", 5, desc)) {//without quotes
      return 0;
    }
  }
  std::cout<<"Desc: "<<desc<<std::endl;
  
  //Get sh (opt)
  if(readKeyValue(s, "sh=", 3, sh)){
    std::cout<<"Shorthand: "<<sh<<std::endl;
  }
  //Get para type (opt)
  if(readKeyValue(s, "para=", 5, para)){
    std::cout<<"Para Type: "<<para<<std::endl;
  }
  return 1;
}

void parseFlagTemplates(){
  // Open the file
  std::ifstream f ("flags.tmpl");
  std::string nextBlock;

  if(f.is_open()){
    //Extract the next block without any extra chars
    while(extractNextBlock(f, nextBlock)){
      //Build the flag from the tempate string
      Flag(nextBlock);
    }
    f.close();
  }
  else{
    sstd::err<<"Could not open file\n";
  }
}  

int main(int argc, char * argv[]){
  
  parseFlagTemplates();
  return 1;
}
