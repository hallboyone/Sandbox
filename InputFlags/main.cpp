#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <string>
#include <iostream>
#include <limits>//numeric_limits
#include <stdexcept>

//Check if char is valid within block
bool validBlockChar(const char & c){
  if(isalnum(c) || c=='=' || c==';' || c=='"' || c=='_') return true;
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
int readKeyValue(const std::string & s, const char * key, size_t len, std::string & val, char delim = ';'){
  
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

//Makes sure the name of input flag is valid
// 1) Only alpha-numeric and _ chars
// 2) Starts and ends with alpha char
std::string readName(const std::string & root_string){
  std::string name;
  //Read name
  if(!readKeyValue(root_string, "name=", 5, name)) {
    throw std::invalid_argument("Could not find any name key");
  }
  //Make sure only valid chars are used
  if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyz_0123456789") != std::string::npos){
    throw std::invalid_argument("Name not valid");
  }
  //Make sure the name begins and ends with alpha
  if(!isalpha(name[0]) || !isalpha(name.back())){
    throw std::invalid_argument("Name not valid. Must start and and with alpha char");
  }
  return name;
}

std::string readDesc(const std::string & root_string){
  std::string desc;
  //Read desc
  if(!readKeyValue(root_string, "desc=\"", 6, desc)) {//With quotes
    if(!readKeyValue(root_string, "desc=", 5, desc)) {//without quotes
    throw std::invalid_argument("No description found for flag");
    }
  }
  return desc;
}

//Makes sure the sh of input flag is a single alpha char
char readSH(const std::string & root_string){
  std::string sh;
  if(readKeyValue(root_string, "sh=", 3, sh)){
    if(sh.size() != 1 || !isalpha(sh[0])){
      return '\0';
    }
    return sh[0];
  }
  else{
    return '\0';
  }
}

enum DataType {NONE=0, INT, DOUBLE, CHAR, STRING};
typedef struct Flag_{
  std::string name;
  std::string desc;
  char sh;
  DataType para_t;
  std::string data;
} Flag;

DataType readPara(const std::string & root_string){
  std::string para;
  if(readKeyValue(root_string, "para=", 5, para)){
    for(size_t i = 0; i<para.size(); i++){
      para[i] = tolower(para[i]);
    }
    if(para == "int") return INT;
    else if (para == "double") return DOUBLE;
    else if (para == "char") return CHAR;
    else if (para == "string") return STRING;
    else return NONE;
  }
  else return NONE;
}
  
//From a template string, build a flag
Flag BuildFlag(std::string & s){
  std::string name;
  std::string desc;

  Flag flag = {readName(s), readDesc(s), readSH(s), readPara(s)};
  return flag;
}

void printFlag(const Flag & flag){
  std::cout<<"Name           : "<<flag.name<<std::endl;

  std::cout<<"Description    : "<<flag.desc<<std::endl;

  std::cout<<"Shorthand      : ";
  if(flag.sh != '\0') std::cout<<flag.sh<<std::endl;
  else std::cout<<"None\n";
  
  std::cout<<"Parameter type : ";
  switch(flag.para_t){
  case INT:
    std::cout<<"Int\n";
    break;
  case DOUBLE:
    std::cout<<"Double\n";
    break;
  case CHAR:
    std::cout<<"Char\n";
    break;
  case STRING:
    std::cout<<"String\n";
    break;
  default:
    std::cout<<"None\n";
  }   
}

void parseFlagTemplates(){
  // Open the file
  std::ifstream f ("flags.tmpl");
  std::string nextBlock;
  Flag flag;
  if(f.is_open()){
    //Extract the next block without any extra chars
    while(extractNextBlock(f, nextBlock)){
      //Build the flag from the tempate string
      flag = BuildFlag(nextBlock);
      printFlag(flag);
    }
    f.close();
  }
  else{
    std::cerr<<"Could not open file\n";
  }
}  

int main(int argc, char * argv[]){
  
  parseFlagTemplates();
  return 1;
}
